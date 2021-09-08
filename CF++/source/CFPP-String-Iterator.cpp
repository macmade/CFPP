/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        CFPP-String-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Iterator class for CF::String
 */

#include <CF++.hpp>

namespace CF
{
    String::Iterator::Iterator( void ):
        _cfObject( nullptr ),
        _length( 0 ),
        _pos( 0 ),
        _cp( nullptr )
    {}
    
    String::Iterator::Iterator( const Iterator & value ):
        _cfObject( value._cfObject ),
        _length( value._length ),
        _pos( value._pos ),
        _cp( value._cp )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
        }
    }
    
    String::Iterator::Iterator( CFStringRef string, CFStringEncoding encoding, CFIndex length, CFIndex pos ):
        _cfObject( string ),
        _length( length ),
        _pos( pos ),
        _cp( nullptr )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
            
            {
                std::size_t size;
                
                size      = static_cast< std::size_t >( CFStringGetMaximumSizeForEncoding( CFStringGetLength( this->_cfObject ), encoding ) );
                this->_cp = std::shared_ptr< char >( new char[ size + 1 ] );
                
                if( this->_cp != nullptr )
                {
                    memset( this->_cp.get(), 0, size + 1 );
                    CFStringGetCString( this->_cfObject, this->_cp.get(), static_cast< CFIndex >( length + 1 ), encoding );
                }
            }
        }
    }
    
    String::Iterator::Iterator( Iterator && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
        this->_length   = value._length;
        value._length   = 0;
        this->_pos      = value._pos;
        value._pos      = 0;
        this->_cp       = value._cp;
        value._cp       = nullptr;
    }
    
    String::Iterator::~Iterator( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
        }
    }
    
    String::Iterator & String::Iterator::operator = ( Iterator value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    String::Iterator & String::Iterator::operator ++( void )
    {
        this->_pos++;
        
        return *( this );
    }
    
    String::Iterator String::Iterator::operator ++( int )
    {
        Iterator it( *( this ) );
        
        operator++();
        
        return it;
    }
    
    String::Iterator & String::Iterator::operator --( void )
    {
        this->_pos--;
        
        return *( this );
    }
    
    String::Iterator String::Iterator::operator --( int )
    {
        Iterator it( *( this ) );
        
        operator--();
        
        return it;
    }
    
    String::Iterator & String::Iterator::operator += ( CFIndex value )
    {
        this->_pos += value;
        
        return *( this );
    }
    
    String::Iterator & String::Iterator::operator -= ( CFIndex value )
    {
        this->_pos -= value;
        
        return *( this );
    }
    
    String::Iterator String::Iterator::operator + ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i += value;
    }
    
    String::Iterator String::Iterator::operator - ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i -= value;
    }
    
    bool String::Iterator::operator == ( const Iterator & value ) const
    {
        if( this->_cfObject != value._cfObject )
        {
            return false;
        }
        
        if( this->_length != value._length )
        {
            return false;
        }
        
        if( this->_pos != value._pos )
        {
            return false;
        }
        
        return true;
    }
    
    bool String::Iterator::operator != ( const Iterator & value ) const
    {
        return !( *( this ) == value );
    }
    
    char String::Iterator::operator * ( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return 0;
        }
        
        if( this->_cp == nullptr )
        {
            return 0;
        }
        
        if( this->_pos < 0 )
        {
            return 0;
        }
        
        if( this->_pos >= this->_length )
        {
            return 0;
        }
        
        return this->_cp.get()[ this->_pos ];
    }
    
    String::Iterator::operator char () const
    {
        return operator*();
    }
    
    void swap( String::Iterator & v1, String::Iterator & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
        swap( v1._length,   v2._length );
        swap( v1._pos,      v2._pos );
        swap( v1._cp,       v2._cp );
    }
}
