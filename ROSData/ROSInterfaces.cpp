#include "ROSInterfaces.h"

/*
actual-mtu=1500
comment=Config restored 2017-07-25 23:30
default-name=ether1
disabled=false
fp-rx-byte=14603085579
fp-rx-packet=132936525
fp-tx-byte=11018034038
fp-tx-packet=170628564
l2mtu=1580
last-link-up-time=dec/18/2018 03:57:48
link-downs=0
mac-address=E4:8D:8C:3F:92:A0
max-l2mtu=10222
mtu=1500
name=ether1
running=true
rx-byte=14603085579
rx-drop=0
rx-error=0
rx-packet=132936525
slave=true
tx-byte=11018034038
tx-drop=0
tx-error=0
tx-packet=170628564
tx-queue-drop=0
type=ether

actual-mtu=1480
disabled=false
dynamic=true
fp-rx-byte=0
fp-rx-packet=0
fp-tx-byte=0
fp-tx-packet=0
last-link-up-time=jan/03/2019 16:48:28
link-downs=0
mtu=1480
name=<pppoe-AldeaGolf_421>
running=true
rx-byte=3689
rx-drop=0
rx-error=0
rx-packet=54
tx-byte=829
tx-drop=0
tx-error=0
tx-packet=22
tx-queue-drop=0
type=pppoe-in

actual-mtu=1500
comment=VPLS-Traiguera
disabled=false
fp-rx-byte=0
fp-rx-packet=0
fp-tx-byte=0
fp-tx-packet=0
l2mtu=1500
last-link-down-time=jan/02/2019 21:24:07
last-link-up-time=jan/02/2019 21:24:18
link-downs=21
mac-address=02:C4:51:B6:0B:0E
mtu=1500
name=vpls19-Traiguera
running=true
rx-byte=226907987113
rx-drop=0
rx-error=0
rx-packet=606970996
slave=true
tx-byte=1207999420435
tx-drop=0
tx-error=0
tx-packet=1114384861
tx-queue-drop=0
type=vpls
*/
void ROSInterface::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);
	m_name = s.attribute("name");
	m_type = s.attribute("type");
}

ROS::QSentence &ROSInterface::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute("name", m_name);
	sentence.addAttribute("type", m_type);

	return ROSDataBase::toSentence(sentence);
}

bool ROSInterface::hasSameData(const ROSDataBase &rosInterface) const
{
	return
		(m_name == static_cast<const ROSInterface&>(rosInterface).m_name) &&
			(m_type == static_cast<const ROSInterface&>(rosInterface).m_type) ;
}

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSInterface::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	QList<ROS::QSentence> rtn;

	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::Interface) );
	sentence.setResultType( ROS::QSentence::Result::Reply );

	if( step <= 10 )
	{
		ROSInterface iface(routerName);
		iface.setInterfaceType( "ether" );
		iface.setInterfaceName( QString("ether%1").arg(step) );
		iface.toSentence(sentence).setID( QString("s%1").arg(step) );
		rtn.append( sentence );
	}
	else
	if( step == 11 )
	{
		sentence.setResultType( ROS::QSentence::Result::Done );
		rtn.append( sentence );
	}
	return rtn;
}
#endif
