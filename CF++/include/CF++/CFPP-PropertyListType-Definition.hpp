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
 * @header      CFPP-PropertyListType-Definition.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ base class for property list compatible types
 */

#ifndef CFPP_PROPERTY_LIST_TYPE_DEFINITION_H
#define CFPP_PROPERTY_LIST_TYPE_DEFINITION_H

namespace CF
{
    template < class T >
    T PropertyListType< T >::FromPropertyList( const std::string & path )
    {
        Data        data;
        URL         url;
        ReadStream  stream;
        AutoPointer ap;

        if( path.length() == 0 )
        {
            return static_cast< CFTypeRef >( nullptr );
        }

        url = URL::FileSystemURL( path );
        
        if( stream.Open( url ) == false )
        {
            return static_cast< CFTypeRef >( nullptr );
        }
        
        data = stream.Read();
        ap   = CFPropertyListCreateWithData( static_cast< CFAllocatorRef >( nullptr ), data, 0, nullptr, nullptr );
        
        stream.Close();
        
        return ap.As< T >();
    }
    
    template < class T >
    T PropertyListType< T >::FromPropertyListString( const std::string & plist )
    {
        if( plist.length() == 0 )
        {
            return static_cast< CFTypeRef >( nullptr );
        }
        
        return FromPropertyListData( Data( plist ) );
    }
    
    template < class T >
    T PropertyListType< T >::FromPropertyListData( const Data & plist )
    {
        AutoPointer ap;
        
        if( plist.GetLength() == 0 )
        {
            return static_cast< CFTypeRef >( nullptr );
        }
        
        ap = CFPropertyListCreateWithData( static_cast< CFAllocatorRef >( nullptr ), plist, 0, nullptr, nullptr );
        
        return ap.As< T >();
    }
}

#endif /* CFPP_PROPERTY_LIST_TYPE_DEFINITION_H */
