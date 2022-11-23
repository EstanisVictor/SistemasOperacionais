import socket

PORTA = 2222

servidor = socket.socket()
# porta a ser utilizada do processo
servidor.bind(("", PORTA))
servidor.listen(5)
print("Servidor escutando na porta: ", PORTA)

while True:
    # aceitando conexão do servidor com cloiente
    cliente, endereco = servidor.accept()
    print("Conexao aceita de: ", endereco)

    msg_cliente = "".encode()

    while msg_cliente.decode() != "-1":
        mensagem = input("Digite...: ")
        # enviando mensagem para o cliente
        cliente.send(mensagem.encode())

        # recebendo mensagem do cliente
        msg_cliente = cliente.recv(1024)
        print("            C2 respondeu:")
        print("           ", msg_cliente.decode())

    if (msg_cliente.decode() == "-1"):
        cliente.close()
        # netstat -ano | findstr 2222
        # taskkill /f /pid <PID>
