#include <sstream>
#include <iomanip>

#include "ys_date.h"
#define OTL_STL
#define OTL_ODBC
#define OTL_ODBC_MYSQL
#ifndef WIN32
#define OTL_ODBC_UNIX
#endif
#include <otlv4.h>

#include "wx/datetime.h"

using namespace std;

YardDate& YardDate::operator=(const otl_datetime& time)
{
    SetYear(time.year);
	SetMonth(time.month);
	SetDay(time.day);
	SetHour(time.hour);
	SetMinute(time.minute);
	SetSecond(time.second);
	SetFraction(time.fraction);
	SetFracPrecision(time.frac_precision);
    
    return *this;
}

YardDate& YardDate::operator=(const wxDateTime& time)
{
    SetYear(time.GetYear());
	SetMonth(time.GetMonth());
	SetDay(time.GetDay());
	SetHour(time.GetHour());
	SetMinute(time.GetMinute());
	SetSecond(time.GetSecond());
	SetFraction(time.GetMillisecond());
	SetFracPrecision(3);
    return *this;
}

YardDate::YardDate(const XMLNode& node):XMLNode(node)
{}
    
string YardDate::ToString() const
{
	stringstream str;
	str << GetYear() << "-" 
        << setw(2) << setfill('0') << GetMonth() << "-"
        << setw(2) << setfill('0') << GetDay() << " "
        << setw(2) << setfill('0') << GetHour() << ":" 
        << setw(2) << setfill('0') << GetMinute() << ":" 
        << setw(2) << setfill('0') << GetSecond();
	return str.str();
    
}
    
YardDate::YardDate(const otl_datetime& time)
{
    *this = time;
    
}

YardDate::YardDate(const wxDateTime& time)
{
    *this = time;
    
}

string YardDate::DayString() const {
    stringstream str;
	str << GetYear() << "-" 
        << setw(2) << setfill('0') << GetMonth() << "-"
        << setw(2) << setfill('0') << GetDay();
    return str.str();
}
