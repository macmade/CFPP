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
 * @file        Test-CFPP-String.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::String
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_String, CTOR )
{
    CF::String s;
    
    ASSERT_TRUE( s.IsValid() );
    ASSERT_EQ( s.GetValue(),  "" );
    ASSERT_EQ( s.GetLength(), 0 );
}

TEST( CFPP_String, CTOR_AutoPointer )
{
    CF::String s1( CF::AutoPointer( CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII ) ) );
    CF::String s2( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::String s3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
}

TEST( CFPP_String, CTOR_CFType )
{
    CF::String s1( static_cast< CFTypeRef >( CFSTR( "hello, world" ) ) );
    CF::String s2( static_cast< CFTypeRef >( nullptr ) );
    CF::String s3( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
    ASSERT_TRUE(  s1.GetValue() == "hello, world" );
}

TEST( CFPP_String, CTOR_CFString )
{
    CF::String s1( CFSTR( "hello, world" ) );
    CF::String s2( static_cast< CFStringRef >( nullptr ) );
    CF::String s3( static_cast< CFStringRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
    ASSERT_TRUE(  s1.GetValue() == "hello, world" );
}

TEST( CFPP_String, CTOR_NullPointer )
{
    CF::String s( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
}

TEST( CFPP_String, CTOR_AutoPointer_DefaultValue_Encoding )
{
    CF::String s1( CF::AutoPointer( CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII ) ), "hello, universe" );
    CF::String s2( CF::AutoPointer( CFUUIDCreate( nullptr ) ), "hello, universe" );
    CF::String s3( CF::AutoPointer( nullptr ), "hello, universe" );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s3.IsValid() );
    
    ASSERT_TRUE( s1 == "hello, world" );
    ASSERT_TRUE( s2 == "hello, universe" );
    ASSERT_TRUE( s3 == "hello, universe" );
}

TEST( CFPP_String, CTOR_CFType_DefaultValue_Encoding )
{
    CF::String s1( static_cast< CFTypeRef >( CFSTR( "hello, world" ) ), "hello, universe", kCFStringEncodingASCII );
    CF::String s2( static_cast< CFTypeRef >( nullptr ), "hello, universe", kCFStringEncodingASCII );
    CF::String s3( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ), "hello, universe", kCFStringEncodingASCII );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s3.IsValid() );
    ASSERT_TRUE( s1.GetValue() == "hello, world" );
    ASSERT_TRUE( s2.GetValue() == "hello, universe" );
    ASSERT_TRUE( s3.GetValue() == "hello, universe" );
}

TEST( CFPP_String, CTOR_CFString_DefaultValue_Encoding )
{
    CF::String s1( CFSTR( "hello, world" ), "hello, universe", kCFStringEncodingASCII );
    CF::String s2( static_cast< CFStringRef >( nullptr ), "hello, universe", kCFStringEncodingASCII );
    CF::String s3( static_cast< CFStringRef >( CF::Boolean().GetCFObject() ), "hello, universe", kCFStringEncodingASCII );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s3.IsValid() );
    ASSERT_TRUE( s1.GetValue() == "hello, world" );
    ASSERT_TRUE( s2.GetValue() == "hello, universe" );
    ASSERT_TRUE( s3.GetValue() == "hello, universe" );
}

TEST( CFPP_String, CTOR_STDString_Encoding )
{
    CF::String s1( std::string( "hello, world" ), kCFStringEncodingASCII );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s1.GetValue() == "hello, world" );
}

TEST( CFPP_String, CTOR_Char_Encoding )
{
    CF::String s1( const_cast< char * >( "hello, world" ), kCFStringEncodingASCII );
    CF::String s2( static_cast< char * >( nullptr ), kCFStringEncodingASCII );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s1.GetValue() == "hello, world" );
    ASSERT_TRUE( s2.GetValue() == "" );
}

TEST( CFPP_String, CTOR_CChar_Encoding )
{
    CF::String s1( "hello, world", kCFStringEncodingASCII );
    CF::String s2( static_cast< const char * >( nullptr ), kCFStringEncodingASCII );
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s1.GetValue() == "hello, world" );
    ASSERT_TRUE( s2.GetValue() == "" );
}

TEST( CFPP_String, CCTOR )
{
    CF::String s1( "hello, world" );
    CF::String s2( s1 );
    
    ASSERT_TRUE( s2.GetValue() == "hello, world" );
}

TEST( CFPP_String, MCTOR )
{
    CF::String s1( "hello, world" );
    CF::String s2( std::move( s1 ) );
    
    ASSERT_FALSE( s1.IsValid() );
    ASSERT_TRUE(  s2.IsValid() );
    ASSERT_TRUE(  s2.GetValue() == "hello, world" );
}

TEST( CFPP_String, OperatorAssignString )
{
    CF::String s( "hello, world" );
    
    s = CF::String( "hello, universe" );
    
    ASSERT_TRUE( s == "hello, universe" );
    
    s = CF::String();
    
    ASSERT_TRUE( s == "" );
}

TEST( CFPP_String, OperatorAssignAutoPointer )
{
    CF::String s1( static_cast< CFTypeRef >( nullptr ) );
    CF::String s2;
    CF::String s3;
    
    ASSERT_FALSE( s1.IsValid() );
    ASSERT_TRUE(  s2.IsValid() );
    ASSERT_TRUE(  s3.IsValid() );
    
    s1 = CF::AutoPointer( CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII ) );
    s2 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    s3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE(  s1.IsValid() );
    ASSERT_FALSE( s2.IsValid() );
    ASSERT_FALSE( s3.IsValid() );
}

TEST( CFPP_String, OperatorAssignCFType )
{
    CF::String s( "hello, world" );
    
    s = static_cast< CFTypeRef >( CFSTR( "hello, universe" ) );
    
    ASSERT_TRUE( s == "hello, universe" );
    
    s = static_cast< CFTypeRef >( CFSTR( "" ) );
    
    ASSERT_TRUE( s == "" );
    
    s = static_cast< CFTypeRef >( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
}

TEST( CFPP_String, OperatorAssignCFString )
{
    CF::String s( "hello, world" );
    
    s = CFSTR( "hello, universe" );
    
    ASSERT_TRUE( s == "hello, universe" );
    
    s = CFSTR( "" );
    
    ASSERT_TRUE( s == "" );
    
    s = static_cast< CFStringRef >( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
}

TEST( CFPP_String, OperatorAssignNullPointer )
{
    CF::String s;
    
    ASSERT_TRUE( s.IsValid() );
    
    s = nullptr;
    
    ASSERT_FALSE( s.IsValid() );
}

TEST( CFPP_String, OperatorAssignSTDString )
{
    CF::String s( "hello, world" );
    
    s = std::string( "hello, universe" );
    
    ASSERT_TRUE( s == "hello, universe" );
    
    s = std::string();
    
    ASSERT_TRUE( s == "" );
}

TEST( CFPP_String, OperatorAssignChar )
{
    CF::String s( "hello, world" );
    
    s = static_cast< char * >( nullptr );
    
    ASSERT_TRUE( s == "" );
    
    s = const_cast< char * >( "hello, universe" );
    
    ASSERT_TRUE( s == "hello, universe" );
    
    s = const_cast< char * >( "" );
    
    ASSERT_TRUE( s.IsValid() );
    ASSERT_TRUE( s == "" );
}

TEST( CFPP_String, OperatorAssignCChar )
{
    CF::String s( "hello, world" );
    
    s = static_cast< const char * >( nullptr );
    
    ASSERT_TRUE( s == "" );
    
    s = "hello, universe";
    
    ASSERT_TRUE( s == "hello, universe" );
    
    s = "";
    
    ASSERT_TRUE( s.IsValid() );
    ASSERT_TRUE( s == "" );
}

TEST( CFPP_String, OperatorEqualString )
{
    ASSERT_TRUE(  CF::String( "hello, world" ) == CF::String( "hello, world" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == CF::String( "hello, universe" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == CF::String() );
    ASSERT_TRUE(  CF::String()                 == CF::String() );
}

TEST( CFPP_String, OperatorEqualCFType )
{
    ASSERT_TRUE(  CF::String( "hello, world" ) == static_cast< CFTypeRef >( CFSTR( "hello, world" ) ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == static_cast< CFTypeRef >( CFSTR( "hello, universe" ) ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == static_cast< CFTypeRef >( CFSTR( "" ) ) );
    ASSERT_TRUE(  CF::String()                 == static_cast< CFTypeRef >( CFSTR( "" ) ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == static_cast< CFTypeRef >( nullptr ) );
}

TEST( CFPP_String, OperatorEqualCFString )
{
    ASSERT_TRUE(  CF::String( "hello, world" ) == CFSTR( "hello, world" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == CFSTR( "hello, universe" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == CFSTR( "" ) );
    ASSERT_TRUE(  CF::String()                 == CFSTR( "" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == static_cast< CFStringRef >( nullptr ) );
}

TEST( CFPP_String, OperatorEqualSTDString )
{
    ASSERT_TRUE(  CF::String( "hello, world" ) == std::string( "hello, world" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == std::string( "hello, universe" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == std::string() );
    ASSERT_TRUE(  CF::String()                 == std::string() );
}

TEST( CFPP_String, OperatorEqualChar )
{
    ASSERT_TRUE(  CF::String( "hello, world" ) == const_cast< char * >( "hello, world" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == const_cast< char * >( "hello, universe" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == const_cast< char * >( "" ) );
    ASSERT_TRUE(  CF::String()                 == const_cast< char * >( "" ) );
    ASSERT_FALSE( CF::String( "hello, world" ) == static_cast< char * >( nullptr ) );
}

TEST( CFPP_String, OperatorEqualCChar )
{
    ASSERT_TRUE(  CF::String( "hello, world" ) == "hello, world" );
    ASSERT_FALSE( CF::String( "hello, world" ) == "hello, universe" );
    ASSERT_FALSE( CF::String( "hello, world" ) == "" );
    ASSERT_TRUE(  CF::String()                 == "" );
    ASSERT_FALSE( CF::String( "hello, world" ) == static_cast< const char * >( nullptr ) );
}

TEST( CFPP_String, OperatorNotEqualString )
{
    ASSERT_FALSE( CF::String( "hello, world" ) != CF::String( "hello, world" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != CF::String( "hello, universe" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != CF::String() );
    ASSERT_FALSE( CF::String()                 != CF::String() );
}

TEST( CFPP_String, OperatorNotEqualCFType )
{
    ASSERT_FALSE( CF::String( "hello, world" ) != static_cast< CFTypeRef >( CFSTR( "hello, world" ) ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != static_cast< CFTypeRef >( CFSTR( "hello, universe" ) ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != static_cast< CFTypeRef >( CFSTR( "" ) ) );
    ASSERT_FALSE( CF::String()                 != static_cast< CFTypeRef >( CFSTR( "" ) ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != static_cast< CFTypeRef >( nullptr ) );
}

TEST( CFPP_String, OperatorNotEqualCFString )
{
    ASSERT_FALSE( CF::String( "hello, world" ) != CFSTR( "hello, world" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != CFSTR( "hello, universe" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != CFSTR( "" ) );
    ASSERT_FALSE( CF::String()                 != CFSTR( "" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != static_cast< CFStringRef >( nullptr ) );
}

TEST( CFPP_String, OperatorNotEqualSTDString )
{
    ASSERT_FALSE( CF::String( "hello, world" ) != std::string( "hello, world" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != std::string( "hello, universe" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != std::string() );
    ASSERT_FALSE( CF::String()                 != std::string() );
}

TEST( CFPP_String, OperatorNotEqualChar )
{
    ASSERT_FALSE( CF::String( "hello, world" ) != const_cast< char * >( "hello, world" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != const_cast< char * >( "hello, universe" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != const_cast< char * >( "" ) );
    ASSERT_FALSE( CF::String()                 != const_cast< char * >( "" ) );
    ASSERT_TRUE(  CF::String( "hello, world" ) != static_cast< char * >( nullptr ) );
}

TEST( CFPP_String, OperatorNotEqualCChar )
{
    ASSERT_FALSE( CF::String( "hello, world" ) != "hello, world" );
    ASSERT_TRUE(  CF::String( "hello, world" ) != "hello, universe" );
    ASSERT_TRUE(  CF::String( "hello, world" ) != "" );
    ASSERT_FALSE( CF::String()                 != "" );
    ASSERT_TRUE(  CF::String( "hello, world" ) != static_cast< const char * >( nullptr ) );
}

TEST( CFPP_String, OperatorPlusEqualString )
{
    CF::String s( "hello, world" );
    
    s += CF::String( "..." );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
    
    s += CF::String();
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
    
    s = static_cast< CFStringRef >( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
    
    s += CF::String( "hello, world" );
    
    ASSERT_TRUE( s.GetValue() == "hello, world" );
}

TEST( CFPP_String, OperatorPlusEqualCFString )
{
    CF::String s( "hello, world" );
    
    s += CFSTR( "..." );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
    
    ASSERT_NO_THROW(         s += static_cast< CFStringRef >( nullptr ) );
    ASSERT_NO_FATAL_FAILURE( s += static_cast< CFStringRef >( nullptr ) );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
}

TEST( CFPP_String, OperatorPlusEqualSTDString )
{
    CF::String s( "hello, world" );
    
    s += std::string( "..." );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
    
    s += std::string( "" );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
}

TEST( CFPP_String, OperatorPlusEqualChar )
{
    CF::String s( "hello, world" );
    
    s += const_cast< char * >( "..." );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
    
    ASSERT_NO_THROW(         s += static_cast< char * >( nullptr ) );
    ASSERT_NO_FATAL_FAILURE( s += static_cast< char * >( nullptr ) );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
}

TEST( CFPP_String, OperatorPlusEqualCChar )
{
    CF::String s( "hello, world" );
    
    s += static_cast< const char * >( "..." );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
    
    ASSERT_NO_THROW(         s += static_cast< const char * >( nullptr ) );
    ASSERT_NO_FATAL_FAILURE( s += static_cast< const char * >( nullptr ) );
    
    ASSERT_TRUE( s.GetValue() == "hello, world..." );
}

TEST( CFPP_String, OperatorSubscript )
{
    CF::String s( "hello, world" );
    
    ASSERT_EQ( s[   0 ], 'h' );
    ASSERT_EQ( s[  11 ], 'd' );
    ASSERT_EQ( s[  -1 ], 'd' );
    ASSERT_EQ( s[ -12 ], 'h' );
    
    ASSERT_NO_THROW( s[   12 ] );
    ASSERT_NO_THROW( s[  100 ] );
    ASSERT_NO_THROW( s[  -13 ] );
    ASSERT_NO_THROW( s[ -100 ] );
    
    ASSERT_NO_FATAL_FAILURE( s[   12 ] );
    ASSERT_NO_FATAL_FAILURE( s[  100 ] );
    ASSERT_NO_FATAL_FAILURE( s[  -13 ] );
    ASSERT_NO_FATAL_FAILURE( s[ -100 ] );
    
    ASSERT_EQ( s[   12 ], 0 );
    ASSERT_EQ( s[  100 ], 0 );
    ASSERT_EQ( s[  -13 ], 0 );
    ASSERT_EQ( s[ -100 ], 0 );
    
    s = static_cast< CFStringRef >( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
    ASSERT_EQ( s[  11 ], 0 );
    ASSERT_EQ( s[ -11 ], 0 );
}

TEST( CFPP_String, CastToSTDString )
{
    std::string s1( "hello, world" );
    CF::String  s2( "hello, world" );
    
    ASSERT_TRUE( s1 == static_cast< std::string >( s2 ) );
}

TEST( CFPP_String, GetTypeID )
{
    CF::String s;
    
    ASSERT_EQ( s.GetTypeID(), CFStringGetTypeID() );
}

TEST( CFPP_String, GetCFObject )
{
    CF::String s1;
    CF::String s2( "hello, world" );
    CF::String s3( static_cast< CFStringRef >( nullptr ) );
    
    ASSERT_TRUE( s1.GetCFObject() != nullptr );
    ASSERT_TRUE( s2.GetCFObject() != nullptr );
    ASSERT_TRUE( s3.GetCFObject() == nullptr );
    ASSERT_TRUE( CFEqual( s2.GetCFObject(), CFSTR( "hello, world" ) ) );
    ASSERT_EQ( CFGetTypeID( s1.GetCFObject() ), CFStringGetTypeID() );
    ASSERT_EQ( CFGetTypeID( s2.GetCFObject() ), CFStringGetTypeID() );
}

TEST( CFPP_String, HasPrefix_String )
{
    CF::String s1;
    CF::String s2( "hello, world" );
    
    ASSERT_FALSE( s1.HasPrefix( CF::String( "hello" ) ) );
    ASSERT_FALSE( s1.HasPrefix( CF::String( "" ) ) );
    ASSERT_TRUE(  s2.HasPrefix( CF::String( "hello" ) ) );
    ASSERT_FALSE( s2.HasPrefix( CF::String( "" ) ) );
    ASSERT_FALSE( s2.HasPrefix( CF::String( "world" ) ) );
}

TEST( CFPP_String, HasPrefix_CFString )
{
    CF::String s1;
    CF::String s2( "hello, world" );
    
    ASSERT_FALSE( s1.HasPrefix( CFSTR( "hello" ) ) );
    ASSERT_FALSE( s1.HasPrefix( CFSTR( "" ) ) );
    ASSERT_FALSE( s1.HasPrefix( static_cast< CFStringRef >( nullptr ) ) );
    ASSERT_TRUE(  s2.HasPrefix( CFSTR( "hello" ) ) );
    ASSERT_FALSE( s2.HasPrefix( CFSTR( "" ) ) );
    ASSERT_FALSE( s2.HasPrefix( CFSTR( "world" ) ) );
    ASSERT_FALSE( s2.HasPrefix( static_cast< CFStringRef >( nullptr ) ) );
}

TEST( CFPP_String, HasPrefix_STDString )
{
    CF::String s1;
    CF::String s2( "hello, world" );
    
    ASSERT_FALSE( s1.HasPrefix( std::string( "hello" ) ) );
    ASSERT_FALSE( s1.HasPrefix( std::string( "" ) ) );
    ASSERT_TRUE(  s2.HasPrefix( std::string( "hello" ) ) );
    ASSERT_FALSE( s2.HasPrefix( std::string( "" ) ) );
    ASSERT_FALSE( s2.HasPrefix( std::string( "world" ) ) );
}

TEST( CFPP_String, HasSuffix_String )
{
    CF::String s1;
    CF::String s2( "hello, world" );
    
    ASSERT_FALSE( s1.HasSuffix( CF::String( "world" ) ) );
    ASSERT_FALSE( s1.HasSuffix( CF::String( "" ) ) );
    ASSERT_TRUE(  s2.HasSuffix( CF::String( "world" ) ) );
    ASSERT_FALSE( s2.HasSuffix( CF::String( "" ) ) );
    ASSERT_FALSE( s2.HasSuffix( CF::String( "universe" ) ) );
}

TEST( CFPP_String, HasSuffix_CFString )
{
    CF::String s1;
    CF::String s2( "hello, world" );
    
    ASSERT_FALSE( s1.HasSuffix( CFSTR( "world" ) ) );
    ASSERT_FALSE( s1.HasSuffix( CFSTR( "" ) ) );
    ASSERT_FALSE( s1.HasSuffix( static_cast< CFStringRef >( nullptr ) ) );
    ASSERT_TRUE(  s2.HasSuffix( CFSTR( "world" ) ) );
    ASSERT_FALSE( s2.HasSuffix( CFSTR( "" ) ) );
    ASSERT_FALSE( s2.HasSuffix( CFSTR( "universe" ) ) );
    ASSERT_FALSE( s2.HasSuffix( static_cast< CFStringRef >( nullptr ) ) );
}

TEST( CFPP_String, HasSuffix_STDString )
{
    CF::String s1;
    CF::String s2( "hello, world" );
    
    ASSERT_FALSE( s1.HasSuffix( std::string( "world" ) ) );
    ASSERT_FALSE( s1.HasSuffix( std::string( "" ) ) );
    ASSERT_TRUE(  s2.HasSuffix( std::string( "world" ) ) );
    ASSERT_FALSE( s2.HasSuffix( std::string( "" ) ) );
    ASSERT_FALSE( s2.HasSuffix( std::string( "universe" ) ) );
}

TEST( CFPP_String, GetLength )
{
    CF::String s;
    
    ASSERT_EQ( s.GetLength(), 0 );
    
    s.SetValue( "hello, world" );
    
    ASSERT_EQ( s.GetLength(), 12 );
    
    s.SetValue( "" );
    
    ASSERT_EQ( s.GetLength(), 0 );
    
    s = static_cast< CFStringRef >( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
    ASSERT_EQ( s.GetLength(), 0 );
}

TEST( CFPP_String, GetValue )
{
    CF::String  s( "hello, world" );
    
    ASSERT_EQ(   s.GetValue(),                             "hello, world" );
    ASSERT_EQ(   s.GetValue( kCFStringEncodingDOSLatin1 ), "hello, world" );
    ASSERT_EQ(   s.GetValue( kCFStringEncodingISOLatin1 ), "hello, world" );
    ASSERT_EQ(   s.GetValue( kCFStringEncodingISOLatin9 ), "hello, world" );
    ASSERT_TRUE( s.GetValue( kCFStringEncodingUTF16 ).length() > 0 );
    
    s = static_cast< CFStringRef >( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
    ASSERT_EQ( s.GetValue(), "" );
}

TEST( CFPP_String, GetCStringValue )
{
    const char * p;
    CF::String   s( "hello, world" );
    
    p = s.GetCStringValue();
    
    ASSERT_EQ( strcmp( p, "hello, world" ), 0 );
    
    s = static_cast< CFStringRef >( nullptr );
    
    ASSERT_FALSE( s.IsValid() );
    ASSERT_TRUE( s.GetCStringValue() == nullptr );
}

TEST( CFPP_String, SetValue )
{
    CF::String s( "hello, world" );
    
    ASSERT_EQ( s.GetValue(), "hello, world" );
    
    s.SetValue( "hello, universe" );
    
    ASSERT_EQ( s.GetValue(), "hello, universe" );
}

TEST( CFPP_String, Swap )
{
    CF::String s1( "hello, world" );
    CF::String s2( "hello, universe" );
    
    ASSERT_EQ( s1.GetValue(), "hello, world" );
    ASSERT_EQ( s2.GetValue(), "hello, universe" );
    
    swap( s1, s2 );
    
    ASSERT_EQ( s1.GetValue(), "hello, universe" );
    ASSERT_EQ( s2.GetValue(), "hello, world" );
}
