extends Spatial;

const Rotation_Flow=0.2;
const Movement_Flow=0.1;


var player;
var t;

func _ready():
	set_process(true);
	set_process_input(true);
	
	player = get_node("MidPlayer");
	
func _input(event):
	t = player.get_transform();
	
	if event.is_action("Push"):
		t=t.translated(Vector3(-Movement_Flow,0,0));
		
	if event.is_action("Pull"):
		t=t.translated(Vector3(Movement_Flow,0,0));
	
	if event.is_action("RotateLeft"):
		t=t.rotated(Vector3(1,0,0),Rotation_Flow);
		
	if event.is_action("RotateRight"):
		t=t.rotated(Vector3(-1,0,0),Rotation_Flow);
	
	player.set_transform(t);


func _process(delta):
	pass
	
    