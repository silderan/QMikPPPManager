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

#ifndef TABLECELLCOLORS_H
#define TABLECELLCOLORS_H

#include <QColor>
#include <QString>
#include <QFont>

#include "../../SildeQtUtils/src/QIniFile.h"

struct CellLook
{
	QString m_fontFamily;
	bool m_fontBold;
	bool m_fontItalic;
	QColor m_foreColor;
	QColor m_backColor;

	QString saveString() const;
	bool fromSaveString(const QString &saveString);

	CellLook() :
		m_fontFamily("MS Shell Dlg"),
		m_fontBold(false),
		m_fontItalic(false),
		m_foreColor(Qt::black),
		m_backColor(Qt::white)
	{

	}
	CellLook(QColor foreground, QColor background) :
		m_fontFamily("MS Shell Dlg"),
		m_fontBold(false),
		m_fontItalic(false),
		m_foreColor(foreground),
		m_backColor(background)
	{

	}
};

struct TableCellLook
{
	int m_fontSize;		// Tamaño de la fuente usada en la tabla.
	int m_rowHeight;	// Altura de las filas de la tabla.

	CellLook m_connected;
	CellLook m_disconnected;
	CellLook m_enabled;
	CellLook m_disabledTemporary;
	CellLook m_disabledNoPay;
	CellLook m_disabledTechnically;
	CellLook m_disabledUndefined;
	CellLook m_disabledDevicesRetired;
	CellLook m_disabledDevicesNoRetired;

	TableCellLook() :
		m_fontSize(10),
		m_rowHeight(17),
		m_connected(0x00ff00u, 0xFFFFFFu),
		m_disconnected(0x220000u, 0xFFFFFFu),
		m_disabledTemporary(0x000000u, 0xA0FFFFu),
		m_disabledNoPay(0x000000u, 0xFF0000u),
		m_disabledTechnically(0x000000u, 0xFFA0A0u),
		m_disabledUndefined(0x000000u, 0xFFF8080u),
		m_disabledDevicesRetired(0x000000u, 0xFFC0C0u),
		m_disabledDevicesNoRetired(0x000000u, 0xFFC0C0u)
	{

	}

	void save(QIniData &cnfgData)const;
	void load(const QIniData &cnfgData);
};

#endif // TABLECELLCOLORS_H
