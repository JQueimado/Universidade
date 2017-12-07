extends Node

func _ready():
	set_process_input(true);
	
func _input(event):
	
	if event.is_action_pressed("Debug_Restart_Button"):
		get_tree().reload_current_scene();
	
	if event.is_action_pressed("back"):
		get_tree().change_scene("res://Scenes/Menu/MenuScene.tscn");