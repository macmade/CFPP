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
 * @file        Test-CFPP-Boolean.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Boolean
 */

#include <CF++.hpp>
#include "Constants.hpp"

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Boolean, CTOR )
{
    CF::Boolean b1;
    CF::Boolean b2( true );
    
    ASSERT_FALSE( b1.GetValue() );
    ASSERT_TRUE(  b2.GetValue() );
}

TEST( CFPP_Boolean, CTOR_AutoPointer )
{
    CF::Boolean b1( CF::AutoPointer( CFRetain( GetCFBooleanTrue() ) ) );
    CF::Boolean b2( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::Boolean b3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE( b1.IsValid() );
    ASSERT_TRUE( b2.IsValid() );
    ASSERT_TRUE( b3.IsValid() );
    
    ASSERT_TRUE(  b1.GetValue() );
    ASSERT_FALSE( b2.GetValue() );
    ASSERT_FALSE( b3.GetValue() );
}

TEST( CFPP_Boolean, CTOR_CFType )
{
    CFBooleanRef b;
    CFStringRef  s;
    
    b = GetCFBooleanTrue();
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    
    {
        CF::Boolean b1( static_cast< CFTypeRef >( b ) );
        CF::Boolean b2( static_cast< CFTypeRef >( s ) );
        CF::Boolean b3( static_cast< CFTypeRef >( nullptr ) );
        
        ASSERT_TRUE(  b1.GetValue() );
        ASSERT_FALSE( b2.GetValue() );
        ASSERT_FALSE( b3.GetValue() );
    }
    
    CFRelease( s );
}

TEST( CFPP_Boolean, CTOR_CFBoolean )
{
    CF::Boolean b1( GetCFBooleanTrue() );
    CF::Boolean b2( GetCFBooleanFalse() );
    CF::Boolean b3( static_cast< CFBooleanRef >( nullptr ) );
    
    ASSERT_TRUE(  b1.GetValue() );
    ASSERT_FALSE( b2.GetValue() );
    ASSERT_FALSE( b3.GetValue() );
}

TEST( CFPP_Boolean, CTOR_NullPointer )
{
    CF::Boolean b( nullptr );
    
    ASSERT_TRUE(  b.IsValid() );
    ASSERT_FALSE( b.GetValue() );
}

TEST( CFPP_Boolean, CTOR_AutoPointer_DefaultValue )
{
    CF::Boolean b1( CF::AutoPointer( CFRetain( GetCFBooleanTrue() ) ), false );
    CF::Boolean b2( CF::AutoPointer( CFUUIDCreate( nullptr ) ), true );
    CF::Boolean b3( CF::AutoPointer( nullptr ), true );
    
    ASSERT_TRUE( b1.IsValid() );
    ASSERT_TRUE( b2.IsValid() );
    ASSERT_TRUE( b3.IsValid() );
    
    ASSERT_TRUE( b1.GetValue() );
    ASSERT_TRUE( b2.GetValue() );
    ASSERT_TRUE( b3.GetValue() );
}

TEST( CFPP_Boolean, CTOR_CFType_DefaultValue )
{
    CFBooleanRef b;
    CFStringRef  s;
    
    b = GetCFBooleanTrue();
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    
    {
        CF::Boolean b1( static_cast< CFTypeRef >( b ), false );
        CF::Boolean b2( static_cast< CFTypeRef >( s ), true );
        CF::Boolean b3( static_cast< CFTypeRef >( nullptr ), true );
        
        ASSERT_TRUE( b1.GetValue() );
        ASSERT_TRUE( b2.GetValue() );
        ASSERT_TRUE( b3.GetValue() );
    }
    
    CFRelease( s );
}

TEST( CFPP_Boolean, CTOR_CFBoolean_DefaultValue )
{
    CF::Boolean b1( GetCFBooleanTrue(), false );
    CF::Boolean b2( GetCFBooleanFalse(), true );
    CF::Boolean b3( static_cast< CFBooleanRef >( nullptr ), true );
    
    ASSERT_TRUE(  b1.GetValue() );
    ASSERT_FALSE( b2.GetValue() );
    ASSERT_TRUE(  b3.GetValue() );
}

TEST( CFPP_Boolean, CCTOR )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::Boolean b3( b1 );
    CF::Boolean b4( b2 );
    
    ASSERT_TRUE(  b3.GetValue() );
    ASSERT_FALSE( b4.GetValue() );
}

TEST( CFPP_Boolean, MCTOR )
{
    CF::Boolean b1( true );
    CF::Boolean b2( std::move( b1 ) );
    
    ASSERT_FALSE( b1.GetValue() );
    ASSERT_FALSE( b1.IsValid() );
    ASSERT_TRUE(  b2.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignBoolean )
{
    CF::Boolean b1;
    CF::Boolean b2( true );
    CF::Boolean b3( false );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = b2;
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = b3;
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignAutoPointer )
{
    CF::Boolean b1;
    CF::Boolean b2;
    CF::Boolean b3;
    
    b1 = CF::AutoPointer( CFRetain( GetCFBooleanTrue() ) );
    b2 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    b3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE( b1.IsValid() );
    ASSERT_TRUE( b2.IsValid() );
    ASSERT_TRUE( b3.IsValid() );
    
    ASSERT_TRUE(  b1.GetValue() );
    ASSERT_FALSE( b2.GetValue() );
    ASSERT_FALSE( b3.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignCFType )
{
    CF::Boolean b1;
    CF::String  s( "hello, world" );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = static_cast< CFTypeRef >( GetCFBooleanTrue() );
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = static_cast< CFTypeRef >( GetCFBooleanFalse() );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = GetCFBooleanTrue();
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = static_cast< CFTypeRef >( s.GetCFObject() );
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignCFBoolean )
{
    CF::Boolean b1;
    CF::String  s( "hello, world" );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = GetCFBooleanTrue();
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = GetCFBooleanFalse();
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = GetCFBooleanTrue();
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = static_cast< CFBooleanRef >( s.GetCFObject() );
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignNullPointer )
{
    CF::Boolean b( true );
    
    ASSERT_TRUE( b.IsValid() );
    ASSERT_TRUE( b.GetValue() );
    
    b = nullptr;
    
    ASSERT_TRUE(  b.IsValid() );
    ASSERT_FALSE( b.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignBool )
{
    CF::Boolean b1;
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = true;
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = false;
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorEqualBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 == b1 );
    ASSERT_FALSE( b1 == b2 );
    ASSERT_TRUE(  b2 == b2 );
    ASSERT_FALSE( b2 == b1 );
}

TEST( CFPP_Boolean, OperatorEqualCFType )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 == static_cast< CFTypeRef >( GetCFBooleanTrue() ) );
    ASSERT_FALSE( b1 == static_cast< CFTypeRef >( GetCFBooleanFalse() ) );
    ASSERT_FALSE( b1 == static_cast< CFTypeRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 == static_cast< CFTypeRef >( GetCFBooleanFalse() ) );
    ASSERT_FALSE( b2 == static_cast< CFTypeRef >( GetCFBooleanTrue() ) );
    ASSERT_FALSE( b2 == static_cast< CFTypeRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorEqualCFBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 == GetCFBooleanTrue() );
    ASSERT_FALSE( b1 == GetCFBooleanFalse() );
    ASSERT_FALSE( b1 == static_cast< CFBooleanRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 == GetCFBooleanFalse() );
    ASSERT_FALSE( b2 == GetCFBooleanTrue() );
    ASSERT_FALSE( b2 == static_cast< CFBooleanRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorEqualBool )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 == true );
    ASSERT_FALSE( b1 == false );
    ASSERT_TRUE(  b2 == false );
    ASSERT_FALSE( b2 == true );
}

TEST( CFPP_Boolean, OperatorNotEqualBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 != b2 );
    ASSERT_FALSE( b1 != b1 );
    ASSERT_TRUE(  b2 != b1 );
    ASSERT_FALSE( b2 != b2 );
}

TEST( CFPP_Boolean, OperatorNotEqualCFType )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 != static_cast< CFTypeRef >( GetCFBooleanFalse() ) );
    ASSERT_FALSE( b1 != static_cast< CFTypeRef >( GetCFBooleanTrue() ) );
    ASSERT_TRUE(  b1 != static_cast< CFTypeRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 != static_cast< CFTypeRef >( GetCFBooleanTrue() ) );
    ASSERT_FALSE( b2 != static_cast< CFTypeRef >( GetCFBooleanFalse() ) );
    ASSERT_TRUE(  b2 != static_cast< CFTypeRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorNotEqualCFBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 != GetCFBooleanFalse() );
    ASSERT_FALSE( b1 != GetCFBooleanTrue() );
    ASSERT_TRUE(  b1 != static_cast< CFBooleanRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 != GetCFBooleanTrue() );
    ASSERT_FALSE( b2 != GetCFBooleanFalse() );
    ASSERT_TRUE(  b2 != static_cast< CFBooleanRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorNotEqualBool )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 != false );
    ASSERT_FALSE( b1 != true );
    ASSERT_TRUE(  b2 != true );
    ASSERT_FALSE( b2 != false );
}

TEST( CFPP_Boolean, CastToBool )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  static_cast< bool >( b1 ) );
    ASSERT_FALSE( static_cast< bool >( b2 ) );
}

TEST( CFPP_Boolean, GetTypeID )
{
    CF::Boolean b;
    
    ASSERT_EQ( b.GetTypeID(), CFBooleanGetTypeID() );
}

TEST( CFPP_Boolean, GetCFObject )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_NE( b1.GetCFObject(), static_cast< CFTypeRef >( nullptr ) );
    ASSERT_NE( b2.GetCFObject(), static_cast< CFTypeRef >( nullptr ) );
    ASSERT_EQ( b1.GetCFObject(), GetCFBooleanTrue() );
    ASSERT_EQ( b2.GetCFObject(), GetCFBooleanFalse() );
}

TEST( CFPP_Boolean, GetValue )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_EQ( b1.GetValue(), true );
    ASSERT_EQ( b2.GetValue(), false );
}

TEST( CFPP_Boolean, SetValue )
{
    CF::Boolean b( true );
    
    ASSERT_EQ( b.GetValue(), true );
    
    b.SetValue( false );
    
    ASSERT_EQ( b.GetValue(), false );
}

TEST( CFPP_Boolean, Swap )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_EQ( b1.GetValue(), true );
    ASSERT_EQ( b2.GetValue(), false );
    
    swap( b1, b2 );
    
    ASSERT_EQ( b1.GetValue(), false );
    ASSERT_EQ( b2.GetValue(), true );
}
