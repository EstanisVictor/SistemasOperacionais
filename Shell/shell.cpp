#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <dirent.h>

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
    char *cwd = _getcwd(0, 0); // **** microsoft specific ****
    string working_directory(cwd);
    free(cwd);
    return working_directory;
}

int main()
{
    string command = "", directory = current_working_directory();
    vector<string> tokens;

    while (true)
    {
        cout << GREEN << "\nuser@ " << MAGENTA << "SHELL " << YELLOW << directory << endl;
        cout << WHITE << "/> ";
        getline(cin, command);
        tokens = tokenize(command, " ");

        if (command == "dir")
        {
            system(command.c_str());
        }
        else if (command == "ls")
        {
            system(command.c_str());
        }
        else if (tokens[0] == "cat")
        {
            system(command.c_str());
        }
        else if (tokens[0] == "mkdir")
        {
            system(command.c_str());
        }
        else if (tokens[0] == "cd")
        {
            SetCurrentDirectoryA(tokens[1].c_str());
            directory = current_working_directory();
        }
        else if (tokens[0] == "rm")
        {
            system(command.c_str());
        }
        else if (command == "exit")
        {
            system("taskkill /im bash.exe /f");
            return 0;
        }
    }
}