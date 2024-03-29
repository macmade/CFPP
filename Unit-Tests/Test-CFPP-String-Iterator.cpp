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
 * @file        Test-CFPP-String-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::String::Iterator
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_String_Iterator, StringBegin )
{
    CF::String s1;
    CF::String s2( static_cast< CFStringRef >( nullptr ) );
    CF::String s3( "hello" );
    
    ASSERT_EQ( *( s1.begin() ), 0 );
    ASSERT_EQ( *( s2.begin() ), 0 );
    ASSERT_EQ( *( s3.begin() ), 'h' );
    
    ASSERT_TRUE( s1.begin() == s1.end() );
    ASSERT_TRUE( s2.begin() == s2.end() );
    ASSERT_TRUE( s3.begin() != s3.end() );
}

TEST( CFPP_String_Iterator, StringEnd )
{
    CF::String s1;
    CF::String s2( static_cast< CFStringRef >( nullptr ) );
    CF::String s3( "hello" );
    
    ASSERT_EQ( *( s1.end() ), 0 );
    ASSERT_EQ( *( s2.end() ), 0 );
    ASSERT_EQ( *( s3.end() ), 0 );
    
    ASSERT_TRUE( s1.begin() == s1.end() );
    ASSERT_TRUE( s2.begin() == s2.end() );
    ASSERT_TRUE( s3.begin() != s3.end() );
}

TEST( CFPP_String_Iterator, CTOR )
{
    CF::String::Iterator i;
    
    ASSERT_EQ( *( i ), 0 );
}

TEST( CFPP_String_Iterator, CCTOR )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2( i1 );
    CF::String::Iterator i3( s.begin() );
    CF::String::Iterator i4( i3 );
    
    ASSERT_EQ( *( i1 ), 0 );
    ASSERT_EQ( *( i2 ), 0 );
    ASSERT_EQ( *( i3 ), 'h' );
    ASSERT_EQ( *( i4 ), 'h' );
}

TEST( CFPP_String_Iterator, MCTOR )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2( std::move( i1 ) );
    CF::String::Iterator i3( s.begin() );
    CF::String::Iterator i4( std::move( i3 ) );
    
    ASSERT_EQ( *( i1 ), 0 );
    ASSERT_EQ( *( i2 ), 0 );
    ASSERT_EQ( *( i3 ), 0 );
    ASSERT_EQ( *( i4 ), 'h' );
}

TEST( CFPP_String_Iterator, OperatorAssign )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    CF::String::Iterator i3( s.begin() );
    CF::String::Iterator i4;
    
    ASSERT_EQ( *( i1 ), 0 );
    ASSERT_EQ( *( i3 ), 'h' );
    
    i2 = i1;
    i4 = i3;
    
    ASSERT_EQ( *( i2 ), 0 );
    ASSERT_EQ( *( i4 ), 'h' );
}

TEST( CFPP_String_Iterator, OperatorPrefixIncrement )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    CF::String::Iterator i3;
    CF::String::Iterator i4;
    
    i1 = s.begin();
    i2 = ++i1;
    i4 = ++i3;
    
    ASSERT_EQ( *( i1 ), 'e' );
    ASSERT_EQ( *( i2 ), 'e' );
    ASSERT_EQ( *( i3 ), 0 );
    ASSERT_EQ( *( i4 ), 0 );
}

TEST( CFPP_String_Iterator, OperatorPostfixIncrement )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    CF::String::Iterator i3;
    CF::String::Iterator i4;
    
    i1 = s.begin();
    i2 = i1++;
    i4 = i3++;
    
    ASSERT_EQ( *( i1 ), 'e' );
    ASSERT_EQ( *( i2 ), 'h' );
    ASSERT_EQ( *( i3 ), 0 );
    ASSERT_EQ( *( i4 ), 0 );
}

TEST( CFPP_String_Iterator, OperatorPrefixDecrement )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    CF::String::Iterator i3;
    CF::String::Iterator i4;
    
    i1 = s.end();
    i2 = --i1;
    i4 = --i3;
    
    ASSERT_EQ( *( i1 ), 'o' );
    ASSERT_EQ( *( i2 ), 'o' );
    ASSERT_EQ( *( i3 ), 0 );
    ASSERT_EQ( *( i4 ), 0 );
}

TEST( CFPP_String_Iterator, OperatorPostfixDecrement )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    CF::String::Iterator i3;
    CF::String::Iterator i4;
    
    i1 = s.end();
    i2 = i1--;
    i4 = i3--;
    
    ASSERT_EQ( *( i1 ), 'o' );
    ASSERT_EQ( *( i2 ), 0 );
    ASSERT_EQ( *( i3 ), 0 );
    ASSERT_EQ( *( i4 ), 0 );
}

TEST( CFPP_String_Iterator, OperatorPlusEqual )
{
    CF::String           s( "hello" );
    CF::String::Iterator i;
    
    i = s.begin();
    
    ASSERT_EQ( *( i ), 'h' );
    
    i += 1;
    
    ASSERT_EQ( *( i ), 'e' );
    
    i += 0;
    
    ASSERT_EQ( *( i ), 'e' );
    
    i += 2;
    
    ASSERT_EQ( *( i ), 'l' );
}

TEST( CFPP_String_Iterator, OperatorMinusEqual )
{
    CF::String           s( "hello" );
    CF::String::Iterator i;
    
    i = s.end();
    
    ASSERT_EQ( *( i ), 0 );
    
    i -= 1;
    
    ASSERT_EQ( *( i ), 'o' );
    
    i -= 0;
    
    ASSERT_EQ( *( i ), 'o' );
    
    i -= 2;
    
    ASSERT_EQ( *( i ), 'l' );
}

TEST( CFPP_String_Iterator, OperatorPlus )
{
    CF::String           s( "hello" );
    CF::String::Iterator i;
    
    i = s.begin();
    
    ASSERT_EQ( *( i ), 'h' );
    ASSERT_EQ( *( i + static_cast< CFIndex >( 1 ) ), 'e' );
    ASSERT_EQ( *( i + static_cast< CFIndex >( 0 ) ), 'h' );
    ASSERT_EQ( *( i + static_cast< CFIndex >( 2 ) ), 'l' );
}

TEST( CFPP_String_Iterator, OperatorMinus )
{
    CF::String           s( "hello" );
    CF::String::Iterator i;
    
    i = s.end();
    
    ASSERT_EQ( *( i ), 0 );
    ASSERT_EQ( *( i - static_cast< CFIndex >( 1 ) ), 'o' );
    ASSERT_EQ( *( i - static_cast< CFIndex >( 0 ) ), 0 );
    ASSERT_EQ( *( i - static_cast< CFIndex >( 2 ) ), 'l' );
}

TEST( CFPP_String_Iterator, OperatorEqual )
{
    CF::String           s1( "hello" );
    CF::String           s2( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    
    ASSERT_TRUE( i1 == i1 );
    ASSERT_TRUE( i1 == i2 );
    
    i1 = s1.begin();
    i2 = s1.begin();
    
    ASSERT_TRUE( i1 == i1 );
    ASSERT_TRUE( i1 == i2 );
    
    i2++;
    
    ASSERT_FALSE( i1 == i2 );
    
    i2--;
    
    ASSERT_TRUE( i1 == i2 );
    
    s2 += ", world";
    i1  = s1.begin();
    i2  = s2.begin();
    
    ASSERT_FALSE( i1 == i2 );
        
    i1  = s1.begin();
    s1 += ", universe";
    i2  = s1.begin();
    
    ASSERT_FALSE( i1 == i2 );
}

TEST( CFPP_String_Iterator, OperatorNotEqual )
{
    CF::String           s1( "hello" );
    CF::String           s2( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    
    ASSERT_FALSE( i1 != i1 );
    ASSERT_FALSE( i1 != i2 );
    
    i1 = s1.begin();
    i2 = s1.begin();
    
    ASSERT_FALSE( i1 != i1 );
    ASSERT_FALSE( i1 != i2 );
    
    i2++;
    
    ASSERT_TRUE( i1 != i2 );
    
    i2--;
    
    ASSERT_FALSE( i1 != i2 );
    
    s2 += ", world";
    i1  = s1.begin();
    i2  = s2.begin();
    
    ASSERT_TRUE( i1 != i2 );
        
    i1  = s1.begin();
    s1 += ", universe";
    i2  = s1.begin();
    
    ASSERT_TRUE( i1 != i2 );
}

TEST( CFPP_String_Iterator, OperatorDereference )
{
    CF::String           s1( "hello" );
    CF::String           s2( static_cast< CFStringRef >( nullptr ) );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    
    ASSERT_EQ( *( i1 ), 0 );
    ASSERT_EQ( *( i2 ), 0 );
    
    i1 = s1.begin();
    i2 = s2.begin();
    
    ASSERT_EQ( *( i1 ), 'h' );
    ASSERT_EQ( *( i2 ), 0 );
    
    i1--;
    i2--;
    
    ASSERT_EQ( *( i1 ), 0 );
    ASSERT_EQ( *( i2 ), 0 );
}

TEST( CFPP_String_Iterator, OperatorCastToChar )
{
    CF::String           s1( "hello" );
    CF::String           s2( static_cast< CFStringRef >( nullptr ) );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    
    ASSERT_EQ( static_cast< char >( i1 ), 0 );
    ASSERT_EQ( static_cast< char >( i2 ), 0 );
    
    i1 = s1.begin();
    i2 = s2.begin();
    
    ASSERT_EQ( static_cast< char >( i1 ), 'h' );
    ASSERT_EQ( static_cast< char >( i2 ), 0 );
    
    i1--;
    i2--;
    
    ASSERT_EQ( static_cast< char >( i1 ), 0 );
    ASSERT_EQ( static_cast< char >( i2 ), 0 );
}

TEST( CFPP_String_Iterator, Swap )
{
    CF::String           s( "hello" );
    CF::String::Iterator i1;
    CF::String::Iterator i2;
    
    i1 = s.begin();
    i2 = s.end();
    
    ASSERT_TRUE( i1 == s.begin() );
    ASSERT_TRUE( i2 == s.end() );
    
    swap( i1, i2 );
    
    ASSERT_TRUE( i1 == s.end() );
    ASSERT_TRUE( i2 == s.begin() );
}

TEST( CFPP_String_Iterator, TestIterate )
{
    CF::String           s1;
    CF::String           s2( static_cast< CFStringRef >( nullptr ) );
    CF::String           s3( "hello" );
    CF::String::Iterator it;
    CFIndex              i;
    
    {
        i = 0;
        
        for( it = s1.begin(); it != s1.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = s2.begin(); it != s2.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = s3.begin(); it != s3.end(); ++it )
        {
            switch( i )
            {
                case 0: ASSERT_EQ( *( it ), 'h' ); break;
                case 1: ASSERT_EQ( *( it ), 'e' ); break;
                case 2: ASSERT_EQ( *( it ), 'l' ); break;
                case 3: ASSERT_EQ( *( it ), 'l' ); break;
                case 4: ASSERT_EQ( *( it ), 'o' ); break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 5 );
    }
}

TEST( CFPP_String_Iterator, TestIterateSTD )
{
    CF::String           s1;
    CF::String           s2( static_cast< CFStringRef >( nullptr ) );
    CF::String           s3( "hello" );
    CF::String::Iterator it;
    CFIndex              i;
    
    {
        i = 0;
        
        for( it = std::begin( s1 ); it != std::end( s1 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = std::begin( s2 ); it != std::end( s2 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = std::begin( s3 ); it != std::end( s3 ); ++it )
        {
            switch( i )
            {
                case 0: ASSERT_EQ( *( it ), 'h' ); break;
                case 1: ASSERT_EQ( *( it ), 'e' ); break;
                case 2: ASSERT_EQ( *( it ), 'l' ); break;
                case 3: ASSERT_EQ( *( it ), 'l' ); break;
                case 4: ASSERT_EQ( *( it ), 'o' ); break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 5 );
    }
}

TEST( CFPP_String_Iterator, TestIterateCPP11 )
{
    CF::String s1;
    CF::String s2( static_cast< CFStringRef >( nullptr ) );
    CF::String s3( "hello" );
    CFIndex    i;
    
    {
        i = 0;
        
        for( char c: s1 )
        {
            ( void )c;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( char c: s2 )
        {
            ( void )c;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( char c: s3 )
        {
            switch( i )
            {
                case 0: ASSERT_EQ( c, 'h' ); break;
                case 1: ASSERT_EQ( c, 'e' ); break;
                case 2: ASSERT_EQ( c, 'l' ); break;
                case 3: ASSERT_EQ( c, 'l' ); break;
                case 4: ASSERT_EQ( c, 'o' ); break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 5 );
    }
}
