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
 * @file        CFPP-AutoPointer.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ auto-pointer for CF types
 */

#include <CF++.hpp>

namespace CF
{
    AutoPointer::AutoPointer( void ): _cfObject( nullptr )
    {}
    
    AutoPointer::AutoPointer( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            CFRetain( value._cfObject );
        }
        
        this->_cfObject = value._cfObject;
    }
    
    AutoPointer::AutoPointer( CFTypeRef value ): _cfObject( nullptr )
    {
        this->_cfObject = value;
    }
    
    AutoPointer::AutoPointer( AutoPointer && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    AutoPointer::~AutoPointer( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    AutoPointer & AutoPointer::operator = ( AutoPointer value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    AutoPointer & AutoPointer::operator = ( CFTypeRef value )
    {
        return operator =( AutoPointer( value ) );
    }
    
    CFTypeID AutoPointer::GetTypeID( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return 0;
        }
        
        return CFGetTypeID( this->_cfObject );
    }
    
    CFTypeRef AutoPointer::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    void swap( AutoPointer & v1, AutoPointer & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
