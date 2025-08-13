# Pipex
## Overview

This project focuses on system-level programming and reimplementing the behavior of Unix pipelines using the C programming language. The goal is to deepen understanding of core Unix concepts by mimicking shell behavior for command piping.

It covers essential topics in Unix programming, including:

- Process creation
- Inter-process communication (IPC) using pipes
- File descriptor management, including ```dup2()``` for I/O redirection
- Program execution through ```execve()``` and PATH resolution
- Error handling and robust resource management (closing FDs, avoiding leaks)
- Working with file system operations like ```open()```, ```access()```, and permissions

### Getting started
#### Clone the repository
```bash
git clone git@github.com:zakaria552/pipex.git && cd pipex
```
#### Build the project
Make sure you have make installed (```make --version```) and then run the command
```bash
make
```

#### Usage

Piping multiple commands together
```bash
./pipex file cmd cmd1 cmd2 cmd3 ... outfile
# Same in bash as
< file cmd | cmd2 | cmd3 ... > outfile
```
Using here docs

```bash
./pipex here_doc eof cmd cmd1 cmd2 cmd3 ... outfile
# Same in bash as
cmd << eof | cmd1 | cmd2 | cmd3 ... > outfile
```
