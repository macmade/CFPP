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
 * @file        Test-CFPP-Type.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Type
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Type, OperatorEqual )
{
    CF::Number o1 = 1;
    CF::Number o2 = 1;
    CF::Type & t1 = o1;
    CF::Type & t2 = o2;
    
    ASSERT_TRUE( t1 == t2 );
    
    o1 = static_cast< CFNumberRef >( nullptr );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_FALSE( t1 == t2 );
    
    o1 = 1;
    o2 = static_cast< CFNumberRef >( nullptr );
    
    ASSERT_TRUE(  t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_FALSE( t1 == t2 );
    
    o1 = static_cast< CFNumberRef >( nullptr );
    o2 = static_cast< CFNumberRef >( nullptr );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_FALSE( t1 == t2 );
}

TEST( CFPP_Type, OperatorNotEqual )
{
    CF::Number o1 = 0;
    CF::Number o2 = 1;
    CF::Type & t1 = o1;
    CF::Type & t2 = o2;
        
    ASSERT_TRUE( t1 != t2 );
    
    o1 = static_cast< CFNumberRef >( nullptr );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_TRUE(  t1 != t2 );
    
    o1 = 1;
    o2 = static_cast< CFNumberRef >( nullptr );
    
    ASSERT_TRUE(  t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_TRUE(  t1 != t2 );
    
    o1 = static_cast< CFNumberRef >( nullptr );
    o2 = static_cast< CFNumberRef >( nullptr );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_TRUE(  t1 != t2 );
}

TEST( CFPP_Type, CastToCFTypeRef )
{
    CF::Number o;
    CF::Type & t = o;
    
    ASSERT_TRUE( static_cast< CFTypeRef >( t ) != nullptr );
}

TEST( CFPP_Type, CastToCFBooleanRef )
{
    CF::Boolean o1;
    CF::Number  o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFBooleanRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFBooleanRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFNumberRef )
{
    CF::Number  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFNumberRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFNumberRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFDateRef )
{
    CF::Date    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFDateRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFDateRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFStringRef )
{
    CF::String  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFStringRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFStringRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFMutableStringRef )
{
    CF::String  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableStringRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFMutableStringRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFURLRef )
{
    CF::URL     o1( std::string( "http://www.xs-labs.com/" ) );
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFURLRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFURLRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFDataRef )
{
    CF::Data    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFDataRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFDataRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFMutableDataRef )
{
    CF::Data    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableDataRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFMutableDataRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFArrayRef )
{
    CF::Array   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFArrayRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFArrayRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFMutableArrayRef )
{
    CF::Array   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableArrayRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFMutableArrayRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFDictionaryRef )
{
    CF::Dictionary o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFDictionaryRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFDictionaryRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFMutableDictionaryRef )
{
    CF::Dictionary o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableDictionaryRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFMutableDictionaryRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFUUIDRef )
{
    CF::UUID    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFUUIDRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFUUIDRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFErrorRef )
{
    CF::Error   o1( std::string( "Unknown error" ), 0 );
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFErrorRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFErrorRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFReadStreamRef )
{
    CF::ReadStream o1( std::string( "/tmp/cf++.txt" ) );
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFReadStreamRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFReadStreamRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, CastToCFWriteStreamRef )
{
    CF::WriteStream o1( std::string( "/tmp/cf++.txt" ) );
    CF::Boolean     o2;
    CF::Type      & t1 = o1;
    CF::Type      & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFWriteStreamRef >( t1 ) != nullptr );
    ASSERT_TRUE( static_cast< CFWriteStreamRef >( t2 ) == nullptr );
}

TEST( CFPP_Type, Description )
{
    CF::Array      o;
    CF::Type & t = o;
    
    ASSERT_TRUE( t.Description().length() > 0 );
    ASSERT_TRUE( t.Description().find( "<CFArray 0x" ) == 0 );
}

TEST( CFPP_Type, Hash )
{
    CF::Number o;
    CF::Type & t = o;
    
    ASSERT_TRUE( t.Hash() == CFHash( t.GetCFObject() ) );
    
    o = static_cast< CFNumberRef >( nullptr );
    
    ASSERT_FALSE( t.IsValid() );
    ASSERT_EQ( t.Hash(), static_cast< CFHashCode >( 0 ) );
}

TEST( CFPP_Type, Show )
{
    ASSERT_NO_THROW( CF::Array().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Array().Show() );
    
    ASSERT_NO_THROW( CF::Boolean().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Boolean().Show() );
    
    ASSERT_NO_THROW( CF::Data().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Data().Show() );
    
    ASSERT_NO_THROW( CF::Date().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Date().Show() );
    
    ASSERT_NO_THROW( CF::Dictionary().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Dictionary().Show() );
    
    ASSERT_NO_THROW( CF::Error().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Error().Show() );
    
    ASSERT_NO_THROW( CF::Number().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Number().Show() );
    
    ASSERT_NO_THROW( CF::ReadStream().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::ReadStream().Show() );
    
    ASSERT_NO_THROW( CF::String().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::String().Show() );
    
    ASSERT_NO_THROW( CF::URL().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::URL().Show() );
    
    ASSERT_NO_THROW( CF::UUID().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::UUID().Show() );
    
    ASSERT_NO_THROW( CF::WriteStream().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::WriteStream().Show() );
}

TEST( CFPP_Type, GetRetainCount )
{
    CF::Array  o;
    CF::Type & t = o;
    
    ASSERT_TRUE( t.GetRetainCount() == CFGetRetainCount( t.GetCFObject() ) );
    ASSERT_TRUE( t.GetRetainCount() == 1 );
    
    o = static_cast< CFArrayRef >( nullptr );
    
    ASSERT_FALSE( t.IsValid() );
    ASSERT_TRUE(  t.GetRetainCount() == 0 );
}

TEST( CFPP_Type, IsValid )
{
    CF::Data   o1;
    CF::Data   o2( static_cast< CFDataRef >( nullptr ) );
    CF::Type & t1 = o1;
    CF::Type & t2 = o2;
    
    ASSERT_TRUE(  t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
}

TEST( CFPP_Type, IsValidPropertyList )
{
    CF::Data        o1;
    CF::UUID        o2;
    CF::Dictionary  o3;
    CF::Array       o4;
    
    ASSERT_TRUE(  o1.IsValidPropertyList( CF::PropertyListFormatBinary ) );
    ASSERT_FALSE( o2.IsValidPropertyList( CF::PropertyListFormatBinary ) );
    ASSERT_TRUE(  o3.IsValidPropertyList( CF::PropertyListFormatBinary ) );
    ASSERT_TRUE(  o4.IsValidPropertyList( CF::PropertyListFormatBinary ) );
    
    o3.SetValue( CF::String( "Foo" ), CF::String( "Bar" ) );
    o4.AppendValue( CF::Number() );
    
    ASSERT_TRUE(  o3.IsValidPropertyList( CF::PropertyListFormatBinary ) );
    ASSERT_TRUE(  o4.IsValidPropertyList( CF::PropertyListFormatBinary ) );
    
    o3.SetValue( CF::String( "Foo" ), CF::UUID() );
    o4.AppendValue( CF::UUID() );
    
    ASSERT_FALSE(  o3.IsValidPropertyList( CF::PropertyListFormatBinary ) );
    ASSERT_FALSE(  o4.IsValidPropertyList( CF::PropertyListFormatBinary ) );
}

TEST( CFPP_Type, IsBoolean )
{
    CF::Boolean o1;
    CF::Number  o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsBoolean() );
    ASSERT_FALSE( t2.IsBoolean() );
}

TEST( CFPP_Type, IsNumber )
{
    CF::Number  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsNumber() );
    ASSERT_FALSE( t2.IsNumber() );
}

TEST( CFPP_Type, IsDate )
{
    CF::Date    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsDate() );
    ASSERT_FALSE( t2.IsDate() );
}

TEST( CFPP_Type, IsString )
{
    CF::String  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsString() );
    ASSERT_FALSE( t2.IsString() );
}

TEST( CFPP_Type, IsURL )
{
    CF::URL     o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsURL() );
    ASSERT_FALSE( t2.IsURL() );
}

TEST( CFPP_Type, IsData )
{
    CF::Data    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsData() );
    ASSERT_FALSE( t2.IsData() );
}

TEST( CFPP_Type, IsArray )
{
    CF::Array   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsArray() );
    ASSERT_FALSE( t2.IsArray() );
}

TEST( CFPP_Type, IsDictionary )
{
    CF::Dictionary o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE(  t1.IsDictionary() );
    ASSERT_FALSE( t2.IsDictionary() );
}

TEST( CFPP_Type, IsUUID )
{
    CF::UUID    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsUUID() );
    ASSERT_FALSE( t2.IsUUID() );
}

TEST( CFPP_Type, IsError )
{
    CF::Error   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsError() );
    ASSERT_FALSE( t2.IsError() );
}

TEST( CFPP_Type, IsReadStream )
{
    CF::ReadStream o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE(  t1.IsReadStream() );
    ASSERT_FALSE( t2.IsReadStream() );
}

TEST( CFPP_Type, IsWriteStream )
{
    CF::WriteStream o1;
    CF::Boolean     o2;
    CF::Type      & t1 = o1;
    CF::Type      & t2 = o2;
    
    ASSERT_TRUE(  t1.IsWriteStream() );
    ASSERT_FALSE( t2.IsWriteStream() );
}

TEST( CFPP_Type, STDOstreamFriend )
{
    CF::Array         o;
    std::stringstream ss;
    
    ss << o;
    
    ASSERT_TRUE( ss.str().length() > 0 );
    ASSERT_TRUE( ss.str().find( "<CFArray 0x" ) == 0 );
}
