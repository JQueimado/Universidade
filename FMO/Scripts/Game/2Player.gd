extends Spatial

const Movement_Flow=0.1;
var Gk;

func _ready():
	Gk=get_node("GoalKeaper");
	set_process(true);
	
func _process(delta):
	var sv = Server.receve();
	if sv!=[]:
		if str(sv[0])=="1":
			translate(1);
		
		if str(sv[0])=="2":
			translate(-1);
			
		if str(sv[0])=="3":
			rotate(-1);
			
		if str(sv[0])=="4":
			rotate(1);
		

func rotate(side):
	var transform = Gk.get_transform();
	transform=transform.rotated(Vector3(1,0,0),side*Movement_Flow);
	Gk.set_transform(transform);
	
func translate(side):
	var transform = Gk.get_transform();
	transform=transform.translated(Vector3(side*Movement_Flow,0,0));
	Gk.set_transform(transform);