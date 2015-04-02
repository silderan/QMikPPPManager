#ifndef QSECRETDATA_H
#define QSECRETDATA_H

#include "QSentences.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

class QSecretData : public QStandardItemModel
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
	QString m_notas;
	QString m_perfilOriginal;

	void parseComment(const QString &comment);
	void parsePlainComment(QString cm);
	int firstOf(const QString &txt, const QStringList &ws, int from, int *lenMatched );

public:
	QSecretData(){}
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
};

class QSentenceList : public QList<QSecretData>
{
public:
	QSentenceList()
	{

	}
};

class QSecretDataDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QSecretDataDelegate(QObject *parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
						  const QModelIndex &index) const Q_DECL_OVERRIDE;

	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
					  const QModelIndex &index) const Q_DECL_OVERRIDE;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class QSecretDataTable : public QWidget
{
	QSentenceList secrets;
	QTableView vistaTabla;

public:
	QSecretDataTable(QObject *papi = 0)
		: QWidget(papi)
	{
		setupTable();
	}
	void setupTable();
};

#endif // QSECRETDATA_H