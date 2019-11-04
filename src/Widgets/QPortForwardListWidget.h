#ifndef QPORTFORWARDLISTWIDGET_H
#define QPORTFORWARDLISTWIDGET_H

#include <QListWidget>

#include "../Utils/PortForward.h"

class QListWidgetItem;

class QPortForwardListWidget : public QListWidget
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
	void parsePortLine(const QStringList &words, int i);
	void onDoubleClic(QListWidgetItem *item);

public:
	explicit QPortForwardListWidget(QWidget *papi = Q_NULLPTR);
	void addPortForwardRow( const PortForward &port );
	void setup( const QPortForwardList &portForwardList );
	QPortForwardList portForwardList();
	const QString &lastError() const { return m_lastError;	}
	void parsePortText(const QString &txt);

public slots:
	void editPortRequest(int row = -1);
};

#endif // QPORTFORWARDLISTWIDGET_H
