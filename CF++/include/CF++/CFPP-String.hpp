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
 * @header      CFPP-String.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFStringRef wrapper
 */

#ifndef CFPP_STRING_H
#define CFPP_STRING_H

namespace CF
{
    class CFPP_EXPORT String: public PropertyListType< String >
    {
        public:
            
            String( void );
            String( const AutoPointer & value );
            String( CFTypeRef cfObject );
            String( CFStringRef cfObject );
            String( std::nullptr_t );
            String( const AutoPointer & value, std::string defaultValueIfNULL, CFStringEncoding encoding = kCFStringEncodingUTF8 );
            String( CFTypeRef cfObject, std::string defaultValueIfNULL, CFStringEncoding encoding = kCFStringEncodingUTF8 );
            String( CFStringRef cfObject, std::string defaultValueIfNULL, CFStringEncoding encoding = kCFStringEncodingUTF8 );
            String( const std::string & value, CFStringEncoding encoding = kCFStringEncodingUTF8 );
            String( char * value, CFStringEncoding encoding = kCFStringEncodingUTF8 );
            String( const char * value, CFStringEncoding encoding = kCFStringEncodingUTF8 );
            String( const String & value );
            String( String && value ) noexcept;
            
            virtual ~String( void );
            
            String & operator = ( String value );
            String & operator = ( const AutoPointer & value );
            String & operator = ( CFTypeRef value );
            String & operator = ( CFStringRef value );
            String & operator = ( std::nullptr_t );
            String & operator = ( const std::string & value );
            String & operator = ( char * value );
            String & operator = ( const char * value );
            
            bool operator == ( const String & value ) const;
            bool operator == ( CFTypeRef value ) const;
            bool operator == ( CFStringRef value ) const;
            bool operator == ( const std::string & value ) const;
            bool operator == ( char * value ) const;
            bool operator == ( const char * value ) const;
            
            bool operator != ( const String & value ) const;
            bool operator != ( CFTypeRef value ) const;
            bool operator != ( CFStringRef value ) const;
            bool operator != ( const std::string & value ) const;
            bool operator != ( char * value ) const;
            bool operator != ( const char * value ) const;
            
            String & operator += ( const String & value );
            String & operator += ( CFStringRef value );
            String & operator += ( const std::string & value );
            String & operator += ( char * value );
            String & operator += ( const char * value );
            
            char operator [] ( int index ) const;
            
            operator std::string () const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            bool HasPrefix( const String & value ) const;
            bool HasPrefix( CFStringRef value ) const;
            bool HasPrefix( const std::string & value ) const;
            bool HasSuffix( const String & value ) const;
            bool HasSuffix( CFStringRef value ) const;
            bool HasSuffix( const std::string & value ) const;
            
            CFIndex GetLength( void ) const;
            
            std::string  GetValue( CFStringEncoding encoding = kCFStringEncodingUTF8 ) const;
            const char * GetCStringValue( CFStringEncoding encoding = kCFStringEncodingUTF8 ) const;
            void         SetValue( const std::string & value, CFStringEncoding encoding = kCFStringEncodingUTF8 );
            
            friend void swap( String & v1, String & v2 ) noexcept;
            
            #if __cplusplus >= 201703L
            class CFPP_EXPORT Iterator
            #else
            class CFPP_EXPORT Iterator: public std::iterator< std::bidirectional_iterator_tag, char >
            #endif
            {
                public:
                
                    #if __cplusplus >= 201703L
                    using iterator_category = std::bidirectional_iterator_tag;
                    using value_type        = char;
                    using difference_type   = ptrdiff_t;
                    using pointer           = char *;
                    using reference         = char &;
                    #endif
                    
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
                    
                    char operator * ( void ) const;
                    
                    operator char () const;
                    
                    friend void swap( Iterator & v1, Iterator & v2 ) noexcept;
                    
                private:
                    
                    friend class String;
                    
                    Iterator( CFStringRef string, CFStringEncoding encoding, CFIndex length, CFIndex pos = 0 );
                    
                    CFStringRef             _cfObject;
                    CFIndex                 _length;
                    CFIndex                 _pos;
                    std::shared_ptr< char > _cp;
            };
            
            Iterator begin( CFStringEncoding encoding = kCFStringEncodingUTF8 ) const;
            Iterator end( CFStringEncoding encoding = kCFStringEncodingUTF8 ) const;
            
        private:
            
            CFStringRef _cfObject;
    };
}

#endif /* CFPP_STRING_H */
