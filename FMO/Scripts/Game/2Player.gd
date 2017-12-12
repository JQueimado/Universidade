extends Spatial

const Movement_Flow=0.1;
var Gk;

func _ready():
	Gk=get_node("GoalKeaper");
	set_process(true);
	
func _process(delta):
	var sv = Server.receve();
	if sv!=[]:
		if str(sv[0])=="Move":
			rotate()

func rotate():
	var transform = Gk.get_transform();
	transform=transform.rotated(Vector3(1,0,0),Movement_Flow);
	Gk.set_transform(transform);
