extends Node;

const active_debug=true;

#SV
var PORT = 4321;
var ip;
var is_sv;

#Game
var ball;
var timer;
var start;

func _ready():
	is_sv = true;
	Server.start();
	
	ball = get_node("BaseBall");
	timer = get_node("Timer");
	
	start=ball.get_transform();
	
	timer.set_wait_time(global.set_timer);
	timer.start();
	
	set_process(true);
	set_process_input(true);
	
func _process(delta):
	
	if timer.get_time_left()==0:
		get_tree().change_scene("res://Scenes/Game/GameOver.tscn");
		
	global.timer=timer.get_time_left();
	
	if(ball.get_transform().origin.x<=-3.6):
		global.score[0]+=1;
		global.set_timer=timer.get_time_left();
		get_tree().reload_current_scene();
	
	if(ball.get_transform().origin.x>=3.6):
		global.score[1]+=1;
		global.set_timer=timer.get_time_left();
		get_tree().reload_current_scene();
	
	print("Send",ball.get_transform().origin);
	Server.send(ball.get_transform().origin);
	
func _input(event):
	
	if event.is_action_pressed("Debug_Restart_Button"):
		get_tree().reload_current_scene();
	
	if event.is_action_pressed("back"):
		get_tree().change_scene("res://Scenes/Menu/MenuScene.tscn");
		