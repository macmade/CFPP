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
 * @file        CFPP-Data.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDataRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    Data::Data( void ): _cfObject( nullptr )
    {
        this->_cfObject = CFDataCreateMutable( static_cast< CFAllocatorRef >( nullptr ), 0 );
    }
    
    Data::Data( CFIndex capacity ): _cfObject( nullptr )
    {
        this->_cfObject = CFDataCreateMutable( static_cast< CFAllocatorRef >( nullptr ), capacity );
    }
    
    Data::Data( const Data & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = CFDataCreateMutableCopy( static_cast< CFAllocatorRef >( nullptr ), 0, value._cfObject );
        }
    }
    
    Data::Data( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = CFDataCreateMutableCopy( static_cast< CFAllocatorRef >( nullptr ), 0, static_cast< CFDataRef >( value ) );
        }
    }
    
    Data::Data( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFDataCreateMutableCopy( static_cast< CFAllocatorRef >( nullptr ), 0, static_cast< CFDataRef >( value ) );
        }
    }
    
    Data::Data( CFDataRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFDataCreateMutableCopy( static_cast< CFAllocatorRef >( nullptr ), 0, static_cast< CFDataRef >( value ) );
        }
    }
    
    Data::Data( CFStringRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == CFStringGetTypeID() )
        {
            this->_cfObject = CFDataCreateMutable( static_cast< CFAllocatorRef >( nullptr ), 0 );
            
            CFDataAppendBytes( this->_cfObject, reinterpret_cast< const UInt8 * >( CFStringGetCStringPtr( value, kCFStringEncodingUTF8 ) ), CFStringGetLength( value ) );
        }
    }
    
    Data::Data( std::nullptr_t ): Data( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    Data::Data( const std::string & value ): _cfObject( nullptr )
    {
        this->_cfObject = CFDataCreateMutable( static_cast< CFAllocatorRef >( nullptr ), 0 );
        
        CFDataAppendBytes( this->_cfObject, reinterpret_cast< const UInt8 * >( value.c_str() ), static_cast< CFIndex >( value.length() ) );
    }
    
    Data::Data( const Byte * value, CFIndex length ): _cfObject( nullptr )
    {
        if( value != nullptr )
        {
            this->_cfObject = CFDataCreateMutable( static_cast< CFAllocatorRef >( nullptr ), 0 );
            
            CFDataAppendBytes( this->_cfObject, value, length );
        }
    }
    
    Data::Data( std::initializer_list< Byte > value ): Data( static_cast< CFIndex >( value.size() ) )
    {
        for( Byte b: value )
        {
            CFDataAppendBytes( this->_cfObject, &b, 1 );
        }
    }
    
    Data::Data( Data && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    Data::~Data( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
          
    Data & Data::operator = ( Data value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Data & Data::operator = ( const AutoPointer & value )
    {
        return operator =( Data( value ) );
    }
    
    Data & Data::operator = ( CFTypeRef value )
    {
        return operator =( Data( value ) );
    }
    
    Data & Data::operator = ( CFDataRef value )
    {
        return operator =( Data( value ) );
    }
    
    Data & Data::operator = ( CFStringRef value )
    {
        return operator =( Data( value ) );
    }
    
    Data & Data::operator = ( std::nullptr_t )
    {
        return operator =( Data( nullptr ) );
    }
    
    Data & Data::operator = ( const std::string & value )
    {
        return operator =( Data( value ) );
    }
    
    Data::operator const Byte * () const
    {
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        return CFDataGetBytePtr( this->_cfObject );
    }
    
    Data::operator std::string () const
    {
        std::string s;
        
        if( this->_cfObject == nullptr )
        {
            return s;
        }
        
        s = std::string( reinterpret_cast< const char * >( CFDataGetBytePtr( this->_cfObject ) ), static_cast< std::string::size_type >( CFDataGetLength( this->_cfObject ) ) );
        
        return s;
    }
    
    Byte Data::operator [] ( int index ) const
    {
        const Byte * bytes;
        
        if( index < 0 || index >= this->GetLength() )
        {
            return 0;
        }
        
        bytes = this->GetBytePtr();
        
        return bytes[ index ];
    }
            
    Data & Data::operator += ( Byte value )
    {
        if( this->_cfObject != nullptr )
        {
            CFDataAppendBytes( this->_cfObject, &value, 1 );
        }
        
        return *( this );
    }
    
    Data & Data::operator += ( CFStringRef value )
    {
        if( this->_cfObject != nullptr && value != nullptr && CFGetTypeID( value ) == CFStringGetTypeID() )
        {
            CFDataAppendBytes( this->_cfObject, reinterpret_cast< const UInt8 * >( CFStringGetCStringPtr( value, kCFStringEncodingUTF8 ) ), CFStringGetLength( value ) );
        }
        
        return *( this );
    }
    
    Data & Data::operator += ( CFDataRef value )
    {
        if( this->_cfObject != nullptr && value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            CFDataAppendBytes( this->_cfObject, CFDataGetBytePtr( value ), CFDataGetLength( value ) );
        }
        
        return *( this );
    }
    
    Data & Data::operator += ( const Data & value )
    {
        return operator += ( value._cfObject );
    }
    
    Data & Data::operator += ( const std::string & value )
    {
        if( this->_cfObject != nullptr )
        {
            CFDataAppendBytes( this->_cfObject, reinterpret_cast< const UInt8 * >( value.c_str() ), static_cast< CFIndex >( value.length() ) );
        }
        
        return *( this );
    }
    
    CFTypeID Data::GetTypeID( void ) const
    {
        return CFDataGetTypeID();
    }
    
    CFTypeRef Data::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    CFIndex Data::GetLength( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return 0;
        }
        
        return CFDataGetLength( this->_cfObject );
    }
    
    void Data::SetLength( CFIndex length ) const
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFDataSetLength( this->_cfObject, length );
    }
    
    void Data::IncreaseLength( CFIndex extraLength ) const
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFDataIncreaseLength( this->_cfObject, extraLength );
    }
    
    const Byte * Data::GetBytePtr( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        return CFDataGetBytePtr( this->_cfObject );
    }
    
    Byte * Data::GetMutableBytePtr( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        return CFDataGetMutableBytePtr( this->_cfObject );
    }
    
    void Data::GetBytes( CFRange range, Byte * bytes ) const
    {
        if( this->_cfObject == nullptr || bytes == nullptr )
        {
            return;
        }
        
        CFDataGetBytes( this->_cfObject, range, bytes );
    }
    
    void Data::AppendBytes( const Byte * bytes, CFIndex length ) const
    {
        if( this->_cfObject == nullptr || bytes == nullptr )
        {
            return;
        }
        
        CFDataAppendBytes( this->_cfObject, bytes, length );
    }
    
    void Data::ReplaceBytes( CFRange range, const Byte * newBytes, CFIndex newLength ) const
    {
        if( this->_cfObject == nullptr || newBytes == nullptr )
        {
            return;
        }
        
        CFDataReplaceBytes( this->_cfObject, range, newBytes, newLength );
    }
    
    void Data::DeleteBytes( CFRange range ) const
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFDataDeleteBytes( this->_cfObject, range );
    }
    
    CFRange Data::Find( const Data & data, CFRange range, CFDataSearchFlags flags ) const
    {
        CFRange r;
        
        r.location = kCFNotFound;
        r.length   = 0;
        
        if( this->_cfObject == nullptr )
        {
            return r;
        }
        
        return CFDataFind( this->_cfObject, data, range, flags );
    }
    
    Data::Iterator Data::begin( void ) const
    {
        return Iterator( this->_cfObject, this->GetLength() );
    }
    
    Data::Iterator Data::end( void ) const
    {
        return Iterator( this->_cfObject, this->GetLength(), this->GetLength() );
    }
    
    void swap( Data & v1, Data & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
