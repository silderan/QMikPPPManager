#ifndef VOIPDATA_H
#define VOIPDATA_H

#include <QString>
#include <QMap>

struct VoIPData
{
	QString mSipPhone;
	QString mSipUsername;
	QString mSipPassword;
	QString mSipServer;

	QString mSecretUsername;
	QString mComments;
};

class VoIPDataMap : public QMap<QString, VoIPData>
{
	bool loadTxt();
	bool loadCompressed();

public:
	void setVoipData(const VoIPData &voipData)			{ insert(voipData.mSipPhone, voipData);	}
	VoIPData voipData(const QString &phone) const		{ return value(phone);	}
	QStringList userPhones(const QString &userName) const;
	QList<VoIPData> userVoIPData(const QString &userName) const;
	bool userWithVoIP(const QString &userName) const;
	QStringList unusedPhones()const;
	void setUserPhones(const QString &username, QStringList phones);

	void load();
	void save(const QString filename) const;
	void save() const;
};

extern VoIPDataMap gVoipData;

#endif // VOIPDATA_H
