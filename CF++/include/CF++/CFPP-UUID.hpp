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
 * @header      CFPP-UUID.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFUUIDRef wrapper
 */

#ifndef CFPP_UUID_H
#define CFPP_UUID_H

namespace CF
{
    class CFPP_EXPORT UUID: public Type
    {
        public:
            
            UUID( void );
            UUID( const UUID & value );
            UUID( const AutoPointer & value );
            UUID( CFTypeRef value );
            UUID( CFUUIDRef value );
            UUID( std::nullptr_t );
            UUID( const std::string & value );
            UUID( const Data & value );
            UUID( UUID && value ) noexcept;
            
            virtual ~UUID( void );
            
            UUID & operator = ( UUID value );
            UUID & operator = ( const AutoPointer & value );
            UUID & operator = ( CFTypeRef value );
            UUID & operator = ( CFUUIDRef value );
            UUID & operator = ( std::nullptr_t );
            UUID & operator = ( const std::string & value );
            UUID & operator = ( const Data & value );
            
            bool operator == ( const UUID & value ) const;
            bool operator == ( CFTypeRef value ) const;
            bool operator == ( CFUUIDRef value ) const;
            bool operator == ( const std::string & value ) const;
            bool operator == ( const Data & value ) const;
            
            bool operator != ( const UUID & value ) const;
            bool operator != ( CFTypeRef value ) const;
            bool operator != ( CFUUIDRef value ) const;
            bool operator != ( const std::string & value ) const;
            bool operator != ( const Data & value ) const;
            
            operator std::string () const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            String GetString( void ) const;
            Data   GetData( void )   const;
            Data   GetBytes( void )  const;
            
            friend void swap( UUID & v1, UUID & v2 ) noexcept;
            
        private:
            
            CFUUIDRef _cfObject;
    };
}

#endif /* CFPP_UUID_H */
