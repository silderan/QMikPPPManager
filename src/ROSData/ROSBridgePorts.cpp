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

#include "ROSBridgePorts.h"

/*
nextid=*1
auto-isolate=false
bpdu-guard=false
bridge=bridgeGestio
broadcast-flood=true
debug-info= prio 0x8000 num 1
 role:Root (2) learn 1 forward 1 infoIs Rcvd edge 0 sendRSTP 1
 proposing 0 agreed 0 agree 0 synced 1 isolate 0 newInfo 0
 migration:SENSING tc:ACTIVE
 ptimes: Msg:0 Max: 5120 FD: 3840 HT: 512
 pprio: RBI: 8000:4C5E0CA68E04 RPC: 0 BI: 8000:4C5E0CA68E04 tP: 0x8001 rP: 0x8001
 dtimes: Msg:256 Max: 5120 FD: 3840 HT: 512
 dprio: RBI: 8000:4C5E0CA68E04 RPC: 10 BI: 8000:4C5E0CD33140 tP: 0x8001 rP: 0x8001

designated-bridge=0x8000.4C:5E:0C:A6:8E:04
designated-cost=0
designated-port-number=1
disabled=false
dynamic=false
edge=auto
edge-port=false
edge-port-discovery=true
external-fdb-status=false
fast-leave=false
forwarding=true
frame-types=admit-all
horizon=none
hw=true
hw-offload=true
hw-offload-group=switch1
inactive=false
ingress-filtering=false
interface=ether4
internal-path-cost=10
learn=auto
learning=true
multicast-router=temporary-query
path-cost=10
point-to-point=auto
point-to-point-port=true
port-number=1
priority=0x80
pvid=1
restricted-role=false
restricted-tcn=false
role=root-port
root-path-cost=10
sending-rstp=true
status=in-bridge
tag-stacking=false
trusted=true
unknown-multicast-flood=true
unknown-unicast-flood=true.tag
1.id=*0 * */

void ROSBridgePort::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);
	m_ifaceName = s.attribute("interface");
	m_bridgeName = s.attribute("bridge");
}

ROS::QSentence &ROSBridgePort::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute("interface", m_ifaceName);
	sentence.addAttribute("bridge", m_bridgeName);
	return ROSDataBase::toSentence(sentence);
}

bool ROSBridgePort::hasSameData(const ROSDataBase &rosData) const
{
	return
		(m_ifaceName == static_cast<const ROSBridgePort &>(rosData).m_ifaceName) &&
			(m_bridgeName == static_cast<const ROSBridgePort &>(rosData).m_bridgeName);
}

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSBridgePort::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	QList<ROS::QSentence> rtn;

	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::BridgePorts) );
	sentence.setResultType( ROS::QSentence::Result::Reply );

	if( step < 10 )
	{
		ROSBridgePort port(routerName);
		port.setBridgeName( "bridgePPPoE" );
		port.setIfaceName( QString("ether%1").arg(step) );
		port.toSentence(sentence).setID( QString("s%1").arg(step) );
		rtn.append( sentence );
	}
	else
	if( step == 10 )
	{
		sentence.setResultType( ROS::QSentence::Result::Done );
		rtn.append( sentence );
	}

	return rtn;
}
#endif
