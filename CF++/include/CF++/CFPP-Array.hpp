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
 * @header      CFPP-Array.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFArrayRef wrapper
 */

#ifndef CFPP_ARRAY_H
#define CFPP_ARRAY_H

#include <vector>

namespace CF
{
    class CFPP_EXPORT Array: public PropertyListType< Array >
    {
        public:
            
            Array( void );
            Array( CFIndex capacity );
            Array( const Array & value );
            Array( const AutoPointer & value );
            Array( CFTypeRef value );
            Array( CFArrayRef value );
            Array( std::nullptr_t );
            Array( std::initializer_list< CFTypeRef > value );
            Array( Array && value ) noexcept;
            
            virtual ~Array( void );
            
            Array & operator = ( Array value );
            Array & operator = ( const AutoPointer & value );
            Array & operator = ( CFTypeRef value );
            Array & operator = ( CFArrayRef value );
            Array & operator = ( std::nullptr_t );
            
            Array & operator += ( const Array & value );
            Array & operator += ( CFTypeRef value );
            Array & operator += ( CFArrayRef value );
            
            Array & operator << ( CFTypeRef value );
            Array & operator << ( const char * value );
            Array & operator << ( const String & value );
            Array & operator << ( const Number & value );
            
            CFTypeRef operator [] ( int index ) const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            CFIndex   GetCount( void ) const;
            bool      ContainsValue( CFTypeRef value ) const;
            void      RemoveAllValues( void ) const;
            CFTypeRef GetValueAtIndex( CFIndex index ) const;
            void      SetValueAtIndex( CFTypeRef value, CFIndex index ) const;
            void      InsertValueAtIndex( CFTypeRef value, CFIndex index ) const;
            void      AppendValue( CFTypeRef value ) const;
            void      RemoveValueAtIndex( CFIndex index ) const;
            void      AppendArray( CFArrayRef array ) const;
            void      ExchangeValuesAtIndices( CFIndex index1, CFIndex index2 ) const;
                        
            friend void swap( Array & v1, Array & v2 ) noexcept;
            
            class CFPP_EXPORT Iterator: public Type, public std::iterator< std::bidirectional_iterator_tag, CFTypeRef >
            {
                public:
                    
                    Iterator( void );
                    Iterator( const Iterator & value );
                    Iterator( Iterator && value ) noexcept;
                    
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
                    
                    CFTypeRef operator * ( void ) const;
                    
                    operator CFTypeRef () const;
                    
                    CFTypeID  GetTypeID( void ) const;
                    CFTypeRef GetCFObject( void ) const;
                    
                    friend void swap( Iterator & v1, Iterator & v2 ) noexcept;
                    
                private:
                    
                    friend class Array;
                    
                    Iterator( CFArrayRef array, CFIndex count, CFIndex pos = 0 );
                    
                    CFArrayRef _cfObject;
                    CFIndex    _count;
                    CFIndex    _pos;
            };
            
            Iterator begin( void ) const;
            Iterator end( void ) const;
            
        protected:
            
            CFMutableArrayRef _cfObject;
    };
}

#endif /* CFPP_ARRAY_H */
