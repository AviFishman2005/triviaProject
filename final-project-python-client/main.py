import socket
import binascii

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 4554  # The port used by the server
import json

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        choice = input("Enter:\n 1. signup 2. login 3.error")
        username = input("Enter username")
        password = input("Enter password")
        message = ""
        if(choice == "1"):
            message = "3"
            mail = input("Enter mail")
            data = json.dumps({"username": username, "password": password, "email": mail})
            size = str(len(data))
            while len(size) != 4:
                size = "0" + size
            message += size
            message += data
        if(choice == "2"):
            message = "2"
            data = json.dumps({"username": username, "password": password})
            size = str(len(data))
            while len(size) != 4:
                size = "0" + size
            message += size
            message += data
        if(choice == "3"):
            message = "5"
            data = json.dumps({"username": username, "password": password})
            size = str(len(data))
            while len(size) != 4:
                size = "0" + size
            message += size
            message += data
        print(message.encode())
        s.sendall(message.encode())
        data = s.recv(2024)
        print(data)
        code = data[0]
        size = data[1] + data[2] + data[3] + data[4]
        print(size)
        print(code)
