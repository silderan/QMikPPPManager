#include "QSecretData.h"

void QSecretData::parseComment(const QString &comment)
{
    QStringList fields = comment.split("$");
    if( fields.count() > 1 )
    {
        switch( fields.count() )
		{
		default:
			setWPass(fields[11]);
		case 11:
			setSSID(fields[10]);
		case 10:
			setNotas(fields[9]);
		case 9:
			setVozIP(fields[8]=="vozip");
		case 8:
			setEmail(fields[7]);
		case 7:
			setVendedor(fields[6]);
		case 6:
			setInstalador(fields[5]);
		case 5:
			setTelefonos(fields[4]);
		case 4:
			setPoblacion(fields[3]);
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
		setPerfilOriginal((perfilReal().isEmpty() || (perfilReal() == gGlobalConfig.perfilInactivo())) ? gGlobalConfig.perfilBasico() : perfilReal());
		parsePlainComment(comment);
	}
	if( perfilReal() != gGlobalConfig.perfilInactivo() )
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
		setVendedor(cm.mid(i, 8));
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
	return QString("%1$%2$%3$%4$%5$%6$%7$%8$%9$%10")
			.arg(perfilOriginal())
			.arg(nombre())
			.arg(direccion())
			.arg(poblacion())
			.arg(telefonos())
			.arg(instalador())
			.arg(vendedor())
			.arg(email())
			.arg(VozIP()?"vozip":"no")
			.arg(notas());
}

bool QSecretData::activo() const
{
	return perfilReal() != gGlobalConfig.perfilInactivo();
}

void QSecretData::toSentence(ROS::QSentence *s)
{
	s->addAttribute("name", m_usuario);
	s->addAttribute("password", m_contra);
	s->addAttribute("profile", m_perfilOriginal);
	if( !m_IPEstatica.isEmpty() )
		s->addAttribute("remote-address", m_IPEstatica);
	s->addAttribute("comment", comment());
}

QSecretData::QSecretData(const ROS::QSentence &s)
	: m_secretID(s.getID()),
	  m_instalador("no_definido"),
	  m_usuario(s.attribute("name")),
	  m_contra(s.attribute("password")),
	  m_perfilReal(s.attribute("profile")),
	  m_VozIP(false),
	  m_IPEstatica(s.attribute("remote-address")),
	  firstItem(Q_NULLPTR)
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
	if( gGlobalConfig.nivelUsuario() < QSecretDataModel::nivelMinimoEdicion((QSecretDataModel::Columnas)index.column()) )
		return Q_NULLPTR;
	if( index.column() == QSecretDataModel::ColUsuario )
		return Q_NULLPTR;

	if( index.column() == QSecretDataModel::ColPerfil )
		return gGlobalConfig.setupCBPerfilesUsables(new QComboBox(parent), QString());
	else
	if( index.column() == QSecretDataModel::ColIP )
	{
		QComboBox *cb = new QComboBox(parent);
		QStringList ips = static_cast<const QSecretDataModel*>(index.model())->ipsEstaticas();
		Q_ASSERT(cb);
		cb->addItem("IP dinámica");// El primer elemento será para borrar la IP estática
		for( quint32 ip = gGlobalConfig.deIPV4(); ip <= gGlobalConfig.aIPV4(); ip++ )
		{
			QString sip = UINT_TO_IPV4(ip);
			if( !ips.contains(sip) )
				cb->addItem(sip);
		}
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
	if( index.column() == QSecretDataModel::ColPoblacion )
	{
		QComboBox *cb = new QComboBox(parent);
		Q_ASSERT(cb);
		cb->addItems( static_cast<const QSecretDataModel*>(index.model())->poblaciones());
		cb->setEditable(true);
		return cb;
	}
	else
	if( index.column() == QSecretDataModel::ColInstalador )
	{
		QComboBox *cb = new QComboBox(parent);
		Q_ASSERT(cb);
		cb->addItems(gGlobalConfig.instaladores());
		cb->setEditable(true);
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
		gGlobalConfig.select(static_cast<QComboBox*>(editor), index.model()->data(index, Qt::EditRole).toString());
	else
	if( index.column() == QSecretDataModel::ColIP )
	{
		QString ip = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *cb = static_cast<QComboBox*>(editor);
		cb->setCurrentIndex(cb->findText(ip));
		if( cb->currentText() != ip )
			cb->setCurrentText(ip);
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
	if( index.column() == QSecretDataModel::ColPoblacion )
	{
		QString estado = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *cb = static_cast<QComboBox*>(editor);
		cb->setCurrentIndex(cb->findText(estado));
		if( cb->currentText() != estado )
			cb->setCurrentText(estado);
	}
	else
	if( index.column() == QSecretDataModel::ColInstalador )
	{
		QString instalador = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *cb = static_cast<QComboBox*>(editor);
		cb->setCurrentIndex(cb->findText(instalador));
		if( cb->currentText() != instalador )
			cb->setCurrentText(instalador);
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
		model->setData(index, cb->currentText(), Qt::EditRole);
	}
	else
	if( index.column() == QSecretDataModel::ColIP )
	{
		QComboBox *cb = static_cast<QComboBox*>(editor);
		if( cb->currentIndex() == 0 )
			model->setData(index, "", Qt::EditRole);
		else
		if( !cb->currentText().isEmpty() )
			model->setData(index, cb->currentText(), Qt::EditRole);
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
	if( index.column() == QSecretDataModel::ColPoblacion )
	{
		QComboBox *cb = static_cast<QComboBox*>(editor);
		model->setData(index, cb->currentText(), Qt::EditRole);
	}
	else
	if( index.column() == QSecretDataModel::ColInstalador )
	{
		QComboBox *cb = static_cast<QComboBox*>(editor);
		model->setData(index, cb->currentText(), Qt::EditRole);
	}
	else
	{
		QLineEdit *le = static_cast<QLineEdit*>(editor);
		model->setData(index, le->text(), Qt::EditRole);
	}
}

void QSecretDataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

void QPerfilesList::append(const QPerfilData &s)
{
	m_nombres.append(s.nombre());
	QList::append(s);
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

void QSecretDataModel::clear()
{
	m_secrets.clear();
}

#include <QHeaderView>
void QSecretDataModel::addSecretToTable(QSecretData &s, int row)
{
	setItem( row, ColUsuario,	s.setFirstItem(new QSecretItem(s.usuario(), s.secretID())) );
	setItem( row, ColPerfil,	new QSecretItem(s.perfilOriginal(), s.secretID()) );
	setItem( row, ColEstado,	new QSecretItem(s.activo() ? "activo" : "inactivo", s.secretID()) );
	setItem( row, ColIP,        new QSecretItem(s.IPEstatica().isEmpty() ? "?" : s.IPEstatica(), s.secretID()) );
	setItem( row, ColNombre,	new QSecretItem(s.nombre(), s.secretID()) );
	setItem( row, ColDireccion, new QSecretItem(s.direccion(), s.secretID()) );
	setItem( row, ColPoblacion, new QSecretItem(s.poblacion(), s.secretID()) );
	setItem( row, ColTelefonos, new QSecretItem(s.telefonos(), s.secretID()) );
	setItem( row, ColInstalador,new QSecretItem(s.instalador(), s.secretID()) );
	setItem( row, ColVendedor,new QSecretItem(s.vendedor(), s.secretID()) );
	setItem( row, ColEMail,		new QSecretItem(s.email(), s.secretID()) );
	setItem( row, ColVozIP,		new QSecretItem(s.VozIP()?"Sí":"No", s.secretID()) );
	setItem( row, ColNotas,		new QSecretItem(s.notas(), s.secretID()) );
}

bool QSecretDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if( role == Qt::EditRole )
	{
		if( index.data(role).toString() != value.toString() )
		{
			QString ID = secretID(index.row());
			emit datoModificado(static_cast<Columnas>(index.column()), value.toString(), ID);
		}
	}
	return QStandardItemModel::setData(index, value, role);
}

QString QSecretDataModel::usuario(int row)
{
	return index(row, ColUsuario).data(Qt::DisplayRole).toString();
}

QSecretData *QSecretDataModel::secretData(int row)
{
	QString user = usuario(row);
	return findDataByUsername(user);
}

QString QSecretDataModel::secretID(int row)
{
	QSecretData *s = secretData(row);
	if( s )
		return s->secretID();
	return QString();
}

QSecretDataTable::QSecretDataTable(QWidget *papi)
	: QTableView(papi), delegado(papi)
{
	setupTable();
	setItemDelegate(&delegado);
	connect(im, SIGNAL(datoModificado(QSecretDataModel::Columnas,QString,QString)), SIGNAL(datoModificado(QSecretDataModel::Columnas,QString,QString)));
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
								<< "Vendedor"
								<< "EMail"
								<< "VozIP"
								<< "Notas");
	setModel(im);
}

void QSecretDataTable::clear()
{
	im->clear();
}

void QSecretDataModel::fillupTable()
{
	setColumnCount(m_nombresColumnas.count());
	setHorizontalHeaderLabels(m_nombresColumnas);

	setRowCount(m_secrets.count());

	for( int row = 0; row < m_secrets.count(); row++ )
		addSecretToTable(m_secrets[row], row);
}

/**
 * @brief QSecretDataModel::addSecret
 * Añade una nueva estructura de datos "secret" a la lista.
 * El nuevo "secret" sólo se añadirá si su perfil es uno de los válidos.
 * Se tiene en cuenta que, normalmente, el perfil "sin acceso" no es uno de los
 * válidos, pero el "secret" igual debe estar dentro de la lista.
 * @param s
 * @param addToTable
 */
void QSecretDataModel::addSecret(const ROS::QSentence &s, bool addToTable)
{
	QString nombre = s.attribute("profile");

	if( (nombre == gGlobalConfig.perfilInactivo()) || gGlobalConfig.perfilesUsables().contains(nombre) )
		m_secrets.append(s);

	if( addToTable )
	{
		appendRow(0);
		addSecretToTable(m_secrets.last(), m_secrets.count()-1);
	}
}

void QSecretDataModel::actualizaUsuario(const ROS::QSentence &s)
{
	QSecretData *secret;
	if( !s.attribute("name").isEmpty() )
	{
		if( (secret = findDataByUsername(s.attribute("name"))) != Q_NULLPTR )
		{
			QSecretItem *it = static_cast<QSecretItem*>(item(secret->getFirstItem()->row(), ColIP));
			secret->setSesionID(s.getID());
			secret->setIPActiva(s.attribute("address"));
			it->setText( QString("%1").arg(secret->IPActiva()) );
		}
	}
	else
	if( !s.attribute(".dead").isEmpty() )
	{
		if( (secret = findDataBySesionID(s.getID())) != Q_NULLPTR )
		{
			QSecretItem *it = static_cast<QSecretItem*>(item(secret->getFirstItem()->row(), ColIP));
			secret->setIPActiva("");
			secret->setSesionID("");
			if( secret->IPEstatica().isEmpty() )
				it->setText("");
			else
				it->setText( QString("s(%1)").arg(secret->IPEstatica()) );
		}
	}
}

QSecretData *QSecretDataModel::findDataByUsername(const QString &us)
{
	for( int i = 0; i < m_secrets.count(); i++ )
	{
		if( m_secrets[i].usuario() == us )
			return &(m_secrets[i]);
	}
	return Q_NULLPTR;
}

QSecretData *QSecretDataModel::findDataBySesionID(const QString &id)
{
	for( int i = 0; i < m_secrets.count(); i++ )
	{
		if( m_secrets[i].sesionID() == id )
			return &(m_secrets[i]);
	}
	return Q_NULLPTR;
}

QSecretData *QSecretDataModel::findDataBySecretID(const QString &id)
{
	for( int i = 0; i < m_secrets.count(); i++ )
	{
		if( m_secrets[i].secretID() == id )
			return &(m_secrets[i]);
	}
	return Q_NULLPTR;
}

QStringList QSecretDataModel::poblaciones() const
{
	QStringList pobs;
	for( int i = 0; i < m_secrets.count(); i++ )
	{
		if( !m_secrets[i].poblacion().isEmpty() && !pobs.contains(m_secrets[i].poblacion()) )
			pobs.append(m_secrets[i].poblacion());
	}
	return pobs;
}

QStringList QSecretDataModel::ipsEstaticas() const
{
	QStringList ips;
	for( int i = 0; i < m_secrets.count(); i++ )
		ips.append(m_secrets[i].IPEstatica());
	return ips;
}

QConfigData::NivelUsuario QSecretDataModel::nivelMinimoEdicion(QSecretDataModel::Columnas col)
{
	switch( col )
	{
	case ColUsuario:
		return QConfigData::Completo;
	case ColPerfil:
		return QConfigData::Administrador;
	case ColEstado:
		return QConfigData::Administrador;
	case ColIP:
		return QConfigData::Administrador;
	case ColNombre:
		return QConfigData::Instalador;
	case ColDireccion:
		return QConfigData::Instalador;
	case ColPoblacion:
		return QConfigData::Instalador;
	case ColTelefonos:
		return QConfigData::Instalador;
	case ColInstalador:
		return QConfigData::Administrador;
	case ColVendedor:
		return QConfigData::Administrador;
	case ColEMail:
		return QConfigData::Instalador;
	case ColVozIP:
		return QConfigData::Instalador;
	case ColNotas:
		return QConfigData::Instalador;
	case NumColumnas:
		return QConfigData::Completo;
	}
	return QConfigData::Completo;
}
