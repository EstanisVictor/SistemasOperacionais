import socket
from threading import Thread

PORTA = 2222

servidor = socket.socket()
# porta a ser utilizada do processo
servidor.bind(("", PORTA))
servidor.listen(5)
print("Servidor escutando na porta: ", PORTA)


def server():

    while True:
        # aceitando conexão do servidor com cliente
        cliente, endereco = servidor.accept()

        print("Conexao aceita de: ", endereco)

        msg_cliente = "".encode()

        while msg_cliente.decode() != "-1":
            mensagem = input("Digite...: ")
            # enviando mensagem para o cliente
            cliente.send(mensagem.encode())

            # recebendo mensagem do cliente
            msg_cliente = cliente.recv(1024)
            print("Cliente", cliente.getpeername(), " respondeu:")
            print(msg_cliente.decode(), "\n")

        if (msg_cliente.decode().lower() == "sair"):
            cliente.close()
            # netstat -ano | findstr 2222
            # taskkill /f /pid 2222


while True:
    # usando thread para comunicar com mais de um cliente
    Thread(target=server, args=()).start()
