import socket
import os
from pathlib import Path

port = 50016
s = socket.socket()
host = ""

s.bind((host, port))
s.listen(5)
print 'Server listening....'

while True:
    conn, addr = s.accept()
    print 'Got connection from', addr
    data = conn.recv(1024)
    print data
    my_file = Path('./Data/'+data)
    if not my_file.is_file():
        conn.send("file was not found!")
        print("file was not found!")
        continue
    conn.send("file is downloading..")
    f = open('./Data/'+data,'rb')
    l = f.read(1024)
    while (l):
       conn.send(l)
       print('Sent ',repr(l))
       l = f.read(1024)
    f.close()
    print('Done sending')
    conn.send('Thank you for connecting')
    conn.close()
s.close()
