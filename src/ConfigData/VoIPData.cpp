#include "VoIPData.h"

#include <QFile>
#include <QByteArray>

#ifndef QT_NO_DEBUG
#define SAVE_AS_PLAIN_TEXT
#endif

const QString voipFileName( "telefonia" );

bool VoIPDataMap::loadTxt()
{
	QFile f(QString("%1.txt").arg(voipFileName));
	if( f.open(QIODevice::ReadOnly) )
	{
		VoIPData voip;
		clear();

		for( const QByteArray &line : f.readAll().split('\n') )
		{
			QStringList words = QString::fromLatin1(line).split('\t');
			if( (words.count() >= 6) && (words[0].count() >= 6) )
			{
				voip.mSipPhone			= words[0];
				voip.mSipUsername		= words[1];
				voip.mSipPassword		= words[2];
				voip.mSipServer			= words[3];
				voip.mSecretUsername	= words[4];
				voip.mComments			= words[5];

				setVoipData(voip);
			}
		}
		return true;
	}
	return false;
}

bool VoIPDataMap::loadCompressed()
{
	QFile f(QString("%1.voip").arg(voipFileName));
	if( f.open(QIODevice::ReadOnly) )
	{
		VoIPData voip;
		clear();

		for( const QByteArray &line : qUncompress(f.readAll()).split('\n') )
		{
			QStringList words = QString::fromLatin1(line).split('\t');
			if( (words.count() >= 6) && (words[0].count() >= 6) )
			{
				voip.mSipPhone			= words[0];
				voip.mSipUsername		= words[1];
				voip.mSipPassword		= words[2];
				voip.mSipServer			= words[3];
				voip.mSecretUsername	= words[4];
				voip.mComments			= words[5];

				setVoipData(voip);
			}
		}
		return true;
	}
	return false;
}

QStringList VoIPDataMap::userPhones(const QString &userName) const
{
	QStringList rtn;
	QMapIterator<QString, VoIPData> it(*this);
	while( it.hasNext() )
	{
		it.next();
		if( it.value().mSecretUsername == userName )
			rtn.append(it.value().mSipPhone);
	}
	return rtn;
}

QList<VoIPData> VoIPDataMap::userVoIPData(const QString &userName) const
{
	QList<VoIPData> rtn;
	QMapIterator<QString, VoIPData> it(*this);
	Q_ASSERT( !userName.isEmpty() );
	while( it.hasNext() )
	{
		it.next();
		if( it.value().mSecretUsername == userName )
			rtn.append(it.value());
	}
	return rtn;
}

bool VoIPDataMap::userWithVoIP(const QString &userName) const
{
	QMapIterator<QString, VoIPData> it(*this);
	while( it.hasNext() )
	{
		it.next();
		if( it.value().mSecretUsername == userName )
			return true;
	}
	return false;
}

QStringList VoIPDataMap::unusedPhones() const
{
	QStringList rtn;
	QMapIterator<QString, VoIPData> it(*this);
	while( it.hasNext() )
	{
		it.next();
		if( it.value().mSecretUsername.isEmpty() )
			rtn.append(it.key());
	}
	return rtn;
}

void VoIPDataMap::setUserPhones(const QString &username, QStringList newPhones)
{
	// Function not only "sets" username on the voipData.
	// also, it clear "old" data.
	// Maybe there are more optimized ways to do that, but it's not a problem because it's not done massively

	bool needSave = false;
	for( const QString &phone : userPhones(username) )
	{
		if( !newPhones.contains(phone) )
		{
			operator[](phone).mSecretUsername.clear();
			needSave = true;
		}
		else
			newPhones.removeOne(phone);
	}

	if( newPhones.count() )
	{
		needSave = true;
		for( const QString &phone : newPhones )
		{
			operator[](phone).mSecretUsername = username;
		}
	}

	if( needSave )
		save();
}

void VoIPDataMap::load()
{
	if( !loadCompressed() )
		loadTxt();
}

void VoIPDataMap::save(const QString filename) const
{
	QString data;
	QMapIterator<QString, VoIPData> it(*this);
	while( it.hasNext() )
	{
		it.next();
		data += QString("%1\t%2\t%3\t%4\t%5\t%6\n")
				.arg(it.value().mSipPhone)
				.arg(it.value().mSipUsername)
				.arg(it.value().mSipPassword)
				.arg(it.value().mSipServer)
				.arg(it.value().mSecretUsername)
				.arg(it.value().mComments);
	}

	QFile fCompressed(QString("%1.voip").arg(filename));
	if( fCompressed.open(QIODevice::WriteOnly) )
		fCompressed.write(qCompress(data.toLatin1()));
#ifdef SAVE_AS_PLAIN_TEXT
	QFile fText(QString("%1.txt").arg(filename));
	if( fText.open(QIODevice::WriteOnly) )
		fText.write(data.toLatin1());
#endif
}

void VoIPDataMap::save() const
{
	return save(voipFileName);
}

VoIPDataMap gVoipData;
