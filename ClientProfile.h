#ifndef CLIENTPROFILE_H
#define CLIENTPROFILE_H

#include <QStringList>

#include "QSentences.h"
#include "QIniFile.h"

struct ClientProfileData
{
private:
	QString m_name;
	QString m_group;
	quint32 m_txKbps;	// Carga
	quint32 m_rxKbps;	// Descarga
	bool m_disabled;	// Si este perfil es para usuarios dados de baja.
	bool m_internal;	// Si este perfil es interno y no ha de usarse.
	bool m_default;		// Si este perfil es el perfil por defecto.

public:
	const QString &name() const				{ return m_name;	}
	void setName(const QString &n)			{ m_name = n;		}

	const QString &group() const			{ return m_group;	}
	void setGroup(const QString &group)		{ m_group = group;	}

	quint32 upload() const					{ return m_txKbps;	}
	void setUpload(quint32 upKbps)			{ m_txKbps = upKbps;}

	quint32 download() const				{ return m_rxKbps;	}
	void setDownload(quint32 dwKbps)		{ m_rxKbps = dwKbps;}

	bool isInternal() const					{ return m_internal;}
	void setInternal(bool i)				{ m_internal = i;	}

	bool isDisabled() const					{ return m_disabled;}
	void setDisabled(bool d)				{ m_disabled = d;	}

	bool isDefault() const					{ return m_default;	}
	void setDefault(bool d)					{ m_default = d;	}

	ClientProfileData()
		: m_disabled(false),
		  m_internal(false),
		  m_default(false)
	{	}
	explicit ClientProfileData(const ROS::QSentence &s)
		: m_disabled(false),
		  m_internal(false),
		  m_default(false)
	{
		m_name = s.attribute("name");
	}
	explicit ClientProfileData(const QString &saveString)
	{
		fromSaveString(saveString);
	}
	bool operator==(const QString &nombre) const
	{
		return m_name == nombre;
	}
	bool operator==(const ClientProfileData &clientProfileData) const
	{
		return m_name == clientProfileData.m_name;
	}

	QString saveString()const;
	void fromSaveString(const QString &saveString);
};

class QClientProfileList : public QList<ClientProfileData>
{
public:
	void append(const ClientProfileData &s);
	void append(const ROS::QSentence &s)	{ append( ClientProfileData(s) ); }

	bool contains(const QString &s) const;

	void save(QIniData &cnfgData) const;
	void load(const QIniData &cnfgData);

	int indexOfDisabled()const;
	int indexOfDefault()const;

	void setDisabledProfile(int index);
	void setDefaultProfile(int index);
	void setProfileGroupName(int index, const QString &name);

	QStringList profileNames()const;
	// Return all profile names excluding disabled and internals.
	QStringList regularProfileNames()const;
};

#endif // CLIENTPROFILE_H
