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

#include "TableCellLook.h"

QString CellLook::saveString() const
{
	return QString("%1.%2.%3.%4.%5.%6").arg(
				"1", // Version
				m_fontFamily,
				m_fontBold ? "bold" : "normal",
				m_fontItalic ? "italic" : "normal",
				QString::number(m_foreColor.rgba(), 16).toUpper(),
				QString::number(m_backColor.rgba(), 16).toUpper() );
}

bool CellLook::fromSaveString(const QString &saveString)
{
	QStringList data = saveString.split('.');
	if( data.count() > 1 )
	{
		switch( data[0].toUInt() )
		{
		case 1:
			if( data.count() == 6 )
			{
				m_fontFamily = data[1];
				m_fontBold = data[2] == "bold";
				m_fontItalic = data[3] == "italic";
				m_foreColor.setRgba( data[4].toUInt(Q_NULLPTR, 16) );
				m_backColor.setRgba( data[5].toUInt(Q_NULLPTR, 16) );
				return true;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

#define KEY_FONT_SIZE		("table-cell-look-table-font-size")
#define KEY_ROW_HEIGHT		("table-cell-look-table-row-height")
#define KEY_CONNECTED		("table-cell-look-connected")
#define KEY_DISCONNECTED	("table-cell-look-disconnected")
#define KEY_ENABLED			("table-cell-look-enabled-user")
#define KEY_DISABLED_TEMP	("table-cell-look-user-disabled-temporary")
#define KEY_DISABLED_NPAY	("table-cell-look-user-disabled-no-pay")
#define KEY_DISABLED_TECH	("table-cell-look-user-disabled-technically")
#define KEY_DISABLED_UNDE	("table-cell-look-user-disabled-undefined")
#define KEY_DISABLED_RETI	("table-cell-look-user-disabled-devices-retired")
#define KEY_DISABLED_NRETI	("table-cell-look-user-disabled-devices-no-retired")

void TableCellLook::save(QIniData &cnfgData) const
{
	cnfgData[KEY_FONT_SIZE]		= QString::number(m_fontSize);
	cnfgData[KEY_ROW_HEIGHT]	= QString::number(m_rowHeight);

	cnfgData[KEY_CONNECTED]		= m_connected.saveString();
	cnfgData[KEY_DISCONNECTED]	= m_disconnected.saveString();
	cnfgData[KEY_ENABLED]		= m_enabled.saveString();
	cnfgData[KEY_DISABLED_TEMP]	= m_disabledTemporary.saveString();
	cnfgData[KEY_DISABLED_NPAY]	= m_disabledNoPay.saveString();
	cnfgData[KEY_DISABLED_TECH]	= m_disabledTechnically.saveString();
	cnfgData[KEY_DISABLED_UNDE]	= m_disabledUndefined.saveString();
	cnfgData[KEY_DISABLED_RETI]	= m_disabledDevicesRetired.saveString();
	cnfgData[KEY_DISABLED_NRETI]= m_disabledDevicesNoRetired.saveString();
}

void TableCellLook::load(const QIniData &cnfgData)
{
	if( (m_fontSize = cnfgData[KEY_FONT_SIZE].toInt()) <= 1 )
		m_fontSize = 10;
	if( (m_rowHeight = cnfgData[KEY_ROW_HEIGHT].toInt()) <= 5 )
		m_rowHeight = 18;

	m_connected.fromSaveString(cnfgData[KEY_CONNECTED]);
	m_disconnected.fromSaveString(cnfgData[KEY_DISCONNECTED]);
	m_enabled.fromSaveString(cnfgData[KEY_ENABLED]);
	m_disabledTemporary.fromSaveString(cnfgData[KEY_DISABLED_TEMP]);
	m_disabledNoPay.fromSaveString(cnfgData[KEY_DISABLED_NPAY]);
	m_disabledTechnically.fromSaveString(cnfgData[KEY_DISABLED_TECH]);
	m_disabledUndefined.fromSaveString(cnfgData[KEY_DISABLED_UNDE]);
	m_disabledDevicesRetired.fromSaveString(cnfgData[KEY_DISABLED_RETI]);
	m_disabledDevicesNoRetired.fromSaveString(cnfgData[KEY_DISABLED_NRETI]);
}
