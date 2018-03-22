/*******************************************************************************
 * Copyright (c) 2014, Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        CFPP-ReadStream-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Iterator class for CF::ReadStream
 */

#include <CF++.hpp>

#ifdef _WIN32

#include <Windows.h>

static bool        __hasCFStreamProperties             = false;
static CFStringRef __cfStreamPropertyFileCurrentOffset = NULL;

static void __loadCFStreamProperties( void )
{
	HMODULE cfModule;

	if( __hasCFStreamProperties == true )
	{
		return;
	}

	cfModule = GetModuleHandle( L"CoreFoundation.dll" );

	if( cfModule != NULL )
	{
		__hasCFStreamProperties             = true;
		__cfStreamPropertyFileCurrentOffset = *( ( CFStringRef * )GetProcAddress( cfModule, "kCFStreamPropertyFileCurrentOffset" ) );
	}
}

#endif

namespace CF
{
    ReadStream::Iterator::Iterator( void ):
        _cfObject( NULL ),
        _bytesToRead( 0 ),
        _i( 0 ),
        _data( static_cast< CFDataRef >( NULL ) ),
        _end( false )
    {}
    
    ReadStream::Iterator::Iterator( CFReadStreamRef stream, CFIndex bytesToRead, bool end ):
        _cfObject( stream ),
        _bytesToRead( ( bytesToRead > 0 ) ? bytesToRead : 4096 ),
        _i( 0 ),
        _data( static_cast< CFDataRef >( NULL ) ),
        _end( end )
    {
        if( this->_cfObject != NULL )
        {
            CFRetain( this->_cfObject );
            
            this->_Read();
        }
        else
        {
            this->_end = true;
        }
    }
    
    ReadStream::Iterator::Iterator( const Iterator & value ):
        _cfObject( value._cfObject ),
        _bytesToRead( value._bytesToRead ),
        _i( value._i ),
        _data( value._data ),
        _end( value._end )
    {
        if( this->_cfObject != NULL )
        {
            CFRetain( this->_cfObject );
        }
    }

    #ifdef CFPP_HAS_CPP11
    ReadStream::Iterator::Iterator( Iterator && value )
    {
        this->_cfObject     = value._cfObject;
        value._cfObject     = nullptr;
        this->_bytesToRead  = value._bytesToRead;
        value._bytesToRead  = 0;
        this->_i            = value._i;
        value._i            = 0;
        this->_end          = value._end;
        value._end          = false;
        this->_data         = value._data;
        value._data         = static_cast< CFDataRef >( nullptr );
    }
    #endif

    ReadStream::Iterator::~Iterator( void )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
        }
    }

    ReadStream::Iterator & ReadStream::Iterator::operator = ( Iterator value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    ReadStream::Iterator & ReadStream::Iterator::operator ++( void )
    {
        this->_data = static_cast< CFDataRef >( NULL );
        this->_i   += 1;
        
        this->_Read();
        
        return *( this );
    }
    
    ReadStream::Iterator ReadStream::Iterator::operator ++( int )
    {
        Iterator it( *( this ) );
        
        operator++();
        
        return it;
    }

    ReadStream::Iterator & ReadStream::Iterator::operator += ( CFIndex value )
    {
        if( this->_cfObject != NULL )
        {
            this->_data = static_cast< CFDataRef >( NULL );

			#ifdef _WIN32

			__loadCFStreamProperties();

		    if( CFReadStreamSetProperty( this->_cfObject, __cfStreamPropertyFileCurrentOffset, CF::Number( this->_bytesToRead * ( this->_i + value ) ) ) )
			
			#else
            
			if( CFReadStreamSetProperty( this->_cfObject, kCFStreamPropertyFileCurrentOffset, CF::Number( this->_bytesToRead * ( this->_i + value ) ) ) )
			
			#endif
			{
                this->_i += value;
                
                this->_Read();
            }
        }
        
        return *( this );
    }

    ReadStream::Iterator ReadStream::Iterator::operator + ( CFIndex value )
    {
        Iterator i;
        
        i = *( this );
        
        return i += value;
    }

    bool ReadStream::Iterator::operator == ( const Iterator & value ) const
    {
        if( this->_cfObject != value._cfObject )
        {
            return false;
        }
        
        if( this->_end == true && value._end == true )
        {
            return true;
        }
        
        if( this->_bytesToRead != value._bytesToRead )
        {
            return false;
        }
        
        if( this->_i != value._i )
        {
            return false;
        }
        
        if( this->_end != value._end )
        {
            return false;
        }
        
        return true;
    }
    
    bool ReadStream::Iterator::operator != ( const Iterator & value ) const
    {
        return !( *( this ) == value );
    }

    Data ReadStream::Iterator::operator * ( void )
    {
        return this->_data;
    }
    
    ReadStream::Iterator::operator Data ()
    {
        return operator *();
    }
    
    void ReadStream::Iterator::_Read( void )
    {
        UInt8        * buf;
        CFIndex        i;
        CFStreamStatus status;
        
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        if( this->_end == true )
        {
            return;
        }
        
        if( this->_data.IsValid() )
        {
            return;
        }
        
        if( CFReadStreamHasBytesAvailable( this->_cfObject ) == false )
        {
            this->_end = true;
            
            return;
        }
        
        status = CFReadStreamGetStatus( this->_cfObject );
        
        if
        (
               status == kCFStreamStatusNotOpen
            || status == kCFStreamStatusAtEnd
            || status == kCFStreamStatusClosed
            || status == kCFStreamStatusError
        )
        {
            this->_end = true;
            
            return;
        }
        
        buf = new UInt8[ this->_bytesToRead ];
        
        if( buf == NULL )
        {
            return;
        }
        
        i = CFReadStreamRead( this->_cfObject, buf, this->_bytesToRead );
        
        this->_data = CF::Data( buf, i );
        
        delete[] buf;
    }

    void swap( ReadStream::Iterator & v1, ReadStream::Iterator & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject,    v2._cfObject );
        swap( v1._bytesToRead, v2._bytesToRead );
        swap( v1._i,           v2._i );
        swap( v1._data,        v2._data );
        swap( v1._end,         v2._end );
    }
}
