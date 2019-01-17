import socket
import sys
from sys import argv
from time import sleep
import pickle

cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
cliente.connect(('localhost',5000))

input_info = argv[1:]

string=""

for i in input_info:
	string+=i + ";"

cliente.sendall(string.encode())
sleep(0.3)


#pedir input mandar ao server, sendAll
#timesleep, to server ao client ou cliente server, junta a info se mandar dois seguidos
#usar funcao decode e encode quando receber e mandar 
