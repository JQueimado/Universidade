extends Spatial;

const active_Debug=false;

#Movement Restrictions 
const Rotation_Flow=0.1;
const Movement_Flow=0.1;

const Max_Right=[2.736745,0.99029,0.55272,0.99029];

#Player vars
var player=[null,null,null,null];
var current=2;
var t;

func _ready():
	set_process(true);
	set_process_input(true);
	
	#Players
	player[0]=get_node("GoalKeaper");
	player[1]=get_node("Defenders");
	player[2]=get_node("MidPlayer");
	player[3]=get_node("Strikers");
	
	global.player=current;


#Player controlers
func _input(event):
	
	#Player Changer
	if event.is_action_pressed("NextPlayer"):
		current+=1;
		
	if event.is_action_pressed("LastPlayer"):
		current-=1;
		
	if current>=player.size():
		current=player.size()-1;
	
	if current<0:
		current=0;
	
	#Player Movement	
	t = player[current].get_transform();
	
	if event.is_action("Push") and t.origin[0]>=-Max_Right[current]:
		t=t.translated(Vector3(-Movement_Flow,0,0));
		
	if event.is_action("Pull") and t.origin[0]<=Max_Right[current]:
		t=t.translated(Vector3(Movement_Flow,0,0));
	
	if event.is_action("RotateLeft"):
		t=t.rotated(Vector3(1,0,0),Rotation_Flow);
		
	if event.is_action("RotateRight"):
		t=t.rotated(Vector3(-1,0,0),Rotation_Flow);
	
	if active_Debug:
		print(t.origin);
	
	player[current].set_transform(t);
	global.player=current;