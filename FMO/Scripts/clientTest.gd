extends Node

var server = PacketPeerUDP.new();

func _ready():
	server.set_send_address("localhost",4321);
	set_process_input(true);

func _input(event):
	if event.is_action("Debug_Server_Send_Msg"):
		print("sent");
		server.put_var("Move");
		