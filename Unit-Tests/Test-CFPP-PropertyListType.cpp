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
 * @file        Test-CFPP-PropertyListType.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::PropertyListType
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

static const char * __plist = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                              "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
                              "<plist version=\"1.0\">\n"
                              "<dict>\n"
                              "	<key>hello</key>\n"
                              "	<string>world</string>\n"
                              "</dict>\n"
                              "</plist>\n";

TEST( CFPP_PropertyListType, FromPropertyList )
{
    CF::Dictionary d;
    
    d = CF::Dictionary::FromPropertyList( "/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Resources/Info.plist" );
    
    ASSERT_TRUE( d.IsValid() );
    ASSERT_GT( d.GetCount(), 0 );
    ASSERT_EQ( CF::String( d[ "CFBundleIdentifier" ] ), "com.apple.CoreFoundation" );
    
    d = CF::Dictionary::FromPropertyList( "" );
    
    ASSERT_FALSE( d.IsValid() );
    
    d = CF::Dictionary::FromPropertyList( "/foo/bar" );
    
    ASSERT_FALSE( d.IsValid() );
}

TEST( CFPP_PropertyListType, FromPropertyListString )
{
    CF::Dictionary d;
    
    d = CF::Dictionary::FromPropertyListString( __plist );
    
    ASSERT_TRUE( d.IsValid() );
    ASSERT_EQ( d.GetCount(), 1 );
    ASSERT_EQ( CF::String( d[ "hello" ] ), "world" );
    
    d = CF::Dictionary::FromPropertyListString( "" );
    
    ASSERT_FALSE( d.IsValid() );
    
    {
        CF::ReadStream stream;
        CF::Data       data;
        
        stream.Open( "/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Resources/Info.plist" );
        
        data = stream.Read();
        
        stream.Close();
        
        ASSERT_TRUE( data.IsValid() );
        ASSERT_TRUE( data.GetLength() > 0 );
        
        d = CF::Dictionary::FromPropertyListString( data );
        
        ASSERT_TRUE( d.IsValid() );
        ASSERT_TRUE( d.GetCount() > 0 );
    }
}

TEST( CFPP_PropertyListType, FromPropertyListData )
{
    CF::Dictionary d;
    
    d = CF::Dictionary::FromPropertyListData( std::string( __plist ) );
    
    ASSERT_TRUE( d.IsValid() );
    ASSERT_EQ( d.GetCount(), 1 );
    ASSERT_EQ( CF::String( d[ "hello" ] ), "world" );
    
    d = CF::Dictionary::FromPropertyListData( std::string( "" ) );
    
    ASSERT_FALSE( d.IsValid() );
    
    {
        CF::ReadStream stream;
        CF::Data       data;
        
        stream.Open( "/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Resources/Info.plist" );
        
        data = stream.Read();
        
        stream.Close();
        
        ASSERT_TRUE( data.IsValid() );
        ASSERT_TRUE( data.GetLength() > 0 );
        
        d = CF::Dictionary::FromPropertyListData( data );
        
        ASSERT_TRUE( d.IsValid() );
        ASSERT_TRUE( d.GetCount() > 0 );
    }
}

TEST( CFPP_PropertyListType, ToPropertyList_STDString_PropertyListFormat )
{
    CF::Dictionary d1;
    CF::Dictionary d2;
    
    d1 << CF::Pair( "hello", "world" );
    
    ASSERT_TRUE( d1.ToPropertyList( "/tmp/com.xs-labs.cfpp.plist", CF::PropertyListFormatBinary ) );
    
    d2 = CF::Dictionary::FromPropertyList( "/tmp/com.xs-labs.cfpp.plist" );
    
    ASSERT_TRUE( d2.IsValid() );
    ASSERT_EQ( d1, d2 );
    
    ASSERT_TRUE( d1.ToPropertyList( "/tmp/com.xs-labs.cfpp.plist", CF::PropertyListFormatXML ) );
    
    d2 = CF::Dictionary::FromPropertyList( "/tmp/com.xs-labs.cfpp.plist" );
    
    ASSERT_TRUE( d2.IsValid() );
    ASSERT_EQ( d1, d2 );
    
    ASSERT_FALSE( d1.ToPropertyList( "/foo/bar", CF::PropertyListFormatBinary ) );
    ASSERT_FALSE( d1.ToPropertyList( "/foo/bar", CF::PropertyListFormatXML ) );
    
    d1 = static_cast< CFDictionaryRef >( nullptr );
    
    ASSERT_FALSE( d1.ToPropertyList( "/tmp/com.xs-labs.cfpp.plist", CF::PropertyListFormatBinary ) );
    ASSERT_FALSE( d1.ToPropertyList( "/tmp/com.xs-labs.cfpp.plist", CF::PropertyListFormatXML ) );
}

TEST( CFPP_PropertyListType, ToPropertyList_PropertyListFormat )
{
    CF::Dictionary d;
    CF::Data       d1;
    CF::Data       d2;
    
    d << CF::Pair( "hello", "world" );
    
    d1 = d.ToPropertyList( CF::PropertyListFormatBinary );
    d2 = d.ToPropertyList( CF::PropertyListFormatXML );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_GT( d1.GetLength(), 0 );
    ASSERT_GT( d2.GetLength(), 0 );
    
    ASSERT_NE( d1, d2 );
    
    d  = static_cast< CFDictionaryRef >( nullptr );
    d1 = d.ToPropertyList( CF::PropertyListFormatBinary );
    d2 = d.ToPropertyList( CF::PropertyListFormatXML );
    
    ASSERT_FALSE( d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
}
