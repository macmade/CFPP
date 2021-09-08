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
 * @header      CFPP-Error.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFErrorRef wrapper
 */

#ifndef CFPP_ERROR_H
#define CFPP_ERROR_H

namespace CF
{
    class CFPP_EXPORT Error: public Type
    {
        public:
            
            Error( void );
            Error( const Error & value );
            Error( const AutoPointer & value );
            Error( CFTypeRef value );
            Error( CFErrorRef value );
            Error( std::nullptr_t );
            Error( const String & domain, const Number & code );
            Error( const String & domain, const Number & code, const Dictionary & userInfo );
            Error( CFStringRef domain, CFIndex code );
            Error( CFStringRef domain, CFIndex code, CFDictionaryRef userInfo );
            Error( const std::string & domain, CFIndex code );
            Error( const std::string & domain, CFIndex code, const Dictionary & userInfo );
            Error( const char * domain, CFIndex code );
            Error( const char * domain, CFIndex code, const Dictionary & userInfo );
            Error( Error && value ) noexcept;
            
            virtual ~Error( void );
            
            Error & operator = ( Error value );
            Error & operator = ( const AutoPointer & value );
            Error & operator = ( CFTypeRef value );
            Error & operator = ( CFErrorRef value );
            Error & operator = ( std::nullptr_t );
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            String     GetDomain( void ) const;
            Number     GetCode( void ) const;
            Dictionary GetUserInfo( void ) const;
            String     GetDescription( void ) const;
            String     GetFailureReason( void ) const;
            String     GetRecoverySuggestion( void ) const;
            
            friend void swap( Error & v1, Error & v2 ) noexcept;
            
        private:
            
            CFErrorRef _cfObject;
    };
}

#endif /* CFPP_ERROR_H */
