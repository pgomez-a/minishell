# minishell

### Basic Concepts
#### · What is a shell?
A shell, or **command interpreter**, is a software program that provides a user interface to access the services offered by the operating system. Depending on the type of interface used we can find different types of shell:
- **Command-Line Interface (CLI)**
- **Graphical-User Interface (GUI)**
- **Natural-User Interface (NUI)**

Shells are necessary to execute the different commands available on the computer.

#### · What is bash?
**GNU Bash** is the Unix shell and command language. It is a **command interpreter** that generally runs in a text window (CLI) where the user writes commands in text mode. Bash can also read and execute commands from a file called **script**. The reserved words, syntax, environment variables, and other simple features are copied from the sh shell (Bourne Shell). Since bash can read user commands and respond accordingly, bash works as an **intermediary between the Linux kernel and users or programs**.<br>
However, there are many more bash-like shells. If we look in the **/etc/shells** file we will find all the shell types that we can use on our computer. Although we should not confuse bash with a terminal, they work together but are not the same.

#### · What is a terminal?
Device used to communicate with the system. Today's computers use emulated terminals, which is software that emulates a terminal, generally a window where there is a CLI (Command-Line Interface).

#### · What is a prompt?
A prompt is a character or a set of characters that is displayed on a command line **to indicate that the shell is waiting for instructions**. Typically, Bourne Shell and its derivatives use the $ character for non-privileged users. But if the user used is root, the prompt usually has #. The most common syntax used to display the prompt is:

      username@hostname:current_path$

### Differences between absolute and relative paths
What we know as a path is the place where a file is stored within the system. In fact, since we are using a file system, each file has a path within this system, which works as an address for the files. Every command we execute is executed considering its path, so if we don't specify any path, bash will consider that the file we are trying to use is located in our current directory.<br>
There are also two types of paths that we have to differentiate:
- **Absolute paths:** identifies the entire path file, including the root directory -> /home/user/Desktop/file.txt
- **Relative paths:** indicates the path in relation to our current position -> ./Desktop/file.txt (if we are in /home/user). If we want to go to the parent directory, we use '..'



### How to use environment variables?
### What is an OS?
### Basic bash commands
### Bash History
### Login Shell vs Non-login Shell
### Globbing
### Quotes
### Redirections
### Pipes
### Termcaps
### Ttys
### Processes
