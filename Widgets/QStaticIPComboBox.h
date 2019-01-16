#ifndef QSTATICIPCOMBOBOX_H
#define QSTATICIPCOMBOBOX_H

#include "QIPv4RangeComboBox.h"

class QStaticIPComboBox : public QIPv4RangeComboBox
{
	Q_OBJECT

public:
	explicit QStaticIPComboBox(QWidget *parent = Q_NULLPTR);

	void setup(const IPv4RangeList &ipv4RangeList, const IPv4List &ipv4HideList, const IPv4 &initialSelectedIP);
};

#endif // QSTATICIPCOMBOBOX_H
