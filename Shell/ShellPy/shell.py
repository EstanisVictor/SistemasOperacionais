import os
import getpass
import subprocess
from multiprocessing import Process, Semaphore
from threading import Thread
from time import sleep

if os.name == 'nt':
    import msvcrt
    semaphore = Semaphore()
else:
    import fcntl
    semaphore = Semaphore()


def prevent_access_file(file: str, command: list):
    semaphore.acquire()
    try:
        if os.name == 'nt':
            file = open(file, 'r+')
            msvcrt.locking(file.fileno(), msvcrt.LK_RLCK, 1)
            subprocess.run(command)
        else:
            file = open(file, 'r+')
            fcntl.flock(file, fcntl.LOCK_EX | fcntl.LOCK_NB)
            subprocess.run(command)
    except BlockingIOError:
        print('O arquivo está sendo editado por outro terminal. Aguarde ou escolha outro arquivo.')
    finally:
        if os.name == 'nt':
            msvcrt.locking(file.fileno(), msvcrt.LK_UNLCK, 1)
            file.close()
        else:
            fcntl.flock(file, fcntl.LOCK_UN)
            file.close()
        semaphore.release()
        sleep(1)


def run_shell_command():
    while True:
        command = input(f'\n{getpass.getuser()}@ SHELL {os.getcwd()} /> ')
        tokens = command.split(' ')

        if tokens[0] == 'dir' or tokens[0] == 'ls':
            subprocess.run(command, shell=True)

        elif tokens[0] == 'cat':
            if os.name == 'nt':
                subprocess.run(['type', tokens[1]])
            else:
                subprocess.run(['cat', tokens[1]])

        elif tokens[0] == 'mkdir':
            subprocess.run(['mkdir', tokens[1]])

        elif tokens[0] == 'cd':
            subprocess.Popen(command, cwd=tokens[1], shell=True)

        elif tokens[0] == 'rm':
            if tokens[1] == '-a':
                prevent_access_file(tokens[2], ['rm', tokens[2]])
            elif tokens[1] == '-r':
                prevent_access_file(tokens[2], ['rm', '-r', tokens[2]])

        elif tokens[0] == 'cp':
            prevent_access_file(tokens[1], ['cp', tokens[1], tokens[2]])

        elif tokens[0] == 'mv':
            subprocess.run(['mv', tokens[1], tokens[2]])

        elif tokens[0] == 'edit':
            prevent_access_file(tokens[1], ['nano', tokens[1]])

        elif command == 'exit':
            break


shell = Process(target=run_shell_command)
shell.run()
