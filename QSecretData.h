#ifndef QSECRETDATA_H
#define QSECRETDATA_H

#include "QSentences.h"
#include "QConfigData.h"

#include <QDateTime>
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

class QSecretItem : public QStandardItem
{
	QString m_secretID;
public:
	const QString &secretID() const { return m_secretID; }
	void setSecretID(const QString &id) { m_secretID = id; }

	QSecretItem(const QString &txt, const QString &secret_ID)
		: QStandardItem(txt), m_secretID(secret_ID)
	{
	}
};

#define IPPUBLICA_OTROS		(0x01)
#define IPPUBLICA_VOZIP		(0x02)
#define IPPUBLICA_PUERTOS	(0x04)
#define IPPUBLICA_DVR		(0x08)

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
	QString m_comercial;
	QString m_email;
	QString m_SSID;
	QString m_WPass;
	int m_UsaIPPUblica;	// Motivo por el cual usa IP pública (Usa los defines de arriba).
	QString m_notas;
	QString m_perfilOriginal;
	QString m_IPEstatica;
	QString m_IPActiva;
	QString m_sesionID;
	QString m_lastLogOff;
	QString m_uptime;
	QString m_ccliente;	// Código de cliente (Campo clave para enlazarlo a los programas de gestión)
	QSecretItem *firstItem;

	void parseComment(const QString &comment);
	void parsePlainComment(QString cm);
	int firstOf(const QString &txt, const QStringList &ws, int from, int *lenMatched );

public:
	QSecretData():m_UsaIPPUblica(0) {}
	QSecretData(const ROS::QSentence &s);

	const QString &usuario() const				{ return m_usuario;	}
	void setUsuario(const QString &u)			{ m_usuario = u; }

	const QString &contra() const				{ return m_contra; }
	void setContra(const QString &c)			{ m_contra = c; }

	const QString &nombre() const				{ return m_nombre; }
	void setNombre(const QString &n)			{ m_nombre = n; }

	const QString &direccion() const			{ return m_direccion; }
	void setDireccion(const QString &d)			{ m_direccion = d; }

	const QString &telefonos() const			{ return m_telefonos; }
	void setTelefonos(const QString &t)			{ m_telefonos = t; }

	const QString &notas() const				{ return m_notas; }
	void setNotas(const QString &n)				{ m_notas = n; }

	const QString &perfilOriginal() const		{ return m_perfilOriginal; }
	void setPerfilOriginal(const QString &p)	{ m_perfilOriginal = p; }

	const QString &perfilReal() const			{ return m_perfilReal; }
	void setPerfilReal(const QString &p)		{ m_perfilReal = p; }

	const QString &secretID() const				{ return m_secretID; }
	void setSecretID(const QString &id)			{ m_secretID = id; }

	const QString &instalador() const			{ return m_instalador; }
	void setInstalador(const QString &i)		{ m_instalador = i; }

	const QString &poblacion() const			{ return m_poblacion; }
	void setPoblacion(const QString &p)			{ m_poblacion = p; }

	const QString &comercial() const			{ return m_comercial; }
	void setComercial(const QString &c)			{ m_comercial = c; }

	const QString &email() const				{ return m_email; }
	void setEmail(const QString &e)				{ m_email = e; }

	const QString &wPass() const				{ return m_WPass; }
	void setWPass(const QString &w)				{ m_WPass = w; }

	const QString &SSID() const					{ return m_SSID; }
	void setSSID(const QString &s)				{ m_SSID = s; }

	const QString &lastLogedOff() const			{ return m_lastLogOff; }
	void setLastLogedOff(const QString &s)		{ m_lastLogOff = s; }

	const QString &uptime() const				{ return m_uptime; }
	void setUptime(const QString &s)			{ m_uptime = s; }

	const QString &codigoCliente() const		{ return m_ccliente;	}
	void setCodigoCliente(const QString &s)		{ m_ccliente = s;		}

	void setFlagUsaIPPublica(bool b, uint flag);
	QString usaIPPublica() const;
	void setFlagsUsaIPPublica(const QString &s);
	bool usaIPPublica(uint flag) const { return m_UsaIPPUblica & flag; }

	const QString &IPEstatica() const			{ return m_IPEstatica; }
	void setIPEstatica(const QString &i)		{ m_IPEstatica = i; }

	QString IPActiva() const					{ return m_IPActiva; }
	void setIPActiva(const QString &ip)			{ m_IPActiva = ip; }

	bool conectado() const						{ return !IPActiva().isEmpty(); }

	QSecretItem *getFirstItem() const			{ return firstItem; }
	QSecretItem *setFirstItem(QSecretItem *value) { return firstItem = value; }

	const QString &sesionID() const				{ return m_sesionID;}
	void setSesionID(const QString &s)			{ m_sesionID = s; }

	QString comment();
	bool dadoDeBaja() const;

	void toSentence(ROS::QSentence *s);
	bool operator==(const QSecretData &sd)const { return secretID() == sd.secretID(); }
	bool contains(const QString &txt, int filtro) const;
};

class QSecretsList : public QList<QSecretData>
{
public:
	QSecretData findFirstByClientCode(const QString &code, const QSecretData *sdExcepcion);
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

	QSecretItem *setupCellItem(int row, int col, const QString &txt, const QString &secret_id);
public:
	enum Columnas
	{
		ColUsuario,
		ColCCliente,
		ColContrato,
		ColPerfil,
		ColEstado,
		ColIP,
		ColNombre,
		ColDireccion,
		ColPoblacion,
		ColTelefonos,
		ColInstalador,
		ColVendedor,
		ColEMail,
		ColUsaIPPublica,
		ColNotas,
		ColNumber,
		NumColumnas
	};
protected:
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

public:
	QSecretDataModel(int rows, const QStringList &cols, QObject *p = 0);
	void clear();

	void setupTable();
	void fillupTable();
	void addSecret(const QSecretData &sd, bool addToTable = false);
	void delSecret(const ROS::QSentence &s);
	void actualizaUsuario(const ROS::QSentence &s);
	QString usuario(int row);
	QString secretID(int row);
	QSecretData *secretData(int row);
	QSecretData *findDataByUsername(const QString &us);
	QSecretData *findDataBySesionID(const QString &id);
	QSecretData *findDataBySecretID(const QString &id);
	QSecretData *findDataByClientCode(const QString &code, const QSecretData *sdExcepcion);
	int row(const QString &id);

	QStringList poblaciones() const;
	IPv4List ipsEstaticasUsadas() const;

	static QConfigData::NivelUsuario nivelMinimoEdicion(Columnas col);
	const QSecretsList &secrets() const { return m_secrets; }

signals:
	void datoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &secretID, bool *isValid);

};

#define FILTRO_USUARIO		(0x00000001)
#define FILTRO_NOMBRE		(0x00000010)
#define FILTRO_DIRECCION	(0x00000020)
#define FILTRO_POBLACION	(0x00000040)
#define FILTRO_TELEFONOS	(0x00000080)
#define FILTRO_EMAIL		(0x00000100)
#define FILTRO_PERFIL		(0x00000800)
#define FILTRO_IP			(0x00001000)
#define FILTRO_CCLIENTE		(0x00002000)
#define FILTRO_ALTA			(0x00004000)
#define FILTRO_BAJA			(0x00008000)

class QSecretDataTable : public QTableView
{
	Q_OBJECT

	QSecretDataModel *im;
	QSecretDataDelegate delegado;

	friend class QSecretDataDelegate;

private slots:
	void onCellDobleClic(const QModelIndex & index);
	void onCellClicked(const QModelIndex & index);

public:
	QSecretDataTable(QWidget *papi = 0);
	void setupTable();
	void fillupTable() { im->fillupTable(); }
	void clear();
	void addSecret(const ROS::QSentence &s, bool addToTable = false) { im->addSecret(s, addToTable); }
	void delSecret(const ROS::QSentence &s) {im->delSecret(s); }
	void actualizaUsuario(const ROS::QSentence &s) { im->actualizaUsuario(s); }
	QSecretData *findDataByUsername(const QString &us)	{ return im->findDataByUsername(us); }
	QSecretData *findDataBySesionID(const QString &id)	{ return im->findDataBySesionID(id); }
	QSecretData *findDataBySecretID(const QString &id)	{ return im->findDataBySecretID(id); }
	QSecretDataModel &secrets() { return *im; }
	const QSecretDataModel &secrets() const { return *im; }
	int count() const { return im->secrets().count();	}
	QSecretsList secretsList(bool visibles = false) const;
	void filterRows(QString txt, int filtro);

signals:
	void dobleClicUsuario(const QSecretData &sd);
	void clicUsuario(const QSecretData &sd);
	void datoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &secretID,bool*);
};

#endif // QSECRETDATA_H
