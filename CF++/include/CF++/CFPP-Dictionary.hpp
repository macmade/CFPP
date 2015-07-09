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
 * @header      CFPP-Dictionary.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDictionaryRef wrapper
 */

#ifndef CFPP_DICTIONARY_H
#define CFPP_DICTIONARY_H

#include <map>

namespace CF
{
    class CFPP_EXPORT Dictionary: public PropertyListType< Dictionary >
    {
        public:
            
            Dictionary( void );
            Dictionary( const Dictionary & value );
            Dictionary( CFTypeRef cfObject );
            Dictionary( CFDictionaryRef cfObject );
            
            #ifdef CFPP_HAS_CPP11
            Dictionary( Dictionary && value );
            #endif
            
            virtual ~Dictionary( void );
            
            Dictionary & operator = ( Dictionary value );
            Dictionary & operator = ( CFTypeRef value );
            Dictionary & operator = ( CFDictionaryRef value );
            
            Dictionary & operator += ( Pair pair );
            Dictionary & operator << ( Pair pair );
            
            CFTypeRef operator [] ( CFTypeRef key ) const;
            CFTypeRef operator [] ( const char * key ) const;
            CFTypeRef operator [] ( String key ) const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            bool      ContainsKey( CFTypeRef key ) const;
            bool      ContainsValue( CFTypeRef value ) const;
            void      RemoveAllValues( void ) const;
            CFIndex   GetCount( void ) const;
            CFTypeRef GetValue( CFTypeRef key ) const;
            void      AddValue( CFTypeRef key, CFTypeRef value ) const;
            void      RemoveValue( CFTypeRef key ) const;
            void      ReplaceValue( CFTypeRef key, CFTypeRef value ) const;
            void      SetValue( CFTypeRef key, CFTypeRef value ) const;
            
            friend void swap( Dictionary & v1, Dictionary & v2 );
            
            class CFPP_EXPORT Iterator: public Type, public std::iterator< std::bidirectional_iterator_tag, CF::Pair >
            {
                public:
                    
                    Iterator( void );
                    Iterator( const Iterator & value );
                    
                    #ifdef CFPP_HAS_CPP11
                    Iterator( Iterator && value );
                    #endif
                    
                    virtual ~Iterator( void );
                    
                    Iterator & operator = ( Iterator value );
                    Iterator & operator ++( void );
                    Iterator   operator ++( int );
                    Iterator & operator --( void );
                    Iterator   operator --( int );
                    
                    Iterator & operator += ( CFIndex value );
                    Iterator & operator -= ( CFIndex value );
                    
                    Iterator operator + ( CFIndex value );
                    Iterator operator - ( CFIndex value );
                    
                    bool operator == ( const Iterator & value ) const;
                    bool operator != ( const Iterator & value ) const;
                    
                    CF::Pair operator *  ( void ) const;
                    CF::Pair operator -> ( void ) const;
                    
                    operator CFTypeRef () const;
                    
                    CFTypeID  GetTypeID( void ) const;
                    CFTypeRef GetCFObject( void ) const;
                    CFTypeRef GetKey( void ) const;
                    CFTypeRef GetValue( void ) const;
                    
                    friend void swap( Iterator & v1, Iterator & v2 );
                    
                private:
                    
                    friend class Dictionary;
                    
                    Iterator( CFDictionaryRef dictionary, CFIndex count, CFIndex pos = 0 );
                    
                    CFDictionaryRef _cfObject;
                    CF::Array       _keys;
                    CFIndex         _count;
                    CFIndex         _pos;
            };
            
            Iterator begin( void ) const;
            Iterator end( void ) const;
            
        private:
            
            CFMutableDictionaryRef _cfObject;
    };

	template<typename>struct ClassFor; template<> struct ClassFor<CFDictionaryRef> { typedef CF::Dictionary type; };

	template<typename>struct ClassFor; template<> struct ClassFor<CFMutableDictionaryRef> { typedef CF::Dictionary type; };
}

#endif /* CFPP_DICTIONARY_H */
