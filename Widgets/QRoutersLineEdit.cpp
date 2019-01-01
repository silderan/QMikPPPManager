#include "QRoutersLineEdit.h"

#include <QList>

QRoutersLineEdit::QRoutersLineEdit(QWidget *parent) : QLineEdit(parent)
{

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
	m_routerIDMap[routerName] = id;
	updateText();
}

void QRoutersLineEdit::delRouter(const QString &routerName)
{
	m_routerIDMap.remove(routerName);
	updateText();
}
