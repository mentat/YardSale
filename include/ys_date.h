/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef YARD_DATE_H
#define YARD_DATE_H

#include "xmlnode.h"
#include "ys_build.h"

class otl_datetime;
class wxDateTime;
class YardDate: public XMLNode
{
 public:
    
    YardDate() { setName("datetime"); }
    YardDate(const string& xml): XMLNode(xml, XMLNode::Str) {}
    YardDate(const otl_datetime& time);
    YardDate(const wxDateTime& time);
    YardDate(const XMLNode& node);
 
    unsigned int GetYear() const
        { return ToInt(child("year").data()); }
    unsigned int GetMonth() const
        { return ToInt(child("month").data()); }
    unsigned int GetDay() const
        { return ToInt(child("day").data()); }
    unsigned int GetHour() const
        { return ToInt(child("hour").data()); }
    unsigned int GetMinute() const
        { return ToInt(child("minute").data()); }
    unsigned int GetSecond() const
        { return ToInt(child("second").data()); }
    unsigned int GetFraction() const
        { return ToInt(child("fraction").data()); }
    unsigned int GetFracPrecision() const
        { return ToInt(child("fraction").property("precision")); }

    void SetYear(unsigned int year)
        { child("year").setData(ToStr(year)); }
    void SetMonth(unsigned int month)
        { child("month").setData(ToStr(month)); }
    void SetDay(unsigned int day)
        { child("day").setData(ToStr(day)); }
    void SetHour(unsigned int hour)
        { child("hour").setData(ToStr(hour)); }
    void SetMinute(unsigned int minute)
        { child("minute").setData(ToStr(minute)); }
    void SetSecond(unsigned int second)
        { child("second").setData(ToStr(second)); }
    void SetFraction(unsigned int frac, unsigned int precision = YS_DEFAULT_TIME_PRECISION)
        { child("fraction").setData(ToStr(frac, precision)); }
    void SetFracPrecision(int precision) 
        { child("fraction").setProperty("precision", ToStr(precision)); }        
 
	YardDate& operator=(const otl_datetime& time);
    YardDate& operator=(const wxDateTime& time);
    
    string ToString() const;
    string DayString() const;
    
};
#endif
