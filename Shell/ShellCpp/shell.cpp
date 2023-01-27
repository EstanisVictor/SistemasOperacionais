#include <bits/stdc++.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

pthread_mutex_t semaphore;

#define YELLOW "\e[0;33m"
#define WHITE "\e[0;37m"
#define GREEN "\e[0;32m"
#define MAGENTA "\e[0;35m"

using namespace std;

vector<string> tokenize(string s, string del = " ")
{
    int start, end = -1 * del.size();
    vector<string> tokens;
    do
    {
        start = end + del.size();
        end = s.find(del, start);
        tokens.push_back(s.substr(start, end - start));
    } while (end != -1);

    return tokens;
}

string current_working_directory()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    string working_directory(cwd);
    return working_directory;
}

void *run_shell_command()
{
    string command = "", directory = current_working_directory();
    vector<string> tokens;
    while (true)
    {
        cout << GREEN << "\nuser@ " << MAGENTA << "SHELL " << YELLOW << directory << endl;
        cout << WHITE << "/> ";
        getline(cin, command);
        tokens = tokenize(command, " ");

        if (tokens[0] == "dir" || tokens[0] == "ls")
        {
#ifdef _WIN32
            system((command).c_str());
#else
            system((command).c_str());
#endif
        }
        else if (tokens[0] == "cat")
        {
            system(("cat " + tokens[1]).c_str());
        }
        else if (tokens[0] == "mkdir")
        {
            system(("mkdir " + tokens[1]).c_str());
        }
        else if (tokens[0] == "cd")
        {
            chdir(tokens[1].c_str());
            directory = current_working_directory();
        }
        else if (tokens[0] == "rm")
        {
            if (tokens[1] == "-a")
            {
                system(("rm " + tokens[2]).c_str());
            }
            else if (tokens[1] == "-r")
            {
#ifdef _WIN32
                system(("rmdir " + tokens[2]).c_str());
#else
                system((command).c_str());
#endif
            }
        }
        else if (command == "exit")
        {
            break;
        }
        else if (tokens[0] == "cp")
        {
#ifdef _WIN32
            system(("copy " + tokens[1] + " " + tokens[2]).c_str());
#else
            system(("cp " + tokens[1] + " " + tokens[2]).c_str());
#endif
        }
        else if (tokens[0] == "mv")
        {
#ifdef _WIN32
            system(("move " + tokens[1] + " " + tokens[2]).c_str());
#else
            system(("mv " + tokens[1] + " " + tokens[2]).c_str());
#endif
        }
        else if (tokens[0] == "edit")
        {
            pthread_mutex_lock(&semaphore);
#ifdef _WIN32
            system(("notepad " + tokens[1]).c_str());
#else
            system(("nano " + tokens[1]).c_str());
#endif
            pthread_mutex_unlock(&semaphore);
        }
    }
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&semaphore, NULL);

    pthread_create(&t1, NULL, NULL, run_shell_command);
    pthread_create(&t2, NULL, NULL, run_shell_command);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&semaphore);
    return 0;
}