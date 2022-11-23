import socket

cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# fazendo conexão com servidor
cliente.connect(("ip da máquina aqui", 2222))

msg = "".encode()

while msg != "-1":
    # recebendo mensagem do servidor
    mensagem = cliente.recv(1024)

    print("            C1 respondeu:")
    print("           ", mensagem.decode())

    msg = input("Digite...: ")

    # enviando mensagem para o servidor
    cliente.send(msg.encode())

    # fechando o cliente
if (msg == "-1"):
    cliente.close()
