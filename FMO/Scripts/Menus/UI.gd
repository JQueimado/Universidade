extends TextureFrame

var scorelabel;
var timer;

func _ready():
	#scoreBoard
	scorelabel = get_node("Score");
	var pos = self.get_size();
	var x = int(pos.x/2-scorelabel.get_size().x/2)
	var y = 0;
	scorelabel.set_pos(Vector2(x,y));
	
	#timer
	timer=get_node("Timer");
	
	set_process(true);
	
func _process(delta):
	scorelabel.set_text(str(global.score[0])+":"+str(global.score[1]));
	
	timer.set_text(str(global.timer));
	

