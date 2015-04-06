#ifndef QSECRETDATA_H
#define QSECRETDATA_H

#include "QSentences.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>


class QSecretItem : public QStandardItem
{
	QString m_secretID;
public:
	const QString &secretID() const { return m_secretID; }

	QSecretItem(const QString &txt, const QString &secret_ID)
		: QStandardItem(txt), m_secretID(secret_ID)
	{
	}
};

class QSecretData
{
	QString m_secretID;
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
	QString m_sesionID;
	QSecretItem *firstItem;

	void parseComment(const QString &comment);
	void parsePlainComment(QString cm);
	int firstOf(const QString &txt, const QStringList &ws, int from, int *lenMatched );

public:
	QSecretData():m_VozIP(false) {}
	QSecretData(const ROS::QSentence &s);

	QString usuario() const				{ return m_usuario;	}
	void setUsuario(const QString &u)	{ m_usuario = u; }

	QString nombre() const				{ return m_nombre; }
	void setNombre(const QString &n)	{ m_nombre = n; }

	QString direccion() const			{ return m_direccion; }
	void setDireccion(const QString &d)	{ m_direccion = d; }

	QString telefonos() const			{ return m_telefonos; }
	void setTelefonos(const QString &t) { m_telefonos = t; }

	QString notas() const				{ return m_notas; }
	void setNotas(const QString &n)		{ m_notas = n; }

	QString perfilOriginal() const		{ return m_perfilOriginal; }
	void setPerfilOriginal(const QString &p) { m_perfilOriginal = p; }

	QString perfilReal() const			{ return m_perfilReal; }
	void setPerfilReal(const QString &p){ m_perfilReal = p; }

	QString secretID() const			{ return m_secretID; }
	void setSecretID(const QString &id)	{ m_secretID = id; }

	QString instalador() const			{ return m_instalador; }
	void setInstalador(const QString &i){ m_instalador = i; }

	QString poblacion() const			{ return m_poblacion; }
	void setPoblacion(const QString &p)	{ m_poblacion = p; }

	QString conseguidor() const			{ return m_conseguidor; }
	void setConseguidor(const QString &c){m_conseguidor = c; }

	QString email() const				{ return m_email; }
	void setEmail(const QString &e)		{ m_email = e; }

	bool VozIP() const					{ return m_VozIP; }
	void setVozIP(bool v)				{ m_VozIP = v; }

	QString IPEstatica() const			{ return m_IPEstatica; }
	void setIPEstatica(const QString &i){ m_IPEstatica = i; }

	QString IPActiva() const			{ return m_IPActiva; }
	void setIPActiva(const QString &ip)	{ m_IPActiva = ip; }

	QSecretItem *getFirstItem() const	{ return firstItem; }
	QSecretItem *setFirstItem(QSecretItem *value) { return firstItem = value; }

	QString sesionID() const { return m_sesionID;}
	void setSesionID(const QString &s) { m_sesionID = s; }

	QString comment();
	bool activo() const;
};

class QSecretsList : public QList<QSecretData>
{
public:
	QSecretsList()
	{

	}
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
	Q_OBJECT

	QSecretsList m_secrets;
	QStringList m_nombresColumnas;

	void addSecretToTable(QSecretData &s, int row);
	friend class QSecretDataDelegate;

public:
	enum Columnas
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
protected:
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
	QString usuario(int row);
	QSecretData *secretData(int row);
	QString secretID(int row);

public:
	QSecretDataModel(int rows, const QStringList &cols, QObject *p = 0);

	void setupTable();
	void fillupTable();
	void setColumnas(const QStringList &nombresColumnas) { m_nombresColumnas = nombresColumnas; }
	void addSecret(const ROS::QSentence &s, bool addToTable = false);
	void actualizaUsuario(const ROS::QSentence &s);
	QSecretData *findDataByUsername(const QString &us);
	QSecretData *findDataBySesionID(const QString &id);
	QSecretData *findDataBySecretID(const QString &id);

signals:
	void datoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &secretID);
};

class QSecretDataTable : public QTableView
{
	Q_OBJECT

	QSecretDataModel *im;
	QSecretDataDelegate delegado;

	friend class QSecretDataDelegate;

public:
	QSecretDataTable(QWidget *papi = 0);
	void setupTable();
	void fillupTable() { im->fillupTable(); }
	void addSecret(const ROS::QSentence &s, bool addToTable = false) { im->addSecret(s, addToTable); }
	void actualizaUsuario(const ROS::QSentence &s) { im->actualizaUsuario(s); }
	QSecretData *findDataByUsername(const QString &us)	{ return im->findDataByUsername(us); }
	QSecretData *findDataBySesionID(const QString &id)	{ return im->findDataBySesionID(id); }
	QSecretData *findDataBySecretID(const QString &id)	{ return im->findDataBySecretID(id); }

signals:
	void datoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &secretID);
};

#endif // QSECRETDATA_H
