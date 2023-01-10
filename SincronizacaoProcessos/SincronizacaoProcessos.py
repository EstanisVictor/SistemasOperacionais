from threading import Thread, Semaphore
from time import sleep

contador = 0

# Criando um objeto semaforo, permitindo que apenas 1 threads possa usar o semáforo por vez
semaforo = Semaphore(1)


class Processo(Thread):

    def __init__(self, p):
        Thread.__init__(self)
        self.p = p

    def run(self):
        global contador

        while True:

            semaforo.acquire()

            print(
                f"processo: {self.p}, entrou na regiao critica, contador: {contador}")

            sleep(1)
            contador = contador + 1

            # liberando o semáforo
            semaforo.release()
            print(
                f"processo: {self.p}, saiu da regiao critica, contador: {contador}")


p1 = Processo(1)
p2 = Processo(2)
p3 = Processo(3)
p4 = Processo(4)
p5 = Processo(5)
p6 = Processo(6)
p7 = Processo(7)
p8 = Processo(8)
p9 = Processo(9)
p10 = Processo(10)

p1.start()
p2.start()
p3.start()
p4.start()
p5.start()
p6.start()
p7.start()
p8.start()
p9.start()
p10.start()

p1.join()
p2.join()
p3.join()
p4.join()
p5.join()
p6.join()
p7.join()
p8.join()
p9.join()
p10.join()
