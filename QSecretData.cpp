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

QString QSecretData::conseguidor() const
{
	return m_conseguidor;
}

void QSecretData::setConseguidor(const QString &conseguidor)
{
	m_conseguidor = conseguidor;
}

QString QSecretData::email() const
{
	return m_email;
}

void QSecretData::setEmail(const QString &email)
{
	m_email = email;
}

bool QSecretData::VozIP() const
{
	return m_VozIP;
}

void QSecretData::setVozIP(bool VozIP)
{
	m_VozIP = VozIP;
}

QString QSecretData::IPEstatica() const
{
	return m_IPEstatica;
}

void QSecretData::setIPEstatica(const QString &IPEstatica)
{
	m_IPEstatica = IPEstatica;
}

QString QSecretData::IPActiva() const
{
	return m_IPActiva;
}

void QSecretData::setIPActiva(const QString &IPActiva)
{
	m_IPActiva = IPActiva;
}
void QSecretData::parseComment(const QString &comment)
{
	QStringList fields = comment.split("$");
	if( fields.count() > 1 )
	{
		switch( fields.count() )
		{
		default:
			setNotas(fields[9]);
		case 9:
			setVozIP(fields[7]=="vozip");
		case 8:
			setEmail(fields[8]);
		case 7:
			setConseguidor(fields[6]);
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
	// Primero intentamos sacar el nombre. Quizá esté a la izquierda, antes del primer .
	int len;
	int i;
	// Buscamos población.
	i = firstOf(cm, QStringList()
				<< "Càlig" << "Calig" << "càlig" << "calig"
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

	i = firstOf(cm, QStringList() << ". " << "." << "C/ " << "C/" << "Urb" << "urb", 0, &len);
	if( i != -1 )
	{
		setNombre(cm.left(i));
		cm = cm.mid(i+len);
	}

	// Busquemos el correo.
	i = cm.indexOf("@");
	if( i != -1 )
	{
		len = i;
		while( i >= 0 )
			if( cm[i] == ' ' )
				break;
			else
				i--;
		while( len < cm.count() )
			if( cm[len] == ' ' )
				break;
			else
				len++;
		setEmail(cm.mid(i, len-i));
		cm.remove(cm.mid(i, len-i));
	}

	// Buscamos conseguidor.
	i = cm.indexOf("metrocom", 0, Qt::CaseInsensitive);
	if( i != - 1)
	{
		setConseguidor(cm.mid(i, 8));
		cm = cm.remove(i, 8);
	}

	// Buscamos teléfono.
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
	setDireccion(cm.remove("()"));
}

QString QSecretData::comment()
{
	if( nombre().isEmpty() )
		return notas();

	return QString("%1$%2$%3$%4$%5$%6$%7$%8$%9$%10")
			.arg(perfilReal())
			.arg(nombre())
			.arg(direccion())
			.arg(poblacion())
			.arg(telefonos())
			.arg(instalador())
			.arg(conseguidor())
			.arg(email())
			.arg(VozIP()?"vozip":"no")
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
	  m_perfilReal(s.attribute("profile")),
	  m_IPEstatica(s.attribute("remote-address")),
	  m_VozIP(false)
{
	parseComment(s.attribute("comment"));
}

#include <QStyleOptionViewItem>
#include <QSpinBox>

QSecretDataDelegate::QSecretDataDelegate(QObject *p)
	: QStyledItemDelegate(p)
{

}

#include <QComboBox>
#include <QLineEdit>
QWidget *QSecretDataDelegate::createEditor(QWidget *parent,
									   const QStyleOptionViewItem &/*option*/,
									   const QModelIndex &index ) const
{
	const QSecretDataModel *model = static_cast<const QSecretDataModel*>(index.model());
	if( index.column() == QSecretDataModel::ColPerfil )
	{
		QComboBox *cb = new QComboBox(parent);
		Q_ASSERT(cb);
		const QStringList &perfiles = model->m_perfiles.nombresPerfiles();
		foreach( QString p, perfiles )
			cb->addItem(p);
		return cb;
	}
	else
	if( index.column() == QSecretDataModel::ColEstado )
	{
		QComboBox *cb = new QComboBox(parent);
		Q_ASSERT(cb);
		cb->addItems(QStringList() << "activo" << "inactivo");
		return cb;
	}
	else
	if( index.column() == QSecretDataModel::ColVozIP )
	{
		QComboBox *cb = new QComboBox(parent);
		Q_ASSERT(cb);
		cb->addItems(QStringList() << "Sí" << "No");
		return cb;
	}
	else
	{
		QLineEdit *le = new QLineEdit(parent);
		Q_ASSERT(le);
		return le;
	}
}

void QSecretDataDelegate::setEditorData(QWidget *editor,
										const QModelIndex &index) const
{
	if( index.column() == QSecretDataModel::ColPerfil )
	{
		QString perfil = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *cb = static_cast<QComboBox*>(editor);
		cb->setCurrentText(perfil);
	}
	else
	if( index.column() == QSecretDataModel::ColEstado )
	{
		QString estado = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *cb = static_cast<QComboBox*>(editor);
		cb->setCurrentIndex(estado == "activo" ? 0 : 1);
	}
	else
	if( index.column() == QSecretDataModel::ColVozIP )
	{
		QString estado = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *cb = static_cast<QComboBox*>(editor);
		cb->setCurrentIndex(estado == "Sí" ? 0 : 1);
	}
	else
	{
		QString txt = index.model()->data(index, Qt::EditRole).toString();
		QLineEdit *le = static_cast<QLineEdit*>(editor);
		le->setText(txt);
	}
}

void QSecretDataDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
								   const QModelIndex &index) const
{
	if( index.column() == QSecretDataModel::ColPerfil )
	{
		QComboBox *cb = static_cast<QComboBox*>(editor);
		QString perfil = cb->currentText();
		model->setData(index, perfil, Qt::EditRole);
	}
	else
	if( index.column() == QSecretDataModel::ColEstado )
	{
		QComboBox *cb = static_cast<QComboBox*>(editor);
		model->setData(index, cb->currentIndex() == 0 ? "activo" : "inactivo", Qt::EditRole);
	}
	else
	if( index.column() == QSecretDataModel::ColVozIP )
	{
		QComboBox *cb = static_cast<QComboBox*>(editor);
		model->setData(index, cb->currentIndex() == 0 ? "Sí" : "No", Qt::EditRole);
	}
	else
	{
		QLineEdit *le = static_cast<QLineEdit*>(editor);
		QString txt = le->text();
		model->setData(index, txt, Qt::EditRole);
	}
}

void QSecretDataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}


void QPerfilesList::append(const QPerfilData &s)
{
	if( s.nombre() != gGlobalConfig.getPerfilInactivo() )
	{
		m_nombresPerfiles.append(s.nombre());
		QList::append(s);
	}
}

bool QPerfilesList::contains(const QString &s) const
{
	for( int i = 0; i < count(); i++ )
		if( at(i) == s )
			return true;
	return false;
}

QSecretDataModel::QSecretDataModel(int rows, const QStringList &cols, QObject *p)
	:QStandardItemModel(rows, cols.count(), p), m_nombresColumnas(cols)
{

}

#include <QHeaderView>
void QSecretDataModel::addSecretToTable(const QSecretData &s, int row)
{
	setItem( row, ColUsuario,	new QStandardItem(s.usuario()) );
	setItem( row, ColPerfil,	new QStandardItem(s.perfilOriginal()) );
	setItem( row, ColEstado,	new QStandardItem(s.activo() ? "activo" : "inactivo") );
	setItem( row, ColIP,        new QStandardItem(s.IPEstatica().isEmpty() ? "?" : s.IPEstatica()) );
	setItem( row, ColNombre,	new QStandardItem(s.nombre()) );
	setItem( row, ColDireccion, new QStandardItem(s.direccion()) );
	setItem( row, ColPoblacion, new QStandardItem(s.poblacion()) );
	setItem( row, ColTelefonos, new QStandardItem(s.telefonos()) );
	setItem( row, ColInstalador,new QStandardItem(s.instalador()) );
	setItem( row, ColConseguidor,new QStandardItem(s.conseguidor()) );
	setItem( row, ColEMail,		new QStandardItem(s.email()) );
	setItem( row, ColVozIP,		new QStandardItem(s.VozIP()?"Sí":"No") );
	setItem( row, ColNotas,		new QStandardItem(s.notas()) );
}

void QSecretDataTable::setupTable()
{
	im = new QSecretDataModel(0, QStringList()
								<< "Usuario"
								<< "Perfil"
								<< "Estado"
								<< "IP"
								<< "Nombre"
								<< "Dirección"
								<< "Población"
								<< "Teléfonos"
								<< "Instalador"
								<< "Conseguidor"
								<< "EMail"
								<< "VozIP"
								<< "Notas");
	setModel(im);
	setFont(QFont("verdana", 8, 8));
}

void QSecretDataModel::fillupTable()
{
	clear();
	setColumnCount(m_nombresColumnas.count());
	setHorizontalHeaderLabels(m_nombresColumnas);

	setRowCount(m_secrets.count());

	for( int row = 0; row < m_secrets.count(); row++ )
		addSecretToTable(m_secrets.at(row), row);
}

void QSecretDataModel::addPerfil(const ROS::QSentence &s)
{
	m_perfiles.append(s);
}

void QSecretDataModel::addSecret(const ROS::QSentence &s, bool addToTable)
{
	QString nombre = s.attribute("name");
	if( (nombre != gGlobalConfig.getPerfilInactivo()) && !m_perfiles.contains(nombre) )
		m_secrets.append(s);
	if( addToTable )
	{
		appendRow(0);
		addSecretToTable(m_secrets.last(), m_secrets.count()-1);
	}
}
