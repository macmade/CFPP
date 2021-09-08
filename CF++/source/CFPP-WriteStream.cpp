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
 * @file        CFPP-WriteStream.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFWriteStreamRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    WriteStream::WriteStream( void ): _cfObject( nullptr )
    {}
    
    WriteStream::WriteStream( URL url ): _cfObject( nullptr )
    {
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
    }
    
    WriteStream::WriteStream( const std::string & path ): _cfObject( nullptr )
    {
        URL url;
        
        url = URL::FileSystemURL( path );
        
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
    }
    
    WriteStream::WriteStream( const char * path ): _cfObject( nullptr )
    {
        URL url;
        
        url = URL::FileSystemURL( path );
        
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
    }
    
    WriteStream::WriteStream( const WriteStream & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value._cfObject ) ) );
        }
    }
    
    WriteStream::WriteStream( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    WriteStream::WriteStream( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    WriteStream::WriteStream( CFWriteStreamRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    WriteStream::WriteStream( std::nullptr_t ): WriteStream( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    WriteStream::WriteStream( WriteStream && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    WriteStream::~WriteStream( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    WriteStream & WriteStream::operator = ( WriteStream value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    WriteStream & WriteStream::operator = ( const AutoPointer & value )
    {
        return operator =( WriteStream( value ) );
    }
    
    WriteStream & WriteStream::operator = ( CFTypeRef value )
    {
        return operator =( WriteStream( value ) );
    }
    
    WriteStream & WriteStream::operator = ( CFWriteStreamRef value )
    {
        return operator =( WriteStream( value ) );
    }
    
    WriteStream & WriteStream::operator = ( std::nullptr_t )
    {
        return operator =( WriteStream( nullptr ) );
    }
    
    CFTypeID WriteStream::GetTypeID( void ) const
    {
        return CFWriteStreamGetTypeID();
    }
    
    CFTypeRef WriteStream::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    bool WriteStream::Open( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFWriteStreamOpen( this->_cfObject ) ) ? true : false;
    }
    
    bool WriteStream::Open( const std::string & path )
    {
        return this->Open( URL::FileSystemURL( path ) );
    }
    
    bool WriteStream::Open( const char * path )
    {
        return this->Open( URL::FileSystemURL( path ) );
    }
    
    bool WriteStream::Open( const URL & url )
    {
        if( this->_cfObject != nullptr )
        {
            this->Close();
            
            CFRelease( this->_cfObject );
        }
        
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
        
        return this->Open();
    }
    
    void WriteStream::Close( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFWriteStreamClose( this->_cfObject );
    }
    
    bool WriteStream::CanAcceptBytes( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFWriteStreamCanAcceptBytes( this->_cfObject ) ) ? true : false;
    }
    
    CFStreamStatus WriteStream::GetStatus( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return kCFStreamStatusError;
        }
        
        return CFWriteStreamGetStatus( this->_cfObject );
    }
    
    Error WriteStream::GetError( void ) const
    {
        AutoPointer e;
        
        if( this->_cfObject == nullptr )
        {
            return e.As< CFErrorRef >();
        }
        
        e = CFWriteStreamCopyError( this->_cfObject );
        
        return e.As< CFErrorRef >();
    }
    
    CFIndex WriteStream::Write( const Data::Byte * buffer, CFIndex length ) const
    {
        if( this->_cfObject == nullptr )
        {
            return -1;
        }
        
        if( buffer == nullptr || length <= 0 )
        {
            return -1;
        }
        
        return CFWriteStreamWrite( this->_cfObject, buffer, length );
    }
    
    CFIndex WriteStream::Write( const Data & data ) const
    {
        return this->Write( data.GetBytePtr(), data.GetLength() );
    }
    
    bool WriteStream::WriteAll( const Data::Byte * buffer, CFIndex length ) const
    {
        CFIndex written;
        
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        if( buffer == nullptr || length <= 0 )
        {
            return false;
        }
        
        while( 1 )
        {
            written = CFWriteStreamWrite( this->_cfObject, buffer, length );
            
            if( written < 0 )
            {
                return false;
            }
            else if( written == 0 )
            {
                return this->GetStatus() == kCFStreamStatusAtEnd;
            }
            else if( written == length )
            {
                return true;
            }
            
            length -= written;
            buffer += written;
            
            if( length < 0 )
            {
                return false;
            }
        }
    }
    
    bool WriteStream::WriteAll( const Data & data ) const
    {
        return this->WriteAll( data.GetBytePtr(), data.GetLength() );
    }
    
    AutoPointer WriteStream::GetProperty( const String & name )
    {
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        return CFWriteStreamCopyProperty( this->_cfObject, name );
    }
    
    bool WriteStream::SetProperty( const String & name, CFTypeRef value )
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFWriteStreamSetProperty( this->_cfObject, name, value ) ) ? true : false;
    }
    
    bool WriteStream::SetClient( CFOptionFlags events, CFWriteStreamClientCallBack callback, CFStreamClientContext * context )
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFWriteStreamSetClient( this->_cfObject, events, callback, context ) ) ? true : false;
    }
    
    void WriteStream::ScheduleWithRunLoop( CFRunLoopRef runLoop, CF::String mode )
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFWriteStreamScheduleWithRunLoop( this->_cfObject, runLoop, mode );
    }
    
    void WriteStream::UnscheduleFromRunLoop( CFRunLoopRef runLoop, CF::String mode )
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFWriteStreamUnscheduleFromRunLoop( this->_cfObject, runLoop, mode );
    }
    
    void swap( WriteStream & v1, WriteStream & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
