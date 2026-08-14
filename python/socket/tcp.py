import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("0.0.0.0", 5000))
server.listen()

print("server listening port 5000")

client, address = server.accept()
print("client connected : ", address)

data = client.recv(1024)
print("received : ", data.decode())

client.sendall(b"hello from server")

client.close()