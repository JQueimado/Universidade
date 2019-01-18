# -*- coding: utf-8 -*-
import socket, select
import traceback # para informação de excepções
from time import sleep

SOCKET_LIST = []    # lista de sockets abertos
RECV_BUFFER = 4096  # valor recomendado na doc. do python
PORT = 5000

lista_contactos={}
listaContactos = "contactos"

# função que trata dados do cliente
def faz_coisas(data, sock):

	input_info=[]	
	print("Client %s\n\tMessage: '%s'" % (sock, data))
	input_info = data.split(";")

	if len(input_info)==1:
		if input_info[0][1].isgigit():
			getPhone(input_info)
		else:
			getNome(input_info)

	
	elif input_info[0] == "-set":
		setNum(input_info[1],input_info[2])
	
	elif input_funcao[1] == "-del":
		if len(input_info)==2:
			delContacto(input_info[2])
		else:
			delNumero(input_info[2],input_info[3])

def getPhone(info, sock): #receber nome devolver numero(s). READ do pickle
	
	string=""
	pickle_in = open("contactos.pickle",'rb')
	lista_contactos = pickle.load(pickle_in)
	
	if info in listaContactos:
		for i in listaContactos[info]:
			string += info + " has number " + i
	else:
		string += "ERROR: No contact found"

	sock.sendall(string.encode())

def getNome(info): #recebe numero, devolve a quem pertence (pode ser >1)
	return

def setNum(nome,num): #definir contacto
	return

def delContacto(nome): #eliminar contacto
	return

def delNumero(nome,num): #eliminar numero pertencente ao nome
	return
	
          
if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(("0.0.0.0", PORT))  # aceita ligações de qualquer lado
    server_socket.listen(10)
    server_socket.setblocking(0) # o socket deixa de ser blocking
    
    # Adicionamos o socket à lista de sockets a monitorizar
    SOCKET_LIST.append(server_socket)
    
    print("Server started on port %d" % (PORT,))

    timecount = 0
    while True:  # ciclo infinito

        # apagamos os sockets que "morreram" entretanto
        for sock in SOCKET_LIST:
            if sock.fileno() < 0:
                SOCKET_LIST.remove(sock)

        # agora, esperamos que haja dados em algum dos sockets que temos
        rsocks,_,_ = select.select(SOCKET_LIST,[],[], 5)

        if len(rsocks) == 0: # timeout
            timecount += 5
            print("Timeout on select() -> %d secs" % (timecount))
            if timecount % 60 == 0:  # passou um minuto
                timecount = 0
            continue
        
        for sock in rsocks:  # percorrer os sockets com nova informação
             
            if sock == server_socket: # há uma nova ligação
                newsock, addr = server_socket.accept()
                newsock.setblocking(0)
                SOCKET_LIST.append(newsock)
                
                print("New client - %s" % (addr,))
                 
            else: # há dados num socket ligado a um cliente
                try:
                    data = sock.recv(RECV_BUFFER).decode()
                    if data:
                        faz_coisas(data, sock)
                        
                    else: # não há dados, o cliente fechou o socket
                        print("Client disconnected 1")
                        sock.close()
                        SOCKET_LIST.remove(sock)
                        
                except Exception as e: # excepção ao ler o socket, o cliente fechou ou morreu
                    print("Client disconnected")
                    print("Exception -> %s" % (e,))
                    print(traceback.format_exc())
                    
                    sock.close()
                    SOCKET_LIST.remove(sock)
                    
                    
