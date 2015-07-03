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
 * @file        Test-CFPP-Data-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Data::Iterator
 */

#include <CF++.hpp>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

static CF::Data::Byte __bytes[] = { 0xDE, 0xAD, 0xBE, 0xEF };

TEST( CFPP_Data_Iterator, DataBegin )
{
    CF::Data d1;
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3( __bytes, sizeof( __bytes ) );
    
    ASSERT_EQ( *( d1.begin() ), 0x00 );
    ASSERT_EQ( *( d2.begin() ), 0x00 );
    ASSERT_EQ( *( d3.begin() ), 0xDE );
    
    ASSERT_TRUE( d1.begin() == d1.end() );
    ASSERT_TRUE( d2.begin() == d2.end() );
    ASSERT_TRUE( d3.begin() != d3.end() );
}

TEST( CFPP_Data_Iterator, DataEnd )
{
    CF::Data d1;
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3( __bytes, sizeof( __bytes ) );
    
    ASSERT_EQ( *( d1.end() ), 0x00 );
    ASSERT_EQ( *( d2.end() ), 0x00 );
    ASSERT_EQ( *( d3.end() ), 0x00 );
    
    ASSERT_TRUE( d1.begin() == d1.end() );
    ASSERT_TRUE( d2.begin() == d2.end() );
    ASSERT_TRUE( d3.begin() != d3.end() );
}

TEST( CFPP_Data_Iterator, CTOR )
{
    CF::Data::Iterator i;
    
    ASSERT_EQ( *( i ), 0x00 );
}

TEST( CFPP_Data_Iterator, CCTOR )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2( i1 );
    CF::Data::Iterator i3( d.begin() );
    CF::Data::Iterator i4( i3 );
    
    ASSERT_EQ( *( i1 ), 0x00 );
    ASSERT_EQ( *( i2 ), 0x00 );
    ASSERT_EQ( *( i3 ), 0xDE );
    ASSERT_EQ( *( i4 ), 0xDE );
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Data_Iterator, MCTOR )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2( std::move( i1 ) );
    CF::Data::Iterator i3( d.begin() );
    CF::Data::Iterator i4( std::move( i3 ) );
    
    ASSERT_EQ( *( i1 ), 0x00 );
    ASSERT_EQ( *( i2 ), 0x00 );
    ASSERT_EQ( *( i3 ), 0x00 );
    ASSERT_EQ( *( i4 ), 0xDE );
}
#endif

TEST( CFPP_Data_Iterator, OperatorAssign )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    CF::Data::Iterator i3( d.begin() );
    CF::Data::Iterator i4;
    
    ASSERT_EQ( *( i1 ), 0x00 );
    ASSERT_EQ( *( i3 ), 0xDE );
    
    i2 = i1;
    i4 = i3;
    
    ASSERT_EQ( *( i2 ), 0x00 );
    ASSERT_EQ( *( i4 ), 0xDE );
}

TEST( CFPP_Data_Iterator, OperatorPrefixIncrement )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    CF::Data::Iterator i3;
    CF::Data::Iterator i4;
    
    i1 = d.begin();
    i2 = ++i1;
    i4 = ++i3;
    
    ASSERT_EQ( *( i1 ), 0xAD );
    ASSERT_EQ( *( i2 ), 0xAD );
    ASSERT_EQ( *( i3 ), 0x00 );
    ASSERT_EQ( *( i4 ), 0x00 );
}

TEST( CFPP_Data_Iterator, OperatorPostfixIncrement )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    CF::Data::Iterator i3;
    CF::Data::Iterator i4;
    
    i1 = d.begin();
    i2 = i1++;
    i4 = i3++;
    
    ASSERT_EQ( *( i1 ), 0xAD );
    ASSERT_EQ( *( i2 ), 0xDE );
    ASSERT_EQ( *( i3 ), 0x00 );
    ASSERT_EQ( *( i4 ), 0x00 );
}

TEST( CFPP_Data_Iterator, OperatorPrefixDecrement )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    CF::Data::Iterator i3;
    CF::Data::Iterator i4;
    
    i1 = d.end();
    i2 = --i1;
    i4 = --i3;
    
    ASSERT_EQ( *( i1 ), 0xEF );
    ASSERT_EQ( *( i2 ), 0xEF );
    ASSERT_EQ( *( i3 ), 0x00 );
    ASSERT_EQ( *( i4 ), 0x00 );
}

TEST( CFPP_Data_Iterator, OperatorPostfixDecrement )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    CF::Data::Iterator i3;
    CF::Data::Iterator i4;
    
    i1 = d.end();
    i2 = i1--;
    i4 = i3--;
    
    ASSERT_EQ( *( i1 ), 0xEF );
    ASSERT_EQ( *( i2 ), 0x00 );
    ASSERT_EQ( *( i3 ), 0x00 );
    ASSERT_EQ( *( i4 ), 0x00 );
}

TEST( CFPP_Data_Iterator, OperatorPlusEqual )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i;
    
    i = d.begin();
    
    ASSERT_EQ( *( i ), 0xDE );
    
    i += 1;
    
    ASSERT_EQ( *( i ), 0xAD );
    
    i += 0;
    
    ASSERT_EQ( *( i ), 0xAD );
    
    i += 2;
    
    ASSERT_EQ( *( i ), 0xEF );
}

TEST( CFPP_Data_Iterator, OperatorMinusEqual )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i;
    
    i = d.end();
    
    ASSERT_EQ( *( i ), 0x00 );
    
    i -= 1;
    
    ASSERT_EQ( *( i ), 0xEF );
    
    i -= 0;
    
    ASSERT_EQ( *( i ), 0xEF );
    
    i -= 2;
    
    ASSERT_EQ( *( i ), 0xAD );
}

TEST( CFPP_Data_Iterator, OperatorPlus )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i;
    
    i = d.begin();
    
    ASSERT_EQ( *( i ), 0xDE );
    ASSERT_EQ( *( i + static_cast< CFIndex >( 1 ) ), 0xAD );
    ASSERT_EQ( *( i + static_cast< CFIndex >( 0 ) ), 0xDE );
    ASSERT_EQ( *( i + static_cast< CFIndex >( 2 ) ), 0xBE );
}

TEST( CFPP_Data_Iterator, OperatorMinus )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i;
    
    i = d.end();
    
    ASSERT_EQ( *( i ), 0x00 );
    ASSERT_EQ( *( i - static_cast< CFIndex >( 1 ) ), 0xEF );
    ASSERT_EQ( *( i - static_cast< CFIndex >( 0 ) ), 0x00 );
    ASSERT_EQ( *( i - static_cast< CFIndex >( 2 ) ), 0xBE );
}

TEST( CFPP_Data_Iterator, OperatorEqual )
{
    CF::Data           d1( __bytes, sizeof( __bytes ) );
    CF::Data           d2( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    
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
}

TEST( CFPP_Data_Iterator, OperatorNotEqual )
{
    CF::Data           d1( __bytes, sizeof( __bytes ) );
    CF::Data           d2( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    
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
}

TEST( CFPP_Data_Iterator, OperatorMultiply )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i;
    
    ASSERT_EQ( *( i ), 0x00 );
    
    i = d.begin();
    
    ASSERT_EQ( *( i ), 0xDE );
}

TEST( CFPP_Data_Iterator, OperatorCastToByte )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i;
    
    ASSERT_EQ( static_cast< CF::Data::Byte >( i ), 0x00 );
    
    i = d.begin();
    
    ASSERT_EQ( static_cast< CF::Data::Byte >( i ), 0xDE );
}

TEST( CFPP_Data_Iterator, Swap )
{
    CF::Data           d( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator i1;
    CF::Data::Iterator i2;
    
    i1 = d.begin();
    i2 = d.end();
    
    ASSERT_TRUE( i1 == d.begin() );
    ASSERT_TRUE( i2 == d.end() );
    
    swap( i1, i2 );
    
    ASSERT_TRUE( i1 == d.end() );
    ASSERT_TRUE( i2 == d.begin() );
}

TEST( CFPP_Data_Iterator, TestIterate )
{
    CF::Data           d1;
    CF::Data           d2( static_cast< CFDataRef >( NULL ) );
    CF::Data           d3( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator it;
    CFIndex            i;
    
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
            switch( i )
            {
                case 0: ASSERT_EQ( *( it ), 0xDE ); break;
                case 1: ASSERT_EQ( *( it ), 0xAD ); break;
                case 2: ASSERT_EQ( *( it ), 0xBE ); break;
                case 3: ASSERT_EQ( *( it ), 0xEF ); break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}

TEST( CFPP_Data_Iterator, TestIterateSTD )
{
    CF::Data           d1;
    CF::Data           d2( static_cast< CFDataRef >( NULL ) );
    CF::Data           d3( __bytes, sizeof( __bytes ) );
    CF::Data::Iterator it;
    CFIndex            i;
    
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
            switch( i )
            {
                case 0: ASSERT_EQ( *( it ), 0xDE ); break;
                case 1: ASSERT_EQ( *( it ), 0xAD ); break;
                case 2: ASSERT_EQ( *( it ), 0xBE ); break;
                case 3: ASSERT_EQ( *( it ), 0xEF ); break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Data_Iterator, TestIterateCPP11 )
{
    CF::Data d1;
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3( __bytes, sizeof( __bytes ) );
    CFIndex  i;
    
    {
        i = 0;
        
        for( CF::Data::Byte b: d1 )
        {
            ( void )b;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( CF::Data::Byte b: d2 )
        {
            ( void )b;
            
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    {
        i = 0;
        
        for( CF::Data::Byte b: d3 )
        {
            switch( i )
            {
                case 0: ASSERT_EQ( b, 0xDE ); break;
                case 1: ASSERT_EQ( b, 0xAD ); break;
                case 2: ASSERT_EQ( b, 0xBE ); break;
                case 3: ASSERT_EQ( b, 0xEF ); break;
            }
            
            i++;
        }
        
        ASSERT_EQ( i, 4 );
    }
}
#endif
