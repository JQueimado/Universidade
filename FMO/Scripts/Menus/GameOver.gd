extends Node

func _ready():
	set_process_input(true);
	
func _input(event):
	if event.is_action_pressed("ui_accept"):
		get_tree().change_scene("res://Scenes/Menu/MenuScene.tscn");
