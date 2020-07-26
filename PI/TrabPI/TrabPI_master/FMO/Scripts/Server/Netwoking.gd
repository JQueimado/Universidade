extends Node

const SEND_PORT=1234;
const RESV_PORT=4321;

var packet = PacketPeerUDP.new();

func start():
	packet.set_send_address(global.ip,SEND_PORT);
	packet.listen(RESV_PORT);
	
func send(data):
	packet.put_var(data);

func receve():
	var msg=[];
	while packet.get_available_packet_count()>0:
		msg.append(packet.get_var());
	return msg;