extends VButtonArray

func _ready():
	
	pass

func _on_TextureButton_pressed():
	get_tree().change_scene("res://Scenes/Menu/ServerOP.tscn")
	


func _on_Button_pressed():
	 get_tree().change_scene("res://Scenes/HowToPlay/HowToPlay.tscn")
	
	
	
func _on_settings_pressed():
	get_tree().change_scene("res://Scenes/Settings.tscn")
