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

#ifndef DLGPPPLOGVIEWER_H
#define DLGPPPLOGVIEWER_H

#include <QDialog>

#include "Utils/QPPPLogger.h"

namespace Ui
{
	class DlgPPPLogViewer;
}

class DlgPPPLogViewer : public QDialog
{
	Q_OBJECT
	Ui::DlgPPPLogViewer *ui;

	QPPPLogDataList m_pppLogDatalist;
	QString m_userName;
	bool m_localCompactButtonEnable;
	bool m_localCompactButtonVisible;

	void enableCompactButton(bool enable);
	void showCompactButton(bool visible);

public:
	explicit DlgPPPLogViewer(const QString &userName = QString(), QWidget *parent = Q_NULLPTR);
	~DlgPPPLogViewer();

private slots:
	void on_compactLogsButton_clicked();
};

#endif // DLGPPPLOGVIEWER_H
