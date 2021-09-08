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
 * @file        CFPP-Pair.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ pair of CFTypeRef
 */


#include <CF++.hpp>

namespace CF
{    
    Pair::Pair( CFTypeRef key, CFTypeRef value ): _key( nullptr ), _value( nullptr )
    {
        this->SetKey( key );
        this->SetValue( value );
    }
    
    Pair::Pair( const Pair & value ): _key( nullptr ), _value( nullptr )
    {
        this->SetKey( value._key );
        this->SetValue( value._value );
    }
    
    Pair::Pair( const char * key, CFTypeRef value ): _key( nullptr ), _value( nullptr )
    {
        String s;
        
        s = key;
        
        this->SetKey( s );
        this->SetValue( value );
    }
    
    Pair::Pair( const String & key, CFTypeRef value ): _key( nullptr ), _value( nullptr )
    {
        this->SetKey( key );
        this->SetValue( value );
    }
    
    Pair::Pair( const String & key, const String & value ): _key( nullptr ), _value( nullptr )
    {
        this->SetKey( key );
        this->SetValue( value );
    }
    
    Pair::Pair( const char * key, const String & value ): _key( nullptr ), _value( nullptr )
    {
        String s;
        
        s = key;
        
        this->SetKey( s );
        this->SetValue( value );
    }
    
    Pair::Pair( const String & key, const char * value ): _key( nullptr ), _value( nullptr )
    {
        String s;
        
        s = value;
        
        this->SetKey( key );
        this->SetValue( s );
    }
    
    Pair::Pair( const char * key, const char * value ): _key( nullptr ), _value( nullptr )
    {
        String s1;
        String s2;
        
        s1 = key;
        s2 = value;
        
        this->SetKey( s1 );
        this->SetValue( s2 );
    }
    
    Pair::Pair( Pair && value ) noexcept
    {
        this->_key   = value._key;
        value._key   = nullptr;
        this->_value = value._value;
        value._value = nullptr;
    }
    
    Pair::~Pair( void )
    {
        if( this->_key != nullptr )
        {
            CFRelease( this->_key );
        }
        
        if( this->_value != nullptr )
        {
            CFRelease( this->_value );
        }
    }
    
    Pair & Pair::operator = ( Pair value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    CFTypeRef Pair::GetKey( void ) const
    {
        return this->_key;
    }
    
    CFTypeRef Pair::GetValue( void ) const
    {
        return this->_value;
    }

	CFTypeID Pair::GetKeyTypeID(void) const
	{
		if( this->_key != nullptr )
        {
            return CFGetTypeID( this->_key );
        }
        
		return 0;
	}

	CFTypeID Pair::GetValueTypeID(void) const
	{
		if( this->_value != nullptr )
        {
            return CFGetTypeID( this->_value );
        }
        
		return 0;
	}
            
    void Pair::SetKey( CFTypeRef key )
    {
        if( this->_key != nullptr )
        {
            CFRelease( this->_key );
        }
        
        if( key != nullptr )
        {
            this->_key = CFRetain( key );
        }
        else
        {
            this->_key = nullptr;
        }
    }
    
    void Pair::SetValue( CFTypeRef value )
    {
        if( this->_value != nullptr )
        {
            CFRelease( this->_value );
        }
        
        if( value != nullptr )
        {
            this->_value = CFRetain( value );
        }
        else
        {
            this->_value = nullptr;
        }
    }
    
    void swap( Pair & v1, Pair & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._key, v2._key );
        swap( v1._value, v2._value );
    }
}
