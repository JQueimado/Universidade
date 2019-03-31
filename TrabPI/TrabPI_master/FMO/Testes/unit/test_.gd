extends "res://addons/gut/test.gd"
func setup():
	gut.p("ran setup", 2)

func teardown():
	gut.p("ran teardown", 2)

func prerun_setup():
	gut.p("ran run setup", 2)

func postrun_teardown():
	gut.p("ran run teardown", 2)

func test_ball_in_field():
	var org=global_test.ball_pos;
	pending("not done yet");
	
func test_Server_works():
	pending("not done yet");