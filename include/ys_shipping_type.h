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
#ifndef YS_SHIPPING_TYPE_H
#define YS_SHIPPING_TYPE_H

#include "xmlnode.h"
#include "ys_build.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;

/**
 * The YardSale Shipping Type is a OO representation of the datebase
 * package table.
 *
 * @include SHP_Table.sql
 * @ingroup database 
 * @see YardShipType
 * @author Michael Swigon	
 * @version \$Revision: 1.4 $$
 * @see XMLNode
 */

class YardShipType: public XMLNode
{
 public:
   
    friend class YardDatabase;

    YardShipType(const string& xml): XMLNode(xml, Str) {}    
    YardShipType(): XMLNode() { setName("Shipping_Table"); }
    
    const char * GetUnique() const { return "SHP_Type"; }
	/* gettors */

	/// Get shipping type
    string GetShipType() const 
    { return child("SHP_Type").data(); }
	/// Get carrier id
    string GetCarrierIdS() const
    { return child("SHP_REF_CRR_ID").data(); }
	long GetCarrierId() const 
    { return ToLong(GetCarrierIdS()); }
	/// Get shipping cost
    string GetCostS() const
    { return child("SHP_Cost").data(); }
	double GetCost() const 
    { return ToDouble(GetCostS()); }
	/// Get enabled flag
	bool GetEnabled() const 
    { return (GetEnabledS() == "0") ? false : true; }
    string GetEnabledS() const 
    { return child("SHP_Enabled").data(); }

	/* settors */

	/// Set the shipping type
	void SetShipType(const string& str) 
    { child("SHP_Type").setData(str); }
	/// Set the carrier id
	void SetCarrierID(long num) 
    { child("SHP_REF_CRR_ID").setData(ToStr(num)); }
	/// Set the shipping cost
	void SetCost(double num) 
    { child("SHP_Cost").setData(ToStr(num, YS_DEFAULT_MONEY_PRECISION)); }
	/// Set enabled flag
	void SetEnabled(bool flag) 
    { (flag) ? child("SHP_Enabled").setData("1") : child("SHP_Enabled").setData("0"); }

    virtual string ToString(const string& delim = ",") const;

};

#endif
