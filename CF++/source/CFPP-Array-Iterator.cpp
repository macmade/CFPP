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
 * @file        CFPP-Array-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Iterator class for CF::Array
 */

#include <CF++.hpp>

namespace CF
{    
    Array::Iterator::Iterator( void ):
        _cfObject( nullptr ),
        _count( 0 ),
        _pos( 0 )
    {}
    
    Array::Iterator::Iterator( const Iterator & value ):
        _cfObject( value._cfObject ),
        _count( value._count ),
        _pos( value._pos )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
        }
    }
    
    Array::Iterator::Iterator( CFArrayRef array, CFIndex count, CFIndex pos ):
        _cfObject( array ),
        _count( count ),
        _pos( pos )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
        }
    }
    
    Array::Iterator::Iterator( Iterator && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
        this->_count    = value._count;
        value._count    = 0;
        this->_pos      = value._pos;
        value._pos      = 0;
    }
    
    Array::Iterator::~Iterator( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
        }
    }
    
    Array::Iterator & Array::Iterator::operator = ( Iterator value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Array::Iterator & Array::Iterator::operator ++( void )
    {
        this->_pos++;
        
        return *( this );
    }
    
    Array::Iterator Array::Iterator::operator ++( int )
    {
        Iterator it( *( this ) );
        
        operator++();
        
        return it;
    }
    
    Array::Iterator & Array::Iterator::operator --( void )
    {
        this->_pos--;
        
        return *( this );
    }
    
    Array::Iterator Array::Iterator::operator --( int )
    {
        Iterator it( *( this ) );
        
        operator--();
        
        return it;
    }
    
    Array::Iterator & Array::Iterator::operator += ( CFIndex value )
    {
        this->_pos += value;
        
        return *( this );
    }
    
    Array::Iterator & Array::Iterator::operator -= ( CFIndex value )
    {
        this->_pos -= value;
        
        return *( this );
    }
    
    Array::Iterator Array::Iterator::operator + ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i += value;
    }
    
    Array::Iterator Array::Iterator::operator - ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i -= value;
    }
    
    bool Array::Iterator::operator == ( const Iterator & value ) const
    {
        if( this->_cfObject != value._cfObject )
        {
            return false;
        }
        
        if( this->_count != value._count )
        {
            return false;
        }
        
        if( this->_pos != value._pos )
        {
            return false;
        }
        
        return true;
    }
    
    bool Array::Iterator::operator != ( const Iterator & value ) const
    {
        return !( *( this ) == value );
    }
    
    CFTypeRef Array::Iterator::operator * ( void ) const
    {
        return this->GetCFObject();
    }
    
    Array::Iterator::operator CFTypeRef () const
    {
        return this->GetCFObject();
    }
    
    CFTypeID Array::Iterator::GetTypeID( void ) const
    {
        CFTypeRef o;
        
        o = this->GetCFObject();
        
        if( o != nullptr )
        {
            return CFGetTypeID( o );
        }
        
        return 0;
    }
    
    CFTypeRef Array::Iterator::GetCFObject( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        if( this->_count == 0 )
        {
            return nullptr;
        }
        
        if( this->_pos >= this->_count )
        {
            return nullptr;
        }
        
        if( this->_pos < 0 )
        {
            return nullptr;
        }
        
        return CFArrayGetValueAtIndex( this->_cfObject, this->_pos );
    }
    
    void swap( Array::Iterator & v1, Array::Iterator & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
        swap( v1._count,    v2._count );
        swap( v1._pos,      v2._pos );
    }
}
