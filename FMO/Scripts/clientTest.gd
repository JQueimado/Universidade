extends Node

var server = PacketPeerUDP.new();
var send=0;

func _ready():
	server.set_send_address("localhost",4321);
	server.listen(1234);
	set_process_input(true);
	set_process(true);
	
func _process(delta):
	var msg = receve();
	if msg != []:
		print (msg[0]);
	if send!=0:
		server.put_var(send);
		send=0;
	
func receve():
	var msg=[];
	while server.get_available_packet_count()>0:
		msg.append(server.get_var());
	return msg;

func _input(event):
		
	if event.is_action("ui_up"):
		send =1;
		
	if event.is_action("ui_down"):
		send =2;
	
	if event.is_action("ui_left"):
		send =3;
		
	if event.is_action("ui_right"):
		send =4;