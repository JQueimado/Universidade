extends Node

var server = PacketPeerUDP.new();
var send;

func _ready():
	server.set_send_address("localhost",4321);
	set_process_input(true);
	set_process(true);
	
func _process(delta):
	var msg = receve();
	if msg != []:
		print ("Receved",msg[0]);
	
		
func receve():
	server.listen(4321);
	var msg=[];
	while server.get_available_packet_count()>0:
		msg.append(server.get_var());
	return msg;

func _input(event):
	send=true;
	print ("Input");
	if event.is_action("ui_up"):
		server.put_var(1);
		
	if event.is_action("ui_down"):
		server.put_var(2);
	
	if event.is_action("ui_left"):
		server.put_var(3);
		
	if event.is_action("ui_right"):
		server.put_var(4);
	send=false;