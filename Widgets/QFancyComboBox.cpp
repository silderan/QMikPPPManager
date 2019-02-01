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

#include "QFancyComboBox.h"

QFancyComboBox::QFancyComboBox(QWidget *papi)
	: QComboBox(papi)
	, m_hasDefaultData(false)
{

}

void QFancyComboBox::setup(const QString &defaultValueDescription, const QString &defaultValueData, const QStringList &addList, const QStringList &skipList, const QString &currentSelected)
{
	clear();

	if( (m_hasDefaultData = !defaultValueDescription.isEmpty()) )
		addItem( defaultValueDescription, defaultValueData );

	int i = -1;
	foreach( QString t, addList )
	{
		if( t == currentSelected )
		{
			i = count();
			addItem(t);
		}
		else
		if( !skipList.contains(t) )
			addItem(t);
	}
	if( count() )
	{
		if( i == -1 )
		{
			if( !defaultValueDescription.isEmpty() )
				i = 0;
			else
			if( !currentSelected.isEmpty() )
			{
				i = count();
				addItem(currentSelected);
			}
		}
		setCurrentIndex(i);
	}
}

void QFancyComboBox::setup(const QStringList &addList, const QString &currentSelected, bool addIfNecessary)
{
	clear();
	if( currentSelected.isEmpty() )
		return setup(addList);
	addItems(addList);
	return selectText(currentSelected, addIfNecessary);
}

void QFancyComboBox::updateList(const QStringList &addList, bool addIfNecessary)
{
	if( currentText().isEmpty() )
		return setup(addList);
	else
		return setup(addList, currentText(), addIfNecessary );
}

QString QFancyComboBox::currentText()
{
	if( (currentIndex() == 0) && m_hasDefaultData )
		return currentData().toString();
	return QComboBox::currentText();
}

void QFancyComboBox::selectText(const QString &text, bool addIfNecessary)
{
	int i = findData(text, Qt::EditRole);
	if( i == -1 )
	{
		if( addIfNecessary )
		{
			i = count();
			addItem(text);
		}
		else
			return setCurrentText(text);
	}
	setCurrentIndex(i);
}
