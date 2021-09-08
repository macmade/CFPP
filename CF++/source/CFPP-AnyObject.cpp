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
 * @file        CFPP-AnyObject.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ generic container for CF types
 */

#include <CF++.hpp>

namespace CF
{
    AnyObject::AnyObject( void ): _cfObject( nullptr )
    {}
    
    AnyObject::AnyObject( const AnyObject & value ): _cfObject( value._cfObject )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
        }
    }
    
    AnyObject::AnyObject( const AutoPointer & value ): _cfObject( value.GetCFObject() )
    {
        if( this->_cfObject != nullptr )
        {
            CFRetain( this->_cfObject );
        }
    }
    
    AnyObject::AnyObject( CFTypeRef value ): _cfObject( value )
    {
        if( value != nullptr )
        {
            CFRetain( value );
        }
    }
    
    AnyObject::AnyObject( std::nullptr_t ): AnyObject()
    {}
    
    AnyObject::AnyObject( AnyObject && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    AnyObject::~AnyObject( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    AnyObject & AnyObject::operator = ( AnyObject value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    AnyObject & AnyObject::operator = ( const AutoPointer & value )
    {
        return operator =( AnyObject( value ) );
    }
    
    AnyObject & AnyObject::operator = ( CFTypeRef value )
    {
        return operator =( AnyObject( value ) );
    }
    
    AnyObject & AnyObject::operator = ( std::nullptr_t )
    {
        return operator =( AnyObject( nullptr ) );
    }
    
    CFTypeID AnyObject::GetTypeID( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return 0;
        }
        
        return CFGetTypeID( this->_cfObject );
    }
    
    CFTypeRef AnyObject::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    void swap( AnyObject & v1, AnyObject & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
