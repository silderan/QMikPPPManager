#ifndef QROUTERSLINEEDIT_H
#define QROUTERSLINEEDIT_H

#include <QLineEdit>
#include <QMap>
#include <QStringList>

#include "../ROSData/ROSDataBasics.h"

class QRoutersLineEdit : public QLineEdit
{
	Q_OBJECT
	QRouterIDMap m_routerIDMap;

	void updateText();
public:
	explicit QRoutersLineEdit(QWidget *parent = Q_NULLPTR);
	~QRoutersLineEdit();

	void addRouterID(const QString &routerName, const QString &id);
	void delRouter(const QString &routerName);

	inline QList<QString> routers()const	{ return m_routerIDMap.keys();	}
	inline bool count() const	{ return m_routerIDMap.count();		}
	inline bool isEmpty() const	{ return m_routerIDMap.isEmpty();	}

	inline const QRouterIDMap &routerIDMap() const				{ return m_routerIDMap;	}
	inline QString rosObjectID(const QString &routerName) const	{ return m_routerIDMap.value(routerName);	}
	inline int routersCount() const								{ return m_routerIDMap.count();	}
};

#endif // QROUTERSLINEEDIT_H
