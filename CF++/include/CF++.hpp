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
 * @header      CF++.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ main header file
 */

#ifndef CFPP
#define CFPP

#include <CoreFoundation/CoreFoundation.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

/*
 * Disable warnings about class members not having DLL-interface.
 * Eg: std::shared_ptr
 */
#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable: 4251 )
#endif

#ifdef _WIN32
#ifdef CFPP_DLL_BUILD
#define CFPP_EXPORT __declspec( dllexport )
#else
#define CFPP_EXPORT __declspec( dllimport )
#endif
#else
#define CFPP_EXPORT     
#endif

#include <CF++/CFPP-Type.hpp>
#include <CF++/CFPP-PropertyListBase.hpp>
#include <CF++/CFPP-PropertyListType.hpp>
#include <CF++/CFPP-AutoPointer.hpp>
#include <CF++/CFPP-AnyObject.hpp>
#include <CF++/CFPP-AnyPropertyListType.hpp>
#include <CF++/CFPP-Null.hpp>
#include <CF++/CFPP-Boolean.hpp>
#include <CF++/CFPP-Number.hpp>
#include <CF++/CFPP-String.hpp>
#include <CF++/CFPP-URL.hpp>
#include <CF++/CFPP-Data.hpp>
#include <CF++/CFPP-Date.hpp>
#include <CF++/CFPP-Array.hpp>
#include <CF++/CFPP-Pair.hpp>
#include <CF++/CFPP-Dictionary.hpp>
#include <CF++/CFPP-Error.hpp>
#include <CF++/CFPP-UUID.hpp>
#include <CF++/CFPP-ReadStream.hpp>
#include <CF++/CFPP-WriteStream.hpp>
#include <CF++/CFPP-PropertyListType-Definition.hpp>
#include <CF++/CFPP-Object.hpp>

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif /* CFPP */
