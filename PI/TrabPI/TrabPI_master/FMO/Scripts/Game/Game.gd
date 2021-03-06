extends Node;

const active_debug=true;
const delay_time=1;
var test;

#SV
var is_sv;

#Game
var ball;
var timer;
var start;

func _ready():
	test=get_node("UI/Gut");
	test.hide();
	
	is_sv = global.ip=="localhost";
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
		Server.send([3,global.score]);
		get_tree().reload_current_scene();
	
	if(ball.get_transform().origin.x>=3.6):
		global.score[1]+=1;
		global.set_timer=timer.get_time_left();
		Server.send([3,global.score]);
		get_tree().reload_current_scene();
		
	if is_sv:
		var msg =ball.get_transform();
		Server.send([1,msg]);
	else:
		var msg = Server.receve();
		if msg != []:
			var arr  = msg[0];
			var x = Vector3(1,0,0);
			var y = Vector3(0,1,0);
			var z = Vector3(0,0,1);
			var org = Vector3(arr[0],arr[1],arr[2]);
			ball.set_transform(Transform(x,y,z,org));
			
	#tesing
	global_test.ball_pos=ball.get_transform().origin;
			
	
func _input(event):
	
	if event.is_action_pressed("Debug_Restart_Button"):
		get_tree().reload_current_scene();
	
	if event.is_action_pressed("back"):
		get_tree().change_scene("res://Scenes/Menu/MenuScene.tscn");
		
	if event.is_action_pressed("Test"):
		if test.is_visible():
			test.hide();
		else:
			test.show();