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
 * @file        Test-CFPP-ReadStream-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::ReadStream::Iterator
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_ReadStream_Iterator, ReadStreamBegin )
{
    {
        CF::ReadStream s1;
        CF::ReadStream s2;
        
        s1.Open( "/etc/hosts" );
        
        ASSERT_TRUE(  ( *( s1.begin() ) ).IsValid() );
        ASSERT_FALSE( ( *( s2.begin() ) ).IsValid() );
        
        s1.Close();
    }
    
    {
        CF::ReadStream s1;
        
        s1.Open( "/etc/hosts" );
        
        ASSERT_GT( ( *( s1.begin() ) ).GetLength(), 0 );
        
        s1.Close();
    }
    
    {
        CF::ReadStream s1;
        
        s1.Open( "/etc/hosts" );
        
        ASSERT_EQ( ( *( s1.begin( 10 ) ) ).GetLength(), 10 );
        
        s1.Close();
    }
    
    {
        CF::ReadStream s1;
        CF::ReadStream s2;
        
        s1.Open( "/etc/hosts" );
        
        ASSERT_TRUE( s1.begin() != s1.end() );
        ASSERT_TRUE( s2.begin() == s2.end() );
        
        s1.Close();
    }
}

TEST( CFPP_ReadStream_Iterator, ReadStreamEnd )
{
    {
        CF::ReadStream s1;
        CF::ReadStream s2;
        
        s1.Open( "/etc/hosts" );
        
        ASSERT_FALSE( ( *( s1.end() ) ).IsValid() );
        ASSERT_FALSE( ( *( s2.end() ) ).IsValid() );
        
        s1.Close();
    }
    
    {
        CF::ReadStream s1;
        
        s1.Open( "/etc/hosts" );
        
        ASSERT_EQ( ( *( s1.end() ) ).GetLength(), 0 );
        
        s1.Close();
    }
    
    {
        CF::ReadStream s1;
        CF::ReadStream s2( static_cast< CFReadStreamRef >( nullptr ) );
        CF::ReadStream s3;
        
        s1.Open( "/etc/hosts" );
        
        ASSERT_TRUE( s1.begin() != s1.end() );
        ASSERT_TRUE( s2.begin() == s2.end() );
        
        s1.Close();
    }
}

TEST( CFPP_ReadStream_Iterator, CTOR )
{
    CF::ReadStream::Iterator i;
    
    ASSERT_FALSE( ( *( i ) ).IsValid() );
}

TEST( CFPP_ReadStream_Iterator, CCTOR )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    
    s1.Open( "/etc/hosts" );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2( i1 );
        CF::ReadStream::Iterator i3( s1.begin() );
        CF::ReadStream::Iterator i4( i3 );
        CF::ReadStream::Iterator i5( s2.begin() );
        CF::ReadStream::Iterator i6( i5 );
        
        ASSERT_FALSE( ( *( i1 ) ).IsValid() );
        ASSERT_FALSE( ( *( i2 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i3 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i4 ) ).IsValid() );
        ASSERT_FALSE( ( *( i5 ) ).IsValid() );
        ASSERT_FALSE( ( *( i6 ) ).IsValid() );
        
        ASSERT_GT( ( *( i3 ) ).GetLength(), 0 );
        ASSERT_GT( ( *( i4 ) ).GetLength(), 0 );
        
        ASSERT_EQ( *( i3 ), *( i4 ) );
    }
    
    s1.Close();
}

TEST( CFPP_ReadStream_Iterator, MCTOR )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    
    s1.Open( "/etc/hosts" );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2( std::move( i1 ) );
        CF::ReadStream::Iterator i3( s1.begin() );
        CF::ReadStream::Iterator i4( std::move( i3 ) );
        CF::ReadStream::Iterator i5( s2.begin() );
        CF::ReadStream::Iterator i6( std::move( i5 ) );
        
        ASSERT_FALSE( ( *( i1 ) ).IsValid() );
        ASSERT_FALSE( ( *( i2 ) ).IsValid() );
        ASSERT_FALSE( ( *( i3 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i4 ) ).IsValid() );
        ASSERT_FALSE( ( *( i5 ) ).IsValid() );
        ASSERT_FALSE( ( *( i6 ) ).IsValid() );
        
        ASSERT_GT( ( *( i4 ) ).GetLength(), 0 );
    }
    
    s1.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorAssign )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    
    s1.Open( "/etc/hosts" );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2;
        CF::ReadStream::Iterator i3( s1.begin() );
        CF::ReadStream::Iterator i4;
        CF::ReadStream::Iterator i5( s2.begin() );
        CF::ReadStream::Iterator i6;
        
        ASSERT_FALSE( ( *( i1 ) ).IsValid() );
        ASSERT_FALSE( ( *( i2 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i3 ) ).IsValid() );
        ASSERT_FALSE( ( *( i4 ) ).IsValid() );
        ASSERT_FALSE( ( *( i5 ) ).IsValid() );
        ASSERT_FALSE( ( *( i6 ) ).IsValid() );
        
        ASSERT_GT( ( *( i3 ) ).GetLength(), 0 );
        
        i2 = i1;
        i4 = i3;
        i6 = i5;
        
        ASSERT_FALSE( ( *( i2 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i4 ) ).IsValid() );
        ASSERT_FALSE( ( *( i5 ) ).IsValid() );
        
        ASSERT_GT( ( *( i4 ) ).GetLength(), 0 );
        
        ASSERT_EQ( *( i3 ), *( i4 ) );
    }
    
    s1.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorPrefixIncrement )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    CF::ReadStream s3;
    CF::Data       d1;
    CF::Data       d2;
    
    s1.Open( "/etc/hosts" );
    s3.Open( "/etc/hosts" );
    
    d1 = s3.Read( 10 );
    d2 = s3.Read( 10 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT( d1.GetLength(), 0 );
    ASSERT_GT( d2.GetLength(), 0 );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2;
        CF::ReadStream::Iterator i3;
        CF::ReadStream::Iterator i4;
        
        i1 = s1.begin( 10 );
        i2 = ++i1;
        i3 = s2.begin( 10 );
        i4 = ++i3;
        
        ASSERT_TRUE(  ( *( i1 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i2 ) ).IsValid() );
        ASSERT_FALSE( ( *( i3 ) ).IsValid() );
        ASSERT_FALSE( ( *( i4 ) ).IsValid() );
        
        ASSERT_GT( ( *( i1 ) ).GetLength(), 0 );
        ASSERT_GT( ( *( i2 ) ).GetLength(), 0 );
        
        ASSERT_EQ( i1, i2 );
        ASSERT_EQ( *( i1 ), d2 );
        ASSERT_EQ( *( i2 ), d2 );
    }
    
    s1.Close();
    s3.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorPostfixIncrement )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    CF::ReadStream s3;
    CF::Data       d1;
    CF::Data       d2;
    
    s1.Open( "/etc/hosts" );
    s3.Open( "/etc/hosts" );
    
    d1 = s3.Read( 10 );
    d2 = s3.Read( 10 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT( d1.GetLength(), 0 );
    ASSERT_GT( d2.GetLength(), 0 );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2;
        CF::ReadStream::Iterator i3;
        CF::ReadStream::Iterator i4;
        
        i1 = s1.begin( 10 );
        i2 = i1++;
        i3 = s2.begin( 10 );
        i4 = i3++;
        
        ASSERT_TRUE(  ( *( i1 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i2 ) ).IsValid() );
        ASSERT_FALSE( ( *( i3 ) ).IsValid() );
        ASSERT_FALSE( ( *( i4 ) ).IsValid() );
        
        ASSERT_GT( ( *( i1 ) ).GetLength(), 0 );
        ASSERT_GT( ( *( i2 ) ).GetLength(), 0 );
        
        ASSERT_NE( i1, i2 );
        ASSERT_EQ( *( i1 ), d2 );
        ASSERT_EQ( *( i2 ), d1 );
    }
    
    s1.Close();
    s3.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorPlusEqual )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    CF::ReadStream s3;
    CF::Data       d1;
    CF::Data       d2;
    CF::Data       d3;
    
    s1.Open( "/etc/hosts" );
    s3.Open( "/etc/hosts" );
    
    d1 = s3.Read( 10 );
    d2 = s3.Read( 10 );
    d3 = s3.Read( 10 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    ASSERT_TRUE( d3.IsValid() );
    
    ASSERT_GT( d1.GetLength(), 0 );
    ASSERT_GT( d2.GetLength(), 0 );
    ASSERT_GT( d3.GetLength(), 0 );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2;
        
        i1  = s1.begin( 10 );
        i1 += 2;
        i2  = s2.begin( 10 );
        i2 += 2;
        
        ASSERT_TRUE(  ( *( i1 ) ).IsValid() );
        ASSERT_FALSE( ( *( i2 ) ).IsValid() );
        
        ASSERT_GT( ( *( i1 ) ).GetLength(), 0 );
        
        ASSERT_EQ( *( i1 ), d3 );
    }
    
    s1.Close();
    s3.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorPlus )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    CF::ReadStream s3;
    CF::Data       d1;
    CF::Data       d2;
    CF::Data       d3;
    
    s1.Open( "/etc/hosts" );
    s3.Open( "/etc/hosts" );
    
    d1 = s3.Read( 10 );
    d2 = s3.Read( 10 );
    d3 = s3.Read( 10 );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    ASSERT_TRUE( d3.IsValid() );
    
    ASSERT_GT( d1.GetLength(), 0 );
    ASSERT_GT( d2.GetLength(), 0 );
    ASSERT_GT( d3.GetLength(), 0 );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2;
        CF::ReadStream::Iterator i3;
        CF::ReadStream::Iterator i4;
        
        i1 = s1.begin( 10 );
        i2 = i1 + 2;
        i3 = s2.begin( 10 );
        i4 = i3 + 2;
        
        ASSERT_TRUE(  ( *( i1 ) ).IsValid() );
        ASSERT_TRUE(  ( *( i2 ) ).IsValid() );
        ASSERT_FALSE( ( *( i3 ) ).IsValid() );
        ASSERT_FALSE( ( *( i4 ) ).IsValid() );
        
        ASSERT_GT( ( *( i1 ) ).GetLength(), 0 );
        ASSERT_GT( ( *( i2 ) ).GetLength(), 0 );
        
        ASSERT_NE( i1, i2 );
        ASSERT_EQ( *( i1 ), d1 );
        ASSERT_EQ( *( i2 ), d3 );
    }
    
    s1.Close();
    s3.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorEqual )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    CF::ReadStream s3;
    
    s1.Open( "/etc/hosts" );
    s3.Open( "/etc/hosts" );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2;
        CF::ReadStream::Iterator i3;
        CF::ReadStream::Iterator i4;
        CF::ReadStream::Iterator i5;
        CF::ReadStream::Iterator i6;
        
        ASSERT_TRUE( i1 == i2 );
        
        i1 = s1.begin();
        i2 = s1.end();
        i3 = s2.begin();
        i4 = s2.end();
        i5 = s3.begin();
        i6 = s3.end();
        
        ASSERT_FALSE( i1 == i2 );
        ASSERT_TRUE(  i3 == i4 );
        ASSERT_FALSE( i5 == i6 );
        
        ASSERT_FALSE( i1 == i5 );
        ASSERT_FALSE( i2 == i6 );
        
        i2 = i1;
        
        ASSERT_TRUE( i1 == i2 );
        
        i2 = i1 + 1;
        
        ASSERT_FALSE( i1 == i2 );
    }
    
    s1.Close();
    s3.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorNotEqual )
{
    CF::ReadStream s1;
    CF::ReadStream s2;
    CF::ReadStream s3;
    
    s1.Open( "/etc/hosts" );
    s3.Open( "/etc/hosts" );
    
    {
        CF::ReadStream::Iterator i1;
        CF::ReadStream::Iterator i2;
        CF::ReadStream::Iterator i3;
        CF::ReadStream::Iterator i4;
        CF::ReadStream::Iterator i5;
        CF::ReadStream::Iterator i6;
        
        ASSERT_FALSE( i1 != i2 );
        
        i1 = s1.begin();
        i2 = s1.end();
        i3 = s2.begin();
        i4 = s2.end();
        i5 = s3.begin();
        i6 = s3.end();
        
        ASSERT_TRUE(  i1 != i2 );
        ASSERT_FALSE( i3 != i4 );
        ASSERT_TRUE(  i5 != i6 );
        
        ASSERT_TRUE( i1 != i5 );
        ASSERT_TRUE( i2 != i6 );
        
        i2 = i1;
        
        ASSERT_FALSE( i1 != i2 );
        
        i2 = i1 + 1;
        
        ASSERT_TRUE( i1 != i2 );
    }
    
    s1.Close();
    s3.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorDereference )
{
    CF::ReadStream           s1;
    CF::ReadStream           s2;
    CF::ReadStream::Iterator i1;
    CF::ReadStream::Iterator i2;
    
    s1.Open( "/etc/hosts" );
    
    i1 = s1.begin();
    i2 = s2.begin();
    
    ASSERT_TRUE(  ( *( i1 ) ).IsValid() );
    ASSERT_FALSE( ( *( i2 ) ).IsValid() );
    
    s1.Close();
}

TEST( CFPP_ReadStream_Iterator, OperatorCastToData )
{
    CF::ReadStream           s1;
    CF::ReadStream           s2;
    CF::ReadStream::Iterator i1;
    CF::ReadStream::Iterator i2;
    
    s1.Open( "/etc/hosts" );
    
    i1 = s1.begin();
    i2 = s2.begin();
    
    ASSERT_TRUE(  static_cast< CF::Data >( i1 ).IsValid() );
    ASSERT_FALSE( static_cast< CF::Data >( i2 ).IsValid() );
    
    s1.Close();
}

TEST( CFPP_ReadStream_Iterator, Swap )
{
    CF::ReadStream           s;
    CF::ReadStream::Iterator i1;
    CF::ReadStream::Iterator i2;
    
    s.Open( "/etc/hosts" );
    
    i1 = s.begin();
    i2 = s.end();
    
    ASSERT_TRUE( i1 != s.end() );
    ASSERT_TRUE( i2 == s.end() );
    
    ASSERT_TRUE(  ( *( i1 ) ).IsValid() );
    ASSERT_FALSE( ( *( i2 ) ).IsValid() );
    
    swap( i1, i2 );
    
    ASSERT_TRUE( i1 == s.end() );
    ASSERT_TRUE( i2 != s.end() );
    
    ASSERT_FALSE( ( *( i1 ) ).IsValid() );
    ASSERT_TRUE(  ( *( i2 ) ).IsValid() );
    
    s.Close();
}

TEST( CFPP_ReadStream_Iterator, TestIterate )
{
    CF::ReadStream           s1;
    CF::ReadStream           s2;
    CF::ReadStream::Iterator it;
    CFIndex                  i;
    
    s1.Open( "/etc/hosts" );
    
    {
        i = 0;
        
        for( it = s1.begin( 10 ); it != s1.end(); ++it )
        {
            ASSERT_TRUE( ( *( it ) ).IsValid() );
            
            i++;
        }
        
        ASSERT_GT( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = s2.begin( 10 ); it != s2.end(); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    s1.Close();
}

TEST( CFPP_ReadStream_Iterator, TestIterateSTD )
{
    CF::ReadStream           s1;
    CF::ReadStream           s2;
    CF::ReadStream::Iterator it;
    CFIndex                  i;
    
    s1.Open( "/etc/hosts" );
    
    {
        i = 0;
        
        for( it = std::begin( s1 ); it != std::end( s1 ); ++it )
        {
            ASSERT_TRUE( ( *( it ) ).IsValid() );
            
            i++;
        }
        
        ASSERT_GT( i, 0 );
    }
    
    {
        i = 0;
        
        for( it = std::begin( s2 ); it != std::end( s2 ); ++it )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    s1.Close();
}

TEST( CFPP_ReadStream_Iterator, TestIterateCPP11 )
{
    CF::ReadStream           s1;
    CF::ReadStream           s2;
    CF::ReadStream::Iterator it;
    CFIndex                  i;
    
    s1.Open( "/etc/hosts" );
    
    {
        i = 0;
        
        for( CF::Data d: s1 )
        {
            ASSERT_TRUE( d.IsValid() );
            
            i++;
        }
        
        ASSERT_GT( i, 0 );
    }
    
    {
        i = 0;
        
        for( CF::Data d: s2 )
        {
            i++;
        }
        
        ASSERT_EQ( i, 0 );
    }
    
    s1.Close();
}
