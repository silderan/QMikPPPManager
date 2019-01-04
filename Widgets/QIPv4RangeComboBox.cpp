#include "QIPv4RangeComboBox.h"

QIPv4RangeComboBox::QIPv4RangeComboBox(QWidget *papi) :
	QComboBox(papi)
{

}

void QIPv4RangeComboBox::setup(const IPv4RangeMap &ipv4RangeMap, const IPv4List &ipv4HideList, const IPv4 &initialSelectedIP)
{
	IPv4RangeMapIterator it(ipv4RangeMap);
	int newSel = -1;

	while( it.hasNext() )
	{
		it.next();
		for( IPv4 first = it.value().first(); first <= it.value().last(); ++first )
		{
			if( !ipv4HideList.contains(first) )
			{
				addItem( first.toString(), it.value().name() );
				if( initialSelectedIP.isValid() && (first == initialSelectedIP) )
					newSel = count()-1;
			}
		}
	}
	if( newSel != -1 )
		setCurrentIndex(newSel);
}
