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
 * @file        Test-CFPP-Object.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Object
 */

#include <CF++.hpp>
#include "Constants.hpp"

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Object, CTOR )
{
    CF::Object< CFBagRef > o;
    
    ASSERT_FALSE( o.IsValid() );
}

TEST( CFPP_Object, CTOR_AutoPointer )
{
    CF::Object< CFBagRef > o1( CF::AutoPointer( CFBagCreate( NULL, NULL, 0, NULL ) ) );
    CF::Object< CFBagRef > o2( CF::AutoPointer( NULL ) );
    
    ASSERT_TRUE(  o1.IsValid() );
    ASSERT_FALSE( o2.IsValid() );
}

TEST( CFPP_Object, CTOR_CFBag )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( NULL, NULL, 0, NULL );
    
    {
        CF::Object< CFBagRef > o1( static_cast< CFBagRef >( cfB ) );
        CF::Object< CFBagRef > o2( static_cast< CFBagRef >( NULL ) );
        
        ASSERT_TRUE(  o1.IsValid() );
        ASSERT_FALSE( o2.IsValid() );
    }
    
    CFRelease( cfB );
}

TEST( CFPP_Object, CCTOR )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( NULL, NULL, 0, NULL );
    
    {
        CF::Object< CFBagRef > o1( cfB );
        CF::Object< CFBagRef > o2( o1 );
        
        ASSERT_TRUE( o2.IsValid() );
        ASSERT_EQ( o1.GetCFObject(), o2.GetCFObject() );
    }
    
    CFRelease( cfB );
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Object, MCTOR )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( NULL, NULL, 0, NULL );
    
    {
        CF::Object< CFBagRef > o1( cfB );
        CF::Object< CFBagRef > o2( std::move( o1 ) );
        
        ASSERT_FALSE( o1.IsValid() );
        ASSERT_TRUE(  o2.IsValid() );
    }
    
    CFRelease( cfB );
}
#endif

TEST( CFPP_Object, OperatorAssignBag )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( NULL, NULL, 0, NULL );
    
    {
        CF::Object< CFBagRef > o1( cfB );
        CF::Object< CFBagRef > o2;
        
        o2 = o1;
        
        ASSERT_TRUE( o1.IsValid() );
        ASSERT_TRUE( o2.IsValid() );
        ASSERT_EQ( o1.GetCFObject(), o2.GetCFObject() );
    }
    
    CFRelease( cfB );
}

TEST( CFPP_Object, OperatorAssignAutoPointer )
{
    CF::Object< CFBagRef > o1;
    
    ASSERT_FALSE( o1.IsValid() );
    
    o1 = CF::AutoPointer( CFBagCreate( NULL, NULL, 0, NULL ) );
    
    ASSERT_TRUE(  o1.IsValid() );
}

TEST( CFPP_Object, OperatorAssignCFBag )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( NULL, NULL, 0, NULL );
    
    {
        CF::Object< CFBagRef > o1;
        
        o1 = static_cast< CFBagRef >( cfB );
        
        ASSERT_TRUE( o1.IsValid() );
        
        o1 = static_cast< CFBagRef >( NULL );
        
        ASSERT_FALSE( o1.IsValid() );
    }
    
    CFRelease( cfB );
}

TEST( CFPP_Object, GetTypeID )
{
    CF::Object< CFBagRef > o1;
    
    ASSERT_EQ( o1.GetTypeID(), static_cast< CFTypeID >( 0 ) );
    
    o1 = CF::AutoPointer( CFBagCreate( NULL, NULL, 0, NULL ) );
    
    ASSERT_EQ( o1.GetTypeID(), CFBagGetTypeID() );
}

TEST( CFPP_Object, GetCFObject )
{
    CF::Object< CFBagRef > o1( CF::AutoPointer( CFBagCreate( NULL, NULL, 0, NULL ) ) );
    CF::Object< CFBagRef > o2;
    
    ASSERT_TRUE( o1.GetCFObject() != NULL );
    ASSERT_TRUE( o2.GetCFObject() == NULL );
    ASSERT_EQ( CFGetTypeID( o1.GetCFObject() ), CFBagGetTypeID() );
}

TEST( CFPP_Object, Swap )
{
    CF::Object< CFBagRef > o1( CF::AutoPointer( CFBagCreate( NULL, NULL, 0, NULL ) ) );
    CF::Object< CFBagRef > o2;
    
    swap( o1, o2 );
    
    ASSERT_FALSE( o1.IsValid() );
    ASSERT_TRUE(  o2.IsValid() );
}
