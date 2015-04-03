#include "QSecretData.h"

#include "QConfigData.h"

QString QSecretData::direccion() const
{
	return m_direccion;
}

void QSecretData::setDireccion(const QString &Direccion)
{
	m_direccion = Direccion;
}

QString QSecretData::telefonos() const
{
	return m_telefonos;
}

void QSecretData::setTelefonos(const QString &Telefonos)
{
	m_telefonos = Telefonos;
}

QString QSecretData::notas() const
{
	return m_notas;
}

void QSecretData::setNotas(const QString &Notas)
{
	m_notas = Notas;
}


QString QSecretData::perfilOriginal() const
{
	return m_perfilOriginal;
}

void QSecretData::setPerfilOriginal(const QString &perfilOriginal)
{
	m_perfilOriginal = perfilOriginal;
}

QString QSecretData::perfilReal() const
{
	return m_perfilReal;
}

void QSecretData::setPerfilReal(const QString &perfil)
{
	m_perfilReal = perfil;
}

QString QSecretData::nombre() const
{
	return m_nombre;
}

void QSecretData::setNombre(const QString &Nombre)
{
	m_nombre = Nombre;
}


QString QSecretData::ID() const
{
	return m_ID;
}

void QSecretData::setID(const QString &ID)
{
	m_ID = ID;
}

QString QSecretData::instalador() const
{
	return m_instalador;
}

void QSecretData::setInstalador(const QString &instalador)
{
	m_instalador = instalador;
}

QString QSecretData::poblacion() const
{
	return m_poblacion;
}

void QSecretData::setPoblacion(const QString &poblacion)
{
	m_poblacion = poblacion;
}
void QSecretData::parseComment(const QString &comment)
{
	QStringList fields = comment.split("$");
	if( fields.count() > 1 )
	{
		switch( fields.count() )
		{
		default:
			setNotas(fields[6]);
		case 6:
			setInstalador(fields[5]);
		case 5:
			setTelefonos(fields[4]);
		case 4:
			setPerfilReal(fields[3]);
		case 3:
			setDireccion(fields[2]);
		case 2:
			setNombre(fields[1]);
			setPerfilOriginal(fields[0]);
			break;
		}
	}
	else
	{
		setPerfilOriginal((perfilReal().isEmpty() || (perfilReal() == gGlobalConfig.getPerfilInactivo())) ? gGlobalConfig.getPerfilBasico() : perfilReal());
		parsePlainComment(comment);
	}
	if( perfilReal() != gGlobalConfig.getPerfilInactivo() )
		setPerfilOriginal(perfilReal());
}

int QSecretData::firstOf(const QString &txt, const QStringList &ws, int from, int *lenMatched)
{
	int i = -1;
	foreach( QString w, ws )
	{
		int f = txt.indexOf(w, from, Qt::CaseInsensitive);
		if( (f != -1) && ((i == -1) || (f < i)) )
		{
			i = f;
			*lenMatched = w.count();
		}
	}
	return i;
}

void QSecretData::parsePlainComment(QString cm)
{
	int len;
	int i = firstOf(cm, QStringList() << ". " << "." << "C/ " << "C/", 0, &len);
	if( i != -1 )
	{
		setNombre(cm.left(i));
		cm = cm.mid(i+len);
	}

	i = firstOf(cm, QStringList()
				<< "benicarló" << "benicarlo"
				<< "Peñíscola" << "Penyíscola" << "peníscola"
				<< "Peñiscola" << "Penyiscola" << "peniscola"
				<< "Vinaròs" << "Vinaros" << "Vinarós" << "Vinaroz"
				<< "sant jordi"
				<< "ulldecona"
				<< "la cenia" << "la cénia" << "la cènia"
				<< "traiguera",
				0, &len);
	if( i != -1 )
	{
		setPoblacion(cm.mid(i, len));
		cm = cm.remove(i, len);
	}

	for( i = 0; i < cm.count(); i++ )
	{
		if( (cm[i] == '9') || (cm[i] == '6') )
		{
			for( len = i+1; ((len - i) <= 9) && (len < cm.count()); len++ )
			{
				if( (cm[len].toLatin1() < '0') || (cm[len].toLatin1() > '9') )
					break;
			}
			if( (len - i) == 9 )
			{
				if( telefonos().count() )
					setTelefonos(QString("%1, %2").arg(telefonos(), cm.mid(i, 9)));
				else
					setTelefonos(cm.mid(i, 9));
				cm.remove(i, 9);
			}
			else
				i = len;
		}
		if( cm[i] == '0' )
		{
			for( len = i+1; ((len - i) <= 13) && (len < cm.count()); len++ )
			{
				if( (cm[len].toLatin1() < '0') || (cm[len].toLatin1() > '9') )
					break;
			}
			if( (len - i) == 13 )
			{
				if( telefonos().count() )
					setTelefonos(QString("%1, %2").arg(telefonos(), cm.mid(i, 13)));
				else
					setTelefonos(cm.mid(i, 13));
				cm.remove(i, 13);
			}
			else
				i = len;
		}
	}
	setDireccion(cm);
}

QString QSecretData::comment()
{
	if( nombre().isEmpty() )
		return notas();

	return QString("%1$%2$%3$%4$%5$%6$%7")
			.arg(perfilReal())
			.arg(nombre())
			.arg(direccion())
			.arg(poblacion())
			.arg(telefonos())
			.arg(instalador())
			.arg(notas());
}

bool QSecretData::activo() const
{
	return perfilReal() != gGlobalConfig.getPerfilInactivo();
}

QSecretData::QSecretData(const ROS::QSentence &s)
	: m_ID(s.getID()),
	  m_instalador("no_definido"),
	  m_usuario(s.attribute("name")),
	  m_contra(s.attribute("password")),
	  m_perfilReal(s.attribute("profile"))
{
	parseComment(s.attribute("comment"));
}

#include <QStyleOptionViewItem>
#include <QSpinBox>

QSecretDataDelegate::QSecretDataDelegate(QObject *p)
	: QStyledItemDelegate(p)
{

}

QWidget *QSecretDataDelegate::createEditor(QWidget *parent,
									   const QStyleOptionViewItem &/* option */,
									   const QModelIndex &/* index */) const
{
	QSpinBox *editor = new QSpinBox(parent);
	editor->setFrame(false);
	editor->setMinimum(0);
	editor->setMaximum(100);

	return editor;
}

void QSecretDataDelegate::setEditorData(QWidget *editor,
										const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();

	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

void QSecretDataDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
								   const QModelIndex &index) const
{
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();
	int value = spinBox->value();

	model->setData(index, value, Qt::EditRole);
}

void QSecretDataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}


#include <QHeaderView>
void QSecretDataTable::setupTable()
{
	im = new QStandardItemModel(0, 10);
	setModel(im);
}

void QSecretDataTable::fillupTable()
{
	im->clear();
	im->setColumnCount(NumColumnas);
	im->setRowCount(secrets.count());

	blockSignals(true);
	for(int i = 0; i < secrets.count(); i++ )
	{
		im->setItem(0, ColUsuario, new QStandardItem(secrets[i].usuario()));
	}
	blockSignals(false);
}

void QSecretDataTable::addPerfil(const ROS::QSentence &s)
{

}

void QSecretDataTable::addSecret(const ROS::QSentence &s, bool addToTable)
{
	QString nombre = s.attribute("name");
	if( (nombre != gGlobalConfig.getPerfilInactivo()) && !perfiles.contains(nombre) )
		secrets.append(s);
}
