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
