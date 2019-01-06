#ifndef ROSDATAMANAGERBASE_H
#define ROSDATAMANAGERBASE_H

#include <QString>
#include <QMap>
#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>

#include "../ROSAPI/QSentences.h"

template <typename T>
class ROSDataManagerBase
{
	QObject *m_ob;
	QString m_routerName;
	QString m_sentenceTag;
	int m_doneSlot;
	int m_replySlot;
	int m_errorSlot;
	QMap<QString, T> m_idDataMap;
	bool m_clearOnDone;

	int setupSlot(const char *slotFunction)
	{
		Q_ASSERT( m_ob != Q_NULLPTR );

		if( slotFunction != Q_NULLPTR )
		{
			while( isdigit(*slotFunction) )
				slotFunction++;
#ifndef QT_NO_DEBUG
			if( m_ob->metaObject()->indexOfMethod(slotFunction) == -1 )
				qWarning("Función %s no localizada en %s", slotFunction, m_ob->metaObject()->className());
			else
#endif
			return m_ob->metaObject()->indexOfMethod(slotFunction);
		}
		return -1;
	}

public:
	ROSDataManagerBase() : m_clearOnDone(true)
	{	}

	inline const QString &sentenceTag() { return m_sentenceTag;	}

	inline T rosData(const QString &dataID)			{ return m_idDataMap.value(dataID, T(QString("InvalidROSData")));	}
	inline QList<T> rosDataList()					{ return m_idDataMap.values();		}
	inline const QMap<QString, T> &rosDataMap()		{ return m_idDataMap;				}

	void onDone(const ROS::QSentence &sentence)
	{
		if( m_ob && (m_doneSlot != -1) && sentence.tag() == m_sentenceTag )
		{
			Q_ASSERT( !m_routerName.isEmpty() );

			m_ob->metaObject()->method(m_doneSlot).invoke(m_ob, Q_ARG(QString, m_routerName) );
			if( m_clearOnDone )
				m_ob = Q_NULLPTR;
		}
	}
	void onReply(const ROS::QSentence &sentence)
	{
		Q_ASSERT( !sentence.getID().isEmpty() );

		if( m_ob && (m_replySlot != -1) && (sentence.tag() == m_sentenceTag) )
		{
			Q_ASSERT( !m_routerName.isEmpty() );

			T t(m_routerName, sentence);

			if( t.deleting() )
				m_idDataMap.remove(t.dataID());
			else
				m_idDataMap.insert(sentence.getID(), t);

			m_ob->metaObject()->method(m_replySlot).invoke(m_ob, Q_ARG(QString, m_routerName), Q_ARG(T*, &t));
		}
	}

	void setup(QObject *receiverOb, const QString &routerName, const QString &sentenceTag, const char *replySlot, const char *doneSlot, const char *errorSlot, bool clearOnDone)
	{
		Q_ASSERT( (m_ob = receiverOb)!= Q_NULLPTR );
		Q_ASSERT( !(m_routerName = routerName).isEmpty() );

		m_doneSlot			= setupSlot(doneSlot);
		m_replySlot			= setupSlot(replySlot);
		m_errorSlot			= setupSlot(errorSlot);
		m_sentenceTag		= sentenceTag;
		m_clearOnDone		= clearOnDone;
	}
};
#endif // ROSDATAMANAGERBASE_H

