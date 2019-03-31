import socket
import sys
from sys import argv
from time import sleep
import pickle

cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
cliente.connect(('localhost',5000))

if __name__ == "__main__":
	
	try:

		while True:
			inp = format( input("$ ") )

			cliente.sendall( inp.encode() )

			print( cliente.recv(1024).decode() )

	except Exception as e:
		print(e)



#pedir input mandar ao server, sendAll
#timesleep, to server ao client ou cliente server, junta a info se mandar dois seguidos
#usar funcao decode e encode quando receber e mandar 
