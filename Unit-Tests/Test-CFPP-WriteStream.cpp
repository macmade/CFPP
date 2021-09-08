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
 * @file        Test-CFPP-WriteStream.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::WriteStream
 */

#include <CF++.hpp>
#include <thread>
#include <chrono>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_WriteStream, CTOR )
{
    CF::WriteStream s;
    
    ASSERT_FALSE( s.IsValid() );
}

TEST( CFPP_WriteStream, CTOR_STDString )
{
    CF::WriteStream s1( std::string( "/etc/hosts" ) );
    CF::WriteStream s2( std::string( "/tmp/com.xs-labs.cfpp" ) );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
}

TEST( CFPP_WriteStream, CTOR_CChar )
{
    CF::WriteStream s1( "/etc/hosts" );
    CF::WriteStream s2( "/tmp/com.xs-labs.cfpp" );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
}

TEST( CFPP_WriteStream, CTOR_URL )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2( CF::URL( "file:///tmp/com.xs-labs.cfpp" ) );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
}

TEST( CFPP_WriteStream, CTOR_AutoPointer )
{
    CF::WriteStream s1( CF::AutoPointer( CFWriteStreamCreateWithFile( nullptr, CF::URL( "file:///etc/hosts" ) ) ) );
    CF::WriteStream s2( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::WriteStream s3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
}

TEST( CFPP_WriteStream, CTOR_CFType )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2( static_cast< CFTypeRef >( s1.GetCFObject() ) );
    CF::WriteStream s3( static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_TRUE(  s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
}

TEST( CFPP_WriteStream, CTOR_CFWriteStream )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2( static_cast< CFWriteStreamRef >( const_cast< void * >( s1.GetCFObject() ) ) );
    CF::WriteStream s3( static_cast< CFWriteStreamRef >( nullptr ) );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_TRUE(  s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
}

TEST( CFPP_WriteStream, CTOR_NullPointer )
{
    CF::WriteStream s( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
}

TEST( CFPP_WriteStream, CCTOR )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2( s1 );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
}

TEST( CFPP_WriteStream, MCTOR )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2( std::move( s1 ) );
    
    ASSERT_FALSE( s1.IsValid() );
    ASSERT_TRUE(  s2.IsValid() );
}

TEST( CFPP_WriteStream, OperatorAssignWriteStream )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2;
    CF::WriteStream s3;
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
    
    s2 = s1;
    
    ASSERT_TRUE( s2.IsValid() );
    
    s2 = s3;
    
    ASSERT_FALSE( s2.IsValid() );
}

TEST( CFPP_WriteStream, OperatorAssignAutoPointer )
{
    CF::WriteStream s1;
    CF::WriteStream s2( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s3( CF::URL( "file:///etc/hosts" ) );
    
    ASSERT_FALSE( s1.IsValid() );
    ASSERT_TRUE(  s2.IsValid() );
    ASSERT_TRUE(  s3.IsValid() );
    
    s1 = CF::AutoPointer( CFWriteStreamCreateWithFile( nullptr, CF::URL( "file:///etc/hosts" ) ) );
    s2 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    s3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
}

TEST( CFPP_WriteStream, OperatorAssignCFType )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2;
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    
    s2 = static_cast< CFTypeRef >( s1.GetCFObject() );
    
    ASSERT_TRUE( s2.IsValid() );
    
    s2 = static_cast< CFTypeRef >( nullptr );
    
    ASSERT_FALSE( s2.IsValid() );
}

TEST( CFPP_WriteStream, OperatorAssignCFWriteStream )
{
    CF::WriteStream s1( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s2;
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    
    s2 = static_cast< CFWriteStreamRef >( const_cast< void * >( s1.GetCFObject() ) );
    
    ASSERT_TRUE( s2.IsValid() );
    
    s2 = static_cast< CFWriteStreamRef >( nullptr );
    
    ASSERT_FALSE( s2.IsValid() );
}

TEST( CFPP_WriteStream, OperatorAssignNullPointer )
{
    CF::WriteStream s( std::string( "/etc/hosts" ) );
    
    ASSERT_TRUE( s.IsValid() );
    
    s = nullptr;
    
    ASSERT_FALSE( s.IsValid() );
}

TEST( CFPP_WriteStream, GetTypeID )
{
    CF::WriteStream s;
    
    ASSERT_EQ( s.GetTypeID(), CFWriteStreamGetTypeID() );
}

TEST( CFPP_WriteStream, GetCFObject )
{
    CF::WriteStream s1;
    CF::WriteStream s2( CF::URL( "file:///etc/hosts" ) );
    CF::WriteStream s3( static_cast< CFWriteStreamRef >( nullptr ) );
    
    ASSERT_TRUE( s1.GetCFObject() == nullptr );
    ASSERT_TRUE( s2.GetCFObject() != nullptr );
    ASSERT_TRUE( s3.GetCFObject() == nullptr );
    ASSERT_EQ( CFGetTypeID( s2.GetCFObject() ), CFWriteStreamGetTypeID() );
}

TEST( CFPP_WriteStream, Open )
{
    CF::WriteStream s1;
    CF::WriteStream s2( std::string( "/etc/hosts" ) );
    CF::WriteStream s3( std::string( "/tmp/com.xs-labs.cfpp" ) );
    
    ASSERT_FALSE( s1.Open() );
    ASSERT_FALSE( s2.Open() );
    ASSERT_TRUE(  s3.Open() );
    
    s1.Close();
    s2.Close();
    s3.Close();
    
    ASSERT_FALSE( s1.Open() );
    ASSERT_FALSE( s2.Open() );
    ASSERT_FALSE( s3.Open() );
}

TEST( CFPP_WriteStream, Open_STDString )
{
    CF::WriteStream s;
    
    ASSERT_FALSE( s.IsValid() );
    ASSERT_FALSE( s.Open( std::string( "/etc/hosts" ) ) );
    ASSERT_TRUE(  s.IsValid() );
    ASSERT_TRUE(  s.Open( std::string( "/tmp/com.xs-labs.cfpp" ) ) );
    ASSERT_TRUE(  s.IsValid() );
    
    s.Close();
}

TEST( CFPP_WriteStream, Open_CChar )
{
    CF::WriteStream s;
    
    ASSERT_FALSE( s.IsValid() );
    ASSERT_FALSE( s.Open( "/etc/hosts" ) );
    ASSERT_TRUE(  s.IsValid() );
    ASSERT_TRUE(  s.Open( "/tmp/com.xs-labs.cfpp" ) );
    ASSERT_TRUE(  s.IsValid() );
    
    s.Close();
}

TEST( CFPP_WriteStream, Open_URL )
{
    CF::WriteStream s;
    
    ASSERT_FALSE( s.IsValid() );
    ASSERT_FALSE( s.Open( CF::URL( "file:///etc/hosts" ) ) );
    ASSERT_TRUE(  s.IsValid() );
    ASSERT_TRUE(  s.Open( CF::URL( "file:///tmp/com.xs-labs.cfpp" ) ) );
    ASSERT_TRUE(  s.IsValid() );
    
    s.Close();
}

TEST( CFPP_WriteStream, Close )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_NO_FATAL_FAILURE( s1.Close() );
    ASSERT_NO_FATAL_FAILURE( s2.Close() );
    ASSERT_NO_FATAL_FAILURE( s3.Close() );
    
    ASSERT_NO_THROW( s1.Close() );
    ASSERT_NO_THROW( s2.Close() );
    ASSERT_NO_THROW( s3.Close() );
}

TEST( CFPP_WriteStream, CanAcceptBytes )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    
    ASSERT_FALSE( s1.CanAcceptBytes() );
    ASSERT_FALSE( s2.CanAcceptBytes() );
    ASSERT_FALSE( s3.CanAcceptBytes() );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_FALSE( s1.CanAcceptBytes() );
    ASSERT_FALSE( s2.CanAcceptBytes() );
    ASSERT_TRUE(  s3.CanAcceptBytes() );
    
    s1.Close();
    s2.Close();
    s3.Close();
}

TEST( CFPP_WriteStream, GetStatus )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    
    ASSERT_TRUE( s1.GetStatus() == kCFStreamStatusError );
    ASSERT_TRUE( s2.GetStatus() == kCFStreamStatusNotOpen );
    ASSERT_TRUE( s3.GetStatus() == kCFStreamStatusNotOpen );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_TRUE( s1.GetStatus() == kCFStreamStatusError );
    ASSERT_TRUE( s2.GetStatus() == kCFStreamStatusError );
    ASSERT_TRUE( s3.GetStatus() == kCFStreamStatusOpen );
    
    s1.Close();
    s2.Close();
    s3.Close();
    
    ASSERT_TRUE( s1.GetStatus() == kCFStreamStatusError );
    ASSERT_TRUE( s2.GetStatus() == kCFStreamStatusError );
    ASSERT_TRUE( s3.GetStatus() == kCFStreamStatusClosed );
}

TEST( CFPP_WriteStream, GetError )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    
    ASSERT_EQ( s1.GetError().GetCode(), 0 );
    ASSERT_EQ( s2.GetError().GetCode(), 0 );
    ASSERT_EQ( s3.GetError().GetCode(), 0 );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_EQ( s1.GetError().GetCode(), 0 );
    ASSERT_NE( s2.GetError().GetCode(), 0 );
    ASSERT_EQ( s3.GetError().GetCode(), 0 );
    
    s1.Close();
    s2.Close();
    s3.Close();
}

TEST( CFPP_WriteStream, Write_BytePtr_CFIndex )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    CF::Data::Byte  buf[ 4 ];
    
    buf[ 0 ] = 0xDE;
    buf[ 1 ] = 0xAD;
    buf[ 2 ] = 0xBE;
    buf[ 3 ] = 0xEF;
    
    ASSERT_EQ( s1.Write( buf, sizeof( buf ) ), -1 );
    ASSERT_EQ( s2.Write( buf, sizeof( buf ) ), -1 );
    ASSERT_EQ( s3.Write( buf, sizeof( buf ) ), -1 );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_EQ( s1.Write( buf, sizeof( buf ) ), -1 );
    ASSERT_EQ( s2.Write( buf, sizeof( buf ) ), -1 );
    ASSERT_GE( s3.Write( buf, sizeof( buf ) ),  0 );
    
    ASSERT_NO_FATAL_FAILURE( s1.Write( nullptr, sizeof( buf ) ) );
    ASSERT_NO_FATAL_FAILURE( s2.Write( nullptr, sizeof( buf ) ) );
    ASSERT_NO_FATAL_FAILURE( s3.Write( nullptr, sizeof( buf ) ) );
    
    ASSERT_NO_THROW( s1.Write( nullptr, sizeof( buf ) ) );
    ASSERT_NO_THROW( s2.Write( nullptr, sizeof( buf ) ) );
    ASSERT_NO_THROW( s3.Write( nullptr, sizeof( buf ) ) );
    
    ASSERT_EQ( s1.Write( nullptr, sizeof( buf ) ), -1 );
    ASSERT_EQ( s2.Write( nullptr, sizeof( buf ) ), -1 );
    ASSERT_EQ( s3.Write( nullptr, sizeof( buf ) ), -1 );
    
    s1.Close();
    s2.Close();
    s3.Close();
    
    ASSERT_EQ( s1.Write( buf, sizeof( buf ) ), -1 );
    ASSERT_EQ( s2.Write( buf, sizeof( buf ) ), -1 );
    ASSERT_EQ( s3.Write( buf, sizeof( buf ) ), -1 );
}

TEST( CFPP_WriteStream, Write_Data )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    CF::Data::Byte  buf[ 4 ];
    CF::Data        d;
    
    buf[ 0 ] = 0xDE;
    buf[ 1 ] = 0xAD;
    buf[ 2 ] = 0xBE;
    buf[ 3 ] = 0xEF;
    
    d = CF::Data( buf, sizeof( buf ) );
    
    ASSERT_EQ( s1.Write( d ), -1 );
    ASSERT_EQ( s2.Write( d ), -1 );
    ASSERT_EQ( s3.Write( d ), -1 );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_EQ( s1.Write( d ), -1 );
    ASSERT_EQ( s2.Write( d ), -1 );
    ASSERT_GE( s3.Write( d ),  0 );
    
    s1.Close();
    s2.Close();
    s3.Close();
    
    ASSERT_EQ( s1.Write( d ), -1 );
    ASSERT_EQ( s2.Write( d ), -1 );
    ASSERT_EQ( s3.Write( d ), -1 );
}

TEST( CFPP_WriteStream, WriteAll_BytePtr_CFIndex )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    CF::Data::Byte  buf[ 4 ];
    
    buf[ 0 ] = 0xDE;
    buf[ 1 ] = 0xAD;
    buf[ 2 ] = 0xBE;
    buf[ 3 ] = 0xEF;
    
    ASSERT_FALSE( s1.WriteAll( buf, sizeof( buf ) ) );
    ASSERT_FALSE( s2.WriteAll( buf, sizeof( buf ) ) );
    ASSERT_FALSE( s3.WriteAll( buf, sizeof( buf ) ) );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_FALSE( s1.WriteAll( buf, sizeof( buf ) ) );
    ASSERT_FALSE( s2.WriteAll( buf, sizeof( buf ) ) );
    ASSERT_TRUE(  s3.WriteAll( buf, sizeof( buf ) ) );
    
    ASSERT_NO_FATAL_FAILURE( s1.WriteAll( nullptr, sizeof( buf ) ) );
    ASSERT_NO_FATAL_FAILURE( s2.WriteAll( nullptr, sizeof( buf ) ) );
    ASSERT_NO_FATAL_FAILURE( s3.WriteAll( nullptr, sizeof( buf ) ) );
    
    ASSERT_NO_THROW( s1.WriteAll( nullptr, sizeof( buf ) ) );
    ASSERT_NO_THROW( s2.WriteAll( nullptr, sizeof( buf ) ) );
    ASSERT_NO_THROW( s3.WriteAll( nullptr, sizeof( buf ) ) );
    
    ASSERT_FALSE( s1.WriteAll( nullptr, sizeof( buf ) ) );
    ASSERT_FALSE( s2.WriteAll( nullptr, sizeof( buf ) ) );
    ASSERT_FALSE( s3.WriteAll( nullptr, sizeof( buf ) ) );
    
    s1.Close();
    s2.Close();
    s3.Close();
    
    ASSERT_FALSE( s1.WriteAll( buf, sizeof( buf ) ) );
    ASSERT_FALSE( s2.WriteAll( buf, sizeof( buf ) ) );
    ASSERT_FALSE( s3.WriteAll( buf, sizeof( buf ) ) );
}

TEST( CFPP_WriteStream, WriteAll_Data )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    CF::Data::Byte  buf[ 4 ];
    CF::Data        d;
    
    buf[ 0 ] = 0xDE;
    buf[ 1 ] = 0xAD;
    buf[ 2 ] = 0xBE;
    buf[ 3 ] = 0xEF;
    
    d = CF::Data( buf, sizeof( buf ) );
    
    ASSERT_FALSE( s1.WriteAll( d ) );
    ASSERT_FALSE( s2.WriteAll( d ) );
    ASSERT_FALSE( s3.WriteAll( d ) );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_FALSE( s1.WriteAll( d ) );
    ASSERT_FALSE( s2.WriteAll( d ) );
    ASSERT_TRUE(  s3.WriteAll( d ) );
    
    s1.Close();
    s2.Close();
    s3.Close();
    
    ASSERT_FALSE( s1.WriteAll( d ) );
    ASSERT_FALSE( s2.WriteAll( d ) );
    ASSERT_FALSE( s3.WriteAll( d ) );
}

TEST( CFPP_WriteStream, GetProperty )
{
    CF::WriteStream s1;
    CF::WriteStream s2( "/etc/hosts" );
    CF::WriteStream s3( "/tmp/com.xs-labs.cfpp" );
    CF::AutoPointer p1;
    CF::AutoPointer p2;
    CF::AutoPointer p3;
    
    p1 = s1.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p2 = s2.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p3 = s3.GetProperty( kCFStreamPropertyFileCurrentOffset );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p2.IsValid() );
    ASSERT_FALSE( p3.IsValid() );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    p1 = s1.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p2 = s2.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p3 = s3.GetProperty( kCFStreamPropertyFileCurrentOffset );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p2.IsValid() );
    ASSERT_TRUE(  p3.IsValid() );
    ASSERT_TRUE(  p3.IsNumber() );
    
    s1.Close();
    s2.Close();
    s3.Close();
}

TEST( CFPP_WriteStream, SetProperty )
{
    CF::WriteStream  s1;
    CF::WriteStream  s2( "/etc/hosts" );
    CF::WriteStream  s3( "/tmp/com.xs-labs.cfpp" );
    CF::AutoPointer p1;
    CF::AutoPointer p2;
    CF::AutoPointer p3;
    
    p1 = s1.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p2 = s2.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p3 = s3.GetProperty( kCFStreamPropertyFileCurrentOffset );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p2.IsValid() );
    ASSERT_FALSE( p3.IsValid() );
    
    s1.Open();
    s2.Open();
    s3.Open();
    
    ASSERT_FALSE( s1.SetProperty( kCFStreamPropertyFileCurrentOffset, CF::Number( 42 ) ) );
    ASSERT_TRUE(  s2.SetProperty( kCFStreamPropertyFileCurrentOffset, CF::Number( 42 ) ) );
    ASSERT_TRUE(  s3.SetProperty( kCFStreamPropertyFileCurrentOffset, CF::Number( 42 ) ) );
    
    p1 = s1.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p2 = s2.GetProperty( kCFStreamPropertyFileCurrentOffset );
    p3 = s3.GetProperty( kCFStreamPropertyFileCurrentOffset );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_TRUE(  p2.IsValid() );
    ASSERT_TRUE(  p3.IsValid() );
    
    ASSERT_TRUE( p2.IsNumber() );
    ASSERT_TRUE( p3.IsNumber() );
    
    ASSERT_EQ( p2.As< CF::Number >(), 42 );
    ASSERT_EQ( p3.As< CF::Number >(), 42 );
    
    s1.Close();
    s2.Close();
    s3.Close();
}

static bool __client1 = false;
static bool __client2 = false;
static bool __client3 = false;

void __ClientCallback( CFWriteStreamRef stream, CFStreamEventType type, void * info );
void __ClientCallback( CFWriteStreamRef stream, CFStreamEventType type, void * info )
{
    ( void )stream;
    ( void )type;
    
    if( info != nullptr )
    {
        *( reinterpret_cast< bool * >( info ) ) = true;
    }
}

TEST( CFPP_WriteStream, SetClient )
{
    CF::WriteStream        s1;
    CF::WriteStream        s2( "/etc/hosts" );
    CF::WriteStream        s3( "/tmp/com.xs-labs.cfpp" );
    CFStreamClientContext ctx1;
    CFStreamClientContext ctx2;
    CFStreamClientContext ctx3;
    
    memset( &ctx1, 0, sizeof( CFStreamClientContext ) );
    memset( &ctx2, 0, sizeof( CFStreamClientContext ) );
    memset( &ctx3, 0, sizeof( CFStreamClientContext ) );
    
    ctx1.info = &__client1;
    ctx2.info = &__client2;
    ctx3.info = &__client3;
    
    ASSERT_FALSE( s1.SetClient( kCFStreamEventOpenCompleted, __ClientCallback, &ctx1 ) );
    ASSERT_TRUE(  s2.SetClient( kCFStreamEventOpenCompleted, __ClientCallback, &ctx2 ) );
    ASSERT_TRUE(  s3.SetClient( kCFStreamEventOpenCompleted, __ClientCallback, &ctx3 ) );
    
    s1.ScheduleWithRunLoop( CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    s2.ScheduleWithRunLoop( CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    s3.ScheduleWithRunLoop( CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    
    {
        CFRunLoopRef rl;
        
        rl = CFRunLoopGetCurrent();
        
        std::thread t
        (
            [ s1, s2, s3, rl ] ()
            {
                std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
                
                s1.Open();
                s2.Open();
                s3.Open();
                
                std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
                
                CFRunLoopStop( rl );
            }
        );
        
        t.detach();
    }
    
    CFRunLoopRun();
    
    ASSERT_FALSE( __client1 );
    ASSERT_FALSE( __client2 );
    ASSERT_TRUE(  __client3 );
    
    s1.UnscheduleFromRunLoop( CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    s2.UnscheduleFromRunLoop( CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    s3.UnscheduleFromRunLoop( CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    
    s1.Close();
    s2.Close();
    s3.Close();
}

TEST( CFPP_WriteStream, Swap )
{
    CF::WriteStream s1( "/etc/hosts" );
    CF::WriteStream s2( "/tmp/com.xs-labs.cfpp" );
    
    s1.Open();
    s2.Open();
    
    ASSERT_TRUE( s1.GetStatus() == kCFStreamStatusError );
    ASSERT_TRUE( s2.GetStatus() == kCFStreamStatusOpen );
    
    swap( s1, s2 );
    
    ASSERT_TRUE( s1.GetStatus() == kCFStreamStatusOpen );
    ASSERT_TRUE( s2.GetStatus() == kCFStreamStatusError );
    
    s1.Close();
    s2.Close();
}
