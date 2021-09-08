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
 * @header          TargetConditionals.h
 * @copyright       (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @description     OS X version does not know about WIN64... So let's define
 *                  everything for WIN32 and WIN64.
 *                  Note: __i386__ and __x86_64__ are also defined if needed, so
 *                  CFBase.h can correctly guess the system's endianness.
 */

#ifdef _WIN32

#define TARGET_OS_MAC               0
#define TARGET_OS_WIN32             1
#define TARGET_OS_UNIX              0
#define TARGET_OS_IPHONE            0 
#define TARGET_OS_IOS               0
#define TARGET_OS_WATCH             0
#define TARGET_OS_TV                0
#define TARGET_OS_SIMULATOR         0
#define TARGET_OS_EMBEDDED          0 
#define TARGET_IPHONE_SIMULATOR     TARGET_OS_SIMULATOR /* deprecated */
#define TARGET_OS_NANO              TARGET_OS_WATCH     /* deprecated */ 

#ifdef _WIN64

#ifndef __x86_64__
#define __x86_64__ 1
#endif

#define TARGET_CPU_PPC          0
#define TARGET_CPU_PPC64        0
#define TARGET_CPU_68K          0
#define TARGET_CPU_X86          0
#define TARGET_CPU_X86_64       1
#define TARGET_CPU_ARM          0
#define TARGET_CPU_ARM64        0
#define TARGET_CPU_MIPS         0
#define TARGET_CPU_SPARC        0
#define TARGET_CPU_ALPHA        0
#define TARGET_RT_MAC_CFM       0
#define TARGET_RT_MAC_MACHO     1
#define TARGET_RT_LITTLE_ENDIAN 1
#define TARGET_RT_BIG_ENDIAN    0
#define TARGET_RT_64_BIT        1

#else

#ifndef __i386__
#define __i386__ 1
#endif

#define TARGET_CPU_PPC          0
#define TARGET_CPU_PPC64        0
#define TARGET_CPU_68K          0
#define TARGET_CPU_X86          1
#define TARGET_CPU_X86_64       0
#define TARGET_CPU_ARM          0
#define TARGET_CPU_ARM64        0
#define TARGET_CPU_MIPS         0
#define TARGET_CPU_SPARC        0
#define TARGET_CPU_ALPHA        0
#define TARGET_RT_MAC_CFM       0
#define TARGET_RT_MAC_MACHO     1
#define TARGET_RT_LITTLE_ENDIAN 1
#define TARGET_RT_BIG_ENDIAN    0
#define TARGET_RT_64_BIT        0

#endif

#endif
