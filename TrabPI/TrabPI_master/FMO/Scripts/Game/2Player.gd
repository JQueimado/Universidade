extends Spatial

const Movement_Flow=0.1;
var Gk;

func _ready():
	Gk=get_node("GoalKeaper");
	set_process(true);
	
func _process(delta):
	var sv = Server.receve();
	while sv!=[]:
		var pack = sv[0];
		
		if pack[0]==1:
			if str(pack[1])=="1":
				translate(1);
			
			if str(pack[1])=="2":
				translate(-1);
				
			if str(pack[1])=="3":
				rotate(-1);
				
			if str(pack[1])=="4":
				rotate(1);
		
		var msg=Gk.get_transform();
		Server.send([2,msg]);
		sv.pop_front();
		

func rotate(side):
	var transform = Gk.get_transform();
	transform=transform.rotated(Vector3(1,0,0),side*Movement_Flow);
	Gk.set_transform(transform);
	
func translate(side):
	var transform = Gk.get_transform();
	transform=transform.translated(Vector3(side*Movement_Flow,0,0));
	Gk.set_transform(transform);