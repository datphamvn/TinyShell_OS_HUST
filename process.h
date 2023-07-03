PROCESS_INFORMATION pi[100];
STARTUPINFO si[100];
LPSTR cString[100];
HANDLE hHandless[100];
HANDLE hForeProcess;
int status[100];
int numProcess = 0; // number of Process
#define MAX_NAME_ENV 16383
#define MAX_VALUE_ENV 100000

void exec(string command);

string pwd()
{
    string getCurrentDir = "";
    char *buffer = _getcwd(NULL, 0);
    int i = 0;
    while(buffer[i] != '\0')
    {
        getCurrentDir += buffer[i];
        i++;
    }
    return getCurrentDir;
}

void signal_callback_handler(int signum)
{
    if (hForeProcess != NULL)
    {
        TerminateProcess(hForeProcess, 0);
        hForeProcess = NULL;
    }
    //exit(1);
}

void killOneProcess(string s)
{
    int id = atoi(s.c_str());

    bool unKill = true;
    for (int i = 1; i <= numProcess; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);

            printf("Process %s killed\n", cString[i]);
            for (int j = i; j < numProcess; ++j)
            {
                status[j] = status[j + 1];
                pi[j] = pi[j + 1];
                si[j] = si[j + 1];
                cString[j] = cString[j + 1];
            }
            numProcess--;
            unKill = false;
            break;
        }
    }
    if (unKill)
        printf("Can't find process with this id = %d\n", id);
}

void killAllProcess()
{
    for (int i = 1; i <= numProcess; ++i)
    {
        TerminateProcess(pi[i].hProcess, 0);
        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);
    }
    cout << "All process killed ...\n";
    numProcess = 0;
}

void stopProcess(string s)
{
    int id = atoi(s.c_str());
    bool unStop = true;
    for (int i = 1; i <= numProcess; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            if (status[i] == 1)
            {
                status[i] = 0;
                cout << "Stop " << cString[i] << " success\n";
                SuspendThread(pi[i].hThread);
                unStop = false;
                break;
            }
            else
            {
                cout << "Process " << cString[i] << " is still stopping" << endl;
                unStop = false;
                break;
            }
        }
    }
    if (unStop)
        printf("Can't find process with this id = %d\n", id);
}
void resumeProcess(string s)
{
    int id = atoi(s.c_str());
    bool unResume = true;
    for (int i = 1; i <= numProcess; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            if (status[i] == 0)
            {
                status[i] = 1;
                cout << "Process " << cString[i] << " is running again\n";
                ResumeThread(pi[i].hThread);
                unResume = false;
                break;
            }
            else
            {
                cout << "Process " << cString[i] << " is still running" << endl;
                unResume = false;
                break;
            }
        }
    }
    if(unResume)
        printf("Can't find process with this id = %d\n", id);
}

void openProcess(const string mode, const string &s)
{
    void openProcessInForeGround(const string &s);
    void openProcessInBackGround(const string &s);
    if (mode.compare("-bg") == 0 || mode.compare("--background") == 0)
        openProcessInBackGround(s);
    else if (mode.compare("-f") == 0 || mode.compare("--foreground") == 0)
        openProcessInForeGround(s);
    else
        cout << "Error when start process!" << endl;
}

void openProcessInForeGround(const string &s)
{

    PROCESS_INFORMATION pi;                 // lpStartupInfo    // lpProcessInformation
    STARTUPINFO si = {sizeof(STARTUPINFO)}; // cpp string must be modified to use in c
    LPSTR cString = strdup(s.c_str());
    ZeroMemory(&si, sizeof(si)); // fill this block with zeros
    si.cb = sizeof(si);          // CreateProcess(cString, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (!CreateProcess(cString,  // No module name (use command line)
                       NULL,     // Command line
                       NULL,     // Process handle not inheritable
                       NULL,     // Thread handle not inheritable
                       FALSE,    // Set handle inheritance to FALSE
                       CREATE_NEW_CONSOLE,
                       NULL, // Use parent's environment block
                       NULL, // Use parent's starting directory
                       &si,  // Pointer to STARTUPINFO structure
                       &pi)  // Pointer to PROCESS_INFORMATION structure
       )
    {
        printf("Opening process not successful!\n");
        return;
    }
    else
        hForeProcess = pi.hProcess;
    WaitForSingleObject(pi.hProcess, INFINITE); // INFINITE // hProcess: The handle is used to specify the process in all functions that perform operations on the process object.
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

void openProcessInBackGround(const string &s)
{
    void kill(string s);
    ++numProcess;
    status[numProcess] = 1;
    si[numProcess] = {sizeof(STARTUPINFO)};     // lpStartupInfo // lpProcessInformation
    pi[numProcess];                             // cpp string must be modified to use in c
    ZeroMemory(&si[numProcess], sizeof(si[numProcess])); // fill this block with zeros
    si[numProcess].cb = sizeof(si[numProcess]);
    cString[numProcess] = strdup(s.c_str()); // CreateProcess(cString, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (!CreateProcess(cString[numProcess],  // No module name (use command line)
                       NULL,        // Command line
                       NULL,        // Process handle not inheritable
                       NULL,        // Thread handle not inheritable
                       FALSE,       // Set handle inheritance to FALSE
                       CREATE_NEW_CONSOLE,
                       NULL,   // Use parent's environment block
                       NULL,   // Use parent's starting directory
                       &si[numProcess], // Pointer to STARTUPINFO structure
                       &pi[numProcess]) // Pointer to PROCESS_INFORMATION structure
       )
    {
        TerminateProcess(pi[numProcess].hProcess, 0);
        CloseHandle(pi[numProcess].hThread);
        CloseHandle(pi[numProcess].hProcess);
        numProcess--;
        printf("Opening process not successful!\n");
        return;
    }
}

void listOfCurrent()
{
    char *buffer;

    if ((buffer = _getcwd(NULL, 0)) == NULL)
        perror("Error: ");
    if (_chdir(buffer))
    {
        switch (errno)
        {
        case ENOENT:
            cout << "No such file or directory.\n";
            break;
        case EINVAL:
            cout << "Invalid buffer.\n";
            break;
        default:
            cout << "Unknown error.\n";
            break;
        }
    }
    else
        system("dir");

    free(buffer);
}

void showListProcess()
{
    //Track running process
    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    printf(" Numbers            IdProcess                hProcess               Status                      Name   \n");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 1; i <= numProcess; ++i)
    {
        DWORD dwExitCode;
        GetExitCodeProcess(pi[i].hProcess, &dwExitCode);
        if (dwExitCode != 259)
        {
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);
            for (int j = i; j < numProcess; ++j)
            {
                status[j] = status[j + 1];
                pi[j] = pi[j + 1];
                si[j] = si[j + 1];
                cString[j] = cString[j + 1];
            }
            numProcess--;
            i--;
        }
        else
        {
            const char *a = (status[i] == 0) ? "stopping" : "Running ";
            printf("   %-19d%-26d%-20p%s          %s\n", i, pi[i].dwProcessId, pi[i].hProcess, a, cString[i]);
        }
    }
    cout << "\n\n";
}

void cd(string s)
{
    char dir[100];
    LPSTR cString = strdup(s.c_str()); // pass your path in the function
    int ch = chdir(cString);           // if the change of directory was successful it will print successful otherwise it will print not successful
    if (ch < 0)
    {
        openProcess("-bg", cString);
    }
}

void createNewDir(string path)
{
    char *pathDir = const_cast<char*>(path.c_str());
    if(mkdir(pathDir) == -1)
        cerr << " Error : " << strerror(errno) << endl;
    else
        cout << "Folder Created" << endl;
}

void deleteDir(string path)
{
    char *pathDir = const_cast<char*>(path.c_str());
    if(rmdir(pathDir) == -1)
        cerr << " Error : " << strerror(errno) << endl;
    else
        cout << "Folder Deleted" << endl;
}

void read_env(string strENVName)
{
    char *envname = const_cast<char*>(strENVName.c_str());
    HKEY hkey;
    BYTE value[MAX_VALUE_ENV] ;
    DWORD valsize = sizeof(value) ;
    RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_ALL_ACCESS, &hkey);

    if (strENVName == "")
    {
        for (int i = 0; ; i ++)
        {
            TCHAR name[MAX_NAME_ENV];
            DWORD namesz = MAX_NAME_ENV;
            value[0] = '\0';
            DWORD valsize = MAX_VALUE_ENV;
            if (RegEnumValue(hkey, i, name, &namesz, NULL, NULL, value, &valsize) == 0)
                cout << (i < 9 ? "0":"") << i + 1 <<". " << name << " = " << value << endl;
            else
                break;
        }
    }
    else if (RegQueryValueEx(hkey, envname, NULL, NULL, value, &valsize ) == 0)
        cout << "The value of "<< envname << " is: " << value << endl;
    else
        cout << "There no variables has the name " << envname << endl;

    RegCloseKey(hkey);
}

void add_env(string strENVName, string strENVValue)
{
    char *envname = const_cast<char*>(strENVName.c_str());
    char *envvalue = const_cast<char*>(strENVValue.c_str());
    cout << "The environment variable "<< envname<< " is added\n";
    HKEY hkey;
    static BYTE value[100000] ;
    DWORD valsize = sizeof(value) ;
    RegOpenKeyEx(HKEY_CURRENT_USER,"Environment", 0, KEY_ALL_ACCESS, &hkey);
    if(RegQueryValueEx(hkey, envname, NULL, NULL, value, &valsize) == 0)
    {
        char *name  = (char*) value;
        strcat(name, ";");
        strcat(name, envvalue);
        RegSetValueEx(hkey,envname,0,REG_SZ,(BYTE*) name, strlen(name));
    }
    else
        RegSetValueEx(hkey,envname,0,REG_SZ,(BYTE*) envvalue, strlen(envvalue));

    RegCloseKey(hkey);
}

void del_env(string strENVName)
{
    char *envname = const_cast<char*>(strENVName.c_str());
    HKEY hkey;
    RegOpenKeyEx(HKEY_CURRENT_USER,"Environment", 0, KEY_ALL_ACCESS, &hkey);
    if (RegDeleteValue(hkey, envname) == 0)
        cout << "The environment variable " << envname << " is deleted" << endl;
    else
        cout << "There no variables has the name " << envname << endl;
    RegCloseKey(hkey);
}

string getDateTimeNow()
{
    while(1)
    {
        // Get local time
        SYSTEMTIME st;
        GetLocalTime(&st);

        // Convert to tm struct
        tm timeinfo;
        timeinfo.tm_year = st.wYear - 1900;
        timeinfo.tm_mon = st.wMonth - 1;
        timeinfo.tm_mday = st.wDay;
        timeinfo.tm_hour = st.wHour;
        timeinfo.tm_min = st.wMinute;
        timeinfo.tm_sec = st.wSecond;

        // Format the date time string
        ostringstream oss;
        oss << put_time(&timeinfo, "%A %I:%M:%S %p  %d/%m/%Y");
        cout << '\r';
        cout << oss.str();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void getTimeNow()
{
    while(1)
    {
        SYSTEMTIME currentTime;
        GetLocalTime(&currentTime);

        char timeString[20];
        sprintf_s(timeString, "%02d:%02d:%02d", currentTime.wHour, currentTime.wMinute, currentTime.wSecond);

        cout << '\r';
        cout << string(timeString);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void runBat(string path)
{
    ifstream file(path);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
            exec(line);
    }
    else
        cout << "File " << path << " do not exist in this directory\n";
}
