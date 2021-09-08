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
 * @file        Test-CFPP-Error.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Error
 */

#include <CF++.hpp>
#include "Constants.hpp"

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Error, CTOR )
{
    CF::Error e;
    
    ASSERT_FALSE( e.IsValid() );
}

TEST( CFPP_Error, CTOR_AutoPointer )
{
    CF::Error e1( CF::AutoPointer( CFErrorCreate( nullptr, CF::String( "com.xs-labs" ), 0, nullptr ) ) );
    CF::Error e2( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::Error e3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  e1.IsValid() );
    ASSERT_FALSE( e2.IsValid() );
    ASSERT_FALSE( e3.IsValid() );
}

TEST( CFPP_Error, CTOR_CFType )
{
    CFErrorRef cfE;
    
    cfE = CFErrorCreate( nullptr, CFSTR( "com.xs-labs" ), 42, nullptr );
    
    {
        CF::Error e1( static_cast< CFTypeRef >( cfE ) );
        CF::Error e2( static_cast< CFTypeRef >( nullptr ) );
        CF::Error e3( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
        
        ASSERT_TRUE(  e1.IsValid() );
        ASSERT_FALSE( e2.IsValid() );
        ASSERT_FALSE( e3.IsValid() );
        ASSERT_EQ( e1.GetDomain(), "com.xs-labs" );
    }
    
    CFRelease( cfE );
}

TEST( CFPP_Error, CTOR_CFError )
{
    CFErrorRef cfE;
    
    cfE = CFErrorCreate( nullptr, CFSTR( "com.xs-labs" ), 42, nullptr );
    
    {
        CF::Error e1( static_cast< CFErrorRef >( cfE ) );
        CF::Error e2( static_cast< CFErrorRef >( nullptr ) );
        CF::Error e3( static_cast< CFErrorRef >( const_cast< void * >( CF::Boolean().GetCFObject() ) ) );
        
        ASSERT_TRUE(  e1.IsValid() );
        ASSERT_FALSE( e2.IsValid() );
        ASSERT_FALSE( e3.IsValid() );
        ASSERT_EQ( e1.GetDomain(), "com.xs-labs" );
    }
    
    CFRelease( cfE );
}

TEST( CFPP_Error, CTOR_NullPointer )
{
    CF::Error e( nullptr );
    
    ASSERT_FALSE( e.IsValid() );
}

TEST( CFPP_Error, CTOR_StringDomain_NumberCode )
{
    CF::Error e( CF::String( "com.xs-labs" ), CF::Number( 42 ) );
    
    ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e.GetCode(), 42 );
}

TEST( CFPP_Error, CTOR_StringDomain_NumberCode_DictionaryInfo )
{
    CF::Dictionary info;
    
    info << CF::Pair( "hello", "hello, world" );
    
    {
        CF::Error e( CF::String( "com.xs-labs" ), CF::Number( 42 ), info );
        
        ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
        ASSERT_EQ( e.GetCode(), 42 );
        ASSERT_GT( e.GetUserInfo().GetCount(), 0 );
        ASSERT_EQ( CF::String( e.GetUserInfo()[ "hello" ] ), "hello, world" );
    }
}

TEST( CFPP_Error, CTOR_CFDomain_CFCode )
{
    CF::Error e( CFSTR( "com.xs-labs" ), 42 );
    
    ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e.GetCode(), 42 );
}

TEST( CFPP_Error, CTOR_CFDomain_CFCode_CFInfo )
{
    CF::Dictionary info;
    
    info << CF::Pair( "hello", "hello, world" );
    
    {
        CF::Error e( CFSTR( "com.xs-labs" ), 42, static_cast< CFDictionaryRef >( info.GetCFObject() ) );
        
        ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
        ASSERT_EQ( e.GetCode(), 42 );
        ASSERT_GT( e.GetUserInfo().GetCount(), 0 );
        ASSERT_EQ( CF::String( e.GetUserInfo()[ "hello" ] ), "hello, world" );
    }
}

TEST( CFPP_Error, CTOR_STDStringDomain_CFCode )
{
    CF::Error e( std::string( "com.xs-labs" ), 42 );
    
    ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e.GetCode(), 42 );
}

TEST( CFPP_Error, CTOR_STDStringDomain_CFCode_DictionaryInfo )
{
    CF::Dictionary info;
    
    info << CF::Pair( "hello", "hello, world" );
    
    {
        CF::Error e( std::string( "com.xs-labs" ), 42, static_cast< CFDictionaryRef >( info.GetCFObject() ) );
        
        ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
        ASSERT_EQ( e.GetCode(), 42 );
        ASSERT_GT( e.GetUserInfo().GetCount(), 0 );
        ASSERT_EQ( CF::String( e.GetUserInfo()[ "hello" ] ), "hello, world" );
    }
}

TEST( CFPP_Error, CTOR_CCharDomain_CFCode )
{
    CF::Error e( "com.xs-labs", 42 );
    
    ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e.GetCode(), 42 );
}

TEST( CFPP_Error, CTOR_CCharDomain_CFCode_DictionaryInfo )
{
    CF::Dictionary info;
    
    info << CF::Pair( "hello", "hello, world" );
    
    {
        CF::Error e( "com.xs-labs", 42, static_cast< CFDictionaryRef >( info.GetCFObject() ) );
        
        ASSERT_EQ( e.GetDomain(), "com.xs-labs" );
        ASSERT_EQ( e.GetCode(), 42 );
        ASSERT_GT( e.GetUserInfo().GetCount(), 0 );
        ASSERT_EQ( CF::String( e.GetUserInfo()[ "hello" ] ), "hello, world" );
    }
}

TEST( CFPP_Error, CCTOR )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2( e1 );
    
    ASSERT_TRUE( e2.IsValid() );
    ASSERT_EQ( e2.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e2.GetCode(), 42 );
}

TEST( CFPP_Error, MCTOR )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2( std::move( e1 ) );
    
    ASSERT_FALSE( e1.IsValid() );
    ASSERT_TRUE(  e2.IsValid() );
    ASSERT_EQ( e2.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e2.GetCode(), 42 );
}

TEST( CFPP_Error, OperatorAssignError )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2( "org.xs-labs", 0 );
    
    e2 = e1;
    
    ASSERT_TRUE(  e2.IsValid() );
    ASSERT_EQ( e2.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e2.GetCode(), 42 );
}

TEST( CFPP_Error, OperatorAssignAutoPointer )
{
    CF::Error e1;
    CF::Error e2( "com.xs-labs", 0 );
    CF::Error e3( "org.xs-labs", 0 );
    
    ASSERT_FALSE( e1.IsValid() );
    ASSERT_TRUE(  e2.IsValid() );
    ASSERT_TRUE(  e3.IsValid() );
    
    e1 = CF::AutoPointer( CFErrorCreate( nullptr, CF::String( "com.xs-labs" ), 0, nullptr ) );
    e2 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    e3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE(  e1.IsValid() );
    ASSERT_FALSE( e2.IsValid() );
    ASSERT_FALSE( e3.IsValid() );
}

TEST( CFPP_Error, OperatorAssignCFType )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2( "org.xs-labs", 0 );
    
    e2 = static_cast< CFTypeRef >( e1.GetCFObject() );
    
    ASSERT_TRUE(  e2.IsValid() );
    ASSERT_EQ( e2.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e2.GetCode(), 42 );
    
    e2 = static_cast< CFTypeRef >( nullptr );
    
    ASSERT_FALSE( e2.IsValid() );
}

TEST( CFPP_Error, OperatorAssignCFError )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2( "org.xs-labs", 0 );
    
    e2 = static_cast< CFErrorRef >( const_cast< void * >( e1.GetCFObject() ) );
    
    ASSERT_TRUE(  e2.IsValid() );
    ASSERT_EQ( e2.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e2.GetCode(), 42 );
    
    e2 = static_cast< CFErrorRef >( nullptr );
    
    ASSERT_FALSE( e2.IsValid() );
}

TEST( CFPP_Error, OperatorAssignNullPointer )
{
    CF::Error e( "com.xs-labs", 42 );
    
    ASSERT_TRUE( e.IsValid() );
    
    e = nullptr;
    
    ASSERT_FALSE( e.IsValid() );
}

TEST( CFPP_Error, GetTypeID )
{
    CF::Error e;
    
    ASSERT_EQ( e.GetTypeID(), CFErrorGetTypeID() );
}

TEST( CFPP_Error, GetCFObject )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2;
    
    ASSERT_TRUE( e1.GetCFObject() != nullptr );
    ASSERT_TRUE( e2.GetCFObject() == nullptr );
    ASSERT_EQ( CFGetTypeID( e1.GetCFObject() ), CFErrorGetTypeID() );
}

TEST( CFPP_Error, GetDomain )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2;
    
    ASSERT_EQ( e1.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e2.GetDomain(), "" );
}

TEST( CFPP_Error, GetCode )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2;
    
    ASSERT_EQ( e1.GetCode(), 42 );
    ASSERT_EQ( e2.GetCode(), 0 );
}

TEST( CFPP_Error, GetUserInfo )
{
    CF::Dictionary info;
    
    info << CF::Pair( CF::String( "hello" ), CF::String( "hello, world" ) );
    
    {
        CF::Dictionary i;
        CF::Error      e( "com.xs-labs", 42, info );
        
        ASSERT_GT( e.GetUserInfo().GetCount(), 0 );
        ASSERT_EQ( CF::String( e.GetUserInfo()[ "hello" ] ), "hello, world" );
        
        e = static_cast< CFErrorRef >( nullptr );
        
        ASSERT_FALSE( e.IsValid() );
        ASSERT_EQ( e.GetUserInfo().GetCount(), 0 );
    }
}

TEST( CFPP_Error, GetDescription )
{
    CF::Dictionary info;
    
    info << CF::Pair( CF::String( GetCFErrorLocalizedDescriptionKey() ), CF::String( "hello, world" ) );
    
    {
        CF::Error e( "com.xs-labs", 42, info );
        
        ASSERT_EQ( e.GetDescription(), "hello, world" );
        
        e = static_cast< CFErrorRef >( nullptr );
        
        ASSERT_FALSE( e.IsValid() );
        ASSERT_EQ( e.GetDescription(), "" );
    }
}

TEST( CFPP_Error, GetFailureReason )
{
    CF::Dictionary info;
    
    info << CF::Pair( CF::String( GetCFErrorLocalizedFailureReasonKey() ), CF::String( "hello, world" ) );
    
    {
        CF::Error e( "com.xs-labs", 42, info );
        
        ASSERT_EQ( e.GetFailureReason(), "hello, world" );
        
        e = static_cast< CFErrorRef >( nullptr );
        
        ASSERT_FALSE( e.IsValid() );
        ASSERT_EQ( e.GetFailureReason(), "" );
    }
}

TEST( CFPP_Error, GetRecoverySuggestion )
{
    CF::Dictionary info;
    
    info << CF::Pair( CF::String( GetCFErrorLocalizedRecoverySuggestionKey() ), CF::String( "hello, world" ) );
    
    {
        CF::Error e( "com.xs-labs", 42, info );
        
        ASSERT_EQ( e.GetRecoverySuggestion(), "hello, world" );
        
        e = static_cast< CFErrorRef >( nullptr );
        
        ASSERT_FALSE( e.IsValid() );
        ASSERT_EQ( e.GetRecoverySuggestion(), "" );
    }
}

TEST( CFPP_Error, Swap )
{
    CF::Error e1( "com.xs-labs", 42 );
    CF::Error e2;
    
    swap( e1, e2 );
    
    ASSERT_FALSE( e1.IsValid() );
    ASSERT_TRUE(  e2.IsValid() );
    ASSERT_EQ( e2.GetDomain(), "com.xs-labs" );
    ASSERT_EQ( e2.GetCode(), 42 );
}
