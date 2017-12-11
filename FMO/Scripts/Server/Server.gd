class Server extends SceneTree:
	
	const SERVER_PORT=5001;
	const MAX_PLAYERS=1;
	
	func createServer():
		var peer = NetworkedMultiplayerENet.new();
		peer.create_server(SERVER_PORT, MAX_PLAYERS);
		get_tree().set_network_peer(peer);
		