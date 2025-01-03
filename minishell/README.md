# Minishell

Minishell is a project aimed at creating a simple command-line interpreter (shell) in C. It provides an opportunity to work with processes, file descriptors, and signal handling. The goal is to create a shell that behaves similarly to Bash.

## Instalation
1. Download repository
```bash
  git clone https://github.com/Zuraw7/minishell.git
  cd minishell
```
2. Compile source code
```bash
make
```
3. Run executable file
```bash
./minishell
```
# To avoid readline function leaks run
```bash
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.supp ./minishell
```

## Features

1. **Prompt Display:** Displays a prompt while waiting for user input.
2. **Command History:** Maintains a history of executed commands.
3. **Command Execution:** Searches for and executes commands while supporting environment variables.
4. **Quote Interpretation:** Handles single (`'`) and double (`"`) quotes, interpreting special characters accordingly.
5. **Redirections:** Implements input (`<`), output (`>`), heredoc (`<<`), and append (`>>`) redirections.
6. **Pipes:** Supports connecting commands with pipes (`|`).
7. **Built-in Commands:** Implements built-in commands that work like their Bash counterparts.

## My Contributions

As part of this group project, I was responsible for the following:

### 1. Input Parsing
- Dividing user input into arguments, commands, quotes, and operators.
- Converting the input into easy-to-execute elements by splitting it into tokens.

### 2. Built-in Command Implementation
- Ensuring built-in commands work exactly like in Bash.
- Implementing the following commands:
  - `echo` (with `-n` option)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Project Structure

- **Includes:** Contains the header file for Minishell and the `libft` library.
- **Sources:** Contains the source code, divided into the following subdirectories:
  - **Utils:** Utility functions.
  - **Parsing:** Takes user input and converts it into executable tokens.
  - **Builtins:** Implements built-in commands like `cd`, `echo`, and `exit`.
  - **Exec:** Executes commands and manages redirections.


