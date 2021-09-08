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
* @file        Win32-Init.cpp
* @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
* @abstract    Win32 initialization routines
*/

#include <Windows.h>
#include <string>

struct CFPP_Win32Init
{
    CFPP_Win32Init( void )
    {
        char      * commonProgFiles;
        std::string mobileSupport;
        std::string appleSupport;

        #ifdef _WIN64
        commonProgFiles = nullptr;
        #else
        commonProgFiles = getenv( "COMMONPROGRAMFILES(x86)" );
        #endif

        if( commonProgFiles == nullptr )
        {
            commonProgFiles = getenv( "COMMONPROGRAMFILES" );
        }

        mobileSupport = std::string( commonProgFiles ) + "\\Apple\\Mobile Device Support";
        appleSupport  = std::string( commonProgFiles ) + "\\Apple\\Apple Application Support";

        SetDllDirectoryA( mobileSupport.c_str() );
        SetDllDirectoryA( appleSupport.c_str() );
    }
};

static struct CFPP_Win32Init init;
