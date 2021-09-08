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
 * @file        CFPP-Date.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDateRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    Date Date::CurrentDate( void )
    {
        Date date;
        
        return date;
    }
    
    Date::Date( void ): _cfObject( nullptr )
    {
        this->SetValue( CFAbsoluteTimeGetCurrent() );
    }
    
    Date::Date( const Date & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = static_cast< CFDateRef >( CFRetain( value._cfObject ) );
        }
    }
    
    Date::Date( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFDateRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    Date::Date( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFDateRef >( CFRetain( value ) );
        }
    }
    
    Date::Date( CFDateRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFDateRef >( CFRetain( value ) );
        }
    }
    
    Date::Date( std::nullptr_t ): Date( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    Date::Date( CFAbsoluteTime value ): _cfObject( nullptr )
    {
        this->SetValue( value );
    }
    
    Date::Date( Date && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    Date::~Date( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    Date & Date::operator = ( Date value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Date & Date::operator = ( const AutoPointer & value )
    {
        return operator =( Date( value ) );
    }
    
    Date & Date::operator = ( CFTypeRef value )
    {
        return operator =( Date( value ) );
    }
    
    Date & Date::operator = ( CFDateRef value )
    {
        return operator =( Date( value ) );
    }
    
    Date & Date::operator = ( std::nullptr_t )
    {
        return operator =( Date( nullptr ) );
    }
    
    Date & Date::operator = ( CFAbsoluteTime value )
    {
        return operator =( Date( value ) );
    }
    
    bool Date::operator == ( const Date & value ) const
    {
        if( this->_cfObject == nullptr || value._cfObject == nullptr )
        {
            return false;
        }
        
        return CFDateCompare( this->_cfObject, value._cfObject, nullptr ) == kCFCompareEqualTo;
    }
    
    bool Date::operator == ( CFTypeRef value ) const
    {
        return operator ==( Date( value ) );
    }
    
    bool Date::operator == ( CFDateRef value ) const
    {
        return operator ==( Date( value ) );
    }
    
    bool Date::operator == ( CFAbsoluteTime value ) const
    {
        return operator ==( Date( value ) );
    }
    
    bool Date::operator != ( const Date & value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator != ( CFTypeRef value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator != ( CFDateRef value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator != ( CFAbsoluteTime value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator >= ( const Date & value ) const
    {
        CFComparisonResult r;
        
        if( this->_cfObject == nullptr || value._cfObject == nullptr )
        {
            return false;
        }
        
        r = CFDateCompare( this->_cfObject, value._cfObject, nullptr );
        
        return r == kCFCompareGreaterThan || r == kCFCompareEqualTo;
    }
    
    bool Date::operator >= ( CFDateRef value ) const
    {
        return operator >=( Date( value ) );
    }
    
    bool Date::operator >= ( CFAbsoluteTime value ) const
    {
        return operator >=( Date( value ) );
    }
    
    bool Date::operator <= ( const Date & value ) const
    {
        CFComparisonResult r;
        
        if( this->_cfObject == nullptr || value._cfObject == nullptr )
        {
            return false;
        }
        
        r = CFDateCompare( this->_cfObject, value._cfObject, nullptr );
        
        return r == kCFCompareLessThan || r == kCFCompareEqualTo;
    }
    
    bool Date::operator <= ( CFDateRef value ) const
    {
        return operator <=( Date( value ) );
    }
    
    bool Date::operator <= ( CFAbsoluteTime value ) const
    {
        return operator <=( Date( value ) );
    }
    
    bool Date::operator > ( const Date & value ) const
    {
        if( this->_cfObject == nullptr || value._cfObject == nullptr )
        {
            return false;
        }
        
        return CFDateCompare( this->_cfObject, value._cfObject, nullptr ) == kCFCompareGreaterThan;
    }
    
    bool Date::operator > ( CFDateRef value ) const
    {
        return operator >( Date( value ) );
    }
    
    bool Date::operator > ( CFAbsoluteTime value ) const
    {
        return operator >( Date( value ) );
    }
    
    bool Date::operator < ( const Date & value ) const
    {
        if( this->_cfObject == nullptr || value._cfObject == nullptr )
        {
            return false;
        }
        
        return CFDateCompare( this->_cfObject, value._cfObject, nullptr ) == kCFCompareLessThan;
    }
    
    bool Date::operator < ( CFDateRef value ) const
    {
        return operator <( Date( value ) );
    }
    
    bool Date::operator < ( CFAbsoluteTime value ) const
    {
        return operator <( Date( value ) );
    }
    
    Date & Date::operator += ( const Date & value )
    {
        this->SetValue( this->GetValue() + value.GetValue() );
        
        return *( this );
    }
    
    Date & Date::operator += ( CFDateRef value )
    {
        return operator +=( Date( value ) );
    }
    
    Date & Date::operator += ( CFAbsoluteTime value )
    {
        return operator +=( Date( value ) );
    }
    
    Date & Date::operator -= ( const Date & value )
    {
        this->SetValue( this->GetValue() - value.GetValue() );
        
        return *( this );
    }
    
    Date & Date::operator -= ( CFDateRef value )
    {
        return operator -=( Date( value ) );
    }
    
    Date & Date::operator -= ( CFAbsoluteTime value )
    {
        return operator -=( Date( value ) );
    }
    
    Date Date::operator + ( const Date & value )
    {
        return Date( *( this ) ) += value;
    }
    
    Date Date::operator + ( CFDateRef value )
    {
        return operator +( Date( value ) );
    }
    
    Date Date::operator + ( CFAbsoluteTime value )
    {
        return operator +( Date( value ) );
    }
    
    Date Date::operator - ( const Date & value )
    {
        return Date( *( this ) ) -= value;
    }
    
    Date Date::operator - ( CFDateRef value )
    {
        return operator -( Date( value ) );
    }
    
    Date Date::operator - ( CFAbsoluteTime value )
    {
        return operator -( Date( value ) );
    }
    
    Date & Date::operator ++ ( void )
    {
        this->SetValue( this->GetValue() + 1 );
        
        return *( this );
    }
    
    Date Date::operator ++ ( int )
    {
        Date n;
        
        n = *( this );
        
        operator++();
        
        return n;
    }
    
    Date & Date::operator -- ( void )
    {
        this->SetValue( this->GetValue() - 1 );
        
        return *( this );
    }
    
    Date Date::operator -- ( int )
    {
        Date n;
        
        n = *( this );
        
        operator--();
        
        return n;
    }
    
    Date::operator CFAbsoluteTime () const
    {
        return this->GetValue();
    }
    
    CFTypeID Date::GetTypeID( void ) const
    {
        return CFDateGetTypeID();
    }
    
    CFTypeRef Date::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    CFAbsoluteTime Date::GetValue( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return static_cast< CFAbsoluteTime >( 0 );
        }
        
        return CFDateGetAbsoluteTime( this->_cfObject );
    }
    
    void Date::SetValue( CFAbsoluteTime value )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
        }
        
        this->_cfObject = CFDateCreate( static_cast< CFAllocatorRef >( nullptr ), value );
    }
    
    void swap( Date & v1, Date & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
