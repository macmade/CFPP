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
 * @file        Test-CFPP-UUID.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::UUID
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_UUID, CTOR )
{
    CF::UUID u;
    
    ASSERT_TRUE( u.IsValid() );
    ASSERT_GT( u.GetString().GetLength(), 0 );
}

TEST( CFPP_UUID, CTOR_AutoPointer )
{
    CF::UUID u1( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::UUID u2( CF::AutoPointer( CFDateCreate( nullptr, 0 ) ) );
    CF::UUID u3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_UUID, CTOR_CFType )
{
    CF::UUID u1;
    CF::UUID u2( static_cast< CFTypeRef >( u1.GetCFObject() ) );
    CF::UUID u3( static_cast< CFTypeRef >( nullptr ) );
    CF::UUID u4( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    ASSERT_EQ( u1, u2 );
}

TEST( CFPP_UUID, CTOR_CFUUID )
{
    CF::UUID u1;
    CF::UUID u2( static_cast< CFUUIDRef >( u1.GetCFObject() ) );
    CF::UUID u3( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u4( static_cast< CFUUIDRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    ASSERT_EQ( u1, u2 );
}

TEST( CFPP_UUID, CTOR_NullPointer )
{
    CF::UUID u( nullptr );
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_UUID, CTOR_STDString )
{
    CF::UUID u1( std::string( "" ) );
    CF::UUID u2( std::string( "ABCDEFG" ) );
    CF::UUID u3( std::string( "ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGA" ) );
    CF::UUID u4( std::string( "ABCDEFAB-ABCD-ABCD-ABCD-ABCDEFABCDEF" ) );
    
    ASSERT_FALSE( u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_TRUE(  u3.IsValid() );
    ASSERT_TRUE(  u4.IsValid() );
    
    ASSERT_TRUE( u2 == std::string( "ABCDEF00-0000-0000-0000-000000000000" ) );
    ASSERT_TRUE( u3 == std::string( "ABCDEF00-CDEF-ABCD-00AB-DE00ABCDEF00" ) );
    ASSERT_TRUE( u4 == std::string( "ABCDEFAB-ABCD-ABCD-ABCD-ABCDEFABCDEF" ) );
}

TEST( CFPP_UUID, CTOR_Data )
{
    CF::Data d1( static_cast< CFDataRef >( nullptr ) );
    CF::Data d2( std::string( "ABCDEFG" ) );
    CF::Data d3( std::string( "ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGA" ) );
    CF::Data d4( std::string( "ABCDEFAB-ABCD-ABCD-ABCD-ABCDEFABCDEF" ) );
    CF::UUID u1( d1 );
    CF::UUID u2( d2 );
    CF::UUID u3( d3 );
    CF::UUID u4( d4 );
    
    ASSERT_TRUE( u1.IsValid() );
    ASSERT_TRUE( u2.IsValid() );
    ASSERT_TRUE( u3.IsValid() );
    ASSERT_TRUE( u4.IsValid() );
    
    std::cout << u2 << std::endl;
    std::cout << u3 << std::endl;
    std::cout << u4 << std::endl;
    
    ASSERT_TRUE( u1 == std::string( "00000000-0000-0000-0000-000000000000" ) );
    ASSERT_TRUE( u2 == std::string( "41424344-4546-4700-0000-000000000000" ) );
    ASSERT_TRUE( u3 == std::string( "41424344-4546-4741-4243-444546474142" ) );
    ASSERT_TRUE( u4 == std::string( "41424344-4546-4142-2D41-4243442D4142" ) );
}

TEST( CFPP_UUID, CCTOR )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u4( u3 );
    
    ASSERT_TRUE( u1.IsValid() );
    ASSERT_TRUE( u1.IsValid() );
    ASSERT_EQ( u1.GetString(), u2.GetString() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
}

TEST( CFPP_UUID, MCTOR )
{
    CF::UUID u1;
    CF::UUID u2( std::move( u1 ) );
    
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_FALSE( u1.IsValid() );
}

TEST( CFPP_UUID, OperatorAssignUUID )
{
    CF::UUID u1;
    CF::UUID u2;
    
    ASSERT_NE( u1.GetString(), u2.GetString() );
    
    u1 = u2;
    
    ASSERT_EQ( u1.GetString(), u2.GetString() );
}

TEST( CFPP_UUID, OperatorAssignAutoPointer )
{
    CF::UUID u1( static_cast< CFTypeRef >( nullptr ) );
    CF::UUID u2;
    CF::UUID u3;
    
    ASSERT_FALSE( u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_TRUE(  u3.IsValid() );
    
    u1 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    u2 = CF::AutoPointer( CFDateCreate( nullptr, 0 ) );
    u3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE(  u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
}

TEST( CFPP_UUID, OperatorAssignCFType )
{
    CF::UUID u1;
    CF::UUID u2;
    
    ASSERT_NE( u1, u2 );
    
    u1 = static_cast< CFTypeRef >( u2.GetCFObject() );
    
    ASSERT_TRUE( u1.IsValid() );
    ASSERT_EQ( u1, u2 );
    
    u1 = static_cast< CFTypeRef >( nullptr );
    
    ASSERT_FALSE( u1.IsValid() );
    
    u1 = u2;
    
    ASSERT_TRUE( u1.IsValid() );
    
    u1 = static_cast< CFTypeRef >( CF::Boolean().GetCFObject() );
    
    ASSERT_FALSE( u1.IsValid() );
}

TEST( CFPP_UUID, OperatorAssignCFUUID )
{
    CF::UUID u1;
    CF::UUID u2;
    
    ASSERT_NE( u1, u2 );
    
    u1 = static_cast< CFUUIDRef >( u2.GetCFObject() );
    
    ASSERT_TRUE( u1.IsValid() );
    ASSERT_EQ( u1, u2 );
    
    u1 = static_cast< CFUUIDRef >( nullptr );
    
    ASSERT_FALSE( u1.IsValid() );
    
    u1 = u2;
    
    ASSERT_TRUE( u1.IsValid() );
    
    u1 = static_cast< CFUUIDRef >( CF::Boolean().GetCFObject() );
    
    ASSERT_FALSE( u1.IsValid() );
}

TEST( CFPP_UUID, OperatorAssignNullPointer )
{
    CF::UUID u;
    
    ASSERT_TRUE( u.IsValid() );
    
    u = nullptr;
    
    ASSERT_FALSE( u.IsValid() );
}

TEST( CFPP_UUID, OperatorAssignSTDString )
{
    CF::UUID u1( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u2( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u3( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_FALSE( u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    
    u1 = std::string( "" );
    u2 = std::string( "ABCDEFG" );
    u3 = std::string( "ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGA" );
    u4 = std::string( "ABCDEFAB-ABCD-ABCD-ABCD-ABCDEFABCDEF" );
    
    ASSERT_FALSE( u1.IsValid() );
    ASSERT_TRUE(  u2.IsValid() );
    ASSERT_TRUE(  u3.IsValid() );
    ASSERT_TRUE(  u4.IsValid() );
    
    ASSERT_TRUE( u2 == std::string( "ABCDEF00-0000-0000-0000-000000000000" ) );
    ASSERT_TRUE( u3 == std::string( "ABCDEF00-CDEF-ABCD-00AB-DE00ABCDEF00" ) );
    ASSERT_TRUE( u4 == std::string( "ABCDEFAB-ABCD-ABCD-ABCD-ABCDEFABCDEF" ) );
}

TEST( CFPP_UUID, OperatorAssignData )
{
    CF::Data d1( static_cast< CFDataRef >( nullptr ) );
    CF::Data d2( std::string( "ABCDEFG" ) );
    CF::Data d3( std::string( "ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGA" ) );
    CF::Data d4( std::string( "ABCDEFAB-ABCD-ABCD-ABCD-ABCDEFABCDEF" ) );
    CF::UUID u1( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u2( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u3( static_cast< CFUUIDRef >( nullptr ) );
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_FALSE( u1.IsValid() );
    ASSERT_FALSE( u2.IsValid() );
    ASSERT_FALSE( u3.IsValid() );
    ASSERT_FALSE( u4.IsValid() );
    
    u1 = d1;
    u2 = d2;
    u3 = d3;
    u4 = d4;
    
    ASSERT_TRUE( u1.IsValid() );
    ASSERT_TRUE( u2.IsValid() );
    ASSERT_TRUE( u3.IsValid() );
    ASSERT_TRUE( u4.IsValid() );
    
    ASSERT_TRUE( u1 == std::string( "00000000-0000-0000-0000-000000000000" ) );
    ASSERT_TRUE( u2 == std::string( "41424344-4546-4700-0000-000000000000" ) );
    ASSERT_TRUE( u3 == std::string( "41424344-4546-4741-4243-444546474142" ) );
    ASSERT_TRUE( u4 == std::string( "41424344-4546-4142-2D41-4243442D4142" ) );
}

TEST( CFPP_UUID, OperatorEqualUUID )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_TRUE(  u1 == u2 );
    ASSERT_FALSE( u1 == u3 );
    ASSERT_FALSE( u4 == u1 );
    ASSERT_FALSE( u4 == u4 );
}

TEST( CFPP_UUID, OperatorEqualCFType )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_TRUE(  u1 == static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u4 == static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u4 == static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u4 == static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
}

TEST( CFPP_UUID, OperatorEqualCFUUID )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_TRUE(  u1 == static_cast< CFUUIDRef >( u2.GetCFObject() ) );
    ASSERT_FALSE( u1 == static_cast< CFUUIDRef >( u3.GetCFObject() ) );
    ASSERT_FALSE( u4 == static_cast< CFUUIDRef >( u1.GetCFObject() ) );
    ASSERT_FALSE( u4 == static_cast< CFUUIDRef >( u4.GetCFObject() ) );
    ASSERT_FALSE( u4 == static_cast< CFUUIDRef >( CF::Boolean().GetCFObject() ) );
}

TEST( CFPP_UUID, OperatorEqualSTDString )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_TRUE(  u1 == static_cast< std::string >( u2.GetString() ) );
    ASSERT_FALSE( u1 == static_cast< std::string >( u3.GetString() ) );
    ASSERT_FALSE( u4 == static_cast< std::string >( u1.GetString() ) );
    ASSERT_FALSE( u4 == static_cast< std::string >( u4.GetString() ) );
}

TEST( CFPP_UUID, OperatorEqualData )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_TRUE(  u1 == u2.GetData() );
    ASSERT_FALSE( u1 == u3.GetData() );
    ASSERT_FALSE( u4 == u1.GetData() );
    ASSERT_FALSE( u4 == u4.GetData() );
}

TEST( CFPP_UUID, OperatorNotEqualUUID )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_FALSE( u1 != u2 );
    ASSERT_TRUE(  u1 != u3 );
    ASSERT_TRUE(  u4 != u1 );
    ASSERT_TRUE(  u4 != u4 );
}

TEST( CFPP_UUID, OperatorNotEqualCFType )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_FALSE( u1 != static_cast< CFTypeRef >( u2.GetCFObject() ) );
    ASSERT_TRUE(  u1 != static_cast< CFTypeRef >( u3.GetCFObject() ) );
    ASSERT_TRUE(  u4 != static_cast< CFTypeRef >( u1.GetCFObject() ) );
    ASSERT_TRUE(  u4 != static_cast< CFTypeRef >( u4.GetCFObject() ) );
    ASSERT_TRUE(  u4 != static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
}

TEST( CFPP_UUID, OperatorNotEqualCFUUID )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_FALSE( u1 != static_cast< CFUUIDRef >( u2.GetCFObject() ) );
    ASSERT_TRUE(  u1 != static_cast< CFUUIDRef >( u3.GetCFObject() ) );
    ASSERT_TRUE(  u4 != static_cast< CFUUIDRef >( u1.GetCFObject() ) );
    ASSERT_TRUE(  u4 != static_cast< CFUUIDRef >( u4.GetCFObject() ) );
    ASSERT_TRUE(  u4 != static_cast< CFUUIDRef >( CF::Boolean().GetCFObject() ) );
}

TEST( CFPP_UUID, OperatorNotEqualSTDString )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_FALSE( u1 != static_cast< std::string >( u2.GetString() ) );
    ASSERT_TRUE(  u1 != static_cast< std::string >( u3.GetString() ) );
    ASSERT_TRUE(  u4 != static_cast< std::string >( u1.GetString() ) );
    ASSERT_TRUE(  u4 != static_cast< std::string >( u4.GetString() ) );
}

TEST( CFPP_UUID, OperatorNotEqualData )
{
    CF::UUID u1;
    CF::UUID u2( u1 );
    CF::UUID u3;
    CF::UUID u4( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_FALSE( u1 != u2.GetData() );
    ASSERT_TRUE(  u1 != u3.GetData() );
    ASSERT_TRUE(  u4 != u1.GetData() );
    ASSERT_TRUE(  u4 != u4.GetData() );
}

TEST( CFPP_UUID, CastToSTDString )
{
    CF::UUID    u;
    std::string s( static_cast< std::string >( u ) );
    
    ASSERT_TRUE( s.length() == 36 );
    ASSERT_EQ( u.GetString(), s );
}

TEST( CFPP_UUID, GetTypeID )
{
    CF::UUID u;
    
    ASSERT_EQ( u.GetTypeID(), CFUUIDGetTypeID() );
}

TEST( CFPP_UUID, GetCFObject )
{
    CF::UUID u1;
    CF::UUID u2( static_cast< CFUUIDRef >( nullptr ) );
    
    ASSERT_TRUE( u1.GetCFObject() != nullptr );
    ASSERT_TRUE( u2.GetCFObject() == nullptr );
    ASSERT_EQ( CFGetTypeID( u1.GetCFObject() ), CFUUIDGetTypeID() );
}

TEST( CFPP_UUID, GetString )
{
    CF::UUID u;
    
    ASSERT_EQ( u.GetString().GetLength(), 36 );
    
    u = static_cast< CFUUIDRef >( nullptr );
    
    ASSERT_FALSE( u.IsValid() );
    ASSERT_EQ( u.GetString().GetLength(), 0 );
}

TEST( CFPP_UUID, GetData )
{
    CF::UUID u;
    
    ASSERT_EQ( u.GetData().GetLength(), 36 );
    
    u = static_cast< CFUUIDRef >( nullptr );
    
    ASSERT_FALSE( u.IsValid() );
    ASSERT_EQ( u.GetData().GetLength(), 0 );
}

TEST( CFPP_UUID, GetBytes )
{
    CF::UUID u;
    
    ASSERT_EQ( u.GetBytes().GetLength(), 16 );
    
    u = static_cast< CFUUIDRef >( nullptr );
    
    ASSERT_FALSE( u.IsValid() );
    ASSERT_EQ( u.GetBytes().GetLength(), 0 );
}

TEST( CFPP_UUID, Swap )
{
    CF::UUID    u1;
    CF::UUID    u2;
    std::string s1( u1.GetString() );
    std::string s2( u2.GetString() );
    
    ASSERT_EQ( u1.GetString(), s1 );
    ASSERT_EQ( u2.GetString(), s2 );
    
    swap( u1, u2 );
    
    ASSERT_EQ( u1.GetString(), s2 );
    ASSERT_EQ( u2.GetString(), s1 );
}
