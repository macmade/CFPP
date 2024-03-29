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
 * @file        Test-CFPP-URL.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::URL
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

#ifdef GetUserName
#undef GetUserName
#endif

TEST( CFPP_URL, FileSystemURL_STDString )
{
    CF::URL u1 = CF::URL::FileSystemURL( std::string( "/etc/hosts" ) );
    CF::URL u2 = CF::URL::FileSystemURL( std::string( "/foo/bar" ) );
    CF::URL u3 = CF::URL::FileSystemURL( std::string( "" ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_URL, FileSystemURL_CChar )
{
    CF::URL u1 = CF::URL::FileSystemURL( "/etc/hosts" );
    CF::URL u2 = CF::URL::FileSystemURL( "/foo/bar" );
    CF::URL u3 = CF::URL::FileSystemURL( "" );
    CF::URL u4 = CF::URL::FileSystemURL( static_cast< const char * >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
}

TEST( CFPP_URL, FileSystemURL_CFType )
{
    CF::URL u1 = CF::URL::FileSystemURL( static_cast< CFTypeRef >( CF::String( "/etc/hosts" ) ) );
    CF::URL u2 = CF::URL::FileSystemURL( static_cast< CFTypeRef >( CF::String( "/foo/bar" ) ) );
    CF::URL u3 = CF::URL::FileSystemURL( static_cast< CFTypeRef >( CF::String( "" ) ) );
    CF::URL u4 = CF::URL::FileSystemURL( static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
}

TEST( CFPP_URL, FileSystemURL_CFString )
{
    CF::URL u1 = CF::URL::FileSystemURL( static_cast< CFStringRef >( CF::String( "/etc/hosts" ) ) );
    CF::URL u2 = CF::URL::FileSystemURL( static_cast< CFStringRef >( CF::String( "/foo/bar" ) ) );
    CF::URL u3 = CF::URL::FileSystemURL( static_cast< CFStringRef >( CF::String( "" ) ) );
    CF::URL u4 = CF::URL::FileSystemURL( static_cast< CFStringRef >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
}

TEST( CFPP_URL, CTOR )
{
    CF::URL u;
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_URL, CTOR_AutoPointer )
{
    CF::URL u1( CF::AutoPointer( CFURLCreateWithFileSystemPath( nullptr, CF::String( "/etc/hosts" ), kCFURLPOSIXPathStyle, false ) ) );
    CF::URL u2( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::URL u3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_URL, CTOR_CFType )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2( static_cast< CFTypeRef >( u1.GetCFObject() ) );
    CF::URL u3( static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_URL, CTOR_CFURL )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2( static_cast< CFURLRef >( u1.GetCFObject() ) );
    CF::URL u3( static_cast< CFURLRef >( nullptr ) );
    
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_URL, CTOR_CFString )
{
    CF::URL u1( static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) ) );
    CF::URL u2( static_cast< CFStringRef >( CF::String( "" ) ) );
    CF::URL u3( static_cast< CFStringRef >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_URL, CTOR_CFString_URL )
{
    CF::URL base( "http://www.xs-labs.com/" );
    CF::URL u1( static_cast< CFStringRef >( CF::String( "foobar" ) ), base );
    CF::URL u2( static_cast< CFStringRef >( CF::String( "foobar" ) ), CF::URL( nullptr ) );
    CF::URL u3( static_cast< CFStringRef >( CF::String( "" ) ), base );
    CF::URL u4( static_cast< CFStringRef >( nullptr ), base );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    
    ASSERT_TRUE(  u1.GetBaseURL().IsValid() );
    ASSERT_FALSE( u2.GetBaseURL().IsValid() );
    ASSERT_FALSE( u3.GetBaseURL().IsValid() );
    ASSERT_FALSE( u4.GetBaseURL().IsValid() );
    
    ASSERT_EQ( u1.GetBaseURL(), base );
}

TEST( CFPP_URL, CTOR_NullPointer )
{
    CF::URL u( nullptr );
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_URL, CTOR_STDString )
{
    CF::URL u1( std::string( "http://www.xs-labs.com/" ) );
    CF::URL u2( std::string( "" ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
}

TEST( CFPP_URL, CTOR_STDString_URL )
{
    CF::URL base( "http://www.xs-labs.com/" );
    CF::URL u1( std::string( "foobar" ), base );
    CF::URL u2( std::string( "foobar" ), CF::URL( nullptr ) );
    CF::URL u3( std::string( "" ), base );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    
    ASSERT_TRUE(  u1.GetBaseURL().IsValid() );
    ASSERT_FALSE( u2.GetBaseURL().IsValid() );
    ASSERT_FALSE( u3.GetBaseURL().IsValid() );
    
    ASSERT_EQ( u1.GetBaseURL(), base );
}

TEST( CFPP_URL, CTOR_CChar )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2( "" );
    CF::URL u3( static_cast< const char * >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_URL, CTOR_CChar_URL )
{
    CF::URL base( "http://www.xs-labs.com/" );
    CF::URL u1( "foobar", base );
    CF::URL u2( "foobar", CF::URL( nullptr ) );
    CF::URL u3( "", base );
    CF::URL u4( static_cast< const char * >( nullptr ), base );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    
    ASSERT_TRUE(  u1.GetBaseURL().IsValid() );
    ASSERT_FALSE( u2.GetBaseURL().IsValid() );
    ASSERT_FALSE( u3.GetBaseURL().IsValid() );
    ASSERT_FALSE( u4.GetBaseURL().IsValid() );
    
    ASSERT_EQ( u1.GetBaseURL(), base );
}

TEST( CFPP_URL, CCTOR )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2( u1 );
    CF::URL u3( static_cast< const char * >( nullptr ) );
    CF::URL u4( u3 );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
}

TEST( CFPP_URL, MCTOR )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2( std::move( u1 ) );
    
    ASSERT_FALSE( u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
}

TEST( CFPP_URL, OperatorAssignURL )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    CF::URL u3( static_cast< const char * >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    
    u2 = u1;
    
    ASSERT_TRUE( u2.IsValid() );
    
    u2 = u3;
    
    ASSERT_FALSE( u2.IsValid() );
}

TEST( CFPP_URL, OperatorAssignAutoPointer )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.com/" );
    
    ASSERT_FALSE( u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_TRUE(  u3.IsValid() );
    
    u1 = CF::AutoPointer( CFURLCreateWithFileSystemPath( nullptr, CF::String( "/etc/hosts" ), kCFURLPOSIXPathStyle, false ) );
    u2 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    u3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_URL, OperatorAssignCFType )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    CF::URL u3( static_cast< const char * >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    
    u2 = static_cast< CFTypeRef >( u1.GetCFObject() );
    
    ASSERT_TRUE( u2.IsValid() );
    
    u2 = static_cast< CFTypeRef >( u3.GetCFObject() );
    
    ASSERT_FALSE( u2.IsValid() );
}

TEST( CFPP_URL, OperatorAssignCFURL )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    CF::URL u3( static_cast< const char * >( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    
    u2 = static_cast< CFURLRef >( u1.GetCFObject() );
    
    ASSERT_TRUE( u2.IsValid() );
    
    u2 = static_cast< CFURLRef >( u3.GetCFObject() );
    
    ASSERT_FALSE( u2.IsValid() );
}

TEST( CFPP_URL, OperatorAssignCFString )
{
    CF::URL u;
    
    ASSERT_FALSE( u.IsValid() );
    
    u = static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) );
    
    ASSERT_TRUE( u.IsValid() );
    
    u = static_cast< CFStringRef >( CF::String( "" ) );
    
    ASSERT_FALSE( u.IsValid() );
    
    u = static_cast< CFStringRef >( nullptr );
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_URL, OperatorAssignNullPointer )
{
    CF::URL u( "http://www.xs-labs.com/" );
    
    ASSERT_TRUE( u.IsValid() );
    
    u = nullptr;
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_URL, OperatorAssignSTDString )
{
    CF::URL u;
    
    ASSERT_FALSE( u.IsValid() );
    
    u = std::string( "http://www.xs-labs.com/" );
    
    ASSERT_TRUE( u.IsValid() );
    
    u = std::string( "" );
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_URL, OperatorAssignCChar )
{
    CF::URL u;
    
    ASSERT_FALSE( u.IsValid() );
    
    u = "http://www.xs-labs.com/";
    
    ASSERT_TRUE( u.IsValid() );
    
    u = "";
    
    ASSERT_FALSE( u.IsValid() );
    
    u = static_cast< const char * >( nullptr );
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_URL, OperatorEqualURL )
{
    CF::URL u1;
    CF::URL u2;
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/" );
    CF::URL u5( "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u1 == u1 );
    ASSERT_FALSE( u1 == u2 );
    ASSERT_FALSE( u1 == u3 );
    ASSERT_FALSE( u1 == u4 );
    ASSERT_FALSE( u1 == u5 );
    
    ASSERT_FALSE( u3 == u1 );
    ASSERT_FALSE( u3 == u2 );
    ASSERT_TRUE(  u3 == u3 );
    ASSERT_TRUE(  u3 == u4 );
    ASSERT_FALSE( u3 == u5 );
    
    ASSERT_FALSE( u5 == u1 );
    ASSERT_FALSE( u5 == u2 );
    ASSERT_FALSE( u5 == u3 );
    ASSERT_FALSE( u5 == u4 );
    ASSERT_TRUE(  u5 == u5 );
}

TEST( CFPP_URL, OperatorEqualCFType )
{
    CF::URL u1;
    CF::URL u2;
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/" );
    CF::URL u5( "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u1 == static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFTypeRef >( u5.GetCFObject() ) );
    
    ASSERT_FALSE( u3 == static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u3 == static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_TRUE(  u3 == static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_TRUE(  u3 == static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u3 == static_cast< CFTypeRef >( u5.GetCFObject() ) );
    
    ASSERT_FALSE( u5 == static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u5 == static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u5 == static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u5 == static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_TRUE(  u5 == static_cast< CFTypeRef >( u5.GetCFObject() ) );
}

TEST( CFPP_URL, OperatorEqualCFURL )
{
    CF::URL u1;
    CF::URL u2;
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/" );
    CF::URL u5( "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u1 == static_cast< CFURLRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFURLRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFURLRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFURLRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFURLRef >( u5.GetCFObject() ) );
    
    ASSERT_FALSE( u3 == static_cast< CFURLRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u3 == static_cast< CFURLRef >( u2.GetCFObject() ) );
    ASSERT_TRUE(  u3 == static_cast< CFURLRef >( u3.GetCFObject() ) );
    ASSERT_TRUE(  u3 == static_cast< CFURLRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u3 == static_cast< CFURLRef >( u5.GetCFObject() ) );
    
    ASSERT_FALSE( u5 == static_cast< CFURLRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u5 == static_cast< CFURLRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u5 == static_cast< CFURLRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u5 == static_cast< CFURLRef >( u4.GetCFObject() ) );
    ASSERT_TRUE(  u5 == static_cast< CFURLRef >( u5.GetCFObject() ) );
}

TEST( CFPP_URL, OperatorEqualCFString )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u1 == static_cast< CFStringRef >( CF::String( "" ) ) );
    ASSERT_FALSE( u1 == static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) ) );
    ASSERT_FALSE( u1 == static_cast< CFStringRef >( CF::String( "http://www.xs-labs.org/" ) ) );
    
    ASSERT_FALSE( u2 == static_cast< CFStringRef >( CF::String( "" ) ) );
    ASSERT_TRUE(  u2 == static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) ) );
    ASSERT_FALSE( u2 == static_cast< CFStringRef >( CF::String( "http://www.xs-labs.org/" ) ) );
    
    ASSERT_FALSE( u3 == static_cast< CFStringRef >( CF::String( "" ) ) );
    ASSERT_FALSE( u3 == static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) ) );
    ASSERT_TRUE(  u3 == static_cast< CFStringRef >( CF::String( "http://www.xs-labs.org/" ) ) );
}

TEST( CFPP_URL, OperatorEqualSTDString )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u1 == std::string( "" ) );
    ASSERT_FALSE( u1 == std::string( "http://www.xs-labs.com/" ) );
    ASSERT_FALSE( u1 == std::string( "http://www.xs-labs.org/" ) );
    
    ASSERT_FALSE( u2 == std::string( "" ) );
    ASSERT_TRUE(  u2 == std::string( "http://www.xs-labs.com/" ) );
    ASSERT_FALSE( u2 == std::string( "http://www.xs-labs.org/" ) );
    
    ASSERT_FALSE( u3 == std::string( "" ) );
    ASSERT_FALSE( u3 == std::string( "http://www.xs-labs.com/" ) );
    ASSERT_TRUE(  u3 == std::string( "http://www.xs-labs.org/" ) );
}

TEST( CFPP_URL, OperatorEqualCChar )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u1 == "" );
    ASSERT_FALSE( u1 == "http://www.xs-labs.com/" );
    ASSERT_FALSE( u1 == "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u2 == "" );
    ASSERT_TRUE(  u2 == "http://www.xs-labs.com/" );
    ASSERT_FALSE( u2 == "http://www.xs-labs.org/" );
    
    ASSERT_FALSE( u3 == "" );
    ASSERT_FALSE( u3 == "http://www.xs-labs.com/" );
    ASSERT_TRUE(  u3 == "http://www.xs-labs.org/" );
}

TEST( CFPP_URL, OperatorNotEqualURL )
{
    CF::URL u1;
    CF::URL u2;
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/" );
    CF::URL u5( "http://www.xs-labs.org/" );
    
    ASSERT_TRUE( u1 != u1 );
    ASSERT_TRUE( u1 != u2 );
    ASSERT_TRUE( u1 != u3 );
    ASSERT_TRUE( u1 != u4 );
    ASSERT_TRUE( u1 != u5 );
    
    ASSERT_TRUE(  u3 != u1 );
    ASSERT_TRUE(  u3 != u2 );
    ASSERT_FALSE( u3 != u3 );
    ASSERT_FALSE( u3 != u4 );
    ASSERT_TRUE(  u3 != u5 );
    
    ASSERT_TRUE(  u5 != u1 );
    ASSERT_TRUE(  u5 != u2 );
    ASSERT_TRUE(  u5 != u3 );
    ASSERT_TRUE(  u5 != u4 );
    ASSERT_FALSE( u5 != u5 );
}

TEST( CFPP_URL, OperatorNotEqualCFType )
{
    CF::URL u1;
    CF::URL u2;
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/" );
    CF::URL u5( "http://www.xs-labs.org/" );
    
    ASSERT_TRUE( u1 != static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFTypeRef >( u5.GetCFObject() ) );
    
    ASSERT_TRUE(  u3 != static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_TRUE(  u3 != static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u3 != static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u3 != static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_TRUE(  u3 != static_cast< CFTypeRef >( u5.GetCFObject() ) );
    
    ASSERT_TRUE(  u5 != static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_TRUE(  u5 != static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_TRUE(  u5 != static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_TRUE(  u5 != static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u5 != static_cast< CFTypeRef >( u5.GetCFObject() ) );
}

TEST( CFPP_URL, OperatorNotEqualCFURL )
{
    CF::URL u1;
    CF::URL u2;
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/" );
    CF::URL u5( "http://www.xs-labs.org/" );
    
    ASSERT_TRUE( u1 != static_cast< CFURLRef >( u1.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFURLRef >( u2.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFURLRef >( u3.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFURLRef >( u4.GetCFObject() ) );
    ASSERT_TRUE( u1 != static_cast< CFURLRef >( u5.GetCFObject() ) );
    
    ASSERT_TRUE(  u3 != static_cast< CFURLRef >( u1.GetCFObject() ) );
    ASSERT_TRUE(  u3 != static_cast< CFURLRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u3 != static_cast< CFURLRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u3 != static_cast< CFURLRef >( u4.GetCFObject() ) );
    ASSERT_TRUE(  u3 != static_cast< CFURLRef >( u5.GetCFObject() ) );
    
    ASSERT_TRUE(  u5 != static_cast< CFURLRef >( u1.GetCFObject() ) );
    ASSERT_TRUE(  u5 != static_cast< CFURLRef >( u2.GetCFObject() ) );
    ASSERT_TRUE(  u5 != static_cast< CFURLRef >( u3.GetCFObject() ) );
    ASSERT_TRUE(  u5 != static_cast< CFURLRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u5 != static_cast< CFURLRef >( u5.GetCFObject() ) );
}

TEST( CFPP_URL, OperatorNotEqualCFString )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.org/" );
    
    ASSERT_TRUE( u1 != static_cast< CFStringRef >( CF::String( "" ) ) );
    ASSERT_TRUE( u1 != static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) ) );
    ASSERT_TRUE( u1 != static_cast< CFStringRef >( CF::String( "http://www.xs-labs.org/" ) ) );
    
    ASSERT_TRUE(  u2 != static_cast< CFStringRef >( CF::String( "" ) ) );
    ASSERT_FALSE( u2 != static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) ) );
    ASSERT_TRUE(  u2 != static_cast< CFStringRef >( CF::String( "http://www.xs-labs.org/" ) ) );
    
    ASSERT_TRUE(  u3 != static_cast< CFStringRef >( CF::String( "" ) ) );
    ASSERT_TRUE(  u3 != static_cast< CFStringRef >( CF::String( "http://www.xs-labs.com/" ) ) );
    ASSERT_FALSE( u3 != static_cast< CFStringRef >( CF::String( "http://www.xs-labs.org/" ) ) );
}

TEST( CFPP_URL, OperatorNotEqualSTDString )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.org/" );
    
    ASSERT_TRUE( u1 != std::string( "" ) );
    ASSERT_TRUE( u1 != std::string( "http://www.xs-labs.com/" ) );
    ASSERT_TRUE( u1 != std::string( "http://www.xs-labs.org/" ) );
    
    ASSERT_TRUE(  u2 != std::string( "" ) );
    ASSERT_FALSE( u2 != std::string( "http://www.xs-labs.com/" ) );
    ASSERT_TRUE(  u2 != std::string( "http://www.xs-labs.org/" ) );
    
    ASSERT_TRUE(  u3 != std::string( "" ) );
    ASSERT_TRUE(  u3 != std::string( "http://www.xs-labs.com/" ) );
    ASSERT_FALSE( u3 != std::string( "http://www.xs-labs.org/" ) );
}

TEST( CFPP_URL, OperatorNotEqualCChar )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.org/" );
    
    ASSERT_TRUE( u1 != "" );
    ASSERT_TRUE( u1 != "http://www.xs-labs.com/" );
    ASSERT_TRUE( u1 != "http://www.xs-labs.org/" );
    
    ASSERT_TRUE(  u2 != "" );
    ASSERT_FALSE( u2 != "http://www.xs-labs.com/" );
    ASSERT_TRUE(  u2 != "http://www.xs-labs.org/" );
    
    ASSERT_TRUE(  u3 != "" );
    ASSERT_TRUE(  u3 != "http://www.xs-labs.com/" );
    ASSERT_FALSE( u3 != "http://www.xs-labs.org/" );
}

TEST( CFPP_URL, OperatorDivideCFString )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1 /= static_cast< CFStringRef >( CF::String( "foo" ) );
    u1 /= static_cast< CFStringRef >( CF::String( "" ) );
    u1 /= static_cast< CFStringRef >( CF::String( "bar" ) );
    
    u2 /= static_cast< CFStringRef >( CF::String( "foo" ) );
    u2 /= static_cast< CFStringRef >( CF::String( "" ) );
    u2 /= static_cast< CFStringRef >( CF::String( "bar" ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar" );
}

TEST( CFPP_URL, OperatorDivideSTDString )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1 /= std::string( "foo" );
    u1 /= std::string( "" );
    u1 /= std::string( "bar" );
    
    u2 /= std::string( "foo" );
    u2 /= std::string( "" );
    u2 /= std::string( "bar" );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar" );
}

TEST( CFPP_URL, OperatorDivideCChar )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1 /= "foo";
    u1 /= "";
    u1 /= static_cast< const char * >( nullptr );
    u1 /= "bar";
    
    u2 /= "foo";
    u2 /= "";
    u2 /= static_cast< const char * >( nullptr );
    u2 /= "bar";
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar" );
}

TEST( CFPP_URL, OperatorSubscript )
{
    CF::URL u1;
    CF::URL u2( "http://macmade:1234@www.xs-labs.com/foo/bar.txt?foo=bar&bar=foo#foobar" );
    
    ASSERT_EQ( u1[ CF::URL::PartAll ],               "" );
    ASSERT_EQ( u1[ CF::URL::PartFileSystemPath ],    "" );
    ASSERT_EQ( u1[ CF::URL::PartFragment ],          "" );
    ASSERT_EQ( u1[ CF::URL::PartHostName ],          "" );
    ASSERT_EQ( u1[ CF::URL::PartLastPathComponent ], "" );
    ASSERT_EQ( u1[ CF::URL::PartNetLocation ],       "" );
    ASSERT_EQ( u1[ CF::URL::PartPassword ],          "" );
    ASSERT_EQ( u1[ CF::URL::PartPath ],              "" );
    ASSERT_EQ( u1[ CF::URL::PartPathExtension ],     "" );
    ASSERT_EQ( u1[ CF::URL::PartQueryString ],       "" );
    ASSERT_EQ( u1[ CF::URL::PartResourceSpecifier ], "" );
    ASSERT_EQ( u1[ CF::URL::PartScheme ],            "" );
    ASSERT_EQ( u1[ CF::URL::PartStrictPath ],        "" );
    ASSERT_EQ( u1[ CF::URL::PartUserName ],          "" );
    
    ASSERT_EQ( u2[ CF::URL::PartAll ],               static_cast< std::string >( u2 ) );
    ASSERT_EQ( u2[ CF::URL::PartFileSystemPath ],    "/foo/bar.txt" );
    ASSERT_EQ( u2[ CF::URL::PartFragment ],          "foobar" );
    ASSERT_EQ( u2[ CF::URL::PartHostName ],          "www.xs-labs.com" );
    ASSERT_EQ( u2[ CF::URL::PartLastPathComponent ], "bar.txt" );
    ASSERT_EQ( u2[ CF::URL::PartNetLocation ],       "macmade:1234@www.xs-labs.com" );
    ASSERT_EQ( u2[ CF::URL::PartPassword ],          "1234" );
    ASSERT_EQ( u2[ CF::URL::PartPath ],              "/foo/bar.txt" );
    ASSERT_EQ( u2[ CF::URL::PartPathExtension ],     "txt" );
    ASSERT_EQ( u2[ CF::URL::PartQueryString ],       "foo=bar&bar=foo" );
    ASSERT_EQ( u2[ CF::URL::PartResourceSpecifier ], "?foo=bar&bar=foo#foobar" );
    ASSERT_EQ( u2[ CF::URL::PartScheme ],            "http" );
    ASSERT_EQ( u2[ CF::URL::PartStrictPath ],        "foo/bar.txt" );
    ASSERT_EQ( u2[ CF::URL::PartUserName ],          "macmade" );
}

TEST( CFPP_URL, CastToString )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    
    ASSERT_EQ( static_cast< std::string >( u1 ), "http://www.xs-labs.com/" );
    ASSERT_EQ( static_cast< std::string >( u2 ), "" );
}

TEST( CFPP_URL, GetTypeID )
{
    CF::URL u;
    
    ASSERT_EQ( u.GetTypeID(), CFURLGetTypeID() );
}

TEST( CFPP_URL, GetCFObject )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( static_cast< CFURLRef >( nullptr ) );
    
    ASSERT_TRUE( u1.GetCFObject() == nullptr );
    ASSERT_TRUE( u2.GetCFObject() != nullptr );
    ASSERT_TRUE( u3.GetCFObject() == nullptr );
    ASSERT_EQ( CFGetTypeID( u2.GetCFObject() ), CFURLGetTypeID() );
}

TEST( CFPP_URL, GetFileSystemPath )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/foo/bar" );
    
    ASSERT_FALSE( u1.GetFileSystemPath( CF::URL::PathStylePOSIX ).IsValid() );
    ASSERT_FALSE( u1.GetFileSystemPath( CF::URL::PathStyleWindows ).IsValid() );
    ASSERT_TRUE(  u2.GetFileSystemPath( CF::URL::PathStylePOSIX ).IsValid() );
    ASSERT_TRUE(  u2.GetFileSystemPath( CF::URL::PathStyleWindows ).IsValid() );
    
    ASSERT_EQ( u2.GetFileSystemPath( CF::URL::PathStylePOSIX ),   "/foo/bar" );
    ASSERT_EQ( u2.GetFileSystemPath( CF::URL::PathStyleWindows ), "\\foo\\bar" );
}

TEST( CFPP_URL, GetFragment )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.com/#foo" );
    
    ASSERT_FALSE( u1.GetFragment().IsValid() );
    ASSERT_FALSE( u2.GetFragment().IsValid() );
    ASSERT_TRUE(  u3.GetFragment().IsValid() );
    
    ASSERT_EQ( u3.GetFragment(), "foo" ); 
}

TEST( CFPP_URL, GetHostName )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    
    ASSERT_FALSE( u1.GetHostName().IsValid() );
    ASSERT_TRUE(  u2.GetHostName().IsValid() );
    
    ASSERT_EQ( u2.GetHostName(), "www.xs-labs.com" ); 
}

TEST( CFPP_URL, GetLastPathComponent )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/foo/bar#foobar" );
    
    ASSERT_FALSE( u1.GetLastPathComponent().IsValid() );
    ASSERT_TRUE(  u2.GetLastPathComponent().IsValid() );
    
    ASSERT_EQ( u2.GetLastPathComponent(), "bar" ); 
}

TEST( CFPP_URL, GetNetLocation )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://macmade:1234@www.xs-labs.com/" );
    
    ASSERT_FALSE( u1.GetNetLocation().IsValid() );
    ASSERT_TRUE(  u2.GetNetLocation().IsValid() );
    ASSERT_TRUE(  u3.GetNetLocation().IsValid() );
    
    ASSERT_EQ( u2.GetNetLocation(), "www.xs-labs.com" ); 
    ASSERT_EQ( u3.GetNetLocation(), "macmade:1234@www.xs-labs.com" ); 
}

TEST( CFPP_URL, GetPassword )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://macmade:1234@www.xs-labs.com/" );
    
    ASSERT_FALSE( u1.GetPassword().IsValid() );
    ASSERT_FALSE( u2.GetPassword().IsValid() );
    ASSERT_TRUE(  u3.GetPassword().IsValid() );
    
    ASSERT_EQ( u3.GetPassword(), "1234" ); 
}

TEST( CFPP_URL, GetPath )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com" );
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/foo/bar#foobar" );
    
    ASSERT_FALSE( u1.GetPath().IsValid() );
    ASSERT_TRUE(  u2.GetPath().IsValid() );
    ASSERT_TRUE(  u3.GetPath().IsValid() );
    ASSERT_TRUE(  u4.GetPath().IsValid() );
    
    ASSERT_EQ( u2.GetPath(), "" );
    ASSERT_EQ( u3.GetPath(), "/" );
    ASSERT_EQ( u4.GetPath(), "/foo/bar" ); 
}

TEST( CFPP_URL, GetPathExtension )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/foo/bar" );
    CF::URL u3( "http://www.xs-labs.com/foo/bar.txt" );
    
    ASSERT_FALSE( u1.GetPathExtension().IsValid() );
    ASSERT_FALSE( u2.GetPathExtension().IsValid() );
    ASSERT_TRUE(  u3.GetPathExtension().IsValid() );
    
    ASSERT_EQ( u3.GetPathExtension(), "txt" ); 
}

TEST( CFPP_URL, GetQueryString )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.com/?foo=1&bar=2" );
    
    ASSERT_FALSE( u1.GetQueryString().IsValid() );
    ASSERT_FALSE( u2.GetQueryString().IsValid() );
    ASSERT_TRUE(  u3.GetQueryString().IsValid() );
    
    ASSERT_EQ( u3.GetQueryString(), "foo=1&bar=2" ); 
}

TEST( CFPP_URL, GetResourceSpecifier )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.com/#foobar?foo=bar" );
    
    ASSERT_FALSE( u1.GetResourceSpecifier().IsValid() );
    ASSERT_FALSE( u2.GetResourceSpecifier().IsValid() );
    ASSERT_TRUE(  u3.GetResourceSpecifier().IsValid() );
    
    ASSERT_EQ( u3.GetResourceSpecifier(), "#foobar?foo=bar" ); 
}

TEST( CFPP_URL, GetScheme )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    
    ASSERT_FALSE( u1.GetScheme().IsValid() );
    ASSERT_TRUE(  u2.GetScheme().IsValid() );
    
    ASSERT_EQ( u2.GetScheme(), "http" ); 
}

TEST( CFPP_URL, GetStrictPath )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com" );
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/foo/bar#foobar" );
    
    ASSERT_FALSE( u1.GetStrictPath().IsValid() );
    ASSERT_FALSE( u2.GetStrictPath().IsValid() );
    ASSERT_TRUE(  u3.GetStrictPath().IsValid() );
    ASSERT_TRUE(  u4.GetStrictPath().IsValid() );
    
    ASSERT_EQ( u3.GetStrictPath(), "" );
    ASSERT_EQ( u4.GetStrictPath(), "foo/bar" );
}

TEST( CFPP_URL, GetUserName )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://macmade:1234@www.xs-labs.com/" );
    
    ASSERT_FALSE( u1.GetUserName().IsValid() );
    ASSERT_FALSE( u2.GetUserName().IsValid() );
    ASSERT_TRUE(  u3.GetUserName().IsValid() );
    
    ASSERT_EQ( u3.GetUserName(), "macmade" ); 
}

TEST( CFPP_URL, GetPortNumber )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "http://www.xs-labs.com:8080/" );
    
    ASSERT_TRUE( u1.GetPortNumber().IsValid() );
    ASSERT_TRUE( u2.GetPortNumber().IsValid() );
    ASSERT_TRUE( u3.GetPortNumber().IsValid() );
    
    ASSERT_EQ( u3.GetPortNumber(), 8080 ); 
}

TEST( CFPP_URL, GetBaseURL )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com/" );
    CF::URL u3( "foobar", CF::URL( "http://www.xs-labs.com/" ) );
    
    ASSERT_FALSE( u1.GetBaseURL().IsValid() );
    ASSERT_FALSE( u2.GetBaseURL().IsValid() );
    ASSERT_TRUE(  u3.GetBaseURL().IsValid() );
    
    ASSERT_EQ( u3.GetBaseURL(), CF::URL( "http://www.xs-labs.com/" ) ); 
}

TEST( CFPP_URL, HasDirectoryPath )
{
    CF::URL u1;
    CF::URL u2( "http://www.xs-labs.com" );
    CF::URL u3( "http://www.xs-labs.com/" );
    CF::URL u4( "http://www.xs-labs.com/foo/bar" );
    CF::URL u5( "http://www.xs-labs.com/foo/bar/" );
    CF::URL u6( "http://www.xs-labs.com/foo/bar.txt" );
    
    ASSERT_FALSE( u1.HasDirectoryPath() );
    ASSERT_FALSE( u2.HasDirectoryPath() );
    ASSERT_TRUE(  u3.HasDirectoryPath() );
    ASSERT_FALSE( u4.HasDirectoryPath() );
    ASSERT_TRUE(  u5.HasDirectoryPath() );
    ASSERT_FALSE( u6.HasDirectoryPath() );
}

TEST( CFPP_URL, AppendPathComponent_CFString )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1.AppendPathComponent( static_cast< CFStringRef >( CF::String( "foo" ) ) );
    u1.AppendPathComponent( static_cast< CFStringRef >( CF::String( "" ) ) );
    u1.AppendPathComponent( static_cast< CFStringRef >( CF::String( "bar" ) ) );
    
    u2.AppendPathComponent( static_cast< CFStringRef >( CF::String( "foo" ) ) );
    u2.AppendPathComponent( static_cast< CFStringRef >( CF::String( "" ) ) );
    u2.AppendPathComponent( static_cast< CFStringRef >( CF::String( "bar" ) ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar" );
}

TEST( CFPP_URL, AppendPathComponent_STDString )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1.AppendPathComponent( std::string( "foo" ) );
    u1.AppendPathComponent( std::string( "" ) );
    u1.AppendPathComponent( std::string( "bar" ) );
    
    u2.AppendPathComponent( std::string( "foo" ) );
    u2.AppendPathComponent( std::string( "" ) );
    u2.AppendPathComponent( std::string( "bar" ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar" );
}

TEST( CFPP_URL, AppendPathComponent_CChar )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1.AppendPathComponent( "foo" );
    u1.AppendPathComponent( "" );
    u1.AppendPathComponent( "bar" );
    
    u2.AppendPathComponent( "foo" );
    u2.AppendPathComponent( "" );
    u2.AppendPathComponent( "bar" );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar" );
}

TEST( CFPP_URL, AppendPathExtension_CFString )
{
    CF::URL u1( "http://www.xs-labs.com/foo/bar?foobar=1" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1.AppendPathExtension( static_cast< CFStringRef >( CF::String( "txt" ) ) );
    u2.AppendPathExtension( static_cast< CFStringRef >( CF::String( "txt" ) ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar.txt?foobar=1" );
}

TEST( CFPP_URL, AppendPathExtension_STDString )
{
    CF::URL u1( "http://www.xs-labs.com/foo/bar?foobar=1" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1.AppendPathExtension( std::string( "txt" ) );
    u2.AppendPathExtension( std::string( "txt" ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar.txt?foobar=1" );
}

TEST( CFPP_URL, AppendPathExtension_CChar )
{
    CF::URL u1( "http://www.xs-labs.com/foo/bar?foobar=1" );
    CF::URL u2;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    u1.AppendPathExtension( "txt" );
    u2.AppendPathExtension( "txt" );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar.txt?foobar=1" );
}

TEST( CFPP_URL, DeleteLastPathComponent )
{
    CF::URL u1( "http://www.xs-labs.com/" );
    CF::URL u2( "http://www.xs-labs.com/foo/bar?foobar=1" );
    CF::URL u3( "http://www.xs-labs.com/foo/bar.txt?foobar=1" );
    CF::URL u4;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_TRUE(  u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    
    u1.DeleteLastPathComponent();
    u2.DeleteLastPathComponent();
    u3.DeleteLastPathComponent();
    u4.DeleteLastPathComponent();
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_TRUE(  u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/../" );
    ASSERT_EQ( u2, "http://www.xs-labs.com/foo/?foobar=1" );
    ASSERT_EQ( u3, "http://www.xs-labs.com/foo/?foobar=1" );
}

TEST( CFPP_URL, DeletePathExtension )
{
    CF::URL u1( "http://www.xs-labs.com/foo/bar?foobar=1" );
    CF::URL u2( "http://www.xs-labs.com/foo/bar.txt?foobar=1" );
    CF::URL u3;
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    
    u1.DeletePathExtension();
    u2.DeletePathExtension();
    u3.DeletePathExtension();
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    
    ASSERT_EQ( u1, "http://www.xs-labs.com/foo/bar?foobar=1" );
    ASSERT_EQ( u2, "http://www.xs-labs.com/foo/bar?foobar=1" );
}

TEST( CFPP_URL, Swap )
{
    CF::URL u1( "http://www.xs-labs.com" );
    CF::URL u2( "http://www.xs-labs.org" );
    
    ASSERT_TRUE( u1 == "http://www.xs-labs.com" );
    ASSERT_TRUE( u2 == "http://www.xs-labs.org" );
    
    swap( u1, u2 );
    
    ASSERT_TRUE( u1 == "http://www.xs-labs.org" );
    ASSERT_TRUE( u2 == "http://www.xs-labs.com" );
}
