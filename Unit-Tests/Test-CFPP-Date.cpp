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
 * @file        Test-CFPP-Date.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Date
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Date, CurrentDate )
{
    CFAbsoluteTime t;
    CF::Date       d;
    
    t = CFAbsoluteTimeGetCurrent();
    d = CF::Date::CurrentDate();
    
    ASSERT_TRUE( d.IsValid() );
    
    ASSERT_GT(   d.GetValue(), 0 );
    ASSERT_TRUE( d.GetValue() > t - 1 );
    ASSERT_TRUE( d.GetValue() < t + 1 );
}

TEST( CFPP_Date, CTOR )
{
    CFAbsoluteTime t;
    CF::Date       d;
    
    t = CFAbsoluteTimeGetCurrent();
    
    ASSERT_TRUE( d.IsValid() );
    
    ASSERT_GT(   d.GetValue(), 0 );
    ASSERT_TRUE( d.GetValue() > t - 1 );
    ASSERT_TRUE( d.GetValue() < t + 1 );
}

TEST( CFPP_Date, CTOR_AutoPointer )
{
    CF::Date d1( CF::AutoPointer( CFDateCreate( nullptr, 0 ) ) );
    CF::Date d2( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::Date d3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Date, CTOR_CFType )
{
    CFAbsoluteTime t;
    CF::Date       d1( static_cast< CFTypeRef >( CF::Date::CurrentDate().GetCFObject() ) );
    CF::Date       d2( static_cast< CFTypeRef >( nullptr ) );
    
    t = CFAbsoluteTimeGetCurrent();
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    ASSERT_GT(   d1.GetValue(), 0 );
    ASSERT_TRUE( d1.GetValue() > t - 1 );
    ASSERT_TRUE( d1.GetValue() < t + 1 );
}

TEST( CFPP_Date, CTOR_CFDate )
{
    CFAbsoluteTime t;
    CF::Date       d1( static_cast< CFDateRef >( CF::Date::CurrentDate().GetCFObject() ) );
    CF::Date       d2( static_cast< CFDateRef >( nullptr ) );
    
    t = CFAbsoluteTimeGetCurrent();
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    ASSERT_GT(   d1.GetValue(), 0 );
    ASSERT_TRUE( d1.GetValue() > t - 1 );
    ASSERT_TRUE( d1.GetValue() < t + 1 );
}

TEST( CFPP_Date, CTOR_NullPointer )
{
    CF::Date d( nullptr );
    
    ASSERT_FALSE( d.IsValid() );
}

TEST( CFPP_Date, CTOR_CFAbsoluteTime )
{
    CFAbsoluteTime t;
    CF::Date       d1( CFAbsoluteTimeGetCurrent() );
    CF::Date       d2( static_cast< CFAbsoluteTime >(  0 ) );
    CF::Date       d3( static_cast< CFAbsoluteTime >( -1 ) );
    
    t = CFAbsoluteTimeGetCurrent();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    ASSERT_TRUE( d3.IsValid() );
    
    ASSERT_GT(   d1.GetValue(), 0 );
    ASSERT_TRUE( d1.GetValue() > t - 1 );
    ASSERT_TRUE( d1.GetValue() < t + 1 );
}

TEST( CFPP_Date, CCTOR )
{
    CF::Date d1;
    CF::Date d2( d1 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT(   d2.GetValue(), 0 );
    ASSERT_TRUE( d2.GetValue() > d1.GetValue() - 1 );
    ASSERT_TRUE( d2.GetValue() < d1.GetValue() + 1 );
}

TEST( CFPP_Date, MCTOR )
{
    CF::Date d1;
    CF::Date d2( std::move( d1 ) );
    
    ASSERT_FALSE( d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
}

TEST( CFPP_Date, OperatorAssignDate )
{
    CF::Date d1;
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d2 = d1;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT(   d2.GetValue(), 0 );
    ASSERT_TRUE( d2.GetValue() > d1.GetValue() - 1 );
    ASSERT_TRUE( d2.GetValue() < d1.GetValue() + 1 );
    
    d2 = d3;
    
    ASSERT_FALSE( d2.IsValid() );
}

TEST( CFPP_Date, OperatorAssignAutoPointer )
{
    CF::Date d1( static_cast< CFTypeRef >( nullptr ) );
    CF::Date d2;
    CF::Date d3;
    
    ASSERT_FALSE( d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    
    d1 = CF::AutoPointer( CFDateCreate( nullptr, 0 ) );
    d2 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    d3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Date, OperatorAssignCFType )
{
    CF::Date d1;
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d2 = static_cast< CFTypeRef >( d1.GetCFObject() );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT(   d2.GetValue(), 0 );
    ASSERT_TRUE( d2.GetValue() > d1.GetValue() - 1 );
    ASSERT_TRUE( d2.GetValue() < d1.GetValue() + 1 );
    
    d2 = static_cast< CFTypeRef >( d3.GetCFObject() );
    
    ASSERT_FALSE( d2.IsValid() );
}

TEST( CFPP_Date, OperatorAssignCFDate )
{
    CF::Date d1;
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d2 = static_cast< CFDateRef >( d1.GetCFObject() );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT(   d2.GetValue(), 0 );
    ASSERT_TRUE( d2.GetValue() > d1.GetValue() - 1 );
    ASSERT_TRUE( d2.GetValue() < d1.GetValue() + 1 );
    
    d2 = static_cast< CFDateRef >( d3.GetCFObject() );
    
    ASSERT_FALSE( d2.IsValid() );
}

TEST( CFPP_Date, OperatorAssignNullPointer )
{
    CF::Date d;
    
    ASSERT_TRUE( d.IsValid() );
    
    d = nullptr;
    
    ASSERT_FALSE( d.IsValid() );
}

TEST( CFPP_Date, OperatorAssignCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d2 = d1.GetValue();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT(   d2.GetValue(), 0 );
    ASSERT_TRUE( d2.GetValue() > d1.GetValue() - 1 );
    ASSERT_TRUE( d2.GetValue() < d1.GetValue() + 1 );
    
    d2 = static_cast< CFAbsoluteTime >( 0 );
    
    ASSERT_TRUE( d2.IsValid() );
    ASSERT_TRUE( d2.GetValue() > -1 );
    ASSERT_TRUE( d2.GetValue() <  1 );
    
    d2 = static_cast< CFAbsoluteTime >( -1 );
    
    ASSERT_TRUE( d2.IsValid() );
    ASSERT_TRUE( d2.GetValue() > -2 );
    ASSERT_TRUE( d2.GetValue() <  0 );
}

TEST( CFPP_Date, OperatorEqualDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 == d2 );
    ASSERT_FALSE( d1 == d3 );
    ASSERT_FALSE( d1 == d4 );
    
    ASSERT_FALSE( d3 == d1 );
    ASSERT_TRUE(  d3 == d3 );
    ASSERT_FALSE( d3 == d4 );
    
    ASSERT_FALSE( d4 == d1 );
    ASSERT_FALSE( d4 == d3 );
    ASSERT_FALSE( d4 == d4 );
}

TEST( CFPP_Date, OperatorEqualCFType )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 == static_cast< CFTypeRef >( d2.GetCFObject() ) );
    ASSERT_FALSE( d1 == static_cast< CFTypeRef >( d3.GetCFObject() ) );
    ASSERT_FALSE( d1 == static_cast< CFTypeRef >( d4.GetCFObject() ) );
    
    ASSERT_FALSE( d3 == static_cast< CFTypeRef >( d1.GetCFObject() ) );
    ASSERT_TRUE(  d3 == static_cast< CFTypeRef >( d3.GetCFObject() ) );
    ASSERT_FALSE( d3 == static_cast< CFTypeRef >( d4.GetCFObject() ) );
    
    ASSERT_FALSE( d4 == static_cast< CFTypeRef >( d1.GetCFObject() ) );
    ASSERT_FALSE( d4 == static_cast< CFTypeRef >( d3.GetCFObject() ) );
    ASSERT_FALSE( d4 == static_cast< CFTypeRef >( d4.GetCFObject() ) );
}

TEST( CFPP_Date, OperatorEqualCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 == static_cast< CFDateRef >( d2.GetCFObject() ) );
    ASSERT_FALSE( d1 == static_cast< CFDateRef >( d3.GetCFObject() ) );
    ASSERT_FALSE( d1 == static_cast< CFDateRef >( d4.GetCFObject() ) );
    
    ASSERT_FALSE( d3 == static_cast< CFDateRef >( d1.GetCFObject() ) );
    ASSERT_TRUE(  d3 == static_cast< CFDateRef >( d3.GetCFObject() ) );
    ASSERT_FALSE( d3 == static_cast< CFDateRef >( d4.GetCFObject() ) );
    
    ASSERT_FALSE( d4 == static_cast< CFDateRef >( d1.GetCFObject() ) );
    ASSERT_FALSE( d4 == static_cast< CFDateRef >( d3.GetCFObject() ) );
    ASSERT_FALSE( d4 == static_cast< CFDateRef >( d4.GetCFObject() ) );
}

TEST( CFPP_Date, OperatorEqualCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 == d2.GetValue() );
    ASSERT_FALSE( d1 == d3.GetValue() );
    ASSERT_FALSE( d1 == d4.GetValue() );
    
    ASSERT_FALSE( d3 == d1.GetValue() );
    ASSERT_TRUE(  d3 == d3.GetValue() );
    ASSERT_TRUE(  d3 == d4.GetValue() );
    
    ASSERT_FALSE( d4 == d1.GetValue() );
    ASSERT_FALSE( d4 == d3.GetValue() );
    ASSERT_FALSE( d4 == d4.GetValue() );
}

TEST( CFPP_Date, OperatorNotEqualDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 != d2 );
    ASSERT_TRUE(  d1 != d3 );
    ASSERT_TRUE(  d1 != d4 );
    
    ASSERT_TRUE(  d3 != d1 );
    ASSERT_FALSE( d3 != d3 );
    ASSERT_TRUE(  d3 != d4 );
    
    ASSERT_TRUE( d4 != d1 );
    ASSERT_TRUE( d4 != d3 );
    ASSERT_TRUE( d4 != d4 );
}

TEST( CFPP_Date, OperatorNotEqualCFType )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 != static_cast< CFTypeRef >( d2.GetCFObject() ) );
    ASSERT_TRUE(  d1 != static_cast< CFTypeRef >( d3.GetCFObject() ) );
    ASSERT_TRUE(  d1 != static_cast< CFTypeRef >( d4.GetCFObject() ) );
    
    ASSERT_TRUE(  d3 != static_cast< CFTypeRef >( d1.GetCFObject() ) );
    ASSERT_FALSE( d3 != static_cast< CFTypeRef >( d3.GetCFObject() ) );
    ASSERT_TRUE(  d3 != static_cast< CFTypeRef >( d4.GetCFObject() ) );
    
    ASSERT_TRUE( d4 != static_cast< CFTypeRef >( d1.GetCFObject() ) );
    ASSERT_TRUE( d4 != static_cast< CFTypeRef >( d3.GetCFObject() ) );
    ASSERT_TRUE( d4 != static_cast< CFTypeRef >( d4.GetCFObject() ) );
}

TEST( CFPP_Date, OperatorNotEqualCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 != static_cast< CFDateRef >( d2.GetCFObject() ) );
    ASSERT_TRUE(  d1 != static_cast< CFDateRef >( d3.GetCFObject() ) );
    ASSERT_TRUE(  d1 != static_cast< CFDateRef >( d4.GetCFObject() ) );
    
    ASSERT_TRUE(  d3 != static_cast< CFDateRef >( d1.GetCFObject() ) );
    ASSERT_FALSE( d3 != static_cast< CFDateRef >( d3.GetCFObject() ) );
    ASSERT_TRUE(  d3 != static_cast< CFDateRef >( d4.GetCFObject() ) );
    
    ASSERT_TRUE( d4 != static_cast< CFDateRef >( d1.GetCFObject() ) );
    ASSERT_TRUE( d4 != static_cast< CFDateRef >( d3.GetCFObject() ) );
    ASSERT_TRUE( d4 != static_cast< CFDateRef >( d4.GetCFObject() ) );
}

TEST( CFPP_Date, OperatorNotEqualCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 != d2.GetValue() );
    ASSERT_TRUE(  d1 != d3.GetValue() );
    ASSERT_TRUE(  d1 != d4.GetValue() );
    
    ASSERT_TRUE(  d3 != d1.GetValue() );
    ASSERT_FALSE( d3 != d3.GetValue() );
    ASSERT_FALSE( d3 != d4.GetValue() );
    
    ASSERT_TRUE( d4 != d1.GetValue() );
    ASSERT_TRUE( d4 != d3.GetValue() );
    ASSERT_TRUE( d4 != d4.GetValue() );
}

TEST( CFPP_Date, OperatorGreaterOrEqualDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 >= d2 );
    ASSERT_TRUE(  d1 >= d3 );
    ASSERT_FALSE( d1 >= d4 );
    
    ASSERT_FALSE( d3 >= d1 );
    ASSERT_TRUE(  d3 >= d3 );
    ASSERT_FALSE( d3 >= d4 );
    
    ASSERT_FALSE( d4 >= d1 );
    ASSERT_FALSE( d4 >= d3 );
    ASSERT_FALSE( d4 >= d4 );
}

TEST( CFPP_Date, OperatorGreaterOrEqualCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 >= static_cast< CFDateRef >( d2 ) );
    ASSERT_TRUE(  d1 >= static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d1 >= static_cast< CFDateRef >( d4 ) );
    
    ASSERT_FALSE( d3 >= static_cast< CFDateRef >( d1 ) );
    ASSERT_TRUE(  d3 >= static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d3 >= static_cast< CFDateRef >( d4 ) );
    
    ASSERT_FALSE( d4 >= static_cast< CFDateRef >( d1 ) );
    ASSERT_FALSE( d4 >= static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d4 >= static_cast< CFDateRef >( d4 ) );
}

TEST( CFPP_Date, OperatorGreaterOrEqualCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 >= d2.GetValue() );
    ASSERT_TRUE(  d1 >= d3.GetValue() );
    ASSERT_TRUE(  d1 >= d4.GetValue() );
    
    ASSERT_FALSE( d3 >= d1.GetValue() );
    ASSERT_TRUE(  d3 >= d3.GetValue() );
    ASSERT_TRUE(  d3 >= d4.GetValue() );
    
    ASSERT_FALSE( d4 >= d1.GetValue() );
    ASSERT_FALSE( d4 >= d3.GetValue() );
    ASSERT_FALSE( d4 >= d4.GetValue() );
}

TEST( CFPP_Date, OperatorLesserOrEqualDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 <= d2 );
    ASSERT_FALSE( d1 <= d3 );
    ASSERT_FALSE( d1 <= d4 );
    
    ASSERT_TRUE(  d3 <= d1 );
    ASSERT_TRUE(  d3 <= d3 );
    ASSERT_FALSE( d3 <= d4 );
    
    ASSERT_FALSE( d4 <= d1 );
    ASSERT_FALSE( d4 <= d3 );
    ASSERT_FALSE( d4 <= d4 );
}

TEST( CFPP_Date, OperatorLesserOrEqualCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 <= static_cast< CFDateRef >( d2 ) );
    ASSERT_FALSE( d1 <= static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d1 <= static_cast< CFDateRef >( d4 ) );
    
    ASSERT_TRUE(  d3 <= static_cast< CFDateRef >( d1 ) );
    ASSERT_TRUE(  d3 <= static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d3 <= static_cast< CFDateRef >( d4 ) );
    
    ASSERT_FALSE( d4 <= static_cast< CFDateRef >( d1 ) );
    ASSERT_FALSE( d4 <= static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d4 <= static_cast< CFDateRef >( d4 ) );
}

TEST( CFPP_Date, OperatorLesserOrEqualCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE(  d1 <= d2.GetValue() );
    ASSERT_FALSE( d1 <= d3.GetValue() );
    ASSERT_FALSE( d1 <= d4.GetValue() );
    
    ASSERT_TRUE( d3 <= d1.GetValue() );
    ASSERT_TRUE( d3 <= d3.GetValue() );
    ASSERT_TRUE( d3 <= d4.GetValue() );
    
    ASSERT_FALSE( d4 <= d1.GetValue() );
    ASSERT_FALSE( d4 <= d3.GetValue() );
    ASSERT_FALSE( d4 <= d4.GetValue() );
}

TEST( CFPP_Date, OperatorGreaterDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 > d2 );
    ASSERT_TRUE(  d1 > d3 );
    ASSERT_FALSE( d1 > d4 );
    
    ASSERT_FALSE( d3 > d1 );
    ASSERT_FALSE( d3 > d3 );
    ASSERT_FALSE( d3 > d4 );
    
    ASSERT_FALSE( d4 > d1 );
    ASSERT_FALSE( d4 > d3 );
    ASSERT_FALSE( d4 > d4 );
}

TEST( CFPP_Date, OperatorGreaterCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 > static_cast< CFDateRef >( d2 ) );
    ASSERT_TRUE(  d1 > static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d1 > static_cast< CFDateRef >( d4 ) );
    
    ASSERT_FALSE( d3 > static_cast< CFDateRef >( d1 ) );
    ASSERT_FALSE( d3 > static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d3 > static_cast< CFDateRef >( d4 ) );
    
    ASSERT_FALSE( d4 > static_cast< CFDateRef >( d1 ) );
    ASSERT_FALSE( d4 > static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d4 > static_cast< CFDateRef >( d4 ) );
}

TEST( CFPP_Date, OperatorGreaterCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 > d2.GetValue() );
    ASSERT_TRUE(  d1 > d3.GetValue() );
    ASSERT_TRUE(  d1 > d4.GetValue() );
    
    ASSERT_FALSE( d3 > d1.GetValue() );
    ASSERT_FALSE( d3 > d3.GetValue() );
    ASSERT_FALSE( d3 > d4.GetValue() );
    
    ASSERT_FALSE( d4 > d1.GetValue() );
    ASSERT_FALSE( d4 > d3.GetValue() );
    ASSERT_FALSE( d4 > d4.GetValue() );
}

TEST( CFPP_Date, OperatorLesserDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 < d2 );
    ASSERT_FALSE( d1 < d3 );
    ASSERT_FALSE( d1 < d4 );
    
    ASSERT_TRUE(  d3 < d1 );
    ASSERT_FALSE( d3 < d3 );
    ASSERT_FALSE( d3 < d4 );
    
    ASSERT_FALSE( d4 < d1 );
    ASSERT_FALSE( d4 < d3 );
    ASSERT_FALSE( d4 < d4 );
}

TEST( CFPP_Date, OperatorLesserCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 < static_cast< CFDateRef >( d2 ) );
    ASSERT_FALSE( d1 < static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d1 < static_cast< CFDateRef >( d4 ) );
    
    ASSERT_TRUE(  d3 < static_cast< CFDateRef >( d1 ) );
    ASSERT_FALSE( d3 < static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d3 < static_cast< CFDateRef >( d4 ) );
    
    ASSERT_FALSE( d4 < static_cast< CFDateRef >( d1 ) );
    ASSERT_FALSE( d4 < static_cast< CFDateRef >( d3 ) );
    ASSERT_FALSE( d4 < static_cast< CFDateRef >( d4 ) );
}

TEST( CFPP_Date, OperatorLesserCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_FALSE( d1 < d2.GetValue() );
    ASSERT_FALSE( d1 < d3.GetValue() );
    ASSERT_FALSE( d1 < d4.GetValue() );
    
    ASSERT_TRUE(  d3 < d1.GetValue() );
    ASSERT_FALSE( d3 < d3.GetValue() );
    ASSERT_FALSE( d3 < d4.GetValue() );
    
    ASSERT_FALSE( d4 < d1.GetValue() );
    ASSERT_FALSE( d4 < d3.GetValue() );
    ASSERT_FALSE( d4 < d4.GetValue() );
}

TEST( CFPP_Date, OperatorPlusEqualDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += d2;
    
    ASSERT_TRUE( d1 > d2 );
    
    d1 = d2;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += d3;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += d4;
    
    ASSERT_TRUE( d1 == d2 );
    
    d4 += d1;
    
    ASSERT_TRUE( d4.IsValid() );
    ASSERT_TRUE( d4 == d1 );
}

TEST( CFPP_Date, OperatorPlusEqualCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += static_cast< CFDateRef >( d2 );
    
    ASSERT_TRUE( d1 > d2 );
    
    d1 = d2;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += static_cast< CFDateRef >( d3 );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += static_cast< CFDateRef >( d4 );
    
    ASSERT_TRUE( d1 == d2 );
    
    d4 += static_cast< CFDateRef >( d1 );
    
    ASSERT_TRUE( d4.IsValid() );
    ASSERT_TRUE( d4 == d1 );
}

TEST( CFPP_Date, OperatorPlusEqualCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += d2.GetValue();
    
    ASSERT_TRUE( d1 > d2 );
    
    d1 = d2;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += d3.GetValue();
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 += d4.GetValue();
    
    ASSERT_TRUE( d1 == d2 );
    
    d4 += d1.GetValue();
    
    ASSERT_TRUE( d4.IsValid() );
    ASSERT_TRUE( d4 == d1 );
}

TEST( CFPP_Date, OperatorMinusEqualDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= d2;
    
    ASSERT_TRUE( d1 < d2 );
    
    d1 = d2;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= d3;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= d4;
    
    ASSERT_TRUE( d1 == d2 );
    
    d4 -= d1;
    
    ASSERT_TRUE( d4.IsValid() );
    ASSERT_TRUE( d4 < d1 );
    ASSERT_TRUE( d4 < d3 );
}

TEST( CFPP_Date, OperatorMinusEqualCFDate )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= static_cast< CFDateRef >( d2 );
    
    ASSERT_TRUE( d1 < d2 );
    
    d1 = d2;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= static_cast< CFDateRef >( d3 );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= static_cast< CFDateRef >( d4 );
    
    ASSERT_TRUE( d1 == d2 );
    
    d4 -= static_cast< CFDateRef >( d1 );
    
    ASSERT_TRUE( d4.IsValid() );
    ASSERT_TRUE( d4 < d1 );
    ASSERT_TRUE( d4 < d3 );
}

TEST( CFPP_Date, OperatorMinusEqualCFAbsoluteTime )
{
    CF::Date d1;
    CF::Date d2( d1 );
    CF::Date d3( static_cast< CFAbsoluteTime >( 0 ) );
    CF::Date d4( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= d2.GetValue();
    
    ASSERT_TRUE( d1 < d2 );
    
    d1 = d2;
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= d3.GetValue();
    
    ASSERT_TRUE( d1 == d2 );
    
    d1 -= d4.GetValue();
    
    ASSERT_TRUE( d1 == d2 );
    
    d4 -= d1.GetValue();
    
    ASSERT_TRUE( d4.IsValid() );
    ASSERT_TRUE( d4 < d1 );
    ASSERT_TRUE( d4 < d3 );
}

TEST( CFPP_Date, OperatorPlusDate )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d3 = d1 + d1;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 > d1 );
    ASSERT_TRUE( d3 == d1 + d1 );
    
    d3 = d1 + d2;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = d2 + d1;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
}

TEST( CFPP_Date, OperatorPlusCFDate )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d3 = d1 + static_cast< CFDateRef >( d1 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 > d1 );
    ASSERT_TRUE( d3 == d1 + static_cast< CFDateRef >( d1 ) );
    
    d3 = d1 + static_cast< CFDateRef >( d2 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = d2 + static_cast< CFDateRef >( d1 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
}

TEST( CFPP_Date, OperatorPlusCFAbsoluteTime )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d3 = d1 + d1.GetValue();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 > d1 );
    ASSERT_TRUE( d3 == d1 + d1.GetValue() );
    
    d3 = d1 + d2.GetValue();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = d2 + d1.GetValue();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
}

TEST( CFPP_Date, OperatorMinusDate )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d3 = d1 - d1;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 < d1 );
    ASSERT_TRUE( d3 == d1 - d1 );
    
    d3 = d1 - d2;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = d2 - d1;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 < d1 );
    ASSERT_TRUE( d3 == d2 - d1 );
}

TEST( CFPP_Date, OperatorMinusCFDate )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d3 = d1 - static_cast< CFDateRef >( d1 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 < d1 );
    ASSERT_TRUE( d3 == d1 - static_cast< CFDateRef >( d1 ) );
    
    d3 = d1 - static_cast< CFDateRef >( d2 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = d2 - static_cast< CFDateRef >( d1 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 < d1 );
    ASSERT_TRUE( d3 == d2 - static_cast< CFDateRef >( d1 ) );
}

TEST( CFPP_Date, OperatorMinusCFAbsoluteTime )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d3 = d1 - d1.GetValue();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 < d1 );
    ASSERT_TRUE( d3 == d1 - d1.GetValue() );
    
    d3 = d1 - d2.GetValue();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = d2 - d1.GetValue();
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d3 < d1 );
    ASSERT_TRUE( d3 == d2 - d1.GetValue() );
}

TEST( CFPP_Date, OperatorPrefixIncrement )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3( 1 );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    
    ASSERT_TRUE( d1 > d3 );
    
    d3 = ++d1;
    
    ASSERT_GT( d1.GetValue(), 42 );
    ASSERT_LT( d1.GetValue(), 44 );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = ++d2;
    
    ASSERT_GT( d2.GetValue(), 0 );
    ASSERT_LT( d2.GetValue(), 2 );
    ASSERT_TRUE( d3 == d2 );
}

TEST( CFPP_Date, OperatorPostfixIncrement )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3( 1 );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    
    ASSERT_TRUE( d1 > d3 );
    
    d3 = d1++;
    
    ASSERT_GT( d1.GetValue(), 42 );
    ASSERT_LT( d1.GetValue(), 44 );
    ASSERT_GT( d3.GetValue(), 41 );
    ASSERT_LT( d3.GetValue(), 43 );
    ASSERT_TRUE( d3 < d1 );
    
    d3 = d2++;
    
    ASSERT_GT( d2.GetValue(), 0 );
    ASSERT_LT( d2.GetValue(), 2 );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Date, OperatorPrefixDecrement )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3( 1 );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    
    ASSERT_TRUE( d1 > d3 );
    
    d3 = --d1;
    
    ASSERT_GT( d1.GetValue(), 40 );
    ASSERT_LT( d1.GetValue(), 42 );
    ASSERT_TRUE( d3 == d1 );
    
    d3 = --d2;
    
    ASSERT_GT( d2.GetValue(), -2 );
    ASSERT_LT( d2.GetValue(),  0 );
    ASSERT_TRUE( d3 == d2 );
}

TEST( CFPP_Date, OperatorPostfixDecrement )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    CF::Date d3( 1 );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    
    ASSERT_TRUE( d1 > d3 );
    
    d3 = d1--;
    
    ASSERT_GT( d1.GetValue(), 40 );
    ASSERT_LT( d1.GetValue(), 42 );
    ASSERT_GT( d3.GetValue(), 41 );
    ASSERT_LT( d3.GetValue(), 43 );
    ASSERT_TRUE( d3 > d1 );
    
    d3 = d2--;
    
    ASSERT_GT( d2.GetValue(), -2 );
    ASSERT_LT( d2.GetValue(),  0 );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Date, CastToCFAbsoluteTime )
{
    CF::Date d1( 42 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    ASSERT_GT( static_cast< CFAbsoluteTime >( d1 ), 41 );
    ASSERT_LT( static_cast< CFAbsoluteTime >( d1 ), 43 );
    
    ASSERT_GT( static_cast< CFAbsoluteTime >( d2 ), -1 );
    ASSERT_LT( static_cast< CFAbsoluteTime >( d2 ),  1 );
}

TEST( CFPP_Date, GetTypeID )
{
    CF::Date d;
    
    ASSERT_EQ( d.GetTypeID(), CFDateGetTypeID() );
}

TEST( CFPP_Date, GetCFObject )
{
    CF::Date d1;
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE( d1.GetCFObject() != nullptr );
    ASSERT_TRUE( d2.GetCFObject() == nullptr );
    ASSERT_EQ( CFGetTypeID( d1.GetCFObject() ), CFDateGetTypeID() );
}

TEST( CFPP_Date, GetValue )
{
    CF::Date d1( 1 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    ASSERT_GT( d1.GetValue(), 0 );
    ASSERT_LT( d1.GetValue(), 2 );
    
    ASSERT_GT( d2.GetValue(), -1 );
    ASSERT_LT( d2.GetValue(),  1 );
}

TEST( CFPP_Date, SetValue )
{
    CF::Date d1( 1 );
    CF::Date d2( static_cast< CFDateRef >( nullptr ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d1.SetValue( 42 );
    d2.SetValue( 42 );
    
    ASSERT_GT( d1.GetValue(), 41 );
    ASSERT_LT( d1.GetValue(), 43 );
    
    ASSERT_GT( d2.GetValue(), 41 );
    ASSERT_LT( d2.GetValue(), 43 );
}

TEST( CFPP_Date, Swap )
{
    CF::Date d1( 1 );
    CF::Date d2( 2 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_TRUE( d2 > d1 );
    
    swap( d1, d2 );
    
    ASSERT_TRUE( d1 > d2 );
}
