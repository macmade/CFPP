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
 * @file        Test-CFPP-Dictionary-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Dictionary::Iterator
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Dictionary_Iterator, DictionaryBegin )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( nullptr ) );
    CF::Dictionary d3;
    
    d3 << CF::Pair( "foo", "hello, world" );
    
    CF::Dictionary::Iterator i;
    
    i = d3.begin();
    
    ASSERT_TRUE( d1.begin().GetKey()   == nullptr );
    ASSERT_TRUE( d1.begin().GetValue() == nullptr );
    ASSERT_TRUE( d2.begin().GetKey()   == nullptr );
    ASSERT_TRUE( d2.begin().GetValue() == nullptr );
    ASSERT_TRUE( d3.begin().GetKey()   != nullptr );
    ASSERT_TRUE( d3.begin().GetValue() != nullptr );
    
    ASSERT_TRUE( CF::String( d3.begin().GetKey() )   == "foo" );
    ASSERT_TRUE( CF::String( d3.begin().GetValue() ) == "hello, world" );
    
    ASSERT_TRUE( d1.begin() == d1.end() );
    ASSERT_TRUE( d2.begin() == d2.end() );
    ASSERT_TRUE( d3.begin() != d3.end() );
}

TEST( CFPP_Dictionary_Iterator, DictionaryEnd )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( nullptr ) );
    CF::Dictionary d3;
    
    d3 << CF::Pair( "foo", "hello, world" );
    
    ASSERT_TRUE( d1.end().GetKey()   == nullptr );
    ASSERT_TRUE( d1.end().GetValue() == nullptr );
    ASSERT_TRUE( d2.end().GetKey()   == nullptr );
    ASSERT_TRUE( d2.end().GetValue() == nullptr );
    ASSERT_TRUE( d3.end().GetKey()   == nullptr );
    ASSERT_TRUE( d3.end().GetValue() == nullptr );
    
    ASSERT_TRUE( CF::String( d3.begin().GetKey() )   == "foo" );
    ASSERT_TRUE( CF::String( d3.begin().GetValue() ) == "hello, world" );
    
    ASSERT_TRUE( d1.begin() == d1.end() );
    ASSERT_TRUE( d2.begin() == d2.end() );
    ASSERT_TRUE( d3.begin() != d3.end() );
}

TEST( CFPP_Dictionary_Iterator, CTOR )
{
    CF::Dictionary::Iterator i;
    
    ASSERT_TRUE( i.GetKey()   == nullptr );
    ASSERT_TRUE( i.GetValue() == nullptr );
}

TEST( CFPP_Dictionary_Iterator, CCTOR )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2( i1 );
        CF::Dictionary::Iterator i3( d.begin() );
        CF::Dictionary::Iterator i4( i3 );
        
        ASSERT_TRUE( i1.GetKey()   == nullptr );
        ASSERT_TRUE( i1.GetValue() == nullptr );
        ASSERT_TRUE( i2.GetKey()   == nullptr );
        ASSERT_TRUE( i2.GetValue() == nullptr );
        ASSERT_TRUE( i3.GetKey()   != nullptr );
        ASSERT_TRUE( i3.GetValue() != nullptr );
        ASSERT_TRUE( i4.GetKey()   != nullptr );
        ASSERT_TRUE( i4.GetValue() != nullptr );
        
        ASSERT_TRUE( CF::String( i3.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i3.GetValue() ) == "hello, world" );
        ASSERT_TRUE( CF::String( i4.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i4.GetValue() ) == "hello, world" );
    }
}

TEST( CFPP_Dictionary_Iterator, MCTOR )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2( std::move( i1 ) );
        CF::Dictionary::Iterator i3( d.begin() );
        CF::Dictionary::Iterator i4( std::move( i3 ) );
        
        ASSERT_TRUE( i1.GetKey()   == nullptr );
        ASSERT_TRUE( i1.GetValue() == nullptr );
        ASSERT_TRUE( i2.GetKey()   == nullptr );
        ASSERT_TRUE( i2.GetValue() == nullptr );
        ASSERT_TRUE( i3.GetKey()   == nullptr );
        ASSERT_TRUE( i3.GetValue() == nullptr );
        ASSERT_TRUE( i4.GetKey()   != nullptr );
        ASSERT_TRUE( i4.GetValue() != nullptr );
        
        ASSERT_TRUE( CF::String( i4.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i4.GetValue() ) == "hello, world" );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorAssign )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        CF::Dictionary::Iterator i3( d.begin() );
        CF::Dictionary::Iterator i4;
        
        ASSERT_TRUE( i1.GetKey()   == nullptr );
        ASSERT_TRUE( i1.GetValue() == nullptr );
        ASSERT_TRUE( i3.GetKey()   != nullptr );
        ASSERT_TRUE( i3.GetValue() != nullptr );
        
        ASSERT_TRUE( CF::String( i3.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i3.GetValue() ) == "hello, world" );
        
        i2 = i1;
        i4 = i3;
        
        ASSERT_TRUE( i2.GetKey()   == nullptr );
        ASSERT_TRUE( i2.GetValue() == nullptr );
        ASSERT_TRUE( i4.GetKey()   != nullptr );
        ASSERT_TRUE( i4.GetValue() != nullptr );
        
        ASSERT_TRUE( CF::String( i4.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i4.GetValue() ) == "hello, world" );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorPrefixIncrement )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        CF::Dictionary::Iterator i3;
        CF::Dictionary::Iterator i4;
        
        i1 = d.begin();
        i2 = ++i1;
        i4 = ++i3;
        
        ASSERT_TRUE( i1.GetKey()   != nullptr );
        ASSERT_TRUE( i1.GetValue() != nullptr );
        ASSERT_TRUE( i2.GetKey()   != nullptr );
        ASSERT_TRUE( i2.GetValue() != nullptr );
        ASSERT_TRUE( i3.GetKey()   == nullptr );
        ASSERT_TRUE( i3.GetValue() == nullptr );
        ASSERT_TRUE( i4.GetKey()   == nullptr );
        ASSERT_TRUE( i4.GetValue() == nullptr );
        
        ASSERT_TRUE( CF::String( i1.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i1.GetValue() ).IsValid() );
        ASSERT_TRUE( CF::String( i2.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i2.GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorPostfixIncrement )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        CF::Dictionary::Iterator i3;
        CF::Dictionary::Iterator i4;
        
        i1 = d.begin();
        i2 = i1++;
        i4 = i3++;
        
        ASSERT_TRUE( i1.GetKey()   != nullptr );
        ASSERT_TRUE( i1.GetValue() != nullptr );
        ASSERT_TRUE( i2.GetKey()   != nullptr );
        ASSERT_TRUE( i2.GetValue() != nullptr );
        ASSERT_TRUE( i3.GetKey()   == nullptr );
        ASSERT_TRUE( i3.GetValue() == nullptr );
        ASSERT_TRUE( i4.GetKey()   == nullptr );
        ASSERT_TRUE( i4.GetValue() == nullptr );
        
        ASSERT_TRUE( CF::String( i1.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i1.GetValue() ).IsValid() );
        ASSERT_TRUE( CF::String( i2.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i2.GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorPrefixDecrement )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        CF::Dictionary::Iterator i3;
        CF::Dictionary::Iterator i4;
        
        i1 = d.end();
        i2 = --i1;
        i4 = --i3;
        
        ASSERT_TRUE( i1.GetKey()   != nullptr );
        ASSERT_TRUE( i1.GetValue() != nullptr );
        ASSERT_TRUE( i2.GetKey()   != nullptr );
        ASSERT_TRUE( i2.GetValue() != nullptr );
        ASSERT_TRUE( i3.GetKey()   == nullptr );
        ASSERT_TRUE( i3.GetValue() == nullptr );
        ASSERT_TRUE( i4.GetKey()   == nullptr );
        ASSERT_TRUE( i4.GetValue() == nullptr );
        
        ASSERT_TRUE( CF::String( i1.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i1.GetValue() ).IsValid() );
        ASSERT_TRUE( CF::String( i2.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i2.GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorPostfixDecrement )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        CF::Dictionary::Iterator i3;
        CF::Dictionary::Iterator i4;
        
        i1 = d.end();
        i2 = i1--;
        i4 = i3--;
        
        ASSERT_TRUE( i1.GetKey()   != nullptr );
        ASSERT_TRUE( i1.GetValue() != nullptr );
        ASSERT_TRUE( i2.GetKey()   == nullptr );
        ASSERT_TRUE( i2.GetValue() == nullptr );
        ASSERT_TRUE( i3.GetKey()   == nullptr );
        ASSERT_TRUE( i3.GetValue() == nullptr );
        ASSERT_TRUE( i4.GetKey()   == nullptr );
        ASSERT_TRUE( i4.GetValue() == nullptr );
        
        ASSERT_TRUE( CF::String( i1.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i1.GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorPlusEqual )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    d << CF::Pair( "x", "foo" );
    d << CF::Pair( "y", "bar" );
    
    {
        CF::Dictionary::Iterator i;
        
        i = d.begin();
        
        ASSERT_TRUE( i.GetKey()   != nullptr );
        ASSERT_TRUE( i.GetValue() != nullptr );
        ASSERT_TRUE( CF::String( i.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue() ).IsValid() );
        
        i += 1;
        
        ASSERT_TRUE( i.GetKey()   != nullptr );
        ASSERT_TRUE( i.GetValue() != nullptr );
        ASSERT_TRUE( CF::String( i.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue() ).IsValid() );
        
        i += 0;
        
        ASSERT_TRUE( i.GetKey()   != nullptr );
        ASSERT_TRUE( i.GetValue() != nullptr );
        ASSERT_TRUE( CF::String( i.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue() ).IsValid() );
        
        i += 2;
        
        ASSERT_TRUE( i.GetKey()   != nullptr );
        ASSERT_TRUE( i.GetValue() != nullptr );
        ASSERT_TRUE( CF::String( i.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorMinusEqual )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    d << CF::Pair( "x", "foo" );
    d << CF::Pair( "y", "bar" );
    
    {
        CF::Dictionary::Iterator i;
        
        i = d.end();
        
        ASSERT_TRUE( i.GetKey()   == nullptr );
        ASSERT_TRUE( i.GetValue() == nullptr );
        
        i -= 1;
        
        ASSERT_TRUE( i.GetKey()   != nullptr );
        ASSERT_TRUE( i.GetValue() != nullptr );
        ASSERT_TRUE( CF::String( i.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue() ).IsValid() );
        
        i -= 0;
        
        ASSERT_TRUE( i.GetKey()   != nullptr );
        ASSERT_TRUE( i.GetValue() != nullptr );
        ASSERT_TRUE( CF::String( i.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue() ).IsValid() );
        
        i -= 2;
        
        ASSERT_TRUE( i.GetKey()   != nullptr );
        ASSERT_TRUE( i.GetValue() != nullptr );
        ASSERT_TRUE( CF::String( i.GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorPlus )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    d << CF::Pair( "x", "foo" );
    d << CF::Pair( "y", "bar" );
    
    {
        CF::Dictionary::Iterator i;
        
        i = d.begin();
        
        ASSERT_TRUE( i.GetKey()                                     != nullptr );
        ASSERT_TRUE( i.GetValue()                                   != nullptr );
        ASSERT_TRUE( ( i + static_cast< CFIndex >( 1 ) ).GetKey()   != nullptr );
        ASSERT_TRUE( ( i + static_cast< CFIndex >( 1 ) ).GetValue() != nullptr );
        ASSERT_TRUE( ( i + static_cast< CFIndex >( 0 ) ).GetKey()   != nullptr );
        ASSERT_TRUE( ( i + static_cast< CFIndex >( 0 ) ).GetValue() != nullptr );
        ASSERT_TRUE( ( i + static_cast< CFIndex >( 2 ) ).GetKey()   != nullptr );
        ASSERT_TRUE( ( i + static_cast< CFIndex >( 2 ) ).GetValue() != nullptr );
        
        ASSERT_TRUE( CF::String( i.GetKey()                                     ).IsValid() );
        ASSERT_TRUE( CF::String( i.GetValue()                                   ).IsValid() );
        ASSERT_TRUE( CF::String( ( i + static_cast< CFIndex >( 1 ) ).GetKey()   ).IsValid() );
        ASSERT_TRUE( CF::String( ( i + static_cast< CFIndex >( 1 ) ).GetValue() ).IsValid() );
        ASSERT_TRUE( CF::String( ( i + static_cast< CFIndex >( 0 ) ).GetKey()   ).IsValid() );
        ASSERT_TRUE( CF::String( ( i + static_cast< CFIndex >( 0 ) ).GetValue() ).IsValid() );
        ASSERT_TRUE( CF::String( ( i + static_cast< CFIndex >( 2 ) ).GetKey()   ).IsValid() );
        ASSERT_TRUE( CF::String( ( i + static_cast< CFIndex >( 2 ) ).GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorMinus )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    d << CF::Pair( "x", "foo" );
    d << CF::Pair( "y", "bar" );
    
    {
        CF::Dictionary::Iterator i;
        
        i = d.end();
        
        ASSERT_TRUE( i.GetKey()                                     == nullptr );
        ASSERT_TRUE( i.GetValue()                                   == nullptr );
        ASSERT_TRUE( ( i - static_cast< CFIndex >( 1 ) ).GetKey()   != nullptr );
        ASSERT_TRUE( ( i - static_cast< CFIndex >( 1 ) ).GetValue() != nullptr );
        ASSERT_TRUE( ( i - static_cast< CFIndex >( 0 ) ).GetKey()   == nullptr );
        ASSERT_TRUE( ( i - static_cast< CFIndex >( 0 ) ).GetValue() == nullptr );
        ASSERT_TRUE( ( i - static_cast< CFIndex >( 2 ) ).GetKey()   != nullptr );
        ASSERT_TRUE( ( i - static_cast< CFIndex >( 2 ) ).GetValue() != nullptr );
        
        ASSERT_TRUE( CF::String( ( i - static_cast< CFIndex >( 1 ) ).GetKey()   ).IsValid() );
        ASSERT_TRUE( CF::String( ( i - static_cast< CFIndex >( 1 ) ).GetValue() ).IsValid() );
        ASSERT_TRUE( CF::String( ( i - static_cast< CFIndex >( 2 ) ).GetKey()   ).IsValid() );
        ASSERT_TRUE( CF::String( ( i - static_cast< CFIndex >( 2 ) ).GetValue() ).IsValid() );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorEqual )
{
    CF::Dictionary d1;
    CF::Dictionary d2;
    
    d1 << CF::Pair( "foo", "hello, world" );
    d1 << CF::Pair( "bar", "hello, universe" );
    d1 << CF::Pair( "x", "foo" );
    d1 << CF::Pair( "y", "bar" );
    
    d2 = d1;
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        
        ASSERT_TRUE( i1 == i1 );
        ASSERT_TRUE( i1 == i2 );
        
        i1 = d1.begin();
        i2 = d1.begin();
        
        ASSERT_TRUE( i1 == i1 );
        ASSERT_TRUE( i1 == i2 );
        
        i2++;
        
        ASSERT_FALSE( i1 == i2 );
        
        i2--;
        
        ASSERT_TRUE( i1 == i2 );
        
        i1 = d1.begin();
        i2 = d2.begin();
        
        ASSERT_FALSE( i1 == i2 );
        
        i1 = d1.begin();
        
        d1 << CF::Pair( "foobar", "foobar" );
        
        i2 = d1.begin();
        
        ASSERT_FALSE( i1 == i2 );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorNotEqual )
{
    CF::Dictionary d1;
    CF::Dictionary d2;
    
    d1 << CF::Pair( "foo", "hello, world" );
    d1 << CF::Pair( "bar", "hello, universe" );
    d1 << CF::Pair( "x", "foo" );
    d1 << CF::Pair( "y", "bar" );
    
    d2 = d1;
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        
        ASSERT_FALSE( i1 != i1 );
        ASSERT_FALSE( i1 != i2 );
        
        i1 = d1.begin();
        i2 = d1.begin();
        
        ASSERT_FALSE( i1 != i1 );
        ASSERT_FALSE( i1 != i2 );
        
        i2++;
        
        ASSERT_TRUE( i1 != i2 );
        
        i2--;
        
        ASSERT_FALSE( i1 != i2 );
        
        i1 = d1.begin();
        i2 = d2.begin();
        
        ASSERT_TRUE( i1 != i2 );
        
        i1 = d1.begin();
        
        d1 << CF::Pair( "foobar", "foobar" );
        
        i2 = d1.begin();
        
        ASSERT_TRUE( i1 != i2 );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorDereference )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFArrayRef >( nullptr ) );
    
    d1 << CF::Pair( "foo", "hello, world" );
    d1 << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        
        ASSERT_TRUE( ( *( i1 ) ).GetKey()   == nullptr );
        ASSERT_TRUE( ( *( i1 ) ).GetValue() == nullptr );
        ASSERT_TRUE( ( *( i2 ) ).GetKey()   == nullptr );
        ASSERT_TRUE( ( *( i2 ) ).GetValue() == nullptr );
        
        i1 = d1.begin();
        i2 = d2.begin();
        
        ASSERT_TRUE( ( *( i1 ) ).GetKey()   != nullptr );
        ASSERT_TRUE( ( *( i1 ) ).GetValue() != nullptr );
        ASSERT_TRUE( ( *( i2 ) ).GetKey()   == nullptr );
        ASSERT_TRUE( ( *( i2 ) ).GetValue() == nullptr );
        
        ASSERT_TRUE( CF::String( ( *( i1 ) ).GetKey() ).IsValid() );
        ASSERT_TRUE( CF::String( ( *( i1 ) ).GetValue() ).IsValid() );
        
        i1--;
        i2--;
        
        ASSERT_TRUE( ( *( i1 ) ).GetKey()   == nullptr );
        ASSERT_TRUE( ( *( i1 ) ).GetValue() == nullptr );
        ASSERT_TRUE( ( *( i2 ) ).GetKey()   == nullptr );
        ASSERT_TRUE( ( *( i2 ) ).GetValue() == nullptr );
    }
}

TEST( CFPP_Dictionary_Iterator, GetKey )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFArrayRef >( nullptr ) );
    
    d1 << CF::Pair( "foo", "hello, world" );
    d1 << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        
        ASSERT_TRUE( i1.GetKey() == nullptr );
        ASSERT_TRUE( i2.GetKey() == nullptr );
        
        i1 = d1.begin();
        i2 = d2.begin();
        
        ASSERT_TRUE( i1.GetKey() != nullptr );
        ASSERT_TRUE( i2.GetKey() == nullptr );
        
        ASSERT_TRUE( CF::String( i1.GetKey() ).IsValid() );
        
        i1--;
        i2--;
        
        ASSERT_TRUE( i1.GetKey() == nullptr );
        ASSERT_TRUE( i2.GetKey() == nullptr );
    }
}

TEST( CFPP_Dictionary_Iterator, GetValue )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFArrayRef >( nullptr ) );
    
    d1 << CF::Pair( "foo", "hello, world" );
    d1 << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        
        ASSERT_TRUE( i1.GetValue() == nullptr );
        ASSERT_TRUE( i2.GetValue() == nullptr );
        
        i1 = d1.begin();
        i2 = d2.begin();
        
        ASSERT_TRUE( i1.GetValue() != nullptr );
        ASSERT_TRUE( i2.GetValue() == nullptr );
        
        ASSERT_TRUE( CF::String( i1.GetValue() ).IsValid() );
        
        i1--;
        i2--;
        
        ASSERT_TRUE( i1.GetValue() == nullptr );
        ASSERT_TRUE( i2.GetValue() == nullptr );
    }
}

TEST( CFPP_Dictionary_Iterator, Swap )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    d << CF::Pair( "bar", "hello, universe" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        
        i1 = d.begin();
        i2 = d.end();
        
        ASSERT_TRUE( i1 == d.begin() );
        ASSERT_TRUE( i2 == d.end() );
        
        swap( i1, i2 );
        
        ASSERT_TRUE( i1 == d.end() );
        ASSERT_TRUE( i2 == d.begin() );
    }
}

TEST( CFPP_Dictionary_Iterator, TestIterate )
{
    CF::Dictionary           d1;
    CF::Dictionary           d2( static_cast< CFDictionaryRef >( nullptr ) );
    CF::Dictionary           d3;
    CF::Dictionary::Iterator it;
    CFIndex                  i;
    
    d3 << CF::Pair( "foo", "hello, world" );
    d3 << CF::Pair( "bar", "hello, universe" );
    d3 << CF::Pair( "x",   "foo" );
    d3 << CF::Pair( "y",   "bar" );
    
    {
        i = 0;
        
        for( it = d1.begin(); it != d1.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = d2.begin(); it != d2.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = d3.begin(); it != d3.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}

TEST( CFPP_Dictionary_Iterator, TestIterateSTD )
{
    CF::Dictionary           d1;
    CF::Dictionary           d2( static_cast< CFDictionaryRef >( nullptr ) );
    CF::Dictionary           d3;
    CF::Dictionary::Iterator it;
    CFIndex                  i;
    
    d3 << CF::Pair( "foo", "hello, world" );
    d3 << CF::Pair( "bar", "hello, universe" );
    d3 << CF::Pair( "x",   "foo" );
    d3 << CF::Pair( "y",   "bar" );
    
    {
        i = 0;
        
        for( it = std::begin( d1 ); it != std::end( d1 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = std::begin( d2 ); it != std::end( d2 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = std::begin( d3 ); it != std::end( d3 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}

TEST( CFPP_Dictionary_Iterator, TestIterateCPP11 )
{
    CF::Dictionary           d1;
    CF::Dictionary           d2( static_cast< CFDictionaryRef >( nullptr ) );
    CF::Dictionary           d3;
    CF::Dictionary::Iterator it;
    CFIndex                  i;
    
    d3 << CF::Pair( "foo", "hello, world" );
    d3 << CF::Pair( "bar", "hello, universe" );
    d3 << CF::Pair( "x",   "foo" );
    d3 << CF::Pair( "y",   "bar" );
    
    {
        i = 0;
        
        for( CF::Pair p: d1 )
        {
            ( void )p;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( CF::Pair p: d2 )
        {
            ( void )p;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( CF::Pair p: d3 )
        {
            ASSERT_TRUE( CF::String( p.GetKey() ).IsValid() );
            ASSERT_TRUE( CF::String( p.GetValue() ).IsValid() );
            
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}
