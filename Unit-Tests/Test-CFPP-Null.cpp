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
 * @file        Test-CFPP-Null.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Null
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Null, CTOR )
{
    CF::Null n;
    
    ASSERT_TRUE( n.IsValid() );
    
    #ifndef _WIN32
    ASSERT_EQ( n.GetCFObject(), kCFNull );
    #endif
}

TEST( CFPP_Null, CCTOR )
{
    CF::Null n1;
    CF::Null n2( n1 );
    CF::Null n3( CF::Null( static_cast< CFNullRef >( nullptr ) ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_TRUE(  n2.IsValid() );
    ASSERT_FALSE( n3.IsValid() );
}

TEST( CFPP_Null, CTOR_CFTypeRef )
{
    CF::Null n1( kCFNull );
    CF::Null n2( static_cast< CFTypeRef >( nullptr ) );
    CF::Null n3( static_cast< CFTypeRef >( CF::Array() ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_FALSE( n2.IsValid() );
    ASSERT_FALSE( n3.IsValid() );
}

TEST( CFPP_Null, MCTOR )
{
    CF::Null n1;
    CF::Null n2( std::move( n1 ) );
    
    ASSERT_TRUE( n2.IsValid() );
}

TEST( CFPP_Null, OperatorAssign )
{
    CF::Null n1;
    CF::Null n2( CF::Null( static_cast< CFNullRef >( nullptr ) ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_FALSE( n2.IsValid() );
    
    n2 = n1;
    
    ASSERT_TRUE( n1.IsValid() );
    ASSERT_TRUE( n2.IsValid() );
}

TEST( CFPP_Null, OperatorAssign_CFTypeRef )
{
    CF::Null n( static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_FALSE( n.IsValid() );
    
    n = static_cast< CFTypeRef >( kCFNull );
    
    ASSERT_TRUE( n.IsValid() );
    
    n = static_cast< CFTypeRef >( nullptr );
    
    ASSERT_FALSE( n.IsValid() );
}

TEST( CFPP_Null, GetTypeID )
{
    CF::Null n;
    
    ASSERT_EQ( n.GetTypeID(), CFNullGetTypeID() );
}

TEST( CFPP_Null, GetCFObject )
{
    CF::Null n1;
    CF::Null n2( static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_TRUE( n1.GetCFObject() != nullptr );
    ASSERT_TRUE( n2.GetCFObject() == nullptr );
}

TEST( CFPP_Null, Swap )
{
    CF::Null n1;
    CF::Null n2( static_cast< CFTypeRef >( nullptr ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_FALSE( n2.IsValid() );
    
    swap( n1, n2 );
    
    ASSERT_TRUE(  n2.IsValid() );
    ASSERT_FALSE( n1.IsValid() );
}
