import socket
import sys #we will be able to use filenames given in
            #command line and sys related operations
no_files = len(sys.argv)-1 # this len func gives no of files +1
                      # +1 because it has file name i.e; our client filenames
for i in range(no_files):
    s = socket.socket()
    host = ""
    port = 50016
    s.connect((host, port))
    s.send(sys.argv[i+1])

    file_exist = s.recv(1024)
    print file_exist
    if file_exist == "file was not found!":
        continue
    with open(sys.argv[i+1], 'wb') as f:
        print 'file opened'
        while True:
            print('receiving data...')
            data = s.recv(1024)
            print('data=%s', (data))
            if not data:
                break
            # write data to a file
            f.write(data)

    f.close()
    print('Successfully get the file')
    s.close()
print('connection closed')
