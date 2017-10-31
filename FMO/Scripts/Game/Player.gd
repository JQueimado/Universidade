extends Spatial;
var t;
func _ready():
	set_process(true);

func _process(delta):
	t = get_node("MidPlayer").get_transform();
	t=t.rotated(Vector3(1,0,0),0.1);
	get_node("MidPlayer").set_transform(t);
    