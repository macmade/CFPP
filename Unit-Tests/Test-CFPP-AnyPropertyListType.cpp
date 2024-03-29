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
 * @file        Test-CFPP-AnyPropertyListType.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::AnyPropertyListType
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

static const char * __plist = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                              "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
                              "<plist version=\"1.0\">\n"
                              "<dict>\n"
                              "    <key>hello</key>\n"
                              "    <string>world</string>\n"
                              "</dict>\n"
                              "</plist>\n";

TEST( CFPP_AnyPropertyListType, FromPropertyList )
{
    CF::AnyPropertyListType p( CF::PropertyListFormatBinary );
    
    p = CF::AnyPropertyListType::FromPropertyList( "/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Resources/Info.plist" );
    
    ASSERT_TRUE( p.IsValid() );
    ASSERT_TRUE( p.IsValidPropertyList() );
    ASSERT_TRUE( p.GetTypeID() == CFDictionaryGetTypeID() );
    
    p = CF::Dictionary::FromPropertyList( "" );
    
    ASSERT_FALSE( p.IsValid() );
    ASSERT_FALSE( p.IsValidPropertyList() );
    ASSERT_TRUE(  p.GetTypeID() == 0 );
    
    p = CF::Dictionary::FromPropertyList( "/foo/bar" );
    
    ASSERT_FALSE( p.IsValid() );
    ASSERT_FALSE( p.IsValidPropertyList() );
    ASSERT_TRUE(  p.GetTypeID() == 0 );
}

TEST( CFPP_AnyPropertyListType, FromPropertyListString )
{
    CF::AnyPropertyListType p( CF::PropertyListFormatBinary );
    
    p = CF::AnyPropertyListType::FromPropertyListString( __plist );
    
    ASSERT_TRUE( p.IsValid() );
    ASSERT_TRUE( p.IsValidPropertyList() );
    ASSERT_TRUE( p.GetTypeID() == CFDictionaryGetTypeID() );
    
    p = CF::AnyPropertyListType::FromPropertyListString( "" );
    
    ASSERT_FALSE( p.IsValid() );
    ASSERT_FALSE( p.IsValidPropertyList() );
    ASSERT_TRUE(  p.GetTypeID() == 0 );
    
    {
        CF::ReadStream stream;
        CF::Data       data;
        
        stream.Open( "/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Resources/Info.plist" );
        
        data = stream.Read();
        
        stream.Close();
        
        ASSERT_TRUE( data.IsValid() );
        ASSERT_TRUE( data.GetLength() > 0 );
        
        p = CF::AnyPropertyListType::FromPropertyListString( data );
        
        ASSERT_TRUE( p.IsValid() );
        ASSERT_TRUE( p.IsValidPropertyList() );
        ASSERT_TRUE( p.GetTypeID() == CFDictionaryGetTypeID() );
    }
}

TEST( CFPP_AnyPropertyListType, FromPropertyListData )
{
    CF::AnyPropertyListType p( CF::PropertyListFormatBinary );
    
    p = CF::AnyPropertyListType::FromPropertyListData( std::string( __plist ) );
    
    ASSERT_TRUE( p.IsValid() );
    ASSERT_TRUE( p.IsValidPropertyList() );
    ASSERT_TRUE( p.GetTypeID() == CFDictionaryGetTypeID() );
    
    p = CF::AnyPropertyListType::FromPropertyListData( std::string( "" ) );
    
    ASSERT_FALSE( p.IsValid() );
    ASSERT_FALSE( p.IsValidPropertyList() );
    ASSERT_TRUE(  p.GetTypeID() == 0 );
    
    {
        CF::ReadStream stream;
        CF::Data       data;
        
        stream.Open( "/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Resources/Info.plist" );
        
        data = stream.Read();
        
        stream.Close();
        
        ASSERT_TRUE( data.IsValid() );
        ASSERT_TRUE( data.GetLength() > 0 );
        
        p = CF::AnyPropertyListType::FromPropertyListData( data );
        
        ASSERT_TRUE( p.IsValid() );
        ASSERT_TRUE( p.IsValidPropertyList() );
        ASSERT_TRUE( p.GetTypeID() == CFDictionaryGetTypeID() );
    }
}

TEST( CFPP_AnyPropertyListType, CTOR )
{
    CF::AnyPropertyListType p( CF::PropertyListFormatBinary );
    
    ASSERT_FALSE( p.IsValid() );
    ASSERT_FALSE( p.IsValidPropertyList() );
}

TEST( CFPP_AnyPropertyListType, CCTOR )
{
    CF::AnyPropertyListType p1( CF::PropertyListFormatXML );
    CF::AnyPropertyListType p2( CF::Dictionary().GetCFObject(), CF::PropertyListFormatBinary );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p1.IsValidPropertyList() );
    ASSERT_TRUE(  p1.GetTypeID() == 0 );
    ASSERT_TRUE(  p2.IsValid() );
    ASSERT_TRUE(  p2.IsValidPropertyList() );
    ASSERT_TRUE(  p2.GetTypeID() == CFDictionaryGetTypeID() );
    
    {
        CF::AnyPropertyListType p3( p1 );
        CF::AnyPropertyListType p4( p2 );
        
        ASSERT_FALSE( p3.IsValid() );
        ASSERT_FALSE( p3.IsValidPropertyList() );
        ASSERT_TRUE(  p3.GetTypeID() == 0 );
        ASSERT_TRUE(  p4.IsValid() );
        ASSERT_TRUE(  p4.IsValidPropertyList() );
        ASSERT_TRUE(  p4.GetTypeID() == CFDictionaryGetTypeID() );
        
        ASSERT_EQ( p1.GetFormat(), p3.GetFormat() );
        ASSERT_EQ( p2.GetFormat(), p4.GetFormat() );
    }
}

TEST( CFPP_AnyPropertyListType, CTOR_AutoPointer )
{
    CF::String              s;
    CF::UUID                u;
    CF::AutoPointer         a1;
    CF::AutoPointer         a2( CFRetain( s.GetCFObject() ) );
    CF::AutoPointer         a3( CFRetain( u.GetCFObject() ) );
    CF::AnyPropertyListType p1( a1, CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( a2, CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p3( a3, CF::PropertyListFormatBinary );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p1.IsValidPropertyList() );
    ASSERT_TRUE(  p1.GetTypeID() == 0 );
    
    ASSERT_TRUE( p2.IsValid() );
    ASSERT_TRUE( p2.IsValidPropertyList() );
    ASSERT_TRUE( p2.GetTypeID() == CFStringGetTypeID() );
    
    ASSERT_FALSE( p3.IsValid() );
    ASSERT_FALSE( p3.IsValidPropertyList() );
    ASSERT_TRUE(  p3.GetTypeID() == 0 );
}

TEST( CFPP_AnyPropertyListType, CTOR_CFTypeRef )
{
    CF::String              s;
    CF::UUID                u;
    CF::AnyPropertyListType p1( static_cast< CFTypeRef >( nullptr ), CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( static_cast< CFTypeRef >( s ),       CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p3( static_cast< CFTypeRef >( u ),       CF::PropertyListFormatBinary );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p1.IsValidPropertyList() );
    ASSERT_TRUE(  p1.GetTypeID() == 0 );
    
    ASSERT_TRUE( p2.IsValid() );
    ASSERT_TRUE( p2.IsValidPropertyList() );
    ASSERT_TRUE( p2.GetTypeID() == CFStringGetTypeID() );
    
    ASSERT_FALSE( p3.IsValid() );
    ASSERT_FALSE( p3.IsValidPropertyList() );
    ASSERT_TRUE(  p3.GetTypeID() == 0 );
}

TEST( CFPP_AnyPropertyListType, CTOR_NullPointer )
{
    CF::AnyPropertyListType p( nullptr, CF::PropertyListFormatBinary );
    
    ASSERT_FALSE( p.IsValid() );
    ASSERT_FALSE( p.IsValidPropertyList() );
}

TEST( CFPP_AnyPropertyListType, MCTOR )
{
    CF::AnyPropertyListType p1( CF::Dictionary().GetCFObject(),      CF::PropertyListFormatXML );
    CF::AnyPropertyListType p2( static_cast< CFTypeRef >( nullptr ), CF::PropertyListFormatBinary );
    
    ASSERT_TRUE( p1.IsValid() );
    ASSERT_TRUE( p1.IsValidPropertyList() );
    ASSERT_TRUE( p1.GetTypeID() == CFDictionaryGetTypeID() );
    
    ASSERT_FALSE( p2.IsValid() );
    ASSERT_FALSE( p2.IsValidPropertyList() );
    ASSERT_TRUE(  p2.GetTypeID() == 0 );
    
    {
        CF::AnyPropertyListType p3( std::move( p1 ) );
        CF::AnyPropertyListType p4( std::move( p2 ) );
        
        ASSERT_FALSE( p1.IsValid() );
        ASSERT_FALSE( p1.IsValidPropertyList() );
        ASSERT_TRUE(  p1.GetTypeID() == 0 );
        
        ASSERT_FALSE( p2.IsValid() );
        ASSERT_FALSE( p2.IsValidPropertyList() );
        ASSERT_TRUE(  p2.GetTypeID() == 0 );
        
        ASSERT_TRUE( p3.IsValid() );
        ASSERT_TRUE( p3.IsValidPropertyList() );
        ASSERT_TRUE( p3.GetTypeID() == CFDictionaryGetTypeID() );
        
        ASSERT_FALSE( p4.IsValid() );
        ASSERT_FALSE( p4.IsValidPropertyList() );
        ASSERT_TRUE(  p4.GetTypeID() == 0 );
        
        ASSERT_EQ( p3.GetFormat(), CF::PropertyListFormatXML );
        ASSERT_EQ( p4.GetFormat(), CF::PropertyListFormatBinary );
    }
}

TEST( CFPP_AnyPropertyListType, OperatorAssign )
{
    CF::AnyPropertyListType p1( CF::PropertyListFormatXML );
    CF::AnyPropertyListType p2( CF::Dictionary().GetCFObject(), CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p3( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p4( CF::PropertyListFormatXML );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p1.IsValidPropertyList() );
    ASSERT_TRUE(  p1.GetTypeID() == 0 );
    ASSERT_TRUE(  p2.IsValid() );
    ASSERT_TRUE(  p2.IsValidPropertyList() );
    ASSERT_TRUE(  p2.GetTypeID() == CFDictionaryGetTypeID() );
    
    p3 = p1;
    p4 = p2;
    
    ASSERT_FALSE( p3.IsValid() );
    ASSERT_FALSE( p3.IsValidPropertyList() );
    ASSERT_TRUE(  p3.GetTypeID() == 0 );
    ASSERT_TRUE(  p4.IsValid() );
    ASSERT_TRUE(  p4.IsValidPropertyList() );
    ASSERT_TRUE(  p4.GetTypeID() == CFDictionaryGetTypeID() );
    
    ASSERT_EQ( p3.GetFormat(), CF::PropertyListFormatBinary );
    ASSERT_EQ( p4.GetFormat(), CF::PropertyListFormatXML );
}

TEST( CFPP_AnyPropertyListType, OperatorAssignAutoPointer )
{
    CF::String              s;
    CF::UUID                u;
    CF::AutoPointer         a1;
    CF::AutoPointer         a2( CFRetain( s.GetCFObject() ) );
    CF::AutoPointer         a3( CFRetain( u.GetCFObject() ) );
    CF::AnyPropertyListType p1( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p3( CF::PropertyListFormatBinary );
    
    p1 = a1;
    p2 = a2;
    p3 = a3;
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p1.IsValidPropertyList() );
    ASSERT_TRUE(  p1.GetTypeID() == 0 );
    
    ASSERT_TRUE( p2.IsValid() );
    ASSERT_TRUE( p2.IsValidPropertyList() );
    ASSERT_TRUE( p2.GetTypeID() == CFStringGetTypeID() );
    
    ASSERT_FALSE( p3.IsValid() );
    ASSERT_FALSE( p3.IsValidPropertyList() );
    ASSERT_TRUE(  p3.GetTypeID() == 0 );
}

TEST( CFPP_AnyPropertyListType, OperatorAssignCFTypeRef )
{
    CF::String              s;
    CF::UUID                u;
    CF::AnyPropertyListType p1( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p3( CF::PropertyListFormatBinary );
    
    p1 = static_cast< CFTypeRef >( nullptr );
    p2 = static_cast< CFTypeRef >( s );
    p3 = static_cast< CFTypeRef >( u );
    
    ASSERT_FALSE( p1.IsValid() );
    ASSERT_FALSE( p1.IsValidPropertyList() );
    ASSERT_TRUE(  p1.GetTypeID() == 0 );
    
    ASSERT_TRUE( p2.IsValid() );
    ASSERT_TRUE( p2.IsValidPropertyList() );
    ASSERT_TRUE( p2.GetTypeID() == CFStringGetTypeID() );
    
    ASSERT_FALSE( p3.IsValid() );
    ASSERT_FALSE( p3.IsValidPropertyList() );
    ASSERT_TRUE(  p3.GetTypeID() == 0 );
}

TEST( CFPP_AnyPropertyListType, OperatorAssignNullPointer )
{
    CF::AnyPropertyListType p( CF::String(), CF::PropertyListFormatBinary );
    
    ASSERT_TRUE( p.IsValidPropertyList() );
    
    p = nullptr;
    
    ASSERT_FALSE( p.IsValidPropertyList() );
}

TEST( CFPP_AnyPropertyListType, IsValidPropertyList )
{
    CF::Dictionary          d;
    CF::AnyPropertyListType p1( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( d, CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p3( CF::UUID().GetCFObject(), CF::PropertyListFormatBinary );
    
    ASSERT_FALSE( p1.IsValidPropertyList() );
    ASSERT_TRUE(  p2.IsValidPropertyList() );
    ASSERT_FALSE( p3.IsValidPropertyList() );
    
    d.SetValue( CF::String( "Foo" ), CF::String( "Bar" ) );
    ASSERT_TRUE( p2.IsValidPropertyList() );
    
    d.SetValue( CF::String( "Foo" ), CF::UUID() );
    ASSERT_FALSE( p2.IsValidPropertyList() );
}

TEST( CFPP_AnyPropertyListType, GetTypeID )
{
    CF::AnyPropertyListType p1( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( CF::Dictionary().GetCFObject(), CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p3( CF::Array().GetCFObject(),      CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p4( CF::UUID().GetCFObject(),       CF::PropertyListFormatBinary );
    
    ASSERT_TRUE( p1.GetTypeID() == 0 );
    ASSERT_TRUE( p2.GetTypeID() == CFDictionaryGetTypeID() );
    ASSERT_TRUE( p3.GetTypeID() == CFArrayGetTypeID() );
    ASSERT_TRUE( p4.GetTypeID() == 0 );
}

TEST( CFPP_AnyPropertyListType, GetCFObject )
{
    CF::Dictionary          d;
    CF::AnyPropertyListType p1( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( d, CF::PropertyListFormatBinary );
    
    ASSERT_TRUE(  p1.GetCFObject() == nullptr );
    ASSERT_FALSE( p2.GetCFObject() == nullptr );
    
    d.SetValue( CF::String( "Foo" ), CF::UUID() );
    
    {
        CF::AnyPropertyListType p3( d, CF::PropertyListFormatBinary );
        
        ASSERT_TRUE( p3.GetCFObject() == nullptr );
    }
}

TEST( CFPP_AnyPropertyListType, GetFormat )
{
    CF::AnyPropertyListType p1( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( CF::PropertyListFormatXML );
    
    ASSERT_EQ( p1.GetFormat(), CF::PropertyListFormatBinary );
    ASSERT_EQ( p2.GetFormat(), CF::PropertyListFormatXML );
}

TEST( CFPP_AnyPropertyListType, Swap )
{
    CF::AnyPropertyListType p1( CF::PropertyListFormatBinary );
    CF::AnyPropertyListType p2( CF::Dictionary().GetCFObject(), CF::PropertyListFormatBinary );
    
    ASSERT_TRUE(  p1.GetCFObject() == nullptr );
    ASSERT_FALSE( p2.GetCFObject() == nullptr );
    
    swap( p1, p2 );
    
    ASSERT_FALSE( p1.GetCFObject() == nullptr );
    ASSERT_TRUE(  p2.GetCFObject() == nullptr );
}
