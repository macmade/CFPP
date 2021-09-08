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
 * @header      CFPP-Data.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDataRef wrapper
 */

#ifndef CFPP_DATA_H
#define CFPP_DATA_H

namespace CF
{
    class CFPP_EXPORT Data: public PropertyListType< Data >
    {
        public:
            
            #ifdef _WIN32
            
            typedef unsigned __int8 Byte;
            
            #else
            
            typedef uint8_t Byte;
            
            #endif
            
            Data( void );
            Data( CFIndex capacity );
            Data( const Data & value );
            Data( const AutoPointer & value );
            Data( CFTypeRef value );
            Data( CFDataRef value );
            Data( CFStringRef value );
            Data( std::nullptr_t );
            Data( const std::string & value );
            Data( const Byte * value, CFIndex length );
            Data( std::initializer_list< Byte > value );
            Data( Data && value ) noexcept;
            
            virtual ~Data( void );
            
            Data & operator = ( Data value );
            Data & operator = ( const AutoPointer & value );
            Data & operator = ( CFTypeRef value );
            Data & operator = ( CFDataRef value );
            Data & operator = ( CFStringRef value );
            Data & operator = ( std::nullptr_t );
            Data & operator = ( const std::string & value );
            
            operator const Byte * () const;
            operator std::string  () const;
            
            Byte operator [] ( int index ) const;
            
            Data & operator += ( Byte value );
            Data & operator += ( CFStringRef value );
            Data & operator += ( CFDataRef value );
            Data & operator += ( const Data & value );
            Data & operator += ( const std::string & value );
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            CFIndex      GetLength( void ) const;
            void         SetLength( CFIndex length ) const;
            void         IncreaseLength( CFIndex extraLength ) const;
            const Byte * GetBytePtr( void ) const;
            Byte       * GetMutableBytePtr( void ) const;
            void         GetBytes( CFRange range, Byte * bytes ) const;
            void         AppendBytes( const Byte * bytes, CFIndex length ) const;
            void         ReplaceBytes( CFRange range, const Byte * newBytes, CFIndex newLength ) const;
            void         DeleteBytes( CFRange range ) const;
            CFRange      Find( const Data & data, CFRange range, CFDataSearchFlags flags ) const;
            
            friend void swap( Data & v1, Data & v2 ) noexcept;
            
            class CFPP_EXPORT Iterator: public std::iterator< std::bidirectional_iterator_tag, Byte >
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
                    
                    Byte operator * ( void ) const;
                    
                    operator Byte () const;
                    
                    friend void swap( Iterator & v1, Iterator & v2 ) noexcept;
                    
                private:
                    
                    friend class Data;
                    
                    Iterator( CFDataRef data, CFIndex length, CFIndex pos = 0 );
                    
                    CFDataRef    _cfObject;
                    CFIndex      _length;
                    CFIndex      _pos;
                    const Byte * _bp;
            };
            
            Iterator begin( void ) const;
            Iterator end( void ) const;
            
        private:
            
            CFMutableDataRef _cfObject;
    };
}

#endif /* CFPP_DATA_H */
