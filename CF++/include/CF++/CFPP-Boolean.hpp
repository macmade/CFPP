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
 * @header      CFPP-Boolean.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFBooleanRef wrapper
 */

#ifndef CFPP_BOOLEAN_H
#define CFPP_BOOLEAN_H

namespace CF
{
    class CFPP_EXPORT Boolean: public PropertyListType< Boolean >
    {
        public:
            
            Boolean( const Boolean & value );
            Boolean( const AutoPointer & value );
            Boolean( CFTypeRef cfObject );
            Boolean( CFBooleanRef cfObject );
            Boolean( std::nullptr_t );
            Boolean( const AutoPointer & value, bool defaultValueIfNULL );
            Boolean( CFTypeRef cfObject, bool defaultValueIfNULL );
            Boolean( CFBooleanRef cfObject, bool defaultValueIfNULL );
            Boolean( bool value = false );
            Boolean( Boolean && value ) noexcept;
            
            virtual ~Boolean( void );
            
            Boolean & operator = ( Boolean value );
            Boolean & operator = ( const AutoPointer & value );
            Boolean & operator = ( CFTypeRef value );
            Boolean & operator = ( CFBooleanRef value );
            Boolean & operator = ( std::nullptr_t );
            Boolean & operator = ( bool value );
            
            bool operator == ( const Boolean & value ) const;
            bool operator == ( bool value ) const;
            bool operator == ( CFTypeRef value ) const;
            bool operator == ( CFBooleanRef value ) const;
            
            bool operator != ( const Boolean & value ) const;
            bool operator != ( bool value ) const;
            bool operator != ( CFTypeRef value ) const;
            bool operator != ( CFBooleanRef value ) const;
            
            operator bool () const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            bool GetValue( void ) const;
            void SetValue( bool value );
            
            friend void swap( Boolean & v1, Boolean & v2 ) noexcept;
            
        private:
            
            CFBooleanRef _cfObject;
    };
}

#endif /* CFPP_BOOLEAN_H */
