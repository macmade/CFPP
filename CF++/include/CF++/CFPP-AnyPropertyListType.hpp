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
 * @header      CFPP-AnyPropertyListType.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ generic wrapper for CF property list types
 */

#ifndef CFPP_ANY_PROPERTY_LIST_TYPE_H
#define CFPP_ANY_PROPERTY_LIST_TYPE_H

namespace CF
{
    class Data;
    
    class CFPP_EXPORT AnyPropertyListType: public PropertyListBase
    {
        public:
            
            static AnyPropertyListType FromPropertyList( const std::string & path );
            static AnyPropertyListType FromPropertyListString( const std::string & plist );
            static AnyPropertyListType FromPropertyListData( const Data & plist );
            
            AnyPropertyListType( PropertyListFormat format );
            AnyPropertyListType( const AnyPropertyListType & value );
            AnyPropertyListType( const AutoPointer & value, PropertyListFormat format );
            AnyPropertyListType( CFTypeRef value, PropertyListFormat format );
            AnyPropertyListType( std::nullptr_t, PropertyListFormat format );
            AnyPropertyListType( AnyPropertyListType && value ) noexcept;
            
            virtual ~AnyPropertyListType( void );
            
            AnyPropertyListType & operator = ( AnyPropertyListType value );
            AnyPropertyListType & operator = ( const AutoPointer & value );
            AnyPropertyListType & operator = ( CFTypeRef value );
            AnyPropertyListType & operator = ( std::nullptr_t value );
            
            bool IsValidPropertyList( void ) const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            PropertyListFormat GetFormat( void ) const;
            
            friend void swap( AnyPropertyListType & v1, AnyPropertyListType & v2 ) noexcept;
            
        protected:
            
            CFTypeRef          _cfObject;
            PropertyListFormat _format;
    };
}

#endif /* CFPP_ANY_PROPERTY_LIST_TYPE_H */
