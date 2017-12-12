extends TextureFrame

var scorelabel;
var timer;
var player;

func _ready():
	#scoreBoard
	scorelabel = get_node("Score");
	var pos = self.get_size();
	var x = int(pos.x/2-scorelabel.get_size().x/2)
	var y = 0;
	scorelabel.set_pos(Vector2(x,y));
	
	#timer
	timer=get_node("Timer");
	
	#player
	player = get_node("Player")
	x=int(pos.x-player.get_size().x);
	player.set_pos(Vector2(x,y));
	
	set_process(true);
	
func _process(delta):
	scorelabel.set_text(str(global.score[0])+":"+str(global.score[1]));
	
	timer.set_text(str(int(global.timer)));
	
	var st=str();
	var p = global.player;
	if p==0:
		st="GK";
	if p==1:
		st="DF";
	if p==2:
		st="CD";
	if p==3:
		st="ATK"; 
	player.set_text(st);
	

