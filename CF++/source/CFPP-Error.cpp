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
 * @file        CFPP-Error.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFErrorRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    Error::Error( void ): _cfObject( nullptr )
    {}
    
    Error::Error( const Error & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = reinterpret_cast< CFErrorRef >( const_cast< void * >( CFRetain( value._cfObject ) ) );
        }
    }
    
    Error::Error( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFErrorRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    Error::Error( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = reinterpret_cast< CFErrorRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    Error::Error( CFErrorRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = reinterpret_cast< CFErrorRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    Error::Error( std::nullptr_t ): Error( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    Error::Error( const String & domain, const Number & code ): _cfObject( nullptr )
    {
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            domain,
            static_cast< CFIndex >( code.GetSignedLongValue() ),
            nullptr
        );
    }
    
    Error::Error( const String & domain, const Number & code, const Dictionary & userInfo ): _cfObject( nullptr )
    {
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            domain,
            static_cast< CFIndex >( code.GetSignedLongValue() ),
            userInfo
        );
    }
    
    Error::Error( CFStringRef domain, CFIndex code ): _cfObject( nullptr )
    {
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            domain,
            code,
            nullptr
        );
    }
    
    Error::Error( CFStringRef domain, CFIndex code, CFDictionaryRef userInfo ): _cfObject( nullptr )
    {
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            domain,
            code,
            userInfo
        );
    }
    
    Error::Error( const std::string & domain, CFIndex code ): _cfObject( nullptr )
    {
        String s;
        
        s = domain;
        
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            s,
            code,
            nullptr
        );
    }
    
    Error::Error( const std::string & domain, CFIndex code, const Dictionary & userInfo ): _cfObject( nullptr )
    {
        String s;
        
        s = domain;
        
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            s,
            code,
            userInfo
        );
    }
    
    Error::Error( const char * domain, CFIndex code ): _cfObject( nullptr )
    {
        String s;
        
        s = domain;
        
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            s,
            code,
            nullptr
        );
    }
    
    Error::Error( const char * domain, CFIndex code, const Dictionary & userInfo ): _cfObject( nullptr )
    {
        String s;
        
        s = domain;
        
        this->_cfObject = CFErrorCreate
        (
            static_cast< CFAllocatorRef >( nullptr ),
            s,
            code,
            userInfo
        );
    }
    
    Error::Error( Error && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    Error::~Error( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    
    }
    
    Error & Error::operator = ( Error value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Error & Error::operator = ( const AutoPointer & value )
    {
        return operator =( Error( value ) );
    }
    
    Error & Error::operator = ( CFTypeRef value )
    {
        return operator =( Error( value ) );
    }
    
    Error & Error::operator = ( CFErrorRef value )
    {
        return operator =( Error( value ) );
    }
    
    Error & Error::operator = ( std::nullptr_t )
    {
        return operator =( Error( nullptr ) );
    }
    
    CFTypeID Error::GetTypeID( void ) const
    {
        return CFErrorGetTypeID();
    }
    
    CFTypeRef Error::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    String Error::GetDomain( void ) const
    {
        String      str;
        CFStringRef cfStr;
        
        if( this->_cfObject == nullptr )
        {
            return str;
        }
        
        cfStr = CFErrorGetDomain( this->_cfObject );
        str   = cfStr;
        
        return str;
    }
    
    Number Error::GetCode( void ) const
    {
        Number n;
        
        if( this->_cfObject == nullptr )
        {
            return n;
        }
        
        n = CFErrorGetCode( this->_cfObject );
        
        return n;
    }
    
    Dictionary Error::GetUserInfo( void ) const
    {
        AutoPointer d;
        
        if( this->_cfObject == nullptr )
        {
            return CF::Dictionary();
        }
        
        d = CFErrorCopyUserInfo( this->_cfObject );
        
        return d.As< CFDictionaryRef >();
    }
    
    String Error::GetDescription( void ) const
    {
        AutoPointer s;
        
        if( this->_cfObject == nullptr )
        {
            return CF::String();
        }
        
        s = CFErrorCopyDescription( this->_cfObject );
        
        return s.As< CFStringRef >();
    }
    
    String Error::GetFailureReason( void ) const
    {
        AutoPointer s;
        
        if( this->_cfObject == nullptr )
        {
            return CF::String();
        }
        
        s = CFErrorCopyFailureReason( this->_cfObject );
        
        return s.As< CFStringRef >();
    }
    
    String Error::GetRecoverySuggestion( void ) const
    {
        AutoPointer s;
        
        if( this->_cfObject == nullptr )
        {
            return CF::String();
        }
        
        s = CFErrorCopyRecoverySuggestion( this->_cfObject );
        
        return s.As< CFStringRef >();
    }
    
    void swap( Error & v1, Error & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
