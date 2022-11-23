import socket

cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# fazendo conexão com servidor
cliente.connect(("localhost", 2222))

msg = "".encode()

while msg.lower() != "sair":
    # recebendo mensagem do servidor
    mensagem = cliente.recv(1024)

    if (mensagem.decode().lower() == "sair"):
        cliente.close()
    print("            C1 respondeu:")
    print("           ", mensagem.decode())

    msg = input("Digite...: ")

    # enviando mensagem para o servidor
    cliente.send(msg.encode())

    # fechando o cliente
if (msg.lower() == "sair"):
    cliente.close()
