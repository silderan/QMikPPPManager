#ifndef UTILS_H
#define UTILS_H

#include <QTime>
#include <QDateTime>

#include "../UnitTests.h"

namespace Utils
{
	QDateTime fromROSDateTime(const QString &rosDateTime);
	QDateTime fromROSTime(const QString &rosTime);

#ifdef UNIT_TESTS_UTILS
	void UTests();
#endif
}

#endif // UTILS_H
