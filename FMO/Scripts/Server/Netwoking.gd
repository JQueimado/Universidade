extends Node

const PORT=4321;

var packet = PacketPeerUDP.new();

func start():
	packet.set_send_address(global.ip,PORT);
	
func send(data):
	packet.put_var(data);

func receve():
	var msg=[];
	packet.listen(PORT);
	while packet.get_available_packet_count()>0:
		msg.append(packet.get_var());
	return msg;