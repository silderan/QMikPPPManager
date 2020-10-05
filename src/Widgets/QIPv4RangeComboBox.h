#ifndef QIPV4RANGECOMBOBOX_H
#define QIPV4RANGECOMBOBOX_H

#include <QComboBox>

#include "../../SildeQtUtils/src/IPv4Range.h"

class QIPv4RangeComboBox : public QComboBox
{
public:
	QIPv4RangeComboBox(QWidget *papi = Q_NULLPTR);
	void setup(const IPv4RangeList &ipv4RangeList, const IPv4List &ipv4HideList, const IPv4 &initialSelectedIP = IPv4());

public slots:

};

#endif // QIPV4RANGECOMBOBOX_H
