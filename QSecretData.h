#ifndef QSECRETDATA_H
#define QSECRETDATA_H

#include "QSentences.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

class QSecretData
{
	QString m_ID;
	QString m_instalador;
	QString m_usuario;
	QString m_contra;
	QString m_perfilReal;
	QString m_nombre;
	QString m_direccion;
	QString m_poblacion;
	QString m_telefonos;
	QString m_conseguidor;
	QString m_email;
	bool m_VozIP;
	QString m_notas;
	QString m_perfilOriginal;
	QString m_IPEstatica;
	QString m_IPActiva;

	void parseComment(const QString &comment);
	void parsePlainComment(QString cm);
	int firstOf(const QString &txt, const QStringList &ws, int from, int *lenMatched );

public:
	QSecretData():m_VozIP(false) {}
	QSecretData(const ROS::QSentence &s);

	QString usuario() const				{ return m_usuario;	}
	void setUsuario(const QString &u)	{ m_usuario = u; }
	QString nombre() const;
	void setNombre(const QString &nombre);
	QString direccion() const;
	void setDireccion(const QString &direccion);
	QString telefonos() const;
	void setTelefonos(const QString &telefonos);
	QString notas() const;
	void setNotas(const QString &notas);
	QString perfilOriginal() const;
	void setPerfilOriginal(const QString &perfilOriginal);
	QString perfilReal() const;
	void setPerfilReal(const QString &perfil);
	QString comment();
	bool activo() const;
	QString ID() const;
	void setID(const QString &ID);
	QString instalador() const;
	void setInstalador(const QString &instalador);
	QString poblacion() const;
	void setPoblacion(const QString &poblacion);
	QString conseguidor() const;
	void setConseguidor(const QString &conseguidor);
	QString email() const;
	void setEmail(const QString &email);
	bool VozIP() const;
	void setVozIP(bool VozIP);
	QString IPEstatica() const;
	void setIPEstatica(const QString &IPEstatica);
	QString IPActiva() const;
	void setIPActiva(const QString &IPActiva);
};

class QSecretsList : public QList<QSecretData>
{
public:
	QSecretsList()
	{

	}
};

class QPerfilData
{
	QString m_nombre;

public:
	const QString &nombre() const { return m_nombre; }
	void setNombre(const QString &n) { m_nombre = n; }
	QPerfilData(const ROS::QSentence &s)
	{
		m_nombre = s.attribute("name");
	}
	bool operator==(const QString &nombre) const
	{
		return m_nombre == nombre;
	}
};

class QPerfilesList : public QList<QPerfilData>
{
	QStringList m_nombresPerfiles;

public:
	void append(const QPerfilData &s);
	bool contains(const QString &s) const;
	const QStringList &nombresPerfiles()const { return m_nombresPerfiles; }
};

class QSecretDataDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QSecretDataDelegate(QObject *p);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
						  const QModelIndex &index) const Q_DECL_OVERRIDE;

	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
					  const QModelIndex &index) const Q_DECL_OVERRIDE;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class QSecretDataModel : public QStandardItemModel
{
	QSecretsList m_secrets;
	QPerfilesList m_perfiles;
	QStringList m_nombresColumnas;

	void addSecretToTable(const QSecretData &s, int row);
	friend class QSecretDataDelegate;

	enum columnas
	{
		ColUsuario,
		ColPerfil,
		ColEstado,
		ColIP,
		ColNombre,
		ColDireccion,
		ColPoblacion,
		ColTelefonos,
		ColInstalador,
		ColConseguidor,
		ColEMail,
		ColVozIP,
		ColNotas,
		NumColumnas
	};

public:
	QSecretDataModel(int rows, const QStringList &cols, QObject *p = 0);

	void setupTable();
	void fillupTable();
	void setColumnas(const QStringList &nombresColumnas) { m_nombresColumnas = nombresColumnas; }
	void addPerfil(const ROS::QSentence &s);
	void addSecret(const ROS::QSentence &s, bool addToTable = false);
};

class QSecretDataTable : public QTableView
{
	QSecretDataModel *im;
	QSecretDataDelegate delegado;

	friend class QSecretDataDelegate;

public:
	QSecretDataTable(QWidget *papi = 0)
		: QTableView(papi), delegado(papi)
	{
		setupTable();
		setItemDelegate(&delegado);
	}
	void setupTable();
	void fillupTable() { im->fillupTable(); }
	void addPerfil(const ROS::QSentence &s) {im->addPerfil(s); }
	void addSecret(const ROS::QSentence &s, bool addToTable = false) { im->addSecret(s, addToTable); }
};

#endif // QSECRETDATA_H
