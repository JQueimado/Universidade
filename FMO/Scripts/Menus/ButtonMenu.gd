extends VButtonArray

func _ready():
	
	pass

func _on_TextureButton_pressed():
	get_tree().change_scene("res://Scenes/Game/Game.tscn")
	
	
func _on_Button_pressed():
	 get_tree().change_scene("res://Scenes/HowToPlay/HowToPlay.tscn")
