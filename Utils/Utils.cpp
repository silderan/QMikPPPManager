#include "Utils.h"

QDateTime Utils::fromROSDateTime(const QString &rosDateTime)
{
	QDateTime dateTime;
	dateTime = QDateTime::fromString(rosDateTime, "mm");
	return dateTime;
}
