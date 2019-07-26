/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

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
