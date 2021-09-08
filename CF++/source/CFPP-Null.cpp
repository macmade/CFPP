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
 * @file        CFPP-Null.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFNullRef wrapper
 */

#include <CF++.hpp>

#ifdef _WIN32

#include <Windows.h>

static bool      __hasCFNull = false;
static CFNullRef __cfNull    = nullptr;

static void __loadCFNull( void )
{
    HMODULE cfModule;

    if( __hasCFNull == true )
    {
        return;
    }

    cfModule = GetModuleHandle( L"CoreFoundation.dll" );

    if( cfModule != nullptr )
    {
        __hasCFNull = true;
        __cfNull    = *( ( CFNullRef * )GetProcAddress( cfModule, "kCFNull" ) );
    }
}

#endif

namespace CF
{
    Null::Null( void ): _cfObject( nullptr )
    {
        #ifdef _WIN32
        
        __loadCFNull();
        
        this->_cfObject = __cfNull;
        
        #else
        
        this->_cfObject = kCFNull;
        
        #endif
    }
    
    Null::Null( const Null & value ): _cfObject( value._cfObject )
    {}
    
    Null::Null( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            _cfObject = static_cast< CFNullRef >( value );
        }
    }
    
    Null::Null( Null && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    Null::~Null( void )
    {}
    
    Null & Null::operator = ( Null value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Null & Null::operator = ( CFTypeRef value )
    {
        return operator =( Null( value ) );
    }
    
    CFTypeID Null::GetTypeID( void ) const
    {
        return CFNullGetTypeID();
    }
    
    CFTypeRef Null::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    void swap( Null & v1, Null & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
