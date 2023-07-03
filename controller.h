void exec(string command)
{
    vector<string> lstArg = getArg(command);
    int sizeOfLstArg = lstArg.size();
    if(sizeOfLstArg != 0)
    {
        if (lstArg[0].compare("help") == 0)
            help();

        else if (lstArg[0].compare("exit") == 0)
        {
            killAllProcess();
            this_thread::sleep_for(chrono::milliseconds(1000));
            exit(0);
        }

        else if (lstArg[0].compare("date") == 0)
        {
            HANDLE h1;
            DWORD ThreadId;
            h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)getDateTimeNow, NULL, 0, &ThreadId);
            cin.get();
            TerminateThread(h1, 0);
            CloseHandle(h1);
        }

        else if (lstArg[0].compare("time") == 0)
        {
            HANDLE h1;
            DWORD ThreadId;
            h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)getTimeNow, NULL, 0, &ThreadId);
            cin.get();
            TerminateThread(h1, 0);
            CloseHandle(h1);
        }

        else if (lstArg[0].compare("dir") == 0 || lstArg[0].compare("ls") == 0)
            listOfCurrent();

        else if (lstArg[0].compare("mkdir") == 0)
        {
            if(sizeOfLstArg == 2)
                createNewDir(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else if (lstArg[0].compare("rmdir") == 0)
        {
            if(sizeOfLstArg == 2)
                deleteDir(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else if (lstArg[0].compare("cd") == 0)
        {
            if(sizeOfLstArg == 2)
                cd(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else if (lstArg[0].compare("clear") == 0 || command.compare("cls") == 0)
            system("cls");

        // Create process
        else if (lstArg[0].compare("run") == 0 && sizeOfLstArg == 3)
        {
            if(lstArg[1].compare("notepad") == 0)
                openProcess(lstArg[2], "c:/windows/system32/notepad.exe");
            else if(lstArg[1].compare("mspaint") == 0)
                openProcess(lstArg[2], "c:/windows/system32/mspaint.exe");
            else if(lstArg[1].find(".exe") != string::npos)
            {
                string path = pwd() + "\\" + lstArg[1];
                openProcess(lstArg[2], path);
            }
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        // Manage process
        else if (lstArg[0].compare("list") == 0)
            showListProcess();

        else if (lstArg[0].compare("kill") == 0 && sizeOfLstArg == 2)
        {
            if (lstArg[1].compare("-a") == 0)
                killAllProcess();
            else if(sizeOfLstArg == 2)
                killOneProcess(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else if (lstArg[0].compare("stop") == 0)
        {
            if(sizeOfLstArg == 2)
                stopProcess(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else if (lstArg[0].compare("resume") == 0)
        {
            if(sizeOfLstArg == 2)
                resumeProcess(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        // ENV command
        else if (lstArg[0].compare("env") == 0)
        {
            if(sizeOfLstArg == 1)
                read_env("");
            else if(sizeOfLstArg == 2)
                read_env(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else if (lstArg[0].compare("addenv") == 0 && sizeOfLstArg == 5)
        {
            if(lstArg[1].compare("-n") == 0 || lstArg[1].compare("--name") &&
                    lstArg[3].compare("-v") == 0 || lstArg[3].compare("--value"))
            {
                string envname = lstArg[2];
                string envvalue = lstArg[4];
                add_env(envname, envvalue);
            }
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else if (lstArg[0].compare("delenv") == 0 && sizeOfLstArg == 2)
        {
            if(sizeOfLstArg == 2)
                del_env(lstArg[1]);
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        //run .bat
        else if (lstArg[0].compare("run") == 0 && sizeOfLstArg == 2)
        {
            if(lstArg[1].find(".bat") != string::npos)
            {
                string path = pwd() + "\\" + lstArg[1];
                runBat(path);
            }
            else
                CANNOT_HAVE_OUTPUT(command);
        }

        else
            COMMAND_NOT_FOUND(command);
    }
}
