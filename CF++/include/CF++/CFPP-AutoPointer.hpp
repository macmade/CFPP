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
 * @header      CFPP-AutoPointer.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ auto-pointer for CF types
 */

#ifndef CFPP_AUTO_POINTER_H
#define CFPP_AUTO_POINTER_H

#include <vector>

namespace CF
{
    class CFPP_EXPORT AutoPointer: public Type
    {
        public:
            
            AutoPointer( void );
            AutoPointer( const AutoPointer & value );
            AutoPointer( CFTypeRef value );
            AutoPointer( AutoPointer && value ) noexcept;
            
            virtual ~AutoPointer( void );
            
            AutoPointer & operator = ( AutoPointer value );
            AutoPointer & operator = ( CFTypeRef value );
                        
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            template< typename T >
            T As( void ) const
            {
                return static_cast< T >( const_cast< void * >( this->GetCFObject() ) );
            }
            
            friend void swap( AutoPointer & v1, AutoPointer & v2 ) noexcept;
            
        protected:
            
            CFTypeRef _cfObject;
    };
}

#endif /* CFPP_AUTO_POINTER_H */
