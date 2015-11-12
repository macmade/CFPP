CoreFoundation++
================

[![Build Status](https://img.shields.io/travis/macmade/CFPP.svg?branch=master&style=flat)](https://travis-ci.org/macmade/CFPP)
[![Coverage Status](https://img.shields.io/coveralls/macmade/CFPP.svg?branch=master&style=flat)](https://coveralls.io/r/macmade/CFPP?branch=master)
[![Issues](http://img.shields.io/github/issues/macmade/CFPP.svg?style=flat)](https://github.com/macmade/CFPP/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)
![License](https://img.shields.io/badge/license-boost-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)

### C++ wrapper for CoreFoundation base classes

Table of Contents
-----------------

  1. [About CoreFoundation](#1)
  2. [About CoreFoundation++](#2)
  3. [Availability / Platforms](#3)
  4. [Available / Wrapped classes](#4)
  5. [Example](#5)
  6. [Documentation](#6)
  7. [To-Do](#7)
  8. [License](#8)
  9. [Repository Infos](#9)

<a name="1"></a>
About CoreFoundation
--------------------

Core Foundation (CF) is a C API available in Mac OS X & iOS:

>> Core Foundation is a framework that provides fundamental software services
>> useful to application services, application environments, and to applications
>> themselves. Core Foundation also provides abstractions for common data types,
>> facilitates internationalization with Unicode string storage, and offers
>> a suite of utilities such as plug-in support, XML property lists, URL
>> resource access, and preferences.

*Source: Core Foundation Framework Reference*

To learn more about CoreFoundation, please read the «[Core Foundation Design Concepts][1]» guide.

[1]: https://developer.apple.com/library/mac/documentation/corefoundation/Conceptual/CFDesignConcepts/CFDesignConcepts.html#//apple_ref/doc/uid/10000122i

<a name="2"></a>
About CoreFoundation++
----------------------

CoreFoundation++ (CFPP) is a C++ wrapper for Apple's CoreFoundation API.

CoreFoundation is a powerful C API which allows object-oriented style coding and reference counting memory management in C and provides a lot of useful classes.  
CoreFoundation is intensively used in Apple's low-level frameworks, and is also used as a base for some classes of the Foundation (Objective-C) framework.

That being said, programming with CoreFoundation can sometimes be a real pain.  
Even the simplest things takes several lines of code, which leads to obvious maintainability issues.  
This is especially true when mixing CoreFoundation with C++, because you'll need to cast almost everything.

CoreFoundation++ uses the good parts of the C++ language to wrap the most used CoreFoundation classes, and to makes them easy to use, for instance by using operator overloading.

<a name="3"></a>
Availability / Platforms
------------------------

CoreFoundation++ is available for **MacOS X, iOS and Windows** (Windows builds assume the CoreFoundation DLLs are available), and can be compiled for **32 bits or 64 bits** systems.
  
A complete Xcode project is available, providing the following targets:

    - A Mac OS X static library
    - A Mac OS X dynamic library
    - A Mac OS X framework
    - An iOS static library

On Windows, a VisualStudio solution is provided with the following configurations:

    - DLL - VC120_XP
    - DLL - VC140_XP
    - Static library - VC120_XP
    - Static library - VC140_XP

<a name="4"></a>
Available / Wrapped classes
---------------------------

    - CFType              => CF::Type (abstract)
    - CFBoolean           => CF::Boolean
    - CFNumber            => CF::Number
    - CFString            => CF::String
    - CFDate              => CF::Date
    - CFData              => CF::Data
    - CFMutableData       => CF::Data
    - CFURL               => CF::URL
    - CFArray             => CF::Array
    - CFMutableArray      => CF::Array
    - CFDictionary        => CF::Dictionary
    - CFMutableDictionary => CF::Dictionary
    - CFUUIDRef           => CF::UUID
    - CFErrorRef          => CF::Error
    - CFReadStream        => CF::ReadStream
    - CFWriteStream       => CF::WriteStream

<a name="5"></a>
Example
-------

Let's say you want to create a CFDictionary containing two keys, both CFString objects, the second one created from an external char pointer.  
The value for the first key is a CFData object, created from an external data buffer, while the value for the second key is a CFArray object containing two values, a CFNumber object and a CFURL object, created from an external char pointer.

So let's assume the following:

    extern const char * externalKey;
    extern const char * externalByteBuffer;
    extern size_t       externalByteBufferLength;
    extern const char * externalURL;

### Example with CoreFoundation++:

People used to the CoreFoundation API knows that creating dictionaries and arrays can be extremely painful.  
But with CoreFoundation++, it's extremely easy:

    {
        CF::Number number = 42;
        CF::URL    url    = externalURL;
        CF::Array  array;
        
        /* Adds number and URL to the array */
        array << number << url;
        
        CF::Data data
        (
            ( CF::Data::Byte * )externalByteBuffer,
            ( CFIndex )externalByteBufferLength
        );
        
        CF::Dictionary dictionary;
        
        /* Adds the two key/value pairs in the dictionary */
        dictionary << CF::Pair( "key-1",     data );
        dictionary << CF::Pair( externalKey, data );
        
        /* Prints the dictionary */
        std::cout << dictionary << std::endl;
        
        /* Nothing more, memory is automatically managed... */
    }

### Example with CoreFoundation:

For comparison, with the CoreFoundation C API, you will have write the following code:

    {
        /* First of all, we need a C array to store our dictionary keys */
        CFStringRef keys[ 2 ];
        
        /*
         * Let's create the dictionary keys. First key is straightforward because
         * of the CFSTR macro, while the second one is less...
         */
        keys[ 0 ] = CFSTR( "key-1" );
        keys[ 1 ] = CFStringCreateWithCString
        (
            ( CFAllocatorRef )NULL,
            externalKey,
            kCFStringEncodingUTF8
        );
        
        /* Let's create the data object from the external byte buffer */
        CFDataRef data = CFDataCreate
        (
            ( CFAllocatorRef )NULL,
            ( const UInt8 * )externalByteBuffer,
            ( CFIndex )externalByteBufferLength
        );
        
        /*
         * Now, let's create some number object. Note that we need a temporary
         * variable, as we need to pass an address of a primitive type...
         */
        int tempInt        = 42;
        CFNumberRef number = CFNumberCreate
        (
            ( CFAllocatorRef )NULL,
            kCFNumberSInt32Type,
            &tempInt
        );
        
        /*
         * Now, create an URL object. Note that we need to create a temporary
         * CFString object
         */
        CFStringRef tempStringURL = CFStringCreateWithCString
        (
            ( CFAllocatorRef )NULL,
            externalURL,
            kCFStringEncodingUTF8
        );
        CFURLRef url = CFURLCreateWithString
        (
            ( CFAllocatorRef )NULL,
            tempStringURL,
            NULL
        );
        
        /* Before creating the array, we need a C array to store the values */
        CFTypeRef arrayValues[ 2 ];
        
        arrayValues[ 0 ] = number;
        arrayValues[ 1 ] = url;
        
        /* Now we can create the array... */
        CFArrayRef array = CFArrayCreate
        (
            ( CFAllocatorRef )NULL,
            ( const void ** )arrayValues,
            2,
            &kCFTypeArrayCallBacks
        );
        
        /* Now, of course, we need a C array to store the dictionary values */
        CFTypeRef values[ 2 ];
        
        values[ 0 ] = data;
        values[ 1 ] = array;
        
        /* Finally, we can create our dictionary... */
        CFDictionaryRef dictionary = CFDictionaryCreate
        (
            ( CFAllocatorRef )NULL,
            ( const void ** )keys,
            ( const void ** )values,
            2,
            &kCFTypeDictionaryKeyCallBacks,
            &kCFTypeDictionaryValueCallBacks
        );
        
        /* And of course, as we allocated objects, we need to release them... */
        CFRelease( keys[ 1 ] );
        CFRelease( data );
        CFRelease( number );
        CFRelease( tempStringURL );
        CFRelease( url );
        CFRelease( array );
        
        /* That's it, prints the dictionary and release it */
        CFShow( dictionary );
        CFRelease( dictionary );
    }

<a name="6"></a>
Documentation
-------------

### Memory management

CoreFoundation uses a reference counting memory management scheme.  
All allocated, copied or retained objects must be explicitly released, when the ownership is no longer needed.

It's the same as in Objective-C (with MRC), with the difference that there's no autorelease mechanism.

CoreFoundation++ manages the memory for you, meaning you no longer have to call `CFRelease` explicitly.  
All CF++ wrappers act as a shared pointer (`std::shared_ptr`).

They will automatically retain ownership of a CoreFoundation object, and several CF++ wrappers may own the same object.  
The CoreFoundation object is destroyed and its memory deallocated when either of the following happens:

  * The last remaining CF++ wrapper owning the object is destroyed
  * The last remaining CF++ wrapper owning the object is assigned another CoreFoundation object via operator `=`.

For instance:

    {
        int x                = 42
        CFNumberRef cfNumber = CFNumberCreate
        (
            ( CFAllocatorRef )NULL,
            kCFNumberSInt32Type,
            &x
        );
        
        CF::Number num1 = cfNumber;
        
        /*
         * CF::Number will retain the CFNumber object, so the one
         * we allocated explicitly can be released safely
         */
        CFRelease( cfNumber );
        
        {
            CF::Number num2
            
            /* num1 and num2 owns the same CoreFoundation object */
            num2 = num1:
        }
        
        /*
         * End of scope - num2 is destroyed and will release
         * the CFNumber object, which is still retained by num1
         */
    }
        
    /*
     * End of scope - num1 is destroyed and will release
     * the CFNumber object, which will be deallocated.
     */

### CF::Type

`CF::Type` is the base abstract class for all CF++ wrappers.

**Equality:**

Every CF++ wrapper can be compared using the `==` operator.  
It will evaluate to `false` is the two operands are not of the same type. Otherwise, it will internally use `CFCompare` to test for equality:

    CF::Number  x;
    CF::Boolean y;
    
    if( x == y ) { /* ... */ }
    
**Casting:**

CF++ wrappers can be used transparently as CoreFoundation objects, thanks to the C++ cast operator.  
It means you can use a CF++ wrapper object as argument to a CoreFoundation function:

    CF::String s = "hello, world";
    
    CFShow( s );
    
Besides, all CF++ wrappers can be created with CoreFoundation objects:

    CFStringRef cfS = CFSTR( "hello, world" );
    CF::String  s( cfS );
    /* Or also: */
    CF::String s = cfS;

**Debug output:**

CF++ wrappers can be used with C++ `ostream` objects (like `std::cout`).  
It will print the same output as a call to `CFShow`:

    CF::Number x;
    
    /* Both will produce the same output */
    CFShow( x );
    std::cout << x << std::endl;

### CF::Boolean

`CF::Boolean` is a wrapper for `CFBooleanRef`.

**Creation:**

`CF::Boolean` can be instantiated using another `CF::Boolean`, a `CFBooleanRef` or a `bool`:

    CF::Boolean b1 = kCFBooleanTrue;
    CF::Boolean b2 = b1;
    CF::Boolean b3 = false;

**Mutation:**

`CF::Boolean` value can be set through the `=` operator:

    CF::Boolean b1 = false;
    b1             = true;
    
**Equality:**

`CF::Boolean` can be compared to another `CF::Boolean`, a `CFBooleanRef` or a `bool`:

    CF::Boolean b1 = false;
    CF::Boolean b2 = true;
    
    if( b1 == b2 )             { /* ... */ }
    if( b1 == kCFBooleanTrue ) { /* ... */ }
    if( b1 == true )           { /* ... */ }

**Casting:**

`CF::Boolean` can be safely casted to a `bool` or `CFBooleanRef`:

    CF::Boolean  b1     = true;
    CFBooleanRef cfBool = b1;
    bool         b      = b1;
        
### CF::Number

`CF::Number` is a wrapper for `CFNumberRef`.

**Creation:**

`CF::Number` can be instantiated using another `CF::Number`, a `CFNumberRef` or an integral or floating point type:

    CF::Number n1 = someCFNumberRefObject;
    CF::Number n2 = n1;
    CF::Number n3 = 42;
    CF::Number n4 = 42.0f;

**Mutation:**

`CF::Number` value can be set/transformed through every operator:
    
    CF::Number n1 = 42;
    CF::Number n2 = 10;
    
    n1--;
    n2++;
    
    n1 += n2;
    n1 ^= n2
    n2 += 10;
    n1 &= 0xFF00;
    n2 /= n1;
    n1  = n1 | n2;
    n1  = n1 >> 8;
    
    /* etc... */

Note that you can determine is a `CF::Number` objects contains a floating point value using the `IsFloatType` method.

**Equality:**

`CF::Number` can be compared to another `CF::Number`, a `CFNumberRef` or a an integral or floating point type.  
All comparison operators are available:

    CF::Number n1 = 42;
    CF::Number n2 = 10;
    
    if( ( n1 != someCFNumberRefObject || n1 != n2 ) && n1 == 10 ) { /* ... */ }
    if( n1 != 10.0f || n1 >= 20 || n2 < 40.0f )                   { /* ... */ }
    if( n1 || n2 )                                                { /* ... */ }

**Casting:**

`CF::Number` can be safely casted to a `CFNumberRef` or a an integral or floating point type:

    CF::Number  n1     = 42;
    CFNumberRef cfNum  = n1;
    int         i      = n1;
    long        l      = n1;
    double      d      = n1;
    int64_t     i64    = n1;
    
### CF::String

CF::String is a wrapper for CFStringRef.

**Creation:**

`CF::String` can be instantiated using another CF::String, a CFStringRef, a `std::string` or an `char` pointer:

    CF::String s1 = someCFStringRefObject;
    CF::String s2 = s1;
    CF::String s3 = std::string( "hello, world" );
    CF::String s4 = "hello, world";
    
**Mutation:**

`CF::String` value can be set/transformed through the operator `=` and `+=` operator:
    
    CF::String s = "hello"
    s           += ", world"
    s			 = "hello, universe";

**Equality:**

`CF::String` can be compared to another `CF::String`, a `CFStringRef`, a `std::string` or a `char` pointer:

    CF::String s1 = "hello, world";
    CF::String s2 = "hello, universe";
    
    if( s1 == someCFStringRefObject )            { /* ... */ }
    if( s1 != s2 )                               { /* ... */ }
    if( s1 == std::string( "hello, universe" ) ) { /* ... */ }
    if( s1 != "hello, universe" )                { /* ... */ }

Casting:

`CF::String` can be safely casted to a `CFStringRef`, a `std::string` or a `char` pointer:

    CF::String  s1  = "hello, world";
    CFStringRef cfS = s1;
    std::string s   = s1;
    char      * cp  = s1;

**Character access:**

Individual characters can be accessed through the `[]`operator:

    CF::String s1 = "hello, world";
    char       c1 = s1[  1 ] /* 'e' */;
    char       c2 = s1[ -1 ] /* 'd' */;

### CF::Array

`CF::Array` is a wrapper for `CFArrayRef`.

**Creation:**

`CF::Array` can be instantiated using another `CF::Array`, or a `CFArrayRef`.  
All `CF::Array` objects are created as mutable, and an initial capacity can be passed to the constructor:

    CF::Array a1 = someCFArrayRefObject;
	CF::Array a2 = a1;
	CF::Array a3( 100 );

**Mutation:**

`CFTypeRef` or `CF:Type` objects can be added to an array using the `<<` operator:

    CF::Array  a;
    CF::Number n = 42;
    CF::String s = "hello, world";
    
    a << someCFTypeRefObject;
    a << n;
    a << s;
    
    /* Or simply: */
    a << someCFTypeRefObject << n << s;

An other `CF:Array` can be appended using the `+=` operator:

    CF::Array  a1;
    CF::Array  a2;
    CF::Number n = 42;
    CF::String s = "hello, world";
    
    a1 << n;
    a2 << s;
    a1 += a2;

**Element access:**

Values can be retrieved using the `[]` operator:

    CF::Array  a;
    CF::Number n1 = 42;
    CF::String s1 = "hello, world";
    
    a << someCFTypeRefObject << n1 << s1;
    
    CFTypeRef  cfObject = a[ 0 ];
    CF::Number n2       = a[ 1 ];
    CF::String s2       = a[ 2 ];

**Casting:**

`CF::Array` can be safely casted to a `CFArrayRef`:

    CF::Array  a( 100 );
    CFArrayRef cfA = a;

**Other methods:**

Other `CFArrayRef` methods are available, like `GetCount`, `RemoveValueAtIndex`, `ExchangeValuesAtIndices`, etc.

### CF::Dictionary

`CF::Dictionary` is a wrapper for `CFDictionaryRef`.

**Creation:**

`CF::Dictionary` can be instantiated using another `CF::Dictionary`, or a `CFDictionaryRef`.  
All `CF::Dictionary` objects are created as mutable, and an initial capacity can be passed to the constructor:

    CF::Dictionary d1 = someCFDictionaryRefObject;
	CF::Dictionary d2 = d1;
	CF::Dictionary d3( 100 );

**Mutation:**

A key/value pair can be added to a dictionary using the `+=` operator.  
To create a key/value pair, use the `CF::Pair` object, which can be constructed with `CFTypeRef` or `CF:Type` objects.  
Note that `std::string` or `char` pointers can be safely used as keys:

    CF::Dictionary d;
    CF::String     s = "key";
    CF::Number     n = 42;
    
    d += CF::Pair( someCFTypeRefObject, someOtherCFTypeRefObject );
    d += CF::Pair( s, n );
    d += CF::Pair( std::string( "key" ), n );
    d += CF::Pair( "key", n );

A key can be replaced using the `<<` operator:


    CF::Dictionary d;
    CF::Number     n1 = 42;
    CF::Number     n2 = 43;
    
    d += CF::Pair( s, n1 );
    d << CF::Pair( s, n2 );

**Casting:**

`CF::Dictionary` can be safely casted to a `CFDictionaryRef`:

    CF::Dictionary  d( 100 );
    CFDictionaryRef cfD = d;

**Other methods:**

Other `CFDictionaryRef` methods are available, like `GetCount`, `ContainsKey`, `RemoveValue`, etc.

### CF::Date

`CF::Date` is a wrapper for `CFDateRef`.

**Creation:**

`CF::Date` can be instantiated using another `CF::Date`, a `CFDateRef` or a `CFAbsoluteTime`.  
When a `CF::Date` object is created without argument, it defaults to the current date:  

    CF::Date d1;
    CF::Date d2 = someCFDateRefObject;
	CF::Date d3 = d1;
	CF::Date d4 = 100;

**Mutation:**

`CF::Date` value can be set/transformed through many operators:

    CF::Date d1;
    CF::Date d2;
    
    d1++;
    d2--;
    
    d1 += d2;
    d2  = d1 + d2;

**Equality:**

`CF::Date` can be compared to another `CF::Date`, a `CFDateRef` or a `CFAbsoluteTime`.
Almost all comparison operators are available:

    CF::Date d1;
    CF::Date d2;
    
    if( d1 == someCFDateRefObject ) { /* ... */ }
    if( d1 != d2 )                  { /* ... */ }
    if( d1 >  100 )                 { /* ... */ }
    if( d1 <= d2 )                  { /* ... */ }

**Casting:**

`CF::Date` can be safely casted to a `CFDateRef` or `CFAbsoluteTime`:

    CF::Date       d;
    CFDateRef      cfD = d;
    CFAbsoluteTime t   = d;

### CF::Data

`CF::Data` is a wrapper for `CFDataRef`.

**Creation:**

`CF::Data` can be instantiated using another `CF::Data`, a `CFDataRef`, a `CFStringRef`, a `std::string` or a `CF::Data::Byte` pointer: 

    const char * cp = "hello, world";
    CF::Data     d1 = someCFDataRefObject;
    CF::Data     d2 = someCFStringRefObject;
	CF::Data     d3 = d1;
	CF::Data     d4 = std::string( "hello, world" );
	CF::Data     d5( ( CF::Data::Byte * )cp, 12 );

**Mutation:**

Data can be appended using the `+=` operator.  
The following types can be appended: `CF::Data::Byte`, `CFStringRef`, `CFDataRef`and `std::string`:

    CF::Date d;
    
    d += 42;
    d += someCFtringRefObject;
    d += someCFDataRefObject;
    d += std::string( "hello, world" );

To append a `CF::Data::Byte` pointer, une the `AppendBytes` method.

**Element access:**

Single bytes can be retrieved as `CF::Data::Byte` using the `[]` operator:

    CF::Date       d( std::string( "hello, world" ) );
    CF::Date::byte b = d[ 2 ];

**Casting:**

`CF::Data` can be safely casted to a `CFDataRef`, `std::string` and `CF::Data::Byte` pointer:

    CF::Data         d;
    CFDateRef        cfD = d;
    std::string      s   = d;
    CF::Data::Byte * bp  = d;

**Other methods:**

Other `CFDataRef` methods are available, like `GetLength`, `GetMutableBytePtr`, `ReplaceBytes`, etc.

### CF::URL

`CF::URL` is a wrapper for `CFURLRef`.

**Creation:**

`CF::URL` can be instantiated using another `CF::URL`, a `CFURLRef`, a `CFStringRef`, or a `std::string`: 

    CF::URL url1 = someCFURLRefObject;
    CF::URL url2 = someCFStringRefObject;
    CF::URL url3 = url1;
    CF::URL url4 = std::string( "http://www.example.org/" );

**Equality:**

CF::URL can be compared to another CF::URL, a CFURLRef, a CFStringRef, or a std::string:

    CF::URL url1( "http://www.example.org/" );
    CF::URL url2( "http://www.xs-labs.com/" );
    
    if( url1 == url2 )                                     { /* ... */ }
    if( url1 != someCFURLRefObject )                       { /* ... */ }
    if( url1 == someCFStringRefObject )                    { /* ... */ }
    if( url1 != std::string( "http://www.xs-labs.com/" ) ) { /* ... */ }

**Mutation:**

Path components can be appended to a `CF::URL` using the `/=` operator:

    CF::URL url1( "http://www.example.org/" );
    
    url /= "path";
    url /= "to";
    url /= "some";
    url /= "page";

**Parts access:**

Individual URL parts can be accessed as `std::string` using the `[]` operator, specifying a `CF::URL::Part`, or through regular methods:

    CF::URL url( "http://www.example.org/" );
    
    std::string scheme = url[ CF::URL::PartScheme ];
    std::string host   = url.GetHostName();

**Casting:**

`CF::URL` can be safely casted to a `CFURLRef`, `CFStringRef`, or `std::string`:

    CF::URL     url( "http://www.example.org/" );
    CFURLRef    cfUrl = url;
    CFStringRef cfS   = url;
    std::string s     = url;

<a name="7"></a>
To-Do
-----

The following classes will be implemented soon:

    - CFBundle
    - CFDateFormatter
    - CFNotificationCenter
    - CFNull
    - CFNumberFormatter
    - CFRunLoop
    - CFRunLoopSource
    - CFRunLoopTimer
    - CFSocket
    - CFSet
    - CFMutableSet

<a name="8"></a>
License
-------

CoreFoundation++ is released under the terms of the BOOST License.

<a name="9"></a>
Repository Infos
----------------

    Owner:			Jean-David Gadina - XS-Labs
    Web:			www.xs-labs.com
    Blog:			www.noxeos.com
    Twitter:		@macmade
    GitHub:			github.com/macmade
    LinkedIn:		ch.linkedin.com/in/macmade/
    StackOverflow:	stackoverflow.com/users/182676/macmade
