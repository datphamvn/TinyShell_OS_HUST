#include <windows.h>
#include <direct.h> // _getcwd
#include <processthreadsapi.h> // PROCESS_INFORMATION
#include <handleapi.h> // CloseHandle
#include <bits/stdc++.h>
using namespace std;

string trim(const string &s)
{
    auto start = s.begin();
    while (start != s.end() && isspace(*start))
    {
        start++;
    }

    auto end = s.end();
    do
    {
        end--;
    }
    while (distance(start, end) > 0 && isspace(*end));

    return string(start, end + 1);
}

vector<string> getArg(string line)
{
    const string TOKEN_DELIMETERS = " \t";
    vector<string> tokens;
    size_t position = 0;
    bool in_quotes = false;
    string current_token = "";

    while (position != string::npos)
    {
        position = line.find_first_not_of(TOKEN_DELIMETERS, position);
        if (position != string::npos)
        {
            if (line[position] == '\"')
            {
                in_quotes = true;
                position++;
            }
            size_t end;
            if (in_quotes)
            {
                end = line.find_first_of('\"', position);
            }
            else
            {
                end = line.find_first_of(TOKEN_DELIMETERS, position);
            }
            if (end == string::npos)
            {
                end = line.length();
            }
            string token = line.substr(position, end - position);
            if (in_quotes)
            {
                current_token += token;
                if (line[end - 1] == '\"')
                {
                    tokens.push_back(current_token);
                    current_token = "";
                    in_quotes = false;
                }
                else
                {
                    current_token += " ";
                }
            }
            else
            {
                tokens.push_back(token);
            }
            position = end;
        }
    }
    return tokens;
}

void INFO_SHELL()
{
    cout << "Tiny Shell [Version 1.3.10]" << endl;
    cout << "Developed by Pham Vu Tuan Dat 20210158; Le Tuan Dat 20215340\n" << endl;
}

void COMMAND_NOT_FOUND(string command)
{
    cout << "The command '" + command + "' was not recognized.\n";
}

void CANNOT_HAVE_PARAMETER(string command)
{
    cout << "The command " + command + " cannot have parameters.\n";
}

void CANNOT_HAVE_OUTPUT(string command)
{
    cout << "The command '" + command + "' cannot have an output.\n";
}

void help()
{
    cout << "=========================================== GUIDE TO USING TINY SHELL ===========================================\n\n";
    cout.width(38);
    cout << left << "1.  help"
         << "Provide Help information for commands\n";
    cout.width(38);
    cout << left << "2.  cd .."
         << "Change to the parrent directory of the current directory\n";
    cout.width(38);
    cout << left << "3.  cd <path>"
         << "Change current directory to this path.\n";
    cout.width(38);
    cout << left << "" << "Noted: Using <\"path\"> for path have space character. Ex: cd \"Folder name\"\n";
    cout.width(38);
    cout << left << "4.  dir | ls"
         << "Display list of files in parent directory.\n";
    cout.width(38);
    cout << left << "5.  mkdir <name>"
         << "Create a new folder in current directory.\n";
    cout.width(38);
    cout << left << "6.  rmdir <name>"
         << "Delete a folder in current directory.\n";
    cout.width(38);
    cout << left << "7.  date"
         << "Display date\n";
    cout.width(38);
    cout << left << "8.  time"
         << "Display time\n";

    cout.width(38);
    cout << left << "9.  run mspaint -f|bg"
         << "Open MS paint with foreground or background mode.\n";
    cout.width(38);
    cout << left << "" << "Example in foreground mode: run mspaint -f; run mspaint --foreground\n";
    cout.width(38);
    cout << left << "" << "Example in background mode: run mspaint -bg; run mspaint --background\n";
    cout.width(38);
    cout << left << "10.  run notepad -f|bg"
         << "Open system notepad with foreground or background mode.\n";
    cout.width(38);
    cout << left << "" << "Example in foreground mode: run notepad -f; run notepad --foreground\n";
    cout.width(38);
    cout << left << "" << "Example in background mode: run notepad -bg; run notepad --background\n";
    cout.width(38);
    cout << left << "11.  run [*.exe] -f|bg"
         << "Open an application in current directory with foreground or background mode.\n";
    cout.width(38);
    cout << left << "" << "Example in foreground mode: run [*.exe] -f; run [*.exe] --foreground\n";
    cout.width(38);
    cout << left << "" << "Example in background mode: run [*.exe] -bg; run [*.exe] --background\n";
    cout.width(38);
    cout << left << "12. list"
         << "Display list of processes\n";
    cout.width(38);
    cout << left << "13. stop 'ID'"
         << "Stop a running process\n";
    cout.width(38);
    cout << left << "14. resume 'ID'"
         << "Resume a stopping process\n";
    cout.width(38);
    cout << left << "15. kill 'ID'"
         << "Kill a running process\n";
    cout.width(38);
    cout << left << "16. kill -a"
         << "Kill all running processes\n";
    cout.width(38);
    cout << left << "17. run [*.bat]"
         << "Read *.bat file and run list of command lines\n";
    cout.width(38);
    cout << left << "18. env"
         << "Display all the environment variables and their values\n";
    cout.width(38);
    cout << left << "19. env <name>"
         << "Display the value of the environment variable <name>. Ex: env PYTHON\n";
    cout.width(38);
    cout << left << "20. addenv -n <name> -v <value env>"
         << "Add the environment variable <name> with value is <value env>\n";
    cout.width(38);
    cout << left << "21. delenv <name>"
         << "Delete the environment variable <name>\n";
    cout.width(38);
    cout << left << "22. clear|cls"
         << "Clear tiny shell\n";
    cout.width(38);
    cout << left << "23. exit"
         << "Exit process\n";
    cout << endl;
}
