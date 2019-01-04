#ifndef QSTATICIPCOMBOBOX_H
#define QSTATICIPCOMBOBOX_H

#include "QIPv4RangeComboBox.h"

class QStaticIPComboBox : public QIPv4RangeComboBox
{
	Q_OBJECT

public:
	explicit QStaticIPComboBox(QWidget *parent = Q_NULLPTR);

	void setup(const IPv4RangeMap &ipv4RangeMap, const IPv4List &ipv4UsedList);
};

#endif // QSTATICIPCOMBOBOX_H
