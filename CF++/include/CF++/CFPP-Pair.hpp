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
 * @header      CFPP-Pair.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ pair of CFTypeRef
 */

#ifndef CFPP_PAIR_H
#define CFPP_PAIR_H

namespace CF
{
    class CFPP_EXPORT Pair
    {
        public:
            
            Pair( CFTypeRef key, CFTypeRef value );
            Pair( const Pair & value );
            Pair( const String & key, CFTypeRef value );
            Pair( const char * key, CFTypeRef value );
            Pair( const String & key, const String & value );
            Pair( const char * key, const String & value );
            Pair( const String & key, const char * value );
            Pair( const char * key, const char * value );
            Pair( Pair && value ) noexcept;
            
            virtual ~Pair( void );
            
            Pair & operator = ( Pair value );
            
            CFTypeRef GetKey( void ) const;
            CFTypeRef GetValue( void ) const;
            CFTypeID  GetKeyTypeID( void ) const;
            CFTypeID  GetValueTypeID( void ) const;
            void      SetKey( CFTypeRef key );
            void      SetValue( CFTypeRef value );
            
            friend void swap( Pair & v1, Pair & v2 ) noexcept;
            
        protected:
            
            CFTypeRef _key;
            CFTypeRef _value;
    };
}

#endif /* CFPP_PAIR_H */
