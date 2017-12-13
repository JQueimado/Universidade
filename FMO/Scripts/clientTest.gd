extends Node

var server = PacketPeerUDP.new();

func _ready():
	server.set_send_address("localhost",4321);
	set_process_input(true);

func _input(event):
	if event.is_action("ui_up"):
		server.put_var(1);
		
	if event.is_action("ui_down"):
		server.put_var(2);
	
	if event.is_action("ui_left"):
		server.put_var(3);
		
	if event.is_action("ui_right"):
		server.put_var(4);
		