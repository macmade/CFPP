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
 * @file        Test-CFPP-Array-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Array::Iterator
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Array_Iterator, ArrayBegin )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a3;
    
    a3 << CF::String( "hello, world" );
    
    ASSERT_TRUE( *( a1.begin() ) == nullptr );
    ASSERT_TRUE( *( a2.begin() ) == nullptr );
    ASSERT_TRUE( *( a3.begin() ) != nullptr );
    
    ASSERT_TRUE( CF::String( *( a3.begin() ) ) == "hello, world" );
    
    ASSERT_TRUE( a1.begin() == a1.end() );
    ASSERT_TRUE( a2.begin() == a2.end() );
    ASSERT_TRUE( a3.begin() != a3.end() );
}

TEST( CFPP_Array_Iterator, ArrayEnd )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a3;
    
    a3 << CF::String( "hello, world" );
    
    ASSERT_TRUE( *( a1.end() ) == nullptr );
    ASSERT_TRUE( *( a2.end() ) == nullptr );
    ASSERT_TRUE( *( a3.end() ) == nullptr );
    
    ASSERT_TRUE( CF::String( *( a3.begin() ) ) == "hello, world" );
    
    ASSERT_TRUE( a1.begin() == a1.end() );
    ASSERT_TRUE( a2.begin() == a2.end() );
    ASSERT_TRUE( a3.begin() != a3.end() );
}

TEST( CFPP_Array_Iterator, CTOR )
{
    CF::Array::Iterator i;
    
    ASSERT_TRUE( *( i ) == nullptr );
}

TEST( CFPP_Array_Iterator, CCTOR )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2( i1 );
        CF::Array::Iterator i3( a.begin() );
        CF::Array::Iterator i4( i3 );
        
        ASSERT_TRUE( *( i1 ) == nullptr );
        ASSERT_TRUE( *( i2 ) == nullptr );
        ASSERT_TRUE( *( i3 ) != nullptr );
        ASSERT_TRUE( *( i4 ) != nullptr );
        
        ASSERT_TRUE( CF::String( *( i3 ) ) == "hello, world" );
        ASSERT_TRUE( CF::String( *( i4 ) ) == "hello, world" );
    }
}

TEST( CFPP_Array_Iterator, MCTOR )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2( std::move( i1 ) );
        CF::Array::Iterator i3( a.begin() );
        CF::Array::Iterator i4( std::move( i3 ) );
        
        ASSERT_TRUE( *( i1 ) == nullptr );
        ASSERT_TRUE( *( i2 ) == nullptr );
        ASSERT_TRUE( *( i3 ) == nullptr );
        ASSERT_TRUE( *( i4 ) != nullptr );
        
        ASSERT_TRUE( CF::String( *( i4 ) ) == "hello, world" );
    }
}

TEST( CFPP_Array_Iterator, OperatorAssign )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        CF::Array::Iterator i3( a.begin() );
        CF::Array::Iterator i4;
        
        ASSERT_TRUE( *( i1 ) == nullptr );
        ASSERT_TRUE( *( i3 ) != nullptr );
        
        ASSERT_TRUE( CF::String( *( i3 ) ) == "hello, world" );
        
        i2 = i1;
        i4 = i3;
        
        ASSERT_TRUE( *( i2 ) == nullptr );
        ASSERT_TRUE( *( i4 ) != nullptr );
        
        ASSERT_TRUE( CF::String( *( i4 ) ) == "hello, world" );
    }
}

TEST( CFPP_Array_Iterator, OperatorPrefixIncrement )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        CF::Array::Iterator i3;
        CF::Array::Iterator i4;
        
        i1 = a.begin();
        i2 = ++i1;
        i4 = ++i3;
        
        ASSERT_TRUE( *( i1 ) != nullptr );
        ASSERT_TRUE( *( i2 ) != nullptr );
        ASSERT_TRUE( *( i3 ) == nullptr );
        ASSERT_TRUE( *( i4 ) == nullptr );
        
        ASSERT_TRUE( CF::String( *( i1 ) ) == "hello, universe" );
        ASSERT_TRUE( CF::String( *( i2 ) ) == "hello, universe" );
    }
}

TEST( CFPP_Array_Iterator, OperatorPostfixIncrement )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        CF::Array::Iterator i3;
        CF::Array::Iterator i4;
        
        i1 = a.begin();
        i2 = i1++;
        i4 = i3++;
        
        ASSERT_TRUE( *( i1 ) != nullptr );
        ASSERT_TRUE( *( i2 ) != nullptr );
        ASSERT_TRUE( *( i3 ) == nullptr );
        ASSERT_TRUE( *( i4 ) == nullptr );
        
        ASSERT_TRUE( CF::String( *( i1 ) ) == "hello, universe" );
        ASSERT_TRUE( CF::String( *( i2 ) ) == "hello, world" );
    }
}

TEST( CFPP_Array_Iterator, OperatorPrefixDecrement )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        CF::Array::Iterator i3;
        CF::Array::Iterator i4;
        
        i1 = a.end();
        i2 = --i1;
        i4 = --i3;
        
        ASSERT_TRUE( *( i1 ) != nullptr );
        ASSERT_TRUE( *( i2 ) != nullptr );
        ASSERT_TRUE( *( i3 ) == nullptr );
        ASSERT_TRUE( *( i4 ) == nullptr );
        
        ASSERT_TRUE( CF::String( *( i1 ) ) == "hello, universe" );
        ASSERT_TRUE( CF::String( *( i2 ) ) == "hello, universe" );
    }
}

TEST( CFPP_Array_Iterator, OperatorPostfixDecrement )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        CF::Array::Iterator i3;
        CF::Array::Iterator i4;
        
        i1 = a.end();
        i2 = i1--;
        i4 = i3--;
        
        ASSERT_TRUE( *( i1 ) != nullptr );
        ASSERT_TRUE( *( i2 ) == nullptr );
        ASSERT_TRUE( *( i3 ) == nullptr );
        ASSERT_TRUE( *( i4 ) == nullptr );
        
        ASSERT_TRUE( CF::String( *( i1 ) ) == "hello, universe" );
    }
}

TEST( CFPP_Array_Iterator, OperatorPlusEqual )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    a << CF::String( "foo" );
    a << CF::String( "bar" );
    
    {
        CF::Array::Iterator i;
        
        i = a.begin();
        
        ASSERT_TRUE( *( i ) != nullptr );
        ASSERT_TRUE( CF::String( *( i ) ) == "hello, world" );
        
        i += 1;
        
        ASSERT_TRUE( *( i ) != nullptr );
        ASSERT_TRUE( CF::String( *( i ) ) == "hello, universe" );
        
        i += 0;
        
        ASSERT_TRUE( *( i ) != nullptr );
        ASSERT_TRUE( CF::String( *( i ) ) == "hello, universe" );
        
        i += 2;
        
        ASSERT_TRUE( *( i ) != nullptr );
        ASSERT_TRUE( CF::String( *( i ) ) == "bar" );
    }
}

TEST( CFPP_Array_Iterator, OperatorMinusEqual )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    a << CF::String( "foo" );
    a << CF::String( "bar" );
    
    {
        CF::Array::Iterator i;
        
        i = a.end();
        
        ASSERT_TRUE( *( i ) == nullptr );
        
        i -= 1;
        
        ASSERT_TRUE( *( i ) != nullptr );
        ASSERT_TRUE( CF::String( *( i ) ) == "bar" );
        
        i -= 0;
        
        ASSERT_TRUE( *( i ) != nullptr );
        ASSERT_TRUE( CF::String( *( i ) ) == "bar" );
        
        i -= 2;
        
        ASSERT_TRUE( *( i ) != nullptr );
        ASSERT_TRUE( CF::String( *( i ) ) == "hello, universe" );
    }
}

TEST( CFPP_Array_Iterator, OperatorPlus )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    a << CF::String( "foo" );
    a << CF::String( "bar" );
    
    {
        CF::Array::Iterator i;
        
        i = a.begin();
        
        ASSERT_TRUE( *( i )                               != nullptr );
        ASSERT_TRUE( *( i + static_cast< CFIndex >( 1 ) ) != nullptr );
        ASSERT_TRUE( *( i + static_cast< CFIndex >( 0 ) ) != nullptr );
        ASSERT_TRUE( *( i + static_cast< CFIndex >( 2 ) ) != nullptr );
        
        ASSERT_TRUE( CF::String( *( i ) )                               == "hello, world" );
        ASSERT_TRUE( CF::String( *( i + static_cast< CFIndex >( 1 ) ) ) == "hello, universe" );
        ASSERT_TRUE( CF::String( *( i + static_cast< CFIndex >( 0 ) ) ) == "hello, world" );
        ASSERT_TRUE( CF::String( *( i + static_cast< CFIndex >( 2 ) ) ) == "foo" );
    }
}

TEST( CFPP_Array_Iterator, OperatorMinus )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    a << CF::String( "foo" );
    a << CF::String( "bar" );
    
    {
        CF::Array::Iterator i;
        
        i = a.end();
        
        ASSERT_TRUE( *( i )                               == nullptr );
        ASSERT_TRUE( *( i - static_cast< CFIndex >( 1 ) ) != nullptr );
        ASSERT_TRUE( *( i - static_cast< CFIndex >( 0 ) ) == nullptr );
        ASSERT_TRUE( *( i - static_cast< CFIndex >( 2 ) ) != nullptr );
        
        ASSERT_TRUE( CF::String( *( i - static_cast< CFIndex >( 1 ) ) ) == "bar" );
        ASSERT_TRUE( CF::String( *( i - static_cast< CFIndex >( 2 ) ) ) == "foo" );
    }
}

TEST( CFPP_Array_Iterator, OperatorEqual )
{
    CF::Array a1;
    CF::Array a2;
    
    a1 << CF::String( "hello, world" );
    a1 << CF::String( "hello, universe" );
    a1 << CF::String( "foo" );
    a1 << CF::String( "bar" );
    
    a2 = a1;
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        
        ASSERT_TRUE( i1 == i1 );
        ASSERT_TRUE( i1 == i2 );
        
        i1 = a1.begin();
        i2 = a1.begin();
        
        ASSERT_TRUE( i1 == i1 );
        ASSERT_TRUE( i1 == i2 );
        
        i2++;
        
        ASSERT_FALSE( i1 == i2 );
        
        i2--;
        
        ASSERT_TRUE( i1 == i2 );
        
        i1 = a1.begin();
        i2 = a2.begin();
        
        ASSERT_FALSE( i1 == i2 );
        
        i1 = a1.begin();
        
        a1 << CF::String( "foobar" );
        
        i2 = a1.begin();
        
        ASSERT_FALSE( i1 == i2 );
    }
}

TEST( CFPP_Array_Iterator, OperatorNotEqual )
{
    CF::Array a1;
    CF::Array a2;
    
    a1 << CF::String( "hello, world" );
    a1 << CF::String( "hello, universe" );
    a1 << CF::String( "foo" );
    a1 << CF::String( "bar" );
    
    a2 = a1;
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        
        ASSERT_FALSE( i1 != i1 );
        ASSERT_FALSE( i1 != i2 );
        
        i1 = a1.begin();
        i2 = a1.begin();
        
        ASSERT_FALSE( i1 != i1 );
        ASSERT_FALSE( i1 != i2 );
        
        i2++;
        
        ASSERT_TRUE( i1 != i2 );
        
        i2--;
        
        ASSERT_FALSE( i1 != i2 );
        
        i1 = a1.begin();
        i2 = a2.begin();
        
        ASSERT_TRUE( i1 != i2 );
        
        i1 = a1.begin();
        
        a1 << CF::String( "foobar" );
        
        i2 = a1.begin();
        
        ASSERT_TRUE( i1 != i2 );
    }
}

TEST( CFPP_Array_Iterator, OperatorDereference )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        
        ASSERT_TRUE( *( i1 ) == nullptr );
        ASSERT_TRUE( *( i2 ) == nullptr );
        
        i1 = a1.begin();
        i2 = a2.begin();
        
        ASSERT_TRUE( *( i1 ) != nullptr );
        ASSERT_TRUE( *( i2 ) == nullptr );
        
        ASSERT_TRUE( CF::String( *( i1 ) ) == "hello, world" );
        
        i1--;
        i2--;
        
        ASSERT_TRUE( *( i1 ) == nullptr );
        ASSERT_TRUE( *( i2 ) == nullptr );
    }
}

TEST( CFPP_Array_Iterator, OperatorCastToCFType )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        
        ASSERT_TRUE( static_cast< CFTypeRef >( i1 ) == nullptr );
        ASSERT_TRUE( static_cast< CFTypeRef >( i2 ) == nullptr );
        
        i1 = a1.begin();
        i2 = a2.begin();
        
        ASSERT_TRUE( static_cast< CFTypeRef >( i1 ) != nullptr );
        ASSERT_TRUE( static_cast< CFTypeRef >( i2 ) == nullptr );
        
        ASSERT_TRUE( CF::String( static_cast< CFTypeRef >( i1 ) ) == "hello, world" );
        
        i1--;
        i2--;
        
        ASSERT_TRUE( static_cast< CFTypeRef >( i1 ) == nullptr );
        ASSERT_TRUE( static_cast< CFTypeRef >( i2 ) == nullptr );
    }
}

TEST( CFPP_Array_Iterator, GetTypeID )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        
        ASSERT_TRUE( i1.GetTypeID() == 0 );
        ASSERT_TRUE( i2.GetTypeID() == 0 );
        
        i1 = a1.begin();
        i2 = a2.begin();
        
        ASSERT_TRUE( i1.GetTypeID() == CFStringGetTypeID() );
        ASSERT_TRUE( i2.GetTypeID() == 0 );
        
        i1--;
        i2--;
        
        ASSERT_TRUE( i1.GetTypeID() == 0 );
        ASSERT_TRUE( i2.GetTypeID() == 0 );
    }
}

TEST( CFPP_Array_Iterator, GetCFObject )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        
        ASSERT_TRUE( i1.GetCFObject() == nullptr );
        ASSERT_TRUE( i2.GetCFObject() == nullptr );
        
        i1 = a1.begin();
        i2 = a2.begin();
        
        ASSERT_TRUE( i1.GetCFObject() != nullptr );
        ASSERT_TRUE( i2.GetCFObject() == nullptr );
        
        ASSERT_TRUE( CF::String( i1.GetCFObject() ) == "hello, world" );
        
        i1--;
        i2--;
        
        ASSERT_TRUE( i1.GetCFObject() == nullptr );
        ASSERT_TRUE( i2.GetCFObject() == nullptr );
    }
}

TEST( CFPP_Array_Iterator, Swap )
{
    CF::Array a;
    
    a << CF::String( "hello, world" );
    a << CF::String( "hello, universe" );
    
    {
        CF::Array::Iterator i1;
        CF::Array::Iterator i2;
        
        i1 = a.begin();
        i2 = a.end();
        
        ASSERT_TRUE( i1 == a.begin() );
        ASSERT_TRUE( i2 == a.end() );
        
        swap( i1, i2 );
        
        ASSERT_TRUE( i1 == a.end() );
        ASSERT_TRUE( i2 == a.begin() );
    }
}

TEST( CFPP_Array_Iterator, TestIterate )
{
    CF::Array           a1;
    CF::Array           a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array           a3;
    CF::Array::Iterator it;
    CFIndex              i;
    
    a3 << CF::String( "hello, world" );
    a3 << CF::String( "hello, universe" );
    a3 << CF::String( "foo" );
    a3 << CF::String( "bar" );
    
    {
        i = 0;
        
        for( it = a1.begin(); it != a1.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = a2.begin(); it != a2.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = a3.begin(); it != a3.end(); ++it )
        {
            switch( i )
            {
                case 0: ASSERT_EQ( CF::String( *( it ) ), "hello, world" );    break;
                case 1: ASSERT_EQ( CF::String( *( it ) ), "hello, universe" ); break;
                case 2: ASSERT_EQ( CF::String( *( it ) ), "foo" );             break;
                case 3: ASSERT_EQ( CF::String( *( it ) ), "bar" );             break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}

TEST( CFPP_Array_Iterator, TestIterateSTD )
{
    CF::Array           a1;
    CF::Array           a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array           a3;
    CF::Array::Iterator it;
    CFIndex              i;
    
    a3 << CF::String( "hello, world" );
    a3 << CF::String( "hello, universe" );
    a3 << CF::String( "foo" );
    a3 << CF::String( "bar" );
    
    {
        i = 0;
        
        for( it = std::begin( a1 ); it != std::end( a1 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = std::begin( a2 ); it != std::end( a2 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = std::begin( a3 ); it != std::end( a3 ); ++it )
        {
            switch( i )
            {
                case 0: ASSERT_EQ( CF::String( *( it ) ), "hello, world" );    break;
                case 1: ASSERT_EQ( CF::String( *( it ) ), "hello, universe" ); break;
                case 2: ASSERT_EQ( CF::String( *( it ) ), "foo" );             break;
                case 3: ASSERT_EQ( CF::String( *( it ) ), "bar" );             break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}

TEST( CFPP_Array_Iterator, TestIterateCPP11 )
{
    CF::Array           a1;
    CF::Array           a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array           a3;
    CF::Array::Iterator it;
    CFIndex              i;
    
    a3 << CF::String( "hello, world" );
    a3 << CF::String( "hello, universe" );
    a3 << CF::String( "foo" );
    a3 << CF::String( "bar" );
    
    {
        i = 0;
        
        for( CF::String s: a1 )
        {
            ( void )s;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( CF::String s: a2 )
        {
            ( void )s;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( CF::String s: a3 )
        {
            switch( i )
            {
                case 0: ASSERT_EQ( s, "hello, world" );    break;
                case 1: ASSERT_EQ( s, "hello, universe" ); break;
                case 2: ASSERT_EQ( s, "foo" );             break;
                case 3: ASSERT_EQ( s, "bar" );             break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}
