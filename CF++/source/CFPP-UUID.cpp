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
 * @file        CFPP-UUID.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFUUIDRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    UUID::UUID( void ): _cfObject( nullptr )
    {
        this->_cfObject = CFUUIDCreate( static_cast< CFAllocatorRef >( nullptr ) );
    }
    
    UUID::UUID( const UUID & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = static_cast< CFUUIDRef >( CFRetain( value._cfObject ) );
        }
    }
    
    UUID::UUID( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFUUIDRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    UUID::UUID( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFUUIDRef >( CFRetain( value ) );
        }
    }
    
    UUID::UUID( CFUUIDRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFUUIDRef >( CFRetain( value ) );
        }
    }
    
    UUID::UUID( std::nullptr_t ): UUID( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    UUID::UUID( const std::string & value ): _cfObject( nullptr )
    {
        this->_cfObject = CFUUIDCreateFromString( static_cast< CFAllocatorRef >( nullptr ), CF::String( value ) );
    }
    
    UUID::UUID( const Data & value ): _cfObject( nullptr )
    {
        CFUUIDBytes bytes;
        
        memset( &bytes, 0, sizeof( CFUUIDBytes ) );
        
        bytes.byte0     = value[  0 ];
        bytes.byte1     = value[  1 ];
        bytes.byte2     = value[  2 ];
        bytes.byte3     = value[  3 ];
        bytes.byte4     = value[  4 ];
        bytes.byte5     = value[  5 ];
        bytes.byte6     = value[  6 ];
        bytes.byte7     = value[  7 ];
        bytes.byte8     = value[  8 ];
        bytes.byte9     = value[  9 ];
        bytes.byte10    = value[ 10 ];
        bytes.byte11    = value[ 11 ];
        bytes.byte12    = value[ 12 ];
        bytes.byte13    = value[ 13 ];
        bytes.byte14    = value[ 14 ];
        bytes.byte15    = value[ 15 ];
        this->_cfObject = CFUUIDCreateFromUUIDBytes( static_cast< CFAllocatorRef >( nullptr ), bytes );
    }
    
    UUID::UUID( UUID && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    UUID::~UUID( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    UUID & UUID::operator = ( UUID value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    UUID & UUID::operator = ( const AutoPointer & value )
    {
        return operator =( UUID( value ) );
    }
    
    UUID & UUID::operator = ( CFTypeRef value )
    {
        return operator =( UUID( value ) );
    }
    
    UUID & UUID::operator = ( CFUUIDRef value )
    {
        return operator =( UUID( value ) );
    }
    
    UUID & UUID::operator = ( std::nullptr_t )
    {
        return operator =( UUID( nullptr ) );
    }
    
    UUID & UUID::operator = ( const std::string & value )
    {
        return operator =( UUID( value ) );
    }
    
    UUID & UUID::operator = ( const Data & value )
    {
        return operator =( UUID( value ) );
    }
    
    bool UUID::operator == ( const UUID & value ) const
    {
        return this->GetString() == value.GetString();
    }
    
    bool UUID::operator == ( CFTypeRef value ) const
    {
        return operator ==( UUID( value ) );
    }
    
    bool UUID::operator == ( CFUUIDRef value ) const
    {
        return operator ==( UUID( value ) );
    }
    
    bool UUID::operator == ( const std::string & value ) const
    {
        return this->GetString() == value;
    }
    
    bool UUID::operator == ( const Data & value ) const
    {
        return this->GetData() == value;
    }
    
    bool UUID::operator != ( const UUID & value ) const
    {
        return !operator ==( value );
    }
    
    bool UUID::operator != ( CFTypeRef value ) const
    {
        return !operator ==( value );
    }
    
    bool UUID::operator != ( CFUUIDRef value ) const
    {
        return !operator ==( value );
    }
    
    bool UUID::operator != ( const std::string & value ) const
    {
        return !operator ==( value );
    }
    
    bool UUID::operator != ( const Data & value ) const
    {
        return !operator ==( value );
    }
    
    UUID::operator std::string () const
    {
        return this->GetString();
    }
    
    CFTypeID UUID::GetTypeID( void ) const
    {
        return CFUUIDGetTypeID();
    }
    
    CFTypeRef UUID::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    String UUID::GetString( void ) const
    {
        AutoPointer s;
        
        if( this->_cfObject == nullptr )
        {
            return s.As< CFStringRef >();
        }
        
        s = CFUUIDCreateString( static_cast< CFAllocatorRef >( nullptr ), this->_cfObject );
        
        return s.As< CFStringRef >();
    }
    
    Data UUID::GetData( void ) const
    {
        return Data( static_cast< CFStringRef >( this->GetString() ) );
    }
    
    Data UUID::GetBytes( void ) const
    {
        CFUUIDBytes bytes;
        uint8_t     data[ 16 ];
        
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        memset( &bytes, 0, sizeof( CFUUIDBytes ) );
        memset( data,   0, sizeof( data ) );
        
        bytes = CFUUIDGetUUIDBytes( this->_cfObject );
        
        data[  0 ] = bytes.byte0;
        data[  1 ] = bytes.byte1;
        data[  2 ] = bytes.byte2;
        data[  3 ] = bytes.byte3;
        data[  4 ] = bytes.byte4;
        data[  5 ] = bytes.byte5;
        data[  6 ] = bytes.byte6;
        data[  7 ] = bytes.byte7;
        data[  8 ] = bytes.byte8;
        data[  9 ] = bytes.byte9;
        data[ 10 ] = bytes.byte10;
        data[ 11 ] = bytes.byte11;
        data[ 12 ] = bytes.byte12;
        data[ 13 ] = bytes.byte13;
        data[ 14 ] = bytes.byte14;
        data[ 15 ] = bytes.byte15;
        
        return Data( data, sizeof( data ) );
    }
    
    void swap( UUID & v1, UUID & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
