#ifndef QROSDATABASICS_H
#define QROSDATABASICS_H

#include <QObject>
#include <QString>

#include "Comm.h"

class ROSDataBase
{
public:
	QString m_id;

	virtual void fromSentence(const ROS::QSentence &s);

	virtual ~ROSDataBase()
	{	}
};

class ROSPPPoEManager;

class QROSDataManager : public QObject
{
	Q_OBJECT
	QString m_sentenceTag;
	QObject *m_receiverOb;

protected:
	virtual ROSDataBase *fromSentence(ROS::QSentence &sentence)const = 0;
	virtual ROS::QSentence getallSentence()const = 0;

private slots:
	void onDataReceived(ROS::QSentence &sentence);

public:
	QROSDataManager(ROS::Comm *papi, const QString &sentenceTag) : QObject(papi), m_sentenceTag(sentenceTag), m_receiverOb(Q_NULLPTR)
	{	}

	ROS::Comm *rosAPI() { return dynamic_cast<ROS::Comm *>(parent());	}
	const QString &sentenceTag() const { return m_sentenceTag;	}

	void requestData(QObject *receiverOb = Q_NULLPTR, const char *receivedOneSlot = Q_NULLPTR, const char *receivedAllSlot = Q_NULLPTR, const char *errorSlot = Q_NULLPTR);

signals:
	void reply( ROSDataBase &userData, ROS::Comm *rosAPI );
	void done( ROS::Comm *rosAPI );
	void error( QString errorString, ROS::Comm *rosAPI );
};


#endif // QROSDATABASICS_H
