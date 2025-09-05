# README: *fork\_exec\_wait.c*

## *Overview*

This program demonstrates how to use the fork(), execvp(), and waitpid() system calls to create child processes, execute commands, and handle process synchronization in a UNIX-like system. The program is flexible and supports multiple commands, which can be passed as arguments, or defaults to listing files with ls -l if no arguments are provided.

### *Key System Calls Used:*

* **fork()**: Used to create a child process.
* **execvp()**: Replaces the child process with a new command.
* **waitpid()**: Used by the parent process to wait for the child process to finish.

The program supports 10 different commands by default:

* ls (lists directory contents)
* date (displays the current date and time)
* uname (prints system information)
* ps (lists running processes)
* top (displays system processes dynamically)
* df (shows disk space usage)
* uptime (displays system uptime)
* whoami (prints the current logged-in user)
* free (displays memory usage)
* *Default behavior*: If no command is provided, defaults to ls -l.

## *Features*

* *Fork and Execute*: The program forks a child process, and the child process executes the requested command using execvp().
* *Parent Process Wait*: The parent process waits for the child to complete using waitpid() and handles various statuses (exit code, signals).
* *Error Handling*: Handles errors for fork(), execvp(), and waitpid(). If the command execution fails, the program reports an error.
* *Flexible Command Handling*: Supports several commands (ls, date, uname, ps, top, df, uptime, whoami, free), with the ability to handle user-specified arguments.
* *Graceful Exit*: Uses _exit() in the child process to avoid issues with double flushing of standard I/O buffers.

## *Installation & Compilation*

1. *Save the Code*: Save the code as fork_exec_wait.c.
2. *Compile the Program*:

   * Open a terminal and run the following command to compile the C program:

     bash
     gcc -Wall -Wextra -Wpedantic -O2 fork_exec_wait.c -o fork_demo
     
3. *Run the Program*:

   * After successful compilation, you can run the program with:

     bash
     ./fork_demo [command [arg1 arg2 ...]]
     
   * Example:

     bash
     ./fork_demo ls -l
     

## *Usage*

1. *Parent Process*:

   * The parent process prints its process ID (PID), waits for the child process to finish using waitpid(), and reports the child's exit status.

2. *Child Process*:

   * The child process prints its PID, executes the command provided by the user (or defaults to ls -l), and then terminates.

3. *Error Reporting*:

   * If the fork() fails, an error message is displayed.
   * If the execvp() fails to execute the command, the child will print an error and terminate with the status 127 (command not found).

## *Supported Commands*

* **ls**: Lists the files in the current directory. If no arguments are provided, it defaults to ls -l.
* **date**: Displays the current date and time.
* **uname -a**: Prints detailed system information.
* **ps aux**: Lists all running processes in a detailed format.
* **top -n 1**: Displays the system's processes for one iteration.
* **df -h**: Displays disk space usage in a human-readable format.
* **uptime**: Shows how long the system has been running and the system load.
* **whoami**: Prints the current logged-in user.
* **free -h**: Displays memory usage in a human-readable format.

## *Sample Commands and Outputs*

### 1. **Running ls -l (default)**

bash
$ ./fork_demo
* Parent Process ID: 12345
* Child Process ID: 12346
* total 48
* drwxrwxr-x  2 user user 4096 Jun  1 12:34 folder1
* drwxrwxr-x  2 user user 4096 Jun  1 12:34 folder2
* -rw-rw-r--  1 user user  123 Jun  1 12:34 file1.txt
* Child process has completed.


### 2. **Running date**

bash
* $ ./fork_demo date
* Parent Process ID: 12345
* Child Process ID: 12346
* Tue Jun  1 12:34:56 UTC 2021
* Child process has completed.


### 3. **Running uname -a**

bash
* $ ./fork_demo uname
* Parent Process ID: 12345
* Child Process ID: 12346
* Linux your-machine 5.4.0-84-generic #94-Ubuntu SMP Tue Jun 15 17:42:59 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
* Child process has completed.


### 4. **Running ps aux**

bash
* $ ./fork_demo ps
* Parent Process ID: 12345
* Child Process ID: 12346
* USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
* user     12345  0.1  1.2 123456 23456 pts/0    S+   12:34   0:01 ./fork_demo
* user     12346  0.0  0.1 123456 12345 pts/0    S+   12:34   0:00 ps aux
* Child process has completed.


### 5. **Running top -n 1**

bash
* $ ./fork_demo top
* Parent Process ID: 12345
* Child Process ID: 12346
* top - 12:34:56 up 1 day,  3:14,  2 users,  load average: 0.50, 0.60, 0.70
* Tasks: 200 total,   1 running,  199 sleeping,   0 stopped,   0 zombie
* %Cpu(s):  5.0 us,  3.0 sy,  0.0 ni, 90.0 id,  1.0 wa,  0.0 hi,  1.0 si,  0.0 st
* Mem:    4096MB total,   1024MB used,   3072MB free,   512MB buffers
* Child process has completed.


### 6. **Running df -h**

bash
* $ ./fork_demo df
* Parent Process ID: 12345
* Child Process ID: 12346
* Filesystem      Size  Used Avail Use% Mounted on
* /dev/sda1        50G   12G   35G  25% /
* tmpfs            4.0G  1.0G  3.0G  25% /dev/shm
* Child process has completed.


### 7. **Running uptime**

bash
* $ ./fork_demo uptime
* Parent Process ID: 12345
* Child Process ID: 12346
* 12:34:56 up 1 day,  3:14,  2 users,  load average: 0.50, 0.60, 0.70
* Child process has completed.


### 8. **Running whoami**

* bash
* $ ./fork_demo whoami
* Parent Process ID: 12345
* Child Process ID: 12346
* user
* Child process has completed.


### 9. **Running free -h**

bash
* $ ./fork_demo free
* Parent Process ID: 12345
* Child Process ID: 12346
               * total        used        free      shared  buff/cache   available
* Mem:            7.7Gi       3.2Gi       2.3Gi       0.2Gi       2.2Gi       3.8Gi
* Swap:           2.0Gi       0.0Gi       2.0Gi
* Child process has completed.


### 10. **Unknown Command (Fallback to ls -l)**

bash
* $ ./fork_demo unknown_command
* Unknown command: unknown_command. Defaulting to 'ls -l'.
* Parent Process ID: 12345
* Child Process ID: 12346
* total 48
* drwxrwxr-x  2 user user 4096 Jun  1 12:34 folder1
* drwxrwxr-x  2 user user 4096 Jun  1 12:34 folder2
* -rw-rw-r--  1 user user  123 Jun  1 12:34 file1.txt
* Child process has completed.


## *Conclusion*

This C program now supports 10 different Linux commands, providing a versatile tool for system information and diagnostics. The program is designed to handle multiple commands and fall back to ls -l in case of unrecognized input. It also gracefully handles errors and waits for child processes to complete.
