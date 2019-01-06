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
