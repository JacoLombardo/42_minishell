# minishell

minishell is a 42 School project that recreates a simplified bash-like shell in C. It is one of the largest projects in the 42 common core, focusing on processes, file descriptors, and how shells interpret and execute commands.

## Overview

The goal is to build a working shell that reads input, parses commands, handles pipes and redirections, runs builtins, and executes external programs. It teaches process management, signal handling, and shell internals.

## Composition

- **minishell.c** — entry point and main loop
- **includes/** — headers (execution, parsing, structs, types)
- **source/execution/** — command execution
  - `builtins/` — cd, echo, env, exit, export, pwd, unset
  - `exec.c`, `pipe.c`, `heredoc.c`, `redirections.c`
  - `signals.c`, `subshell.c`, `var.c`
- **source/parsing/** — command parsing and AST
- **source/tokenizing/** — lexer and token handling
- **source/expanding/** — variable expansion (`$VAR`, `$?`)
- **libraries/libft/** — custom C library

## Features

- **Command execution** — external programs via `execve`
- **Builtins** — cd, echo, env, exit, export, pwd, unset
- **Pipes** — `cmd1 | cmd2 | cmd3`
- **Redirections** — `>`, `>>`, `<`, `<<` (heredoc)
- **Variable expansion** — `$VAR`, `$?`
- **Signal handling** — Ctrl+C, Ctrl+\
- **Quotes** — single and double quotes

## Technology

- C (C99)
- libft (custom)
- readline (for input line editing)
- fork, execve, dup2, pipe, waitpid

## Setup

Install readline if needed (e.g. `sudo apt install libreadline-dev` on Debian). Update the readline path in the Makefile if necessary.

Build:

```bash
make
```

Run:

```bash
./minishell
```

## Makefile targets

| Target   | Description              |
|----------|--------------------------|
| `all`    | Build `minishell`        |
| `clean`  | Remove object files      |
| `fclean` | Remove objects and binary |
| `re`     | Fclean then rebuild      |

## Notes

- Team project at 42
- Requires proper readline installation and correct path in Makefile
- Subject: `minishell_subject.pdf`
