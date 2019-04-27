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
    
    ASSERT_TRUE( p.GetCFObject() == NULL );
}

TEST( CFPP_AutoPointer, CTOR_CFType )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    i = CFGetRetainCount( s );
    
    CF::AutoPointer p( static_cast< CFTypeRef >( s ) );
    
    ASSERT_EQ( p.GetCFObject(), s );
    ASSERT_EQ( p.GetRetainCount(), i );
}

TEST( CFPP_AutoPointer, CCTOR )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    i = CFGetRetainCount( s );
    
    CF::AutoPointer p1( s );
    CF::AutoPointer p2( p1 );
    
    ASSERT_EQ( p1.GetCFObject(), p2.GetCFObject() );
    ASSERT_EQ( CFGetRetainCount( p2.GetCFObject() ), i + 1 );
}

#ifdef CFPP_HAS_CPP11
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
#endif

TEST( CFPP_AutoPointer, DTOR )
{
    CFStringRef s;
    CFIndex     i;
    
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
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
    
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
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
    
    s1 = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    i1 = CFGetRetainCount( s1 );
    p  = s1;
    
    ASSERT_EQ( p.GetCFObject(), s1 );
    ASSERT_EQ( p.GetRetainCount(), i1 );
    
    CFRetain( s1 );
    
    ASSERT_EQ( p.GetRetainCount(), i1 + 1 );
    
    s2 = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
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
    
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    
    CF::AutoPointer p1( s );
    CF::AutoPointer p2;
    
    ASSERT_EQ( p1.GetTypeID(), CFStringGetTypeID() );
    ASSERT_EQ( p2.GetTypeID(), static_cast< CFTypeID >( 0 ) );
}

TEST( CFPP_AutoPointer, GetCFObject )
{
    CFStringRef s;
    
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    
    CF::AutoPointer p( s );
    
    ASSERT_EQ( p.GetCFObject(), s );
}

TEST( CFPP_AutoPointer, As )
{
    CFStringRef s;
    CF::String  s1;
    CF::String  s2;
    
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    
    CF::AutoPointer p( s );
    
    s1 = p.As< CFStringRef >();
    s2 = p.As< CF::String >();
    
    ASSERT_TRUE( s1.IsValid() );
    ASSERT_TRUE( s2.IsValid() );
    ASSERT_TRUE( s1 == s2 );
}
