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
 * @file        CFPP-PropertyListBase.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFNumberRef wrapper
 */

#include <CF++.hpp>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wc++11-long-long" /* Do not warn about long long in C++98 */
#endif

namespace CF
{
    bool PropertyListBase::ToPropertyList( const std::string & path, PropertyListFormat format ) const
    {
        URL         url;
        Data        d;
        WriteStream stream;
        bool        ret;
        
        if( this->IsValid() == false )
        {
            return false;
        }
        
        url = URL::FileSystemURL( path );
        d   = this->ToPropertyList( format );
        
        if( d.GetLength() == 0 )
        {
            return false;
        }
        
        if( stream.Open( url ) == false )
        {
            return false;
        }
        
        ret = stream.WriteAll( d );
        
        stream.Close();
        
        return ret;
    }
    
    Data PropertyListBase::ToPropertyList( PropertyListFormat format ) const
    {
        AutoPointer          data;
        CFPropertyListFormat cfFormat;
        
        if( this->IsValid() == false )
        {
            return static_cast< CFDataRef >( nullptr );
        }
        
        cfFormat = kCFPropertyListXMLFormat_v1_0;
        
        if( format == PropertyListFormatBinary )
        {
            cfFormat = kCFPropertyListBinaryFormat_v1_0;
        }
        
        data = CFPropertyListCreateData( static_cast< CFAllocatorRef >( nullptr ), this->GetCFObject(), cfFormat, 0, nullptr );
        
        return data.As< CFDataRef >();
    }
}
