/*******************************************************************************
 * Copyright (c) 2014, Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
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
            return { static_cast< CFTypeRef >( NULL ), PropertyListFormatBinary };
        }

        url = URL::FileSystemURL( path );
        
        if( stream.Open( url ) == false )
        {
            return { static_cast< CFTypeRef >( NULL ), PropertyListFormatBinary };
        }
        
        data = stream.Read();
        ap   = CFPropertyListCreateWithData( static_cast< CFAllocatorRef >( NULL ), data, 0, &f, NULL );
        
        stream.Close();
        
        return { ap, ( f == kCFPropertyListBinaryFormat_v1_0 ) ? PropertyListFormatBinary : PropertyListFormatXML };
    }
    
    AnyPropertyListType AnyPropertyListType::FromPropertyListString( const std::string & plist )
    {
        if( plist.length() == 0 )
        {
            return { static_cast< CFTypeRef >( NULL ), PropertyListFormatBinary };
        }
        
        return FromPropertyListData( Data( plist ) );
    }
    
    AnyPropertyListType AnyPropertyListType::FromPropertyListData( const Data & plist )
    {
        AutoPointer          ap;
        CFPropertyListFormat f;
        
        if( plist.GetLength() == 0 )
        {
            return { static_cast< CFTypeRef >( NULL ), PropertyListFormatBinary };
        }
        
        ap = CFPropertyListCreateWithData( static_cast< CFAllocatorRef >( NULL ), plist, 0, &f, NULL );
        
        return { ap, ( f == kCFPropertyListBinaryFormat_v1_0 ) ? PropertyListFormatBinary : PropertyListFormatXML };
    }
    
    AnyPropertyListType::AnyPropertyListType( PropertyListFormat format ):
        _cfObject( NULL ),
        _format( format )
    {}
    
    AnyPropertyListType::AnyPropertyListType( const AnyPropertyListType & value ):
        _cfObject( NULL ),
        _format( value._format )
    {
        if( value._cfObject != NULL )
        {
            this->_cfObject = CFRetain( value._cfObject );
        }
    }
    
    AnyPropertyListType::AnyPropertyListType( const AutoPointer & value, PropertyListFormat format ):
        _cfObject( NULL ),
        _format( format )
    {
        CFPropertyListFormat f( ( ( format == PropertyListFormatBinary ) ? kCFPropertyListBinaryFormat_v1_0 : kCFPropertyListXMLFormat_v1_0 ) );
        
        if( value.IsValid() && CFPropertyListIsValid( value.GetCFObject(), f ) )
        {
            this->_cfObject = CFRetain( value );
        }
    }
    
    AnyPropertyListType::AnyPropertyListType( CFTypeRef value, PropertyListFormat format ):
        _cfObject( NULL ),
        _format( format )
    {
        CFPropertyListFormat f( ( ( format == PropertyListFormatBinary ) ? kCFPropertyListBinaryFormat_v1_0 : kCFPropertyListXMLFormat_v1_0 ) );
        
        if( value != NULL && CFPropertyListIsValid( value, f ) )
        {
            this->_cfObject = CFRetain( value );
        }
    }
    
    #ifdef CFPP_HAS_CPP11
    AnyPropertyListType::AnyPropertyListType( AnyPropertyListType && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        this->_format   = value._format;
        value._cfObject = nullptr;
    }
    #endif
    
    AnyPropertyListType::~AnyPropertyListType( void )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = NULL;
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
    
    bool AnyPropertyListType::IsValidPropertyList( void ) const
    {
        return Type::IsValidPropertyList( this->_format );
    }
    
    CFTypeID AnyPropertyListType::GetTypeID( void ) const
    {
        if( this->_cfObject == NULL )
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
