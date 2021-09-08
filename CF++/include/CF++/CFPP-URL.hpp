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
 * @header      CFPP-URL.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFURLRef wrapper
 */

#ifndef CFPP_URL_H
#define CFPP_URL_H

namespace CF
{
    class CFPP_EXPORT URL: public Type
    {
        public:
            
            typedef enum
            {
                PartAll                 = 0x00,
                PartFileSystemPath      = 0x01,
                PartFragment            = 0x02,
                PartHostName            = 0x03,
                PartLastPathComponent   = 0x04,
                PartNetLocation         = 0x05,
                /* 0x06 was PartParameterString - Now deprecated */
                PartPassword            = 0x07,
                PartPath                = 0x08,
                PartPathExtension       = 0x09,
                PartQueryString         = 0x0A,
                PartResourceSpecifier   = 0x0B,
                PartScheme              = 0x0C,
                PartStrictPath          = 0x0D,
                PartUserName            = 0x0E
            }
            Part;
            
            typedef enum
            {
                PathStylePOSIX      = 0x00,
                PathStyleWindows    = 0x01
            }
            PathStyle;
            
            static URL FileSystemURL( const std::string & path, bool isDir = false );
            static URL FileSystemURL( const char * path, bool isDir = false );
            static URL FileSystemURL( CFTypeRef path, bool isDir = false );
            static URL FileSystemURL( CFStringRef path, bool isDir = false );
            
            URL( void );
            URL( const URL & value );
            URL( const AutoPointer & value );
            URL( CFTypeRef value );
            URL( CFURLRef value );
            URL( CFStringRef value );
            URL( CFStringRef value, const CF::URL & base );
            URL( std::nullptr_t );
            URL( const std::string & value );
            URL( const std::string & value, const CF::URL & base );
            URL( const char * value );
            URL( const char * value, const CF::URL & base );
            URL( URL && value ) noexcept;
            
            virtual ~URL( void );
            
            URL & operator = ( URL value );
            URL & operator = ( const AutoPointer & value );
            URL & operator = ( CFTypeRef value );
            URL & operator = ( CFURLRef value );
            URL & operator = ( CFStringRef value );
            URL & operator = ( std::nullptr_t );
            URL & operator = ( const std::string & value );
            URL & operator = ( const char * value );
            
            bool operator == ( const URL & value ) const;
            bool operator == ( CFTypeRef value ) const;
            bool operator == ( CFURLRef value ) const;
            bool operator == ( CFStringRef value ) const;
            bool operator == ( const std::string & value ) const;
            bool operator == ( const char * value ) const;
            
            bool operator != ( const URL & value ) const;
            bool operator != ( CFTypeRef value ) const;
            bool operator != ( CFURLRef value ) const;
            bool operator != ( CFStringRef value ) const;
            bool operator != ( const std::string & value ) const;
            bool operator != ( const char * value ) const;
            
            URL & operator /= ( CFStringRef value );
            URL & operator /= ( const std::string & value );
            URL & operator /= ( const char * value );
            
            std::string operator [] ( Part part ) const;
            
            operator std::string () const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            String GetFileSystemPath( PathStyle style = PathStylePOSIX ) const;
            String GetFragment( void ) const;
            String GetHostName( void ) const;
            String GetLastPathComponent( void ) const;
            String GetNetLocation( void ) const;
            String GetPassword( void ) const;
            String GetPath( void ) const;
            String GetPathExtension( void ) const;
            String GetQueryString( void ) const;
            String GetResourceSpecifier( void ) const;
            String GetScheme( void ) const;
            String GetStrictPath( void ) const;
            String GetUserName( void ) const;
            Number GetPortNumber( void ) const;
            URL    GetBaseURL( void ) const;
            bool   HasDirectoryPath( void ) const;
            void   AppendPathComponent( CFStringRef component, bool isDirectory = false );
            void   AppendPathComponent( const std::string & component, bool isDirectory = false );
            void   AppendPathComponent( const char * component, bool isDirectory = false );
            void   AppendPathExtension( CFStringRef extension );
            void   AppendPathExtension( const std::string & extension );
            void   AppendPathExtension( const char * extension );
            void   DeleteLastPathComponent( void );
            void   DeletePathExtension( void );
            
            friend void swap( URL & v1, URL & v2 ) noexcept;
            
        private:
            
            CFURLRef _cfObject;
    };
}

#endif /* CFPP_URL_H */
