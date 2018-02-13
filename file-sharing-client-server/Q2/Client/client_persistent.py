import socket
import sys

r = len(sys.argv)
print r

s = socket.socket()
host = ""
port = 60012
s.connect((host, port))
string =sys.argv[1]
for i in range(2,r):
        print sys.argv[i]
        string = string + ' ' + sys.argv[i]

s.send(string)

for j in range(1,r):

# filename = raw_input("Enter file that you want to download:");
# s.send("Hello server!")
    file_exist = s.recv(1024)
    print file_exist
    if file_exist == "file was not found!":
        continue

    with open(sys.argv[j], 'wb') as f:
        print sys.argv[j]
        print 'file opened'
        while True:
            print('receiving data...')
            data = s.recv(1024)
            print('data=%s', (data))
            if not data:
                # f.close()
                break
        # write data to a file
            f.write(data)
            if data[len(data)-1]=='$':
                f.close()
                break


        print('Successfully get the file')
s.close()
print('connection closed')
