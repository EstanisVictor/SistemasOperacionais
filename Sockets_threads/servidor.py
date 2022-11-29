import socket
import threading
import Thread

PORTA = 2222

servidor = socket.socket()
# porta a ser utilizada do processo
servidor.bind(("localhost", PORTA))
servidor.listen(5)
print("Servidor escutando na porta: ", PORTA)


def server():

    while True:
        # aceitando conexão do servidor com cliente
        cliente, endereco = servidor.accept()

        print("Conexao aceita de: ", endereco)
        # criando thread para multiclientes
        threading.Thread(target=multiClientes, args=(cliente,)).start()


def multiClientes(cliente):
    while mensagem.decode().lower() != "sair":
        mensagem = input("Digite...: ")
        # enviando mensagem para o cliente
        cliente.send(mensagem.encode())


server()
