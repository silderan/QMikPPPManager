#ifndef UTILS_H
#define UTILS_H


#include <QDateTime>

namespace Utils
{
	QDateTime fromROSDateTime(const QString &rosDateTime);
};

#endif // UTILS_H
