import socket
import os
import sys
import time

HOST = '210.125.31.34'
PORT = 443
ADDR = (HOST, PORT)
PATH = './fifo_cmd'


if not os.path.exists(PATH) :
    os.mkfifo(PATH)    

fifo = os.open(PATH, os.O_RDWR)

while(True) :
    try :
        c_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        c_socket.connect(ADDR)
    except Exception as e :
        print("Wrong connection to %s:%d (%s)" % (HOST, PORT, e))
        c_socket.close()
        time.sleep(2)
        continue

    try:
        c_socket.send('DVTYPE=1%%MSGTYPE=3\n')
    except Exception as e :
        continue

    while(True) :
        try :
            data = c_socket.recv(1024)
            if data == '' :
                break
            print (repr(data))
            os.write(fifo, data)

        except (KeyboardInterrupt, SystemExit) :
            c_socket.close()
            fifo.close()
            print ('\nEND')
            raise
    c_socket.close()
