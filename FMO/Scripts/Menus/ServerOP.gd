extends Node

var textBox;

func _ready():
	textBox = get_node("IP");
	set_process_input(true);
	
func _input(event):
	pass

func _on_CreateSV_pressed():
	global.ip="localhost";
	get_tree().change_scene("res://Scenes/Game/Game.tscn");

func _on_JoinSV_pressed():
	global.ip=textBox.get_text();
	get_tree().change_scene("res://Scenes/Game/Game.tscn");
