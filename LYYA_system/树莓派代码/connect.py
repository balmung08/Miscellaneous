import socket
def s_connect():
    HOST = 'xxx.xx.xx.xxx'  # 服务器的公网IP
    PORT = 1177
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.connect((HOST, PORT))
    return sock
def updata(a,sock):
    sock.send(str(a).encode())
def update(a):
    sock = s_connect()
    updata("ts",sock)
    updata(a,sock)
    sock.recv(7)





