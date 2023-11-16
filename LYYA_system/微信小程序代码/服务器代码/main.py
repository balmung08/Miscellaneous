import socket
import time

def socket_portA():
    global status,send_code
    HOST = 'xxx.xx.xx.xx'  # 服务器的私网IP
    PORT = 1177
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((HOST, PORT))
    sock.listen(1)
    num = 0
    while True:
        connection, address = sock.accept()
        connection.settimeout(5)  # 5s
        try:
            code = None
            code = connection.recv(1024)
            if code == b'ts':
                a = connection.recv(1).decode()
                with open("../test/lyya.html", 'w' ) as f:
                    f.write(str(a))
                connection.send("success".encode())
        except Exception as e:
            pass


socket_portA()





