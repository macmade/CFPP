/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2019 Jean-David Gadina - www.xs-labs.com / www.digidna.net
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
 * @header      CFPP-Object.hpp
 * @copyright   (c) 2019 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ generic container for CF types
 */

#ifndef CFPP_OBJECT_H
#define CFPP_OBJECT_H

namespace CF
{
    template< typename _T_ >
    class CFPP_EXPORT Object: public Type
    {
        public:
            
            Object( void ): _cfObject( nullptr )
            {}
            
            Object( const Object< _T_ > & value ): _cfObject( nullptr )
            {
                if( value._cfObject != nullptr )
                {
                    this->_cfObject = reinterpret_cast< _T_ >( const_cast< void * >( CFRetain( value._cfObject ) ) );
                }
            }
            
            Object( const AutoPointer & value ): _cfObject( nullptr )
            {
                if( value.IsValid() )
                {
                    this->_cfObject = static_cast< _T_ >( const_cast< void * >( CFRetain( value ) ) );
                }
            }
            
            Object( _T_ value ): _cfObject( nullptr )
            {
                if( value != nullptr )
                {
                    this->_cfObject = reinterpret_cast< _T_ >( const_cast< void * >( CFRetain( value ) ) );
                }
            }
            
            Object( Object && value ) noexcept
            {
                this->_cfObject = value._cfObject;
                value._cfObject = nullptr;
            }
            
            virtual ~Object( void )
            {
                if( this->_cfObject != nullptr )
                {
                    CFRelease( this->_cfObject );
                    
                    this->_cfObject = nullptr;
                }
            }
            
            Object< _T_ > & operator = ( Object< _T_ > value )
            {
                swap( *( this ), value );
                
                return *( this );
            }
            
            Object< _T_ > & operator = ( const AutoPointer & value )
            {
                return operator =( Object< _T_ >( value ) );
            }
            
            Object< _T_ > & operator = ( _T_ value )
            {
                return operator =( Object< _T_ >( value ) );
            }
            
            virtual CFTypeID GetTypeID( void ) const
            {
                if( this->_cfObject != nullptr )
                {
                    return CFGetTypeID( this->_cfObject );
                }
                
                return 0;
            }
            
            virtual CFTypeRef GetCFObject( void ) const
            {
                return this->_cfObject;
            }
            
            friend void swap( Object< _T_ > & v1, Object< _T_ > & v2 ) noexcept
            {
                using std::swap;
                
                swap( v1._cfObject, v2._cfObject );
            }
            
        protected:
            
            _T_ _cfObject;
    };
}

#endif /* CFPP_OBJECT_H */
