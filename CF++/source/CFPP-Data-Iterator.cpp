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
 * @file        CFPP-Data-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Iterator class for CF::Data
 */

#include <CF++.hpp>

namespace CF
{
    Data::Iterator::Iterator( void ):
        _cfObject( nullptr ),
        _length( 0 ),
        _pos( 0 ),
        _bp( nullptr )
    {}
    
    Data::Iterator::Iterator( const Iterator & value ):
        _cfObject( value._cfObject ),
        _length( value._length ),
        _pos( value._pos ),
        _bp( value._bp )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
        }
    }
    
    Data::Iterator::Iterator( CFDataRef data, CFIndex length, CFIndex pos ):
        _cfObject( data ),
        _length( length ),
        _pos( pos ),
        _bp( nullptr )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
            
            this->_bp = CFDataGetBytePtr( this->_cfObject );
        }
    }
    
    Data::Iterator::Iterator( Iterator && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
        this->_length   = value._length;
        value._length   = 0;
        this->_pos      = value._pos;
        value._pos      = 0;
        this->_bp       = value._bp;
        value._bp       = nullptr;
    }
    
    Data::Iterator::~Iterator( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
        }
    }
    
    Data::Iterator & Data::Iterator::operator = ( Iterator value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Data::Iterator & Data::Iterator::operator ++( void )
    {
        this->_pos++;
        
        return *( this );
    }
    
    Data::Iterator Data::Iterator::operator ++( int )
    {
        Iterator it( *( this ) );
        
        operator++();
        
        return it;
    }
    
    Data::Iterator & Data::Iterator::operator --( void )
    {
        this->_pos--;
        
        return *( this );
    }
    
    Data::Iterator Data::Iterator::operator --( int )
    {
        Iterator it( *( this ) );
        
        operator--();
        
        return it;
    }
    
    Data::Iterator & Data::Iterator::operator += ( CFIndex value )
    {
        this->_pos += value;
        
        return *( this );
    }
    
    Data::Iterator & Data::Iterator::operator -= ( CFIndex value )
    {
        this->_pos -= value;
        
        return *( this );
    }
    
    Data::Iterator Data::Iterator::operator + ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i += value;
    }
    
    Data::Iterator Data::Iterator::operator - ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i -= value;
    }
    
    bool Data::Iterator::operator == ( const Iterator & value ) const
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
    
    bool Data::Iterator::operator != ( const Iterator & value ) const
    {
        return !( *( this ) == value );
    }
    
    Data::Byte Data::Iterator::operator * ( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return 0;
        }
        
        if( this->_bp == nullptr )
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
        
        return this->_bp[ this->_pos ];
    }
    
    Data::Iterator::operator Data::Byte () const
    {
        return operator*();
    }
    
    void swap( Data::Iterator & v1, Data::Iterator & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
        swap( v1._length,   v2._length );
        swap( v1._pos,      v2._pos );
        swap( v1._bp,       v2._bp );
    }
}
