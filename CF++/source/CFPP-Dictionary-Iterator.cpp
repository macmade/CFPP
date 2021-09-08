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
 * @file        CFPP-Dictionary-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Iterator class for CF::Dictionary
 */

#include <CF++.hpp>

namespace CF
{
    Dictionary::Iterator::Iterator( void ):
        _cfObject( nullptr ),
        _keys( static_cast< CFArrayRef >( nullptr ) ),
        _count( 0 ),
        _pos( 0 )
    {}
    
    Dictionary::Iterator::Iterator( const Iterator & value ):
        _cfObject( value._cfObject ),
        _keys( value._keys ),
        _count( value._count ),
        _pos( value._pos )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
        }
    }
    
    Dictionary::Iterator::Iterator( CFDictionaryRef dictionary, CFIndex count, CFIndex pos ):
        _cfObject( dictionary ),
        _count( count ),
        _pos( pos )
    {
        CFTypeRef * cfKeys;
        CFIndex     i;
        
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFRetain( this->_cfObject );
        
        if( count == 0 )
        {
            return;
        }
        
        cfKeys = new CFTypeRef[ static_cast< size_t >( count ) ];
        
        if( cfKeys == nullptr )
        {
            return;
        }
        
        memset( cfKeys, 0, static_cast< size_t >( count ) );
        
        CFDictionaryGetKeysAndValues( this->_cfObject, reinterpret_cast< const void ** >( cfKeys ), nullptr );
        
        for( i = 0; i < count; i++ )
        {
            _keys << cfKeys[ i ];
        }
        
        delete [] cfKeys;
    }
    
    Dictionary::Iterator::Iterator( Iterator && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
        this->_count    = value._count;
        value._count    = 0;
        this->_pos      = value._pos;
        value._pos      = 0;
        
        swap( this->_keys, value._keys );
    }
    
    Dictionary::Iterator::~Iterator( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
        }
    }
    
    Dictionary::Iterator & Dictionary::Iterator::operator = ( Iterator value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Dictionary::Iterator & Dictionary::Iterator::operator ++( void )
    {
        this->_pos++;
        
        return *( this );
    }
    
    Dictionary::Iterator Dictionary::Iterator::operator ++( int )
    {
        Iterator it( *( this ) );
        
        operator++();
        
        return it;
    }
    
    Dictionary::Iterator & Dictionary::Iterator::operator --( void )
    {
        this->_pos--;
        
        return *( this );
    }
    
    Dictionary::Iterator Dictionary::Iterator::operator --( int )
    {
        Iterator it( *( this ) );
        
        operator--();
        
        return it;
    }
    
    Dictionary::Iterator & Dictionary::Iterator::operator += ( CFIndex value )
    {
        this->_pos += value;
        
        return *( this );
    }
    
    Dictionary::Iterator & Dictionary::Iterator::operator -= ( CFIndex value )
    {
        this->_pos -= value;
        
        return *( this );
    }
    
    Dictionary::Iterator Dictionary::Iterator::operator + ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i += value;
    }
    
    Dictionary::Iterator Dictionary::Iterator::operator - ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i -= value;
    }
    
    bool Dictionary::Iterator::operator == ( const Iterator & value ) const
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
    
    bool Dictionary::Iterator::operator != ( const Iterator & value ) const
    {
        return !( *( this ) == value );
    }
    
    CF::Pair Dictionary::Iterator::operator * ( void ) const
    {
        return CF::Pair( this->GetKey(), this->GetValue() );
    }
    
    CFTypeRef Dictionary::Iterator::GetKey( void ) const
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
        
        return this->_keys.GetValueAtIndex( this->_pos );
    }
    
    CFTypeRef Dictionary::Iterator::GetValue( void ) const
    {
        CFTypeRef key;
        
        key = this->GetKey();
        
        if( key == nullptr )
        {
            return nullptr;
        }
        
        return CFDictionaryGetValue( this->_cfObject, key );
    }
    
    void swap( Dictionary::Iterator & v1, Dictionary::Iterator & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
        swap( v1._keys,     v2._keys );
        swap( v1._count,    v2._count );
        swap( v1._pos,      v2._pos );
    }
}
