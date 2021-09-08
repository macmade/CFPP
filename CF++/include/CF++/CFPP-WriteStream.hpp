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
 * @header      CFPP-WriteStream.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFWriteStreamRef wrapper
 */

#ifndef CFPP_WRITE_STREAM_H
#define CFPP_WRITE_STREAM_H

namespace CF
{
    class CFPP_EXPORT WriteStream: public Type
    {
        public:
            
            WriteStream( void );
            WriteStream( const std::string & path );
            WriteStream( const char * path );
            WriteStream( URL url );
            WriteStream( const WriteStream & value );
            WriteStream( const AutoPointer & value );
            WriteStream( CFTypeRef value );
            WriteStream( CFWriteStreamRef value );
            WriteStream( std::nullptr_t );
            WriteStream( WriteStream && value ) noexcept;
            
            virtual ~WriteStream( void );
            
            WriteStream & operator = ( WriteStream value );
            WriteStream & operator = ( const AutoPointer & value );
            WriteStream & operator = ( CFTypeRef value );
            WriteStream & operator = ( CFWriteStreamRef value );
            WriteStream & operator = ( std::nullptr_t );
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            bool               Open( void ) const;
            bool               Open( const std::string & path );
            bool               Open( const char * path );
            bool               Open( const URL & url );
            void               Close( void ) const;
            bool               CanAcceptBytes( void ) const;
            CFStreamStatus     GetStatus( void ) const;
            Error              GetError( void ) const;
            CFIndex            Write( const Data::Byte * buffer, CFIndex length ) const;
            CFIndex            Write( const Data & data ) const;
            bool               WriteAll( const Data::Byte * buffer, CFIndex length ) const;
            bool               WriteAll( const Data & data ) const;
            AutoPointer        GetProperty( const String & name );
            bool               SetProperty( const String & name, CFTypeRef value );
            bool               SetClient( CFOptionFlags events, CFWriteStreamClientCallBack callback, CFStreamClientContext * context );
            void               ScheduleWithRunLoop( CFRunLoopRef runLoop, CF::String mode );
            void               UnscheduleFromRunLoop( CFRunLoopRef runLoop, CF::String mode );
            
            friend void swap( WriteStream & v1, WriteStream & v2 ) noexcept;
            
        private:
            
            CFWriteStreamRef _cfObject;
    };
}

#endif /* CFPP_WRITE_STREAM_H */
