import socket
from pathlib import Path
port = 60012
s = socket.socket()
host = ""
s.bind((host, port))
# s.listen(5)

# filename = raw_input("Enter file to share:")
# filename =
s.listen(5)
print 'Server listening....'
conn,addr = s.accept()
data = conn.recv(1024)
print data+"\n"
splitdata = data.split(' ')
l = len(splitdata)
print l
for i in range(l):
    while True:
        # conn, addr = s.accept()
        # print 'Got connection from', addr
        # data1 = conn.recv(1024)
        # print data1
        # print('Server received', repr(data1))
        print splitdata[i]
        my_file = Path('./Data/'+splitdata[i])
        if not my_file.is_file():
            conn.send("file was not found!")
            print("file was not found!")
            break
        conn.send("file is downloading..")
        f = open('./Data/'+ splitdata[i],'rb')
        l = f.read(1024)
        while (l):
           conn.send(l)
           print('Sent ',repr(l))
           l = f.read(1024)
        conn.send('$')
        f.close()

        print('Done sending')
        break;
# conn.send('Thank you for connecting')
    # conn.close()
s.close()
