#include "utils.h"
#include "process.h"
#include "controller.h"

int main()
{
    INFO_SHELL();
    string command;

    while (true)
    {
        cout << pwd() << ">";
        signal(SIGINT, signal_callback_handler);

        fflush(stdin);
        getline(cin, command);
        cin.clear();

        trim(command);
        exec(command);
    }
    return 0;
}
