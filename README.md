# AFIT-CSCE489-PROJ1

## Compilation and Running Instructions

Download the contents of this repository, and from that directory, run the `make` command. Then run the resulting `myshell` compiled binary. 

## Development Notes
The hardest part of this project by far was parsing string input in C. I went with a tokenization approach, using the `strtok()` function to turn the user input string into a list of whitespace-separated tokens. This made it straightforward to determine what command the user entered and whether their command had the `&` for background processes, as well as handling excess whitespace automatically.  However, this approach made it cumbersome to reconstruct the text string for the update function. If I were to spend more time on this, I might implement a secondary string parsing technique such as sscanf strings or regex, which would allow me to more easily parse whitespace-separated strings. 

The shell loop was relatively easy; I’ve implemented REPL in other projects before. What set this project apart was debugging child processes, and GDB ended up being a handy tool for this. I found that I could use the command `set follow-fork-mode child` to have GDB switch to the child process on the `fork()` call. This made it very easy to figure out what was going wrong if a child process was silently failing. 

## Required Questions
### Why was it necessary that your shell use the `fork` command before running the `exec()` system call?
It was necessary because we want the shell to keep running and getting more user input after the user enters a command. The `exec()` system call essentially wipes the current process clean and overwrites it with the new code to execute, and if successful, it won’t return to the previous process. Thus, the `fork()` command was essential because we want the original process (i.e. the shell) to keep going after the command executes. 

### Explain, in as much detail as possible, what happened when you called the `fprintf` function. 
The `fprintf` function is used to write to a file or output stream, but there are a lot of steps inherent in that. We’ll start with the file definition:

```int fprintf(FILE *fptf, const char *str, …);```

When `fprintf` is called, it is passed a FILE pointer, `fptf`. A FILE pointer is a pointer to a C data structure that is defined and initialized in user space. This structure holds all the information about the file that the user program will need, including the most important bit: the file descriptor.   This descriptor is an integer value that the OS is using to keep track of open files, and it’s what the `fprintf` function will pass to the `write()` system call. 

Before the `write()` call, the `fprintf` function will take the string passed in by str and format it using the C format specifiers and the possible additional arguments denoted by `…`. Once that’s done, it has a value ready to write to the file, and the function will use the `write()` system call. 
The `write()` call is when things finally leave user space and enter kernel space. The OS will take the file descriptor, the string to write, and the length of the final string that `fprintf` calculates. It then attempts to write that buffered data to the file, with synchronization handled by the OS in case other processes are trying to access the same file.

According to the [man page](https://man7.org/linux/man-pages/man2/write.2.html)  for `write()`, the story doesn’t end there. There are several errors that could result from a `write()` call, and they could mean anything from none of the data was written to the data was partially written, but not fully. Presumably, the `fprintf` command handles these and returns error codes for ones that constitute severe issues. Further, a successful return from `write()` does not mean the data has been committed to disk; some OS designs store it in a buffer for a while. This is why the C code had to call the `fflush()` function, which makes its own system calls to force the write to the file. (Per the manpage for `write()`, the `fflush` function may use something like the `fsync()` system call.)
Once the write has been completed, the `fprintf` function back in user space returns the total number of characters written to the file and the program’s execution continues. 
