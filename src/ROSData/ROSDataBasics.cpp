/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#include "ROSDataBasics.h"

#include <QObject>

const char ROSDataBase::separatorCommentChar = '$';
const char *ROSDataBase::userNamePattern = "[^A-Za-z0-9\\-_]";
const char *ROSDataBase::userPassPattern = "[^A-Za-z0-9\\-\\?_]";
const char *ROSDataBase::profilePattern = "[^A-Za-z0-9\\-_\\/\\() ]";
const char *ROSDataBase::emailPattern = "[^A-Za-z0-9\\/\\-_.:!%+='?,@]";
const char *ROSDataBase::phonesPattern = "[^0-9,\\+]";
const char *ROSDataBase::urlPattern = "[^A-Za-z0-9\\/\\-_.:!%+='?,@]";
const char *ROSDataBase::basicNonROSMemberPatern = "[~$]";
const char *ROSDataBase::ssidPattern = "[^A-Za-z0-9\\-_ +@]";
const char *ROSDataBase::wpaPattern = "[^A-Za-z0-9\\-_+@]";

void ROSDataBase::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	m_rosObjectID = s.getID();
    m_delete = !s.attribute(".dead").isEmpty();
	m_comment = s.attribute("comment");
	m_routerName = routerName;
}

ROS::QSentence &ROSDataBase::toSentence(ROS::QSentence &sentence) const
{
	if( !m_rosObjectID.isEmpty() )
		sentence.setID(m_rosObjectID);

	sentence.addAttribute("comment", m_comment);

	return sentence;
}

bool ROSDataBase::checkValidData(const QString &txt, const QString &charsRegExRange, int minLenght)
{
	QRegExp rx(charsRegExRange);

	// If it's negative, means that can be cleared or greather that absoulte value.
	if( minLenght < 0 )
	{
		if( txt.isEmpty() )
			return true;
		minLenght = -minLenght;
	}
	if( txt.length() < minLenght )
	{
		if( minLenght == 1 )
			m_lastError = QObject::tr("no puede estar vacío");
		else
			m_lastError = QObject::tr("debe tener %1 o más caracteres").arg(minLenght);
		return false;
	}
	if( rx.indexIn(txt) != -1 )
	{
		QStringList list = rx.capturedTexts();
		if( (list.count() > 1) || (list.at(0).count() > 1) )
			m_lastError = QObject::tr("los caracteres '%1' no son válidos").arg(list.join(""));
		else
			m_lastError = QObject::tr("el caracter '%1' no es válido").arg(list.at(0));
		return false;
	}
	m_lastError.clear();
	return true;
}

bool ROSDataBase::updateMember(QString &member, const QString &data, const QString &pattern, int minLenght)
{
	if( checkValidData( data, pattern, minLenght) )
	{
		member = data;
		return true;
	}
	return false;
}

