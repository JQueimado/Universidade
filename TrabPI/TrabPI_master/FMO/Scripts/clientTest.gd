extends Node

var server = PacketPeerUDP.new();
var send;
const send_ip ="localhost";

func _ready():
	server.set_send_address(send_ip,4321);
	server.listen(1234);
	set_process_input(true);
	set_process(true);
	
func _process(delta):
	var msg = receve();
	while msg != []:
		var unpack = msg[0];
		if unpack[0]==1:
			var new_msg = Transform(unpack[1]).origin;
			print ("Ball:"," ",new_msg.x," ",new_msg.y," ",new_msg.z);
		elif unpack[0]==2:
			var new_msg = Transform(unpack[1]).origin;
			print ("Player:"," ",new_msg.x," ",new_msg.y," ",new_msg.z);
		elif unpack[0]==3:
			print ("Score: ",unpack[1]);
		msg.pop_front();
		
func receve():
	var msg=[];
	while server.get_available_packet_count()>0:
		msg.append(server.get_var());
	return msg;

func _input(event):
	send=true;
	if event.is_action("ui_up"):
		server.put_var([1,1]);
		
	if event.is_action("ui_down"):
		server.put_var([1,2]);
	
	if event.is_action("ui_left"):
		server.put_var([1,3]);
		
	if event.is_action("ui_right"):
		server.put_var([1,4]);
	send=false;