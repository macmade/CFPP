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
 * @file        Test-CFPP-AnyObject.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::AnyObject
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_AnyObject, CTOR )
{
    CF::AnyObject o;
    
    ASSERT_TRUE( o.GetCFObject() == nullptr );
}

TEST( CFPP_AnyObject, CTOR_AutoPointer )
{
    CF::AutoPointer p( CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII ) );
    CFIndex         i( p.GetRetainCount() );
    CF::AnyObject   o( p );
    
    ASSERT_TRUE( o.IsValid() );
    ASSERT_EQ( o.GetCFObject(), p.GetCFObject() );
    ASSERT_EQ( o.GetRetainCount(), i + 1 );
}

TEST( CFPP_AnyObject, CTOR_CFType )
{
    CF::String      s( "hello, world" );
    CFIndex         i( s.GetRetainCount() );
    CF::AnyObject   o( static_cast< CFTypeRef >( s ) );
    
    ASSERT_TRUE( o.IsValid() );
    ASSERT_EQ( o.GetCFObject(), s.GetCFObject() );
    ASSERT_EQ( o.GetRetainCount(), i + 1 );
}

TEST( CFPP_AnyObject, CTOR_NullPointer )
{
    CF::AnyObject o( nullptr );
    
    ASSERT_FALSE( o.IsValid() );
}

TEST( CFPP_AnyObject, CCTOR )
{
    CF::String      s( "hello, world" );
    CFIndex         i( s.GetRetainCount() );
    CF::AnyObject   o1( s );
    CF::AnyObject   o2( o1 );
    
    ASSERT_TRUE( o1.IsValid() );
    ASSERT_TRUE( o2.IsValid() );
    ASSERT_EQ( o2.GetCFObject(), s.GetCFObject() );
    ASSERT_EQ( o2.GetRetainCount(), i + 2 );
}

TEST( CFPP_AnyObject, MCTOR )
{
    CF::String      s( "hello, world" );
    CFIndex         i( s.GetRetainCount() );
    CF::AnyObject   o1( s );
    CF::AnyObject   o2( std::move( o1 ) );
    
    ASSERT_FALSE( o1.IsValid() );
    ASSERT_TRUE( o2.IsValid() );
    ASSERT_EQ( o2.GetCFObject(), s.GetCFObject() );
    ASSERT_EQ( o2.GetRetainCount(), i + 1 );
}

TEST( CFPP_AnyObject, DTOR )
{
    CF::String s( "hello, world" );
    CFIndex    i( s.GetRetainCount() );
    
    {
        CF::AnyObject o( s );
        
        ASSERT_TRUE( o.IsValid() );
        ASSERT_EQ( s.GetRetainCount(), i + 1 );
    }
    
    ASSERT_EQ( s.GetRetainCount(), i );
}

TEST( CFPP_AnyObject, OperatorAssign )
{
    CF::String     s( "hello, world" );
    CF::AnyObject o1( s );
    CF::AnyObject o2;
    CFIndex        i( o1.GetRetainCount() );
    
    ASSERT_TRUE(  o1.IsValid() );
    ASSERT_FALSE( o2.IsValid() );
    
    o2 = o1;
    
    ASSERT_TRUE( o1.IsValid() );
    ASSERT_TRUE( o2.IsValid() );
    ASSERT_EQ( o2.GetCFObject(), o1.GetCFObject() );
    ASSERT_EQ( o1.GetRetainCount(), i + 1 );
}

TEST( CFPP_AnyObject, OperatorAssignAutoPointer )
{
    CF::AutoPointer p( CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII ) );
    CF::AnyObject   o;
    CFIndex         i( p.GetRetainCount() );
    
    ASSERT_TRUE(  p.IsValid() );
    ASSERT_FALSE( o.IsValid() );
    
    o = p;
    
    ASSERT_TRUE( p.IsValid() );
    ASSERT_TRUE( o.IsValid() );
    ASSERT_EQ( o.GetCFObject(), p.GetCFObject() );
    ASSERT_EQ( o.GetRetainCount(), i + 1 );
}

TEST( CFPP_AnyObject, OperatorAssignCFType )
{
    CF::String    s( "hello, world" );
    CF::AnyObject o;
    CFIndex       i( s.GetRetainCount() );
    
    ASSERT_TRUE(  s.IsValid() );
    ASSERT_FALSE( o.IsValid() );
    
    o = static_cast< CFTypeRef >( s );
    
    ASSERT_TRUE( s.IsValid() );
    ASSERT_TRUE( o.IsValid() );
    ASSERT_EQ( o.GetCFObject(), s.GetCFObject() );
    ASSERT_EQ( o.GetRetainCount(), i + 1 );
}

TEST( CFPP_AnyObject, OperatorAssignNullPointer )
{
    CF::String    s( "hello, world" );
    CFIndex       i( s.GetRetainCount() );
    CF::AnyObject o( s );
    
    ASSERT_TRUE( s.IsValid() );
    ASSERT_TRUE( o.IsValid() );
    
    o = nullptr;
    
    ASSERT_TRUE(  s.IsValid() );
    ASSERT_FALSE( o.IsValid() );
    ASSERT_EQ( s.GetRetainCount(), i );
}

TEST( CFPP_AnyObject, GetTypeID )
{
    CF::AnyObject o1 { CF::Dictionary() };
    CF::AnyObject o2 { CF::Array() };
    CF::AnyObject o3;
    
    ASSERT_TRUE( o1.GetTypeID() == CFDictionaryGetTypeID() );
    ASSERT_TRUE( o2.GetTypeID() == CFArrayGetTypeID() );
    ASSERT_TRUE( o3.GetTypeID() == 0 );
}

TEST( CFPP_AnyObject, GetCFObject )
{
    CF::Dictionary d;
    CF::Array      a;
    CF::AnyObject  o1( d );
    CF::AnyObject  o2( a );
    CF::AnyObject  o3;
    
    ASSERT_TRUE(  o1.IsValid() );
    ASSERT_TRUE(  o2.IsValid() );
    ASSERT_FALSE( o3.IsValid() );
    
    ASSERT_TRUE( o1.GetCFObject() == d.GetCFObject() );
    ASSERT_TRUE( o2.GetCFObject() == a.GetCFObject() );
    ASSERT_TRUE( o3.GetCFObject() == nullptr );
}

TEST( CFPP_AnyObject, As )
{
    CF::String    s1;
    CF::String    s2;
    CF::AnyObject o( CF::String( "hello, world" ) );
    
    s1 = o.As< CFStringRef >();
    s2 = o.As< CF::String >();
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s1 == s2 );
}

TEST( CFPP_AnyObject, Swap )
{
    CF::AnyObject o1 { CF::Dictionary() };
    CF::AnyObject o2 { CF::Array() };
    
    ASSERT_TRUE( o1.GetTypeID() == CFDictionaryGetTypeID() );
    ASSERT_TRUE( o2.GetTypeID() == CFArrayGetTypeID() );
    
    swap( o1, o2 );
    
    ASSERT_TRUE( o1.GetTypeID() == CFArrayGetTypeID() );
    ASSERT_TRUE( o2.GetTypeID() == CFDictionaryGetTypeID() );
}
