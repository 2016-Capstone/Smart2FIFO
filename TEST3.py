import socket
import sys
HOST = '210.125.31.34'
PORT = 443

c_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
c_socket.connect((HOST,PORT))
c_socket.send(b'ID=1\n')

while(True) :
    try :
#        msg = sys.stdin.readline()
#        c_socket.send(msg)
        data = c_socket.recv(1024)
        print(data)
    except (KeyboardInterrupt, SystemExit) :
        c_socket.close()
        print('\nEND')
        raise
