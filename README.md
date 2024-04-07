
# TinyShell_OS_HUST

## Description
TinyShell is a minimalist shell for operating system simulations, developed as part of the Operating Systems course at Hanoi University of Science and Technology (HUST). It provides a basic shell environment with commands for managing files, directories, processes, and system information.

## Installation

To install TinyShell, follow these steps:

1. Clone the repository:
```bash
git clone https://github.com/datphamvn/TinyShell_OS_HUST.git
```

2. Navigate to the TinyShell directory:
```bash
cd TinyShell_OS_HUST
```

3. Compile the source code (ensure you have the necessary compilers installed):
```bash
make all
```

## Usage

Run TinyShell with the command:

```bash
./tinyshell
```

Once started, you can use the following commands within TinyShell:

- `help`: Provide help information for commands.
- `cd ..`: Change to the parent directory of the current directory.
- `cd <path>`: Change the current directory to the specified path. Use quotes for paths with spaces.
- `dir | ls`: Display list of files in the current directory.
- `mkdir <name>`: Create a new folder in the current directory.
- `rmdir <name>`: Delete a folder in the current directory.
- `date`: Display the current date.
- `time`: Display the current time.
- `run mspaint -f|bg`: Open MS Paint in foreground or background mode.
- `run notepad -f|bg`: Open system Notepad in foreground or background mode.
- `run [*.exe] -f|bg`: Execute an executable in the current directory in foreground or background mode.
- `list`: Display list of processes.
- `stop 'ID'`: Stop a running process.
- `resume 'ID'`: Resume a stopped process.
- `kill 'ID'`: Kill a running process.
- `kill -a`: Kill all running processes.
- `run [*.bat]`: Execute a batch file and run a list of command lines.
- `env`: Display all environment variables and their values.
- `env <name>`: Display the value of the specified environment variable.
- `addenv -n <name> -v <value>`: Add an environment variable with the specified value.
- `delenv <name>`: Delete the specified environment variable.
- `clear | cls`: Clear the TinyShell console.
- `exit`: Exit TinyShell.

## Features

- Command parsing and execution
- Directory navigation
- File and process management
- Environment variable manipulation
- System information display

## Contributing

We welcome contributions to TinyShell. If you have suggestions or improvements, please fork the repository, make your changes, and submit a pull request.

## License

TinyShell is released under the MIT License. For more details, see the LICENSE file in the repository.
