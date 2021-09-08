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
 * @file        Test-CFPP-AutoPointer.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::AutoPointer
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_AutoPointer, CTOR )
{
    CF::AutoPointer p;
    
    ASSERT_TRUE( p.GetCFObject() == nullptr );
}

TEST( CFPP_AutoPointer, CTOR_CFType )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    i = CFGetRetainCount( s );
    
    CF::AutoPointer p( static_cast< CFTypeRef >( s ) );
    
    ASSERT_EQ( p.GetCFObject(), s );
    ASSERT_EQ( p.GetRetainCount(), i );
}

TEST( CFPP_AutoPointer, CCTOR )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    i = CFGetRetainCount( s );
    
    CF::AutoPointer p1( s );
    CF::AutoPointer p2( p1 );
    
    ASSERT_EQ( p1.GetCFObject(), p2.GetCFObject() );
    ASSERT_EQ( CFGetRetainCount( p2.GetCFObject() ), i + 1 );
}

TEST( CFPP_AutoPointer, MCTOR )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    i = CFGetRetainCount( s );
    
    CF::AutoPointer p1( s );
    CF::AutoPointer p2( std::move( p1 ) );
    
    ASSERT_EQ( p1.GetCFObject(), static_cast< CFTypeRef >( nullptr ) );
    ASSERT_EQ( p2.GetRetainCount(), i );
}

TEST( CFPP_AutoPointer, DTOR )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    i = CFGetRetainCount( s );
    
    CFRetain( s );
    
    {
        CF::AutoPointer p( s );
        
        ASSERT_EQ( p.GetRetainCount(), i + 1 );
    }
    
    ASSERT_EQ( CFGetRetainCount( s ), i );
    CFRelease( s );
}

TEST( CFPP_AutoPointer, OperatorAssignAutoPointer )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    i = CFGetRetainCount( s );
    
    CF::AutoPointer p1( s );
    
    ASSERT_EQ( p1.GetRetainCount(), i );
    
    CF::AutoPointer p2;
    
    p2 = p1;
    
    ASSERT_EQ( p1.GetCFObject(), p2.GetCFObject() );
    ASSERT_EQ( p2.GetRetainCount(), i + 1 );
}

TEST( CFPP_AutoPointer, OperatorAssignCFType )
{
    CF::AutoPointer p;
    CFStringRef     s1;
    CFStringRef     s2;
    CFIndex         i1;
    CFIndex         i2;
    
    s1 = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    i1 = CFGetRetainCount( s1 );
    p  = s1;
    
    ASSERT_EQ( p.GetCFObject(), s1 );
    ASSERT_EQ( p.GetRetainCount(), i1 );
    
    CFRetain( s1 );
    
    ASSERT_EQ( p.GetRetainCount(), i1 + 1 );
    
    s2 = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    i2 = CFGetRetainCount( s2 );
    p  = s2;
    
    ASSERT_EQ( p.GetCFObject(), s2 );
    ASSERT_EQ( p.GetRetainCount(), i2 );
    ASSERT_EQ( CFGetRetainCount( s1 ), i1 );
    
    CFRelease( s1 );
}

TEST( CFPP_AutoPointer, GetTypeID )
{
    CFStringRef s;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    
    CF::AutoPointer p1( s );
    CF::AutoPointer p2;
    
    ASSERT_EQ( p1.GetTypeID(), CFStringGetTypeID() );
    ASSERT_EQ( p2.GetTypeID(), static_cast< CFTypeID >( 0 ) );
}

TEST( CFPP_AutoPointer, GetCFObject )
{
    CFStringRef s;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    
    CF::AutoPointer p( s );
    
    ASSERT_EQ( p.GetCFObject(), s );
}

TEST( CFPP_AutoPointer, As )
{
    CFStringRef s;
    CF::String  s1;
    CF::String  s2;
    
    s = CFStringCreateWithCString( nullptr, "hello, world", kCFStringEncodingASCII );
    
    CF::AutoPointer p( s );
    
    s1 = p.As< CFStringRef >();
    s2 = p.As< CF::String >();
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s1 == s2 );
}
