# SHELL
A simple shell to execute basic commands in c

Assignment 2
Shell Part 1
Operating Systems and Networks
Monsoon 2021

Specification 1: Display requirement
When you execute your code, a shell prompt of the following form will appear along with
it.
<username@system_name:curr_dir>
Example:
  <Name@UBUNTU:~>
If the user executes "cd" i.e changes the directory, then the
corresponding change will be reflected in the shell as well.

Example:
./a.out
  <Name@UBUNTU:~> cd newdir/test
  <Name@UBUNTU:~/newdir/test> cd ../..
  <Name@UBUNTU:~>

Specification 2: Builtin commands
Builtin commands are contained within the shell itself.
When the name of a built-in command is used as the first word of a simple command the
shell executes the command directly, without invoking another program. Builtin 
commands are necessary to implement functionality impossible or inconvenient to obtain
with separate utilities.
Implemented echo pwd and cd

Example: 
  <Name@UBUNTU:~> echo "abc 'ac' abc"
  “abc ‘ac’ abc”

Specification 3: ls command
Implemented the ls command with its two flags “-a” and “-l”. The following cases are 
handled:

  ● ls
  ● ls -a
  ● ls -l
  ● ls .
  ● ls ..
  ● ls ~
  ● ls -a -l
  ● ls -la / ls -al
  ● ls <Directory/File_name>
  ● ls -<flags> <Directory/File_name>
Example:
  
  <Name@UBUNTU:~> ls -al test_dir

Specification 4: System commands with and without arguments
All other commands are treated as system commands like emacs, vi, and so on. The shell
will be able to execute them either in the background or in the foreground.
Foreground processes: For example, executing a "vi" command in the foreground implies
that your shell will wait for this process to complete and regain control when this process
exits.
Background processes: Any command invoked with "&" is treated as a background
command. This implies that your shell will spawn that process and doesn't wait for the
process to exit. It will keep taking other user commands. Whenever a new background
process is started, it print the PID of the newly created background process on your shell
also.
Example:
    
  <Name@UBUNTU:~> gedit &
  456
  <Name@UBUNTU:~> ls -l -a
  .
  .
  . Execute other commands
  .
  .
  <Name@UBUNTU:~> echo hello

Specification 5: pinfo
pid -- 231
Process Status -- {R/S/S+/Z}
memory -- 67854 {Virtual Memory}
Executable Path -- ~/a.out
-pinfo <pid>: This prints the process info about the given PID.
Example:
<Name@UBUNTU:~>pinfo 7777
pid -- 7777
Process Status -- {R/S/S+/Z}
memory -- 123456 {Virtual Memory}
Executable Path -- /usr/bin/gcc
Process status codes:
1. R/R+: Running
2. S/S+: Sleeping in an interruptible wait
3. Z: Zombie
4. T: Stopped (on a signal)
Note: “+” is added to the status code if the process is in the foreground

Specification 6: Finished Background Processes
If the background process exits then the shell displays the appropriate message to the
user.
Example:
  
  <Name@UBUNTU:~> gedit &
  <Name@UBUNTU:~> cd test
  <Name@UBUNTU:~/test>
  gedit with pid 456 exited normally/abnormally

Specification 7: repeat Command
Implementing the repeat command. The command is responsible for executing the given
instruction multiple times. The first argument to the command specifies the number of
times the following command is to be run.
Example:
    
  <Name@UBUNTU:~/newdir/test> repeat 2 cd ..
  <Name@UBUNTU:~> repeat 3 echo hello
  hello
  hello
  hello
  <Name@UBUNTU:~> repeat 2 sleep 4 ( Sleep for 4 seconds twice)
  <Name@UBUNTU:~>
  

Assignment 3
Operating Systems and Networks | Monsoon 2021
Specification 1: Input/Output Redirection
Using the symbols <, > and >>, the output of commands, usually written to stdout, ​can be redirected to another file, or the input taken from a file other than ​stdin​. Both input and output redirection can be used simultaneously.
Example:
    
output redirection
<tux@linux:~> echo "hello" > output.txt
input redirection
  <tux@linux:~> cat < example.txt
input/output redirection
  <tux@linux:~> sort < file1.txt > lines_sorted.txt

Specification 2: Command Pipelines
A pipe, identified by | , redirects the output of the command on the left as input to the command on the right. One or more commands can be piped as the following
examples show.
Example:
    
two commands
  <tux@linux:~> cat file.txt | wc
three commands
  <tux@linux:~> cat sample2.txt | head -7 | tail -5

Specification 3: I/O Redirection within Command Pipelines
Input/output redirection can occur within command pipelines, as the examples below show.
Example:
  <tux@linux:~> ls | grep *.txt > out.txt
  <tux@linux:~> cat < in.txt | wc -l > lines.txt

Specification 4: User-defined Commands

1. jobs This command prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with
their job number (a sequential number assigned by your shell), process ID and their state, which can either be r ​ unning​ or ​stopped​ . There may be flags specified as well. If the flag specified is -r , then I print only the running processes else if the flag is -s then I print the stopped processes only.
Example:<tux@linux:~> jobs
[1] Running emacs assign1.txt [221]
[2] Running firefox [430]
[4] Stopped gedit [3213]
[3] Stopped vim [3211]

<tux@linux:~> jobs -r
[1] Running emacs assign1.txt [221]
[2] Running firefox [430]
<tux@linux:~> jobs -s
[4] Stopped gedit [3213]
[3] Stopped vim [3211]

2. sig Takes the job number (assigned by your shell) of a running job and sends the signal corresponding to s ​ ignal number​ to that process.
Example:
  
<tux@linux:~> sig 2 9
sends SIGKILL (signal number 9) to the process firefox (job # list as per the previous example), causing it to terminate
3. fg Brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to ​running .​
Example:

<tux@linux:~> fg 4
brings [4] gedit to the foreground
4. bg Changes the state of a stopped background job to running (in the background).
Example:
  
<tux@linux:~> bg 3
Changes the state of [3] vim to running (in the # background).

Specification 5: Signal Handling
1. CTRL-Z It pushes any currently running foreground job into the background, and change its state from running to stopped. This has no effect on the
shell if there is no foreground process running.
2. CTRL-C It interrupts any currently running foreground job, by sending it the ​SIGINT​ signal. This should have no effect on the shell if there is no foreground
process running.
3. CTRL-D It logs you out of your shell, without having any effect on the actual terminal.
