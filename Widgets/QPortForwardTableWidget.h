#ifndef QPORTFORWARDTABLEWIDGET_H
#define QPORTFORWARDTABLEWIDGET_H

#include <QTableWidget>

#include "../Utils/PortForward.h"

class QPortForwardTableWidget : public QTableWidget
{
	QString m_lastError;

	enum Columns
	{
		Name,
		Protocol,
		PublicPortIni,
		PublicPortEnd,
		PrivatePortIni,
		PrivatePortEnd,
		IP,
		Total
	};

	PortForward portForwardRow( int row );

public:
	explicit QPortForwardTableWidget(QWidget *papi = Q_NULLPTR);
	void addPortForwardRow( const PortForward &port );
	void setup( const QPortForwardList &portForwardList );
	QPortForwardList portForwardList();
	const QString &lastError() const { return m_lastError;	}
};

#endif // QPORTFORWARDTABLEWIDGET_H
