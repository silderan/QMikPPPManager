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
			setComercial(fields[6]);
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

	i = firstOf(cm, QStringList() << "C/ " << "C/"
				<< "urb. " << "urb."
				<< "pda. " << "pda."
				<< "ctra. " << "ctra."
				<< ". " << ".", 0, &len);
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
		setComercial(cm.mid(i, 8));
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
	return QString("%1$%2$%3$%4$%5$%6$%7$%8$%9$%10$%11$%12")
			.arg(perfilOriginal())
			.arg(nombre())
			.arg(direccion())
			.arg(poblacion())
			.arg(telefonos())
			.arg(instalador())
			.arg(comercial())
			.arg(email())
			.arg(VozIP()?"vozip":"no")
			.arg(notas())
			.arg(SSID())
			.arg(wPass());
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
	s->addAttribute("service", "pppoe");
	if( m_IPEstatica.isEmpty() )
		s->addAttribute("!remote-address", "");
	else
		s->addAttribute("remote-address", m_IPEstatica);
	s->addAttribute("comment", comment());
}

bool QSecretData::contains(const QString &txt) const
{
	return  m_instalador.contains(txt, Qt::CaseInsensitive) ||
			m_usuario.contains(txt, Qt::CaseInsensitive) ||
			m_contra.contains(txt, Qt::CaseInsensitive) ||
			m_perfilReal.contains(txt, Qt::CaseInsensitive) ||
			m_nombre.contains(txt, Qt::CaseInsensitive) ||
			m_direccion.contains(txt, Qt::CaseInsensitive) ||
			m_poblacion.contains(txt, Qt::CaseInsensitive) ||
			m_telefonos.contains(txt, Qt::CaseInsensitive) ||
			m_comercial.contains(txt, Qt::CaseInsensitive) ||
			m_email.contains(txt, Qt::CaseInsensitive) ||
			m_SSID.contains(txt, Qt::CaseInsensitive) ||
			m_WPass.contains(txt, Qt::CaseInsensitive) ||
			m_notas.contains(txt, Qt::CaseInsensitive) ||
			m_perfilOriginal.contains(txt, Qt::CaseInsensitive) ||
			m_IPEstatica.contains(txt, Qt::CaseInsensitive) ||
			m_IPActiva.contains(txt, Qt::CaseInsensitive);
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
		return gGlobalConfig.setupCBIPsPublicas(new QComboBox(parent),
												static_cast<const QSecretDataModel*>(index.model())->ipsEstaticas(),
												index.data(Qt::EditRole).toString());
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
		return gGlobalConfig.setupCBPoblaciones( new QComboBox(parent),
												 static_cast<const QSecretDataModel*>(index.model())->poblaciones());
	}
	else
	if( index.column() == QSecretDataModel::ColInstalador )
		return gGlobalConfig.setupCBInstaladores(new QComboBox(parent), QString());
	else
	if( index.column() == QSecretDataModel::ColVendedor )
		return gGlobalConfig.setupCBVendedores(new QComboBox(parent), QString());
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
		gGlobalConfig.select(static_cast<QComboBox*>(editor), index.model()->data(index, Qt::EditRole).toString());
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
		gGlobalConfig.select(static_cast<QComboBox*>(editor), index.model()->data(index, Qt::EditRole).toString());
	else
	if( index.column() == QSecretDataModel::ColInstalador )
		gGlobalConfig.select(static_cast<QComboBox*>(editor), index.model()->data(index, Qt::EditRole).toString());
	else
	if( index.column() == QSecretDataModel::ColVendedor )
		gGlobalConfig.select(static_cast<QComboBox*>(editor), index.model()->data(index, Qt::EditRole).toString());
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
	if( index.column() == QSecretDataModel::ColVendedor )
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
	if( !m_nombres.contains(s.nombre()) )
	{
		m_nombres.append(s.nombre());
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

void QSecretDataModel::clear()
{
	m_secrets.clear();
}

#include <QHeaderView>
void QSecretDataModel::addSecretToTable(QSecretData &s, int row)
{
	if( rowCount() <= row )
		setRowCount(row+1);
	s.setFirstItem( setupCellItem(row, ColUsuario,	s.usuario(), s.secretID() ) );
	setupCellItem( row, ColPerfil,		s.perfilOriginal(), s.secretID() );
	setupCellItem( row, ColEstado,		s.activo() ? "activo" : "inactivo", s.secretID() );
	setupCellItem( row, ColIP,			s.IPActiva().isEmpty() ? (s.IPEstatica().isEmpty() ? "desconectado" : s.IPEstatica()) : s.IPActiva(), s.secretID() );
	setupCellItem( row, ColNombre,		s.nombre(), s.secretID() );
	setupCellItem( row, ColDireccion,	s.direccion(), s.secretID() );
	setupCellItem( row, ColPoblacion,	s.poblacion(), s.secretID() );
	setupCellItem( row, ColTelefonos,	s.telefonos(), s.secretID() );
	setupCellItem( row, ColInstalador,	s.instalador(), s.secretID() );
	setupCellItem( row, ColVendedor,	s.comercial(), s.secretID() );
	setupCellItem( row, ColEMail,		s.email(), s.secretID() );
	setupCellItem( row, ColVozIP,		s.VozIP()?"Sí":"No", s.secretID() );
	setupCellItem( row, ColNotas,		s.notas(), s.secretID() );
}

QSecretItem *QSecretDataModel::setupCellItem(int row, int col, const QString &txt, const QString &secret_id)
{
	QSecretItem *it;
	if( (it = static_cast<QSecretItem*>(item(row, col))) == Q_NULLPTR )
		setItem(row, col, it = new QSecretItem(txt, secret_id));
	else
	{
		it->setText(txt);
		it->setSecretID(secret_id);
	}
	return it;
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
	connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onCellDobleClic(QModelIndex)));
}

void QSecretDataTable::onCellDobleClic(const QModelIndex &index)
{
	if( index.column() == QSecretDataModel::ColUsuario )
		emit dobleClicUsuario(*im->secretData(index.row()));
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

void QSecretDataTable::filterRows(const QString &txt)
{
	for( int i = 0; i < im->secrets().count(); i++ )
		setRowHidden(im->secrets().at(i).getFirstItem()->row(), !im->secrets().at(i).contains(txt));
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
void QSecretDataModel::addSecret(const QSecretData &sd, bool addToTable)
{
	if( gGlobalConfig.perfilesUsables().contains(sd.perfilOriginal()) )
	{
		int pos;
		int row;

		if( (pos = m_secrets.indexOf(sd)) == -1 )
		{
			row = pos = m_secrets.count();
			m_secrets.append(sd);
		}
		else
		{
			row = m_secrets[pos].getFirstItem()->row();
			QString sesionID = m_secrets[pos].sesionID();
			QString IP = m_secrets[pos].IPActiva();
			m_secrets[pos] = sd;
			m_secrets[pos].setSesionID(sesionID);
			m_secrets[pos].setIPActiva(IP);
		}

		if( addToTable )
			addSecretToTable(m_secrets[pos], row);
	}
}

void QSecretDataModel::delSecret(const ROS::QSentence &s)
{
	int r = row(s.getID());
	if( r != -1 )
	{
		int c = rowCount();
		removeRow(r);
		setRowCount(c-1);
		m_secrets.removeOne(s);
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
				it->setText( "desconectado" );
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

int QSecretDataModel::row(const QString &id)
{
	QSecretData *sd = findDataBySecretID(id);
	if( sd )
		return sd->getFirstItem()->row();
	return -1;
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
		return QConfigData::Administrador;
	case ColPerfil:
		return QConfigData::Manager;
	case ColEstado:
		return QConfigData::Manager;
	case ColIP:
		return QConfigData::Manager;
	case ColNombre:
		return QConfigData::Instalador;
	case ColDireccion:
		return QConfigData::Instalador;
	case ColPoblacion:
		return QConfigData::Instalador;
	case ColTelefonos:
		return QConfigData::Instalador;
	case ColInstalador:
		return QConfigData::Manager;
	case ColVendedor:
		return QConfigData::Manager;
	case ColEMail:
		return QConfigData::Instalador;
	case ColVozIP:
		return QConfigData::Instalador;
	case ColNotas:
		return QConfigData::Instalador;
	case NumColumnas:
		return QConfigData::Administrador;
	}
	return QConfigData::Administrador;
}
