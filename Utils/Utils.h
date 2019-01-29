#ifndef UTILS_H
#define UTILS_H

#include <QTime>
#include <QDateTime>
#include <QTableWidget>
#include <QAbstractItemModel>

#include "../UnitTests.h"

namespace Utils
{
QDate fromStringDate(const char *date);
QDate fromStringDate(const QString &date);

QDate fromROSStringDate(const char *date);
QDate fromROSStringDate(const QString &date);
QTime fromStringTime(const char *time);
QTime fromStringTime(const QString &time);

QString toStringDate(const QDate &date);
QDateTime fromROSStringDateTime(const QString &rosDateTime);
qint64 fromROSStringTimeToSecs(const QString &rosTime);

QStringList allColumnTexts(const QAbstractItemModel *model, int col, Qt::ItemDataRole role = Qt::EditRole);

void raiseWarning(QWidget *papi, const QString &info, QString title = QString());
void raiseInfo(QWidget *papi, const QString &info, QString title = QString());

#ifdef UNIT_TESTS_UTILS
	void UTests();
#endif
}

#endif // UTILS_H
