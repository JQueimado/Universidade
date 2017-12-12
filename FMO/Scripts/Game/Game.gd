extends Node;

const active_debug=true;

#SV
var is_sv=false;
var sv = PacketPeerUDP.new();
var PORT = 4321;
var ip;

#Game
var ball;

func _ready():
	ip =global.ip;
	sv.set_send_address(ip,PORT);
	
	ball = get_node("BaseBall");
	
	set_process(true);
	set_process_input(true);
	
func _process(delta):
	if is_sv:
		send(ball.get_transform())
	elif sv.get_available_packet_count()!=0:
		var msg=[];
		while sv.get_available_packet_count()>0:
			msg.append(sv.get_var());
		ball.set_transform(msg[0]);
		
func send(data):
	sv.put_packet(data);
	
	
func _input(event):
	
	if event.is_action_pressed("Debug_Server_Send_Msg") and active_debug:
		send("Msg");
	
	if event.is_action_pressed("Debug_Restart_Button"):
		get_tree().reload_current_scene();
	
	if event.is_action_pressed("back"):
		get_tree().change_scene("res://Scenes/Menu/MenuScene.tscn");
		