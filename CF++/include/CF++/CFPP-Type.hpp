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
 * @header      CFPP-Type.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ base abstract class for CF wrappers
 */

#ifndef CFPP_TYPE_H
#define CFPP_TYPE_H

namespace CF
{
    typedef enum
    {
        PropertyListFormatXML       = 0x00,
        PropertyListFormatBinary    = 0x01
    }
    PropertyListFormat;
    
    class CFPP_EXPORT Type
    {
        public:
            
            virtual ~Type( void );
            
            virtual CFTypeID  GetTypeID( void ) const = 0;
            virtual CFTypeRef GetCFObject( void ) const = 0;
            
            bool operator == ( const Type & value ) const;
            bool operator != ( const Type & value ) const;
            
            operator CFTypeRef              () const;
            operator CFBooleanRef           () const;
            operator CFNumberRef            () const;
            operator CFDateRef              () const;
            operator CFStringRef            () const;
            operator CFMutableStringRef     () const;
            operator CFURLRef               () const;
            operator CFDataRef              () const;
            operator CFMutableDataRef       () const;
            operator CFArrayRef             () const;
            operator CFMutableArrayRef      () const;
            operator CFDictionaryRef        () const;
            operator CFMutableDictionaryRef () const;
            operator CFUUIDRef              () const;
            operator CFErrorRef             () const;
            operator CFReadStreamRef        () const;
            operator CFWriteStreamRef       () const;
            
            std::string Description( void ) const;
            CFHashCode  Hash( void ) const;
            void        Show( void ) const;
            CFIndex     GetRetainCount( void ) const;
            
            bool IsValid( void ) const;
            bool IsValidPropertyList( PropertyListFormat format ) const;
            bool IsBoolean( void ) const;
            bool IsNumber( void ) const;
            bool IsDate( void ) const;
            bool IsString( void ) const;
            bool IsURL( void ) const;
            bool IsData( void ) const;
            bool IsArray( void ) const;
            bool IsDictionary( void ) const;
            bool IsUUID( void ) const;
            bool IsError( void ) const;
            bool IsReadStream( void ) const;
            bool IsWriteStream( void ) const;
            
            friend std::ostream & operator << ( std::ostream & os, const Type & obj );
    };
}

#endif /* CFPP_TYPE_H */
