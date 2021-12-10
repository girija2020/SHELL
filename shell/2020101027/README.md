This is the shell I have made.

Assignment 2:

main.c:
I have executed a while loop which calls the functions get prompt and read prompt. It also notes the initial working directory in the global variable.

prompt.c:
In the function getprompt, I get the current working directory and parse it according to the home directory of shell which I take in as extern variable from main.
In readprompt, I continuously read the buffer until a \n is encountered and send my command to be parsed.

parse.c:
Here I token my input and get a value corresponding to the command recieved and switch between various commands. Taken necessary care to remove \n from the command recieved.

cd.c:
In this I use the chdir function to change the directory. I export the homedir value from maindir and when recieved the command ~ I put the homedir value int it. I store the previous working directory value through getcwd and I store it in a global variable so as to not lose it when the function is called again.

ls.c:
In this I used the stuct dirent to get the files and subdirectories in my directory. I checked the permissions of each and every file and print them through get permissions function. And in the get author function I get the owner, group owner, blocks, last modified date(ct_time), size and name of the file. According to the command recieved, I take the values of a and l and get my output accordingly even for multiple files. Files before an year only have year and month not time.

execvp.c:
fg: In this I execute a child process and make my parent process wait till the ending of the child process and return.
bg: I create a child process. And a grandchild process. I make the child process wait till the execution of the grandchild process where the parent will execute without hindrance and call upon the child process's kill through waitpid(WNOHANG).

pinf.c:
I print the process information in this. I read the file /proc/pid/stat and print the values required like pid, memory, state, I print the executable path from the file /proc/pid/exe by reading it as a link.

pwd: I use the getcwd command for this
echo: I use the printf command after tokenization.
repeat: I got my input number, and execute it that number of times using goto statement.
exit: It exits shell. exit(0) was used.

Assignment 3:

jobs: It maintains a linked list of structs and updates it whenever it recieves a signal from a background process.
fg: Changes the state of background process to run in foreground. Gets the pid from jobs. Using signal.
bg: Stopped background processes are restarted in background. Gets the pid from jobs. Using signal.
sig: An appropriate signal is given to a process with pid. Gets the pid from jobs. Using signal.
ctrl - c and ctrl - z: It maintains a signal handler, whenever a process is not running, it ignores it. Implemented by sig_ign. Else, it exits the foreground process. By giving control to signal handlers sigfunc and sigh.
ctrl - d : If the stdin recieves EOF then, we exit the terminal. It happens without effecting the actual terminal.
<,>,>> : They are implemented using dup2. If in place of stdin we have to take input from one file or output to a file instead of stdout.
| : I have implemented single pipe. fds[1] is being written to and is being read from fds[0]. I implemented piping and redirection together in '<' case.