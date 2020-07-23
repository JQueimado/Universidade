run: run_server

run_server: Server.jar Remotes.jar
	java -classpath postgresql-42.2.11.jar:Remotes.jar:Server.jar Server.Server

run_client: Client.jar Remotes.jar
	java -classpath Remotes.jar:Client.jar Client.Client


compile: Remotes.class Client.class Server.class

Remotes.class:
	javac -classpath build/classes -d build/classes/ src/Remotes/*.java 

Client.class: Remotes.jar
	javac -classpath Remotes.jar:build/classes -d build/classes src/Client/*.java

Server.class: postgresql-42.2.11.jar Remotes.jar
	javac -classpath postgresql-42.2.11.jar:Remotes.jar:build/classes -d build/classes src/Server/*.java


clean: clean_class clean_temp

clean_class:
	rm -rf build/classes/*

clean_temp:
	rm -rf Storage.dataobj client_settings.properties server_settings.properties Client.jar Server.jar Remotes.jar

Remotes.jar: Remotes.class
	jar cf Remotes.jar -C build/classes Remotes

Client.jar: Client.class
	jar cfm Client.jar client_manifest.txt -C build/classes Client 

Server.jar: Server.class
	jar cfm Server.jar server_manifest.txt -C build/classes Server
	