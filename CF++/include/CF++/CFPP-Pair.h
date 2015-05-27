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
 * @header      CFPP-Pair.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ pair of CFTypeRef
 */

#ifndef CFPP_PAIR_H
#define CFPP_PAIR_H

#include <CF++/CFPP-String.h>
#include <CF++/CFPP-Number.h>

namespace CF
{
    class Pair
    {
        public:
            
            Pair( CFTypeRef key, CFTypeRef value );
            Pair( const Pair & value );
            Pair( String key, CFTypeRef value );
            Pair( const char * key, CFTypeRef value );
            Pair( String key, String value );
            Pair( const char * key, String value );
            Pair( String key, const char * value );
            Pair( const char * key, const char * value );
            Pair( String key, Number value );
            Pair( const char * key, Number value );
            
            #ifdef CFPP_HAS_CPP11
            Pair( Pair && value );
            #endif
            
            virtual ~Pair( void );
            
            Pair & operator = ( Pair value );
            
            CFTypeRef GetKey( void );
            CFTypeRef GetValue( void );
            void      SetKey( CFTypeRef key );
            void      SetValue( CFTypeRef value );
            
            friend void swap( Pair & v1, Pair & v2 );
            
        protected:
            
            CFTypeRef _key;
            CFTypeRef _value;
    };
}

#endif /* CFPP_PAIR_H */
