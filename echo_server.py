import socket

def start_echo_server(host='127.0.0.1', port=65432):
    # 创建一个TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        # 绑定 socket 到地址 (host, port)
        server_socket.bind((host, port))
        # 监听传入连接
        server_socket.listen()
        print(f"Echo server is running on {host}:{port}")

        while True:
            # 接受一个新的连接
            client_socket, client_address = server_socket.accept()
            with client_socket:
                print(f"Connected by {client_address}")
                while True:
                    # 接收数据
                    data = client_socket.recv(1024)
                    if not data:
                        break
                    # 回显接收到的数据
                    client_socket.sendall(data)

if __name__ == "__main__":
    start_echo_server()
