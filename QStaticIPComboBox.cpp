#include "QStaticIPComboBox.h"

QStaticIPComboBox::QStaticIPComboBox(QWidget *parent) : QIPv4RangeComboBox(parent)
{

}

void QStaticIPComboBox::setup(const IPv4RangeMap &ipv4RangeMap, const IPv4List &ipv4UsedList)
{
	addItem( tr("IP dinámica") );
	QIPv4RangeComboBox::setup(ipv4RangeMap, ipv4UsedList);
}
