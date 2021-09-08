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
    CF::Object< CFBagRef > o1( CF::AutoPointer( CFBagCreate( nullptr, nullptr, 0, nullptr ) ) );
    CF::Object< CFBagRef > o2( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  o1.IsValid() );
    ASSERT_FALSE( o2.IsValid() );
}

TEST( CFPP_Object, CTOR_CFBag )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( nullptr, nullptr, 0, nullptr );
    
    {
        CF::Object< CFBagRef > o1( static_cast< CFBagRef >( cfB ) );
        CF::Object< CFBagRef > o2( static_cast< CFBagRef >( nullptr ) );
        
        ASSERT_TRUE(  o1.IsValid() );
        ASSERT_FALSE( o2.IsValid() );
    }
    
    CFRelease( cfB );
}

TEST( CFPP_Object, CCTOR )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( nullptr, nullptr, 0, nullptr );
    
    {
        CF::Object< CFBagRef > o1( cfB );
        CF::Object< CFBagRef > o2( o1 );
        
        ASSERT_TRUE( o2.IsValid() );
        ASSERT_EQ( o1.GetCFObject(), o2.GetCFObject() );
    }
    
    CFRelease( cfB );
}

TEST( CFPP_Object, MCTOR )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( nullptr, nullptr, 0, nullptr );
    
    {
        CF::Object< CFBagRef > o1( cfB );
        CF::Object< CFBagRef > o2( std::move( o1 ) );
        
        ASSERT_FALSE( o1.IsValid() );
        ASSERT_TRUE(  o2.IsValid() );
    }
    
    CFRelease( cfB );
}

TEST( CFPP_Object, OperatorAssignBag )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( nullptr, nullptr, 0, nullptr );
    
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
    
    o1 = CF::AutoPointer( CFBagCreate( nullptr, nullptr, 0, nullptr ) );
    
    ASSERT_TRUE(  o1.IsValid() );
}

TEST( CFPP_Object, OperatorAssignCFBag )
{
    CFBagRef cfB;
    
    cfB = CFBagCreate( nullptr, nullptr, 0, nullptr );
    
    {
        CF::Object< CFBagRef > o1;
        
        o1 = static_cast< CFBagRef >( cfB );
        
        ASSERT_TRUE( o1.IsValid() );
        
        o1 = static_cast< CFBagRef >( nullptr );
        
        ASSERT_FALSE( o1.IsValid() );
    }
    
    CFRelease( cfB );
}

TEST( CFPP_Object, GetTypeID )
{
    CF::Object< CFBagRef > o1;
    
    ASSERT_EQ( o1.GetTypeID(), static_cast< CFTypeID >( 0 ) );
    
    o1 = CF::AutoPointer( CFBagCreate( nullptr, nullptr, 0, nullptr ) );
    
    ASSERT_EQ( o1.GetTypeID(), CFBagGetTypeID() );
}

TEST( CFPP_Object, GetCFObject )
{
    CF::Object< CFBagRef > o1( CF::AutoPointer( CFBagCreate( nullptr, nullptr, 0, nullptr ) ) );
    CF::Object< CFBagRef > o2;
    
    ASSERT_TRUE( o1.GetCFObject() != nullptr );
    ASSERT_TRUE( o2.GetCFObject() == nullptr );
    ASSERT_EQ( CFGetTypeID( o1.GetCFObject() ), CFBagGetTypeID() );
}

TEST( CFPP_Object, Swap )
{
    CF::Object< CFBagRef > o1( CF::AutoPointer( CFBagCreate( nullptr, nullptr, 0, nullptr ) ) );
    CF::Object< CFBagRef > o2;
    
    swap( o1, o2 );
    
    ASSERT_FALSE( o1.IsValid() );
    ASSERT_TRUE(  o2.IsValid() );
}
