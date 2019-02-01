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

#include "QRoutersLineEdit.h"

#include <QList>

QRoutersLineEdit::QRoutersLineEdit(QWidget *parent) : QLineEdit(parent)
{
	setFrame(false);
	setReadOnly(true);
}

QRoutersLineEdit::~QRoutersLineEdit()
{

}

void QRoutersLineEdit::updateText()
{
	QString routersText;
	QRouterIDMapIterator it(m_routerIDMap);
	while( it.hasNext() )
	{
		it.next();
		if(routersText.isEmpty())
			routersText = QString("%1:%2").arg(it.routerName(), it.dataID());
		else
			routersText += QString(", %1:%2").arg(it.routerName(), it.dataID());
	}
	setText( routersText );
}

void QRoutersLineEdit::addRouterID(const QString &routerName, const QString &id)
{
	if( routerName.count() && id.count() )
	{
		m_routerIDMap[routerName] = id;
		updateText();
	}
}

void QRoutersLineEdit::delRouter(const QString &routerName)
{
	m_routerIDMap.remove(routerName);
	updateText();
}
