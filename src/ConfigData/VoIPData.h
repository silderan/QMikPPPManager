#ifndef VOIPDATA_H
#define VOIPDATA_H

#include <QString>
#include <QMap>
#include <QList>

struct VoIPData
{
	QString mSipPhone;
	QString mSipUsername;
	QString mSipPassword;
	QString mSipServer;

	QString mSecretUsername;
	QString mComments;
};

class VoIPDataList : public QList<VoIPData>
{
	bool loadTxt();
	bool loadCompressed();

public:
	void setVoipData(const VoIPData &voipData);
	VoIPData voipData(const QString &phone) const;
	QStringList userPhones(const QString &userName) const;
	QList<VoIPData> userVoIPData(const QString &userName) const;
	bool userWithVoIP(const QString &userName) const;
	QStringList unusedPhones()const;
	void setUserPhones(const QString &username, QStringList phones);

	void load();
	void save(const QString filename) const;
	void save() const;
};

extern VoIPDataList gVoipData;

#endif // VOIPDATA_H
