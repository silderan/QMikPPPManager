#include "VoIPData.h"

#include <QFile>
#include <QByteArray>

#ifndef QT_NO_DEBUG
#define SAVE_AS_PLAIN_TEXT
#endif

const QString voipFileName( "telefonia" );

bool VoIPDataList::loadTxt()
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

bool VoIPDataList::loadCompressed()
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

				append(voip);
			}
		}
		return true;
	}
	return false;
}

void VoIPDataList::setVoipData(const VoIPData &voipData)
{
	for( VoIPData &d : *this )
	{
		if( d.mSipPhone == voipData.mSipPhone )
		{
			d = voipData;
			return;
		}
	}
	append(voipData);
}

VoIPData VoIPDataList::voipData(const QString &phone) const
{
	for( const VoIPData &d : *this )
	{
		if( d.mSipPhone == phone )
			return d;
	}
	return VoIPData();
}

QStringList VoIPDataList::userPhones(const QString &userName) const
{
	QStringList rtn;
	for( const VoIPData &d : *this )
	{
		if( d.mSecretUsername == userName )
			rtn.append(d.mSipPhone);
	}
	return rtn;
}

QList<VoIPData> VoIPDataList::userVoIPData(const QString &userName) const
{
	QList<VoIPData> rtn;
	Q_ASSERT( !userName.isEmpty() );
	for( const VoIPData &d : *this )
	{
		if( d.mSecretUsername == userName )
			rtn.append(d);
	}
	return rtn;
}

bool VoIPDataList::userWithVoIP(const QString &userName) const
{
	for( const VoIPData &d : *this )
	{
		if( d.mSecretUsername == userName )
			return true;
	}
	return false;
}

QStringList VoIPDataList::unusedPhones() const
{
	QStringList rtn;
	for( const VoIPData &d : *this )
	{
		if( d.mSecretUsername.isEmpty() )
			rtn.append(d.mSipPhone);
	}
	return rtn;
}

void VoIPDataList::setUserPhones(const QString &username, QStringList newPhones)
{
	// Function not only "sets" username on the voipData,
	// also, it clears old phones binded to the username.

	bool needSave = false;
	for( VoIPData &d : *this )
	{
		if( d.mSecretUsername == username )
		{
			if( !newPhones.contains(d.mSipPhone) )
			{
				d.mSecretUsername.clear();
				needSave = true;
			}
		}
		else
		{
			if( newPhones.contains(d.mSipPhone) )
			{
				d.mSecretUsername = username;
				needSave = true;
			}
		}
	}

	if( needSave )
		save();
}

void VoIPDataList::load()
{
	if( !loadCompressed() )
		loadTxt();
}

void VoIPDataList::save(const QString filename) const
{
	QString data;

	for( const VoIPData &d : *this )
	{
		data += QString("%1\t%2\t%3\t%4\t%5\t%6\n")
				.arg(d.mSipPhone)
				.arg(d.mSipUsername)
				.arg(d.mSipPassword)
				.arg(d.mSipServer)
				.arg(d.mSecretUsername)
				.arg(d.mComments);
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

void VoIPDataList::save() const
{
	return save(voipFileName);
}

VoIPDataList gVoipData;
