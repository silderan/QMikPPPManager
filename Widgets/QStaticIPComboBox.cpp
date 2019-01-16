#include "QStaticIPComboBox.h"

QStaticIPComboBox::QStaticIPComboBox(QWidget *parent) : QIPv4RangeComboBox(parent)
{

}

void QStaticIPComboBox::setup(const IPv4RangeList &ipv4RangeList, const IPv4List &ipv4HideList, const IPv4 &initialSelectedIP)
{
	addItem( tr("IP dinámica") );
	QIPv4RangeComboBox::setup(ipv4RangeList, ipv4HideList, initialSelectedIP);
}
