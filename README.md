# minishell

### Basic Concepts
#### What is a shell?
A shell, or **command interpreter**, is a software program that provides a user interface to access the services offered by the operating system. Depending on the type of interface used we can find different types of shell:
- **Command-Line Interface (CLI)**
- **Graphical-User Interface (GUI)**
- **Natural-User Interface (NUI)**

Shells are necessary to execute the different commands available on the computer.

#### What is bash?
**GNU Bash** is the Unix shell and command language. It is a **command interpreter** that generally runs in a text window (CLI) where the user writes commands in text mode. Bash can also read and execute commands from a file called **script**. The reserved words, syntax, environment variables, and other simple features are copied from the sh shell (Bourne Shell). Since bash can read user commands and respond accordingly, bash works as an **intermediary between the Linux kernel and users or programs**.<br>
However, there are many more bash-like shells. If we look in the **/etc/shells** file we will find all the shell types that we can use on our computer. Although we should not confuse bash with a terminal, they work together but are not the same.

#### What is a terminal?
Device used to communicate with the system. Today's computers use emulated terminals, which is software that emulates a terminal, generally a window where there is a CLI (Command-Line Interface).

#### What is a prompt?
A prompt is a character or a set of characters that is displayed on a command line **to indicate that the shell is waiting for instructions**. Typically, Bourne Shell and its derivatives use the $ character for non-privileged users. But if the user used is root, the prompt usually has #. The most common syntax used to display the prompt is:

      username@hostname:current_path$

### Differences between absolute and relative paths
What we know as a path is the place where a file is stored within the system. In fact, since we are using a file system, each file has a path within this system, which works as an address for the files. Every command we execute is executed considering its path, so if we don't specify any path, bash will consider that the file we are trying to use is located in our current directory.<br>
There are also two types of paths that we have to differentiate:
- **Absolute paths:** identifies the entire path file, including the root directory -> /home/user/Desktop/file.txt
- **Relative paths:** indicates the path in relation to our current position -> ./Desktop/file.txt (if we are in /home/user). If we want to go to the parent directory, we use '..'

### How to use environment variables?
Shell environment variables are **used to store settable values** used by shell scripts. In addition, we can create our own environment variables, so we could add them in case we need to run them in our programs.<br>
In bash, we have two types of environment variables:
- **Local variables**
- **Global variables**

The main difference between both types is that **a local variable is only visible from the shell in which it was created**, while **global variables are visible from every running process or every process run from that shell**. When you log in to the shell, the shell sets some global environment variables. All these variables are always in uppercase, so it is easier to differentiate them from those defined by the user. The command used to see the environment variables loaded in our session is **env**.<br>
<br>
To view the global and local variables defined in the shell session, use the set command. Every local variable that is set in the shell session will not be visible from another shell session.

#### PATH variable
PATH is one of the most important environment variables in bash. This variable **contains some paths that will be used to find the commands** that the user wants to execute without specifying its absolute or relative path. For example, if we want to execute ls (whose path is /bin/ls), since a part of the $ PATH variable is the path /bin, it will search /bin and finally execute /bin/ls. This way, the user does not have to worry about the command path. In case you want to know the path of a command, use **which + command**.

### What is an OS?
An Operating System is a set of programs that allows us to manipulate the memory, disk, storage devices and other hardware devices of our computer. In other words, an OS is **software that enables communication between the user and the computer**. If the user wants to store a file, the operating system will process the request and finally the file will be stored in memory if it is not full.<br>
However, in addition to managing hardware resources, an operating system is also **responsible for running processes**. What we know as a process will be seen later in this README file, but it is basically a running program.

### Basic bash commands

### Bash History
When we write and execute commands in the terminal, these commands are stored in a history called .bash_history. We can move through this history by pressing the up and down arrows on our keyboard. Also, if we want to inspect the contents of the .bash_history file, we can use **less .bash_history** to read this file.<br>
513 / 5000
Resultados de traducción
However, this file is not infinite, so there is a limitation on the number of commands that the bash history can store. This limitation is defined by the **$HISTFILESIZE** variable, whose value sets the maximum number of possible commands stored in .bash_history. To see all these commands we can use the **history command**. This command will show a numeric list with all the commands that have been executed, so if we type !n, the command at position n will be executed. 

### Globbing
Technique used to **identify all those files whose names are unknown but match a pattern that we want to identify**. This means that we have a brief idea of the elements that make up the names of these files. To achieve this we use **wildcards**, so that these are used to find patterns in the files that are being searched.<br>
For example:
<ul>
      <li><b>*</b> substitutes a string of characters.</li>
      <li><b>?</b> substitutes a letter in a word.</li>
      <li><b>[ ]</b> the values within them are what you are looking for.</li>
</ul>

### Redirections
Commands in bash **usually receive their input from STDIN and show the result of their execution in STDOUT**. By default, when a command reads from STDIN we have to send it the information using the keyboard, and when it shows its output in STDOUT, we see it on our computer screen. However, there is a way to set STDIN and STDOUT so that the program does not read from the keyboard but from a file, or so that the program is not displayed on the screen but in another file. **This technique used to change the STDIN and STDOUT of a program is accomplished through redirects**.<br>
There are different types of redirects, but the most important are:
<ul>
      <li><b>&gtfile</b> is used to overwrite a file with the output of a command.</li>
      <li><b>&gt&gtfile</b> is used to add the output of a command to the content of a file.</li>
      <li><b>&ltfile</b> sets the stdin of a command, so that it does not read from the keyboard but from the file.</li>
      <li><b>&lt&ltword</b> creates a temporary file that will not be finished until we write the word on a new line.</li>
</ul>

### Pipes
### Termcaps
### Ttys
### Processes
