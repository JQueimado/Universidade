extends Node;

const active_debug=true;

var sv;
const PORT = 4321;

func _ready():
	sv = PacketPeerUDP.new();
	sv.set_send_address('localhost',PORT);
	
	set_process(true);
	set_process_input(true);
	
func _process(delta):
	sv.listen(PORT);
	if(sv.get_available_packet_count()!=0):
		print(str(sv.get_var()));
	
func send(data):
	sv.put_var(data);
	
func _input(event):
	
	if event.is_action_pressed("Debug_Server_Send_Msg") and active_debug:
		send("Msg");
	
	if event.is_action_pressed("Debug_Restart_Button"):
		get_tree().reload_current_scene();
	
	if event.is_action_pressed("back"):
		get_tree().change_scene("res://Scenes/Menu/MenuScene.tscn");
		