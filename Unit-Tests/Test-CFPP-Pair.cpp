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
 * @file        Test-CFPP-Pair.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Pair
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Pair, CTOR_CFType_CFType )
{
    CF::String s1( "hello" );
    CF::String s2( "world" );
    CF::Pair   p( static_cast< CFTypeRef >( s1.GetCFObject() ), static_cast< CFTypeRef >( s2.GetCFObject() ) );
    
    ASSERT_TRUE( p.GetKey()   == s1.GetCFObject() );
    ASSERT_TRUE( p.GetValue() == s2.GetCFObject() );
}

TEST( CFPP_Pair, CTOR_String_CFType )
{
    CF::String s1( "hello" );
    CF::String s2( "world" );
    CF::Pair   p( s1, static_cast< CFTypeRef >( s2.GetCFObject() ) );
    
    ASSERT_TRUE( p.GetKey()   == s1.GetCFObject() );
    ASSERT_TRUE( p.GetValue() == s2.GetCFObject() );
}

TEST( CFPP_Pair, CTOR_CChar_CFType )
{
    const char * s1 = "hello";
    CF::String   s2( "world" );
    CF::Pair     p( s1, static_cast< CFTypeRef >( s2.GetCFObject() ) );
    
    ASSERT_TRUE( CF::String( p.GetKey() ) == s1 );
    ASSERT_TRUE( p.GetValue() == s2.GetCFObject() );
}

TEST( CFPP_Pair, CTOR_String_String )
{
    CF::String s1( "hello" );
    CF::String s2( "world" );
    CF::Pair   p( s1, s2 );
    
    ASSERT_TRUE( p.GetKey()   == s1.GetCFObject() );
    ASSERT_TRUE( p.GetValue() == s2.GetCFObject() );
}

TEST( CFPP_Pair, CTOR_CChar_String )
{
    const char * s1 = "hello";
    CF::String   s2( "world" );
    CF::Pair     p( s1, s2 );
    
    ASSERT_TRUE( CF::String( p.GetKey() ) == s1 );
    ASSERT_TRUE( p.GetValue() == s2.GetCFObject() );
}

TEST( CFPP_Pair, CTOR_String_CChar )
{
    CF::String   s1( "hello" );
    const char * s2 = "world";
    CF::Pair     p( s1, s2 );
    
    ASSERT_TRUE( p.GetKey() == s1.GetCFObject() );
    ASSERT_TRUE( CF::String( p.GetValue() ) == s2 );
}

TEST( CFPP_Pair, CTOR_CChar_CChar )
{
    const char * s1 = "hello";
    const char * s2 = "world";
    CF::Pair     p( s1, s2 );
    
    ASSERT_TRUE( CF::String( p.GetKey() )   == s1 );
    ASSERT_TRUE( CF::String( p.GetValue() ) == s2 );
}

TEST( CFPP_Pair, CCTOR )
{
    CF::Pair p1( "hello", "world" );
    CF::Pair p2( p1 );
    
    ASSERT_EQ( p1.GetKey(),   p2.GetKey() );
    ASSERT_EQ( p1.GetValue(), p2.GetValue() );
}

TEST( CFPP_Pair, MCTOR )
{
    CF::Pair p1( "hello", "world" );
    CF::Pair p2( std::move( p1 ) );
    
    ASSERT_TRUE(  p1.GetKey()   == nullptr );
    ASSERT_TRUE(  p1.GetValue() == nullptr );
    ASSERT_FALSE( p2.GetKey()   == nullptr );
    ASSERT_FALSE( p2.GetValue() == nullptr );
}

TEST( CFPP_Pair, OperatorAssign )
{
    CF::Pair p1( "hello", "world" );
    CF::Pair p2( "hi",    "universe" );
    
    ASSERT_EQ( CF::String( p1.GetKey() ),   "hello" );
    ASSERT_EQ( CF::String( p1.GetValue() ), "world" );
    
    p1 = p2;
    
    ASSERT_EQ( CF::String( p1.GetKey() ),   "hi" );
    ASSERT_EQ( CF::String( p1.GetValue() ), "universe" );
}

TEST( CFPP_Pair, GetKey )
{
    CF::Pair p1( "hello", "world" );
    
    ASSERT_TRUE( p1.GetKey() != nullptr );
}

TEST( CFPP_Pair, GetValue )
{
    CF::Pair p1( "hello", "world" );
    
    ASSERT_TRUE( p1.GetValue() != nullptr );
}

TEST( CFPP_Pair, GetKeyTypeID )
{
    CF::Pair p1( "hello",                          static_cast< CFTypeRef >( nullptr ) );
    CF::Pair p2( CF::Number( 0 ),                  static_cast< CFTypeRef >( nullptr ) );
    CF::Pair p3( static_cast< CFTypeRef >( nullptr ), static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_TRUE( p1.GetKeyTypeID() == CFStringGetTypeID() );
    ASSERT_TRUE( p2.GetKeyTypeID() == CFNumberGetTypeID() );
    ASSERT_TRUE( p3.GetKeyTypeID() == 0 );
}

TEST( CFPP_Pair, GetValueTypeID )
{
    CF::Pair p1( "hello", "world" );
    CF::Pair p2( "hello", CF::Number( 0 ) );
    CF::Pair p3( "hello", static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_TRUE( p1.GetValueTypeID() == CFStringGetTypeID() );
    ASSERT_TRUE( p2.GetValueTypeID() == CFNumberGetTypeID() );
    ASSERT_TRUE( p3.GetValueTypeID() == 0 );
}

TEST( CFPP_Pair, SetKey )
{
    CF::Pair p1( "hello", "world" );
    
    p1.SetKey( CF::String( "hi" ) );
    
    ASSERT_EQ( CF::String( p1.GetKey() ), "hi" );
    
    p1.SetKey( nullptr );
    
    ASSERT_TRUE( p1.GetKey() == nullptr );
}

TEST( CFPP_Pair, SetValue )
{
    CF::Pair p1( "hello", "world" );
    
    p1.SetValue( CF::String( "universe" ) );
    
    ASSERT_EQ( CF::String( p1.GetValue() ), "universe" );
    
    p1.SetValue( nullptr );
    
    ASSERT_TRUE( p1.GetValue() == nullptr );
}

TEST( CFPP_Pair, Swap )
{
    CF::Pair p1( "hello", "world" );
    CF::Pair p2( "hi",    "universe" );
    
    ASSERT_EQ( CF::String( p1.GetKey() ),   "hello" );
    ASSERT_EQ( CF::String( p1.GetValue() ), "world" );
    ASSERT_EQ( CF::String( p2.GetKey() ),   "hi" );
    ASSERT_EQ( CF::String( p2.GetValue() ), "universe" );
    
    swap( p1, p2 );
    
    ASSERT_EQ( CF::String( p2.GetKey() ),   "hello" );
    ASSERT_EQ( CF::String( p2.GetValue() ), "world" );
    ASSERT_EQ( CF::String( p1.GetKey() ),   "hi" );
    ASSERT_EQ( CF::String( p1.GetValue() ), "universe" );
}
