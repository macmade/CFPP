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
 * @file        Constants.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 */

#include "Constants.hpp"

#ifndef _WIN32

#define GET_CONST( _type_, _const_, _func_ )    \
 _type_ _func_( void )                          \
{                                               \
    return _const_;                             \
}

#else

#include <Windows.h>

static HMODULE mod = nullptr;

#define GET_CONST( _type_, _const_, _func_ )                                            \
 _type_ _func_( void )                                                                  \
{                                                                                       \
    if( mod == nullptr )                                                                \
    {                                                                                   \
        mod = GetModuleHandleA( "CoreFoundation.dll" );                                 \
    }                                                                                   \
                                                                                        \
    static _type_ value = nullptr;                                                      \
                                                                                        \
    if( value == nullptr )                                                              \
    {                                                                                   \
        value = *( reinterpret_cast< _type_ * >( GetProcAddress( mod, #_const_ ) ) );   \
    }                                                                                   \
                                                                                        \
    return value;                                                                       \
}

#endif

GET_CONST( CFBooleanRef, kCFBooleanTrue,                            GetCFBooleanTrue )
GET_CONST( CFBooleanRef, kCFBooleanFalse,                           GetCFBooleanFalse )
GET_CONST( CFStringRef,  kCFErrorLocalizedDescriptionKey,           GetCFErrorLocalizedDescriptionKey )
GET_CONST( CFStringRef,  kCFErrorLocalizedFailureReasonKey,         GetCFErrorLocalizedFailureReasonKey )
GET_CONST( CFStringRef,  kCFErrorLocalizedRecoverySuggestionKey,    GetCFErrorLocalizedRecoverySuggestionKey )

