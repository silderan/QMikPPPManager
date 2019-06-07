/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#include "QIPv4RangeComboBox.h"

QIPv4RangeComboBox::QIPv4RangeComboBox(QWidget *papi) :
	QComboBox(papi)
{

}

void QIPv4RangeComboBox::setup(const IPv4RangeList &ipv4RangeList, const IPv4List &ipv4HideList, const IPv4 &initialSelectedIP)
{
	int newSel = -1;
	foreach( const IPv4Range &ipv4Range, ipv4RangeList)
	{
		for( IPv4 first = ipv4Range.first(); first <= ipv4Range.last(); ++first )
		{
			if( !ipv4HideList.contains(first) )
			{
				addItem( first.toString() );
				if( initialSelectedIP.isValid() && (first == initialSelectedIP) )
					newSel = count()-1;
			}
		}
	}
	if( newSel != -1 )
		setCurrentIndex(newSel);
}
