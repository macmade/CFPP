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
 * @header      CFPP-AnyObject.hpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ generic container for CF types
 */

#ifndef CFPP_ANY_OBJECT_H
#define CFPP_ANY_OBJECT_H

#include <vector>

namespace CF
{
    class CFPP_EXPORT AnyObject: public Type
    {
        public:
            
            AnyObject( void );
            AnyObject( const AnyObject & value );
            AnyObject( const AutoPointer & value );
            AnyObject( CFTypeRef value );
            AnyObject( std::nullptr_t );
            AnyObject( AnyObject && value ) noexcept;
            
            virtual ~AnyObject( void );
            
            AnyObject & operator = ( AnyObject value );
            AnyObject & operator = ( const AutoPointer & value );
            AnyObject & operator = ( CFTypeRef value );
            AnyObject & operator = ( std::nullptr_t );
                        
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            template< typename T >
            T As( void ) const
            {
                return static_cast< T >( const_cast< void * >( this->GetCFObject() ) );
            }
            
            friend void swap( AnyObject & v1, AnyObject & v2 ) noexcept;
            
        protected:
            
            CFTypeRef _cfObject;
    };
}

#endif /* CFPP_ANY_OBJECT_H */
