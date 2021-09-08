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
 * @file        CFPP-AnyPropertyListType.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ generic wrapper for CF property list types
 */

#include <CF++.hpp>

namespace CF
{
    AnyPropertyListType AnyPropertyListType::FromPropertyList( const std::string & path )
    {
        Data                 data;
        URL                  url;
        ReadStream           stream;
        AutoPointer          ap;
        CFPropertyListFormat f;

        if( path.length() == 0 )
        {
            return { static_cast< CFTypeRef >( nullptr ), PropertyListFormatBinary };
        }

        url = URL::FileSystemURL( path );
        
        if( stream.Open( url ) == false )
        {
            return { static_cast< CFTypeRef >( nullptr ), PropertyListFormatBinary };
        }
        
        data = stream.Read();
        ap   = CFPropertyListCreateWithData( static_cast< CFAllocatorRef >( nullptr ), data, 0, &f, nullptr );
        
        stream.Close();
        
        return { ap, ( f == kCFPropertyListBinaryFormat_v1_0 ) ? PropertyListFormatBinary : PropertyListFormatXML };
    }
    
    AnyPropertyListType AnyPropertyListType::FromPropertyListString( const std::string & plist )
    {
        if( plist.length() == 0 )
        {
            return { static_cast< CFTypeRef >( nullptr ), PropertyListFormatBinary };
        }
        
        return FromPropertyListData( Data( plist ) );
    }
    
    AnyPropertyListType AnyPropertyListType::FromPropertyListData( const Data & plist )
    {
        AutoPointer          ap;
        CFPropertyListFormat f;
        
        if( plist.GetLength() == 0 )
        {
            return { static_cast< CFTypeRef >( nullptr ), PropertyListFormatBinary };
        }
        
        ap = CFPropertyListCreateWithData( static_cast< CFAllocatorRef >( nullptr ), plist, 0, &f, nullptr );
        
        return { ap, ( f == kCFPropertyListBinaryFormat_v1_0 ) ? PropertyListFormatBinary : PropertyListFormatXML };
    }
    
    AnyPropertyListType::AnyPropertyListType( PropertyListFormat format ):
        _cfObject( nullptr ),
        _format( format )
    {}
    
    AnyPropertyListType::AnyPropertyListType( const AnyPropertyListType & value ):
        _cfObject( nullptr ),
        _format( value._format )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = CFRetain( value._cfObject );
        }
    }
    
    AnyPropertyListType::AnyPropertyListType( const AutoPointer & value, PropertyListFormat format ):
        _cfObject( nullptr ),
        _format( format )
    {
        CFPropertyListFormat f( ( ( format == PropertyListFormatBinary ) ? kCFPropertyListBinaryFormat_v1_0 : kCFPropertyListXMLFormat_v1_0 ) );
        
        if( value.IsValid() && CFPropertyListIsValid( value.GetCFObject(), f ) )
        {
            this->_cfObject = CFRetain( value );
        }
    }
    
    AnyPropertyListType::AnyPropertyListType( CFTypeRef value, PropertyListFormat format ):
        _cfObject( nullptr ),
        _format( format )
    {
        CFPropertyListFormat f( ( ( format == PropertyListFormatBinary ) ? kCFPropertyListBinaryFormat_v1_0 : kCFPropertyListXMLFormat_v1_0 ) );
        
        if( value != nullptr && CFPropertyListIsValid( value, f ) )
        {
            this->_cfObject = CFRetain( value );
        }
    }
    
    AnyPropertyListType::AnyPropertyListType( std::nullptr_t, PropertyListFormat format ):
        AnyPropertyListType( format )
    {}
    
    AnyPropertyListType::AnyPropertyListType( AnyPropertyListType && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        this->_format   = value._format;
        value._cfObject = nullptr;
    }
    
    AnyPropertyListType::~AnyPropertyListType( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    AnyPropertyListType & AnyPropertyListType::operator = ( AnyPropertyListType value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    AnyPropertyListType & AnyPropertyListType::operator = ( const AutoPointer & value )
    {
        return operator =( AnyPropertyListType( value, this->_format ) );
    }
    
    AnyPropertyListType & AnyPropertyListType::operator = ( CFTypeRef value )
    {
        return operator =( AnyPropertyListType( value, this->_format ) );
    }
    
    AnyPropertyListType & AnyPropertyListType::operator = ( std::nullptr_t )
    {
        return operator =( AnyPropertyListType( nullptr, this->_format ) );
    }
    
    bool AnyPropertyListType::IsValidPropertyList( void ) const
    {
        return Type::IsValidPropertyList( this->_format );
    }
    
    CFTypeID AnyPropertyListType::GetTypeID( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return 0;
        }
        
        return CFGetTypeID( this->_cfObject );
    }
    
    CFTypeRef AnyPropertyListType::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    PropertyListFormat AnyPropertyListType::GetFormat( void ) const
    {
        return this->_format;
    }
    
    void swap( AnyPropertyListType & v1, AnyPropertyListType & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
