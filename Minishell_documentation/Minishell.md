Minishell

# Minishell

How shell works :

- [Minishell](#minishell)
    - [1\. Shell read input from :](#1-shell-read-input-from)
    - [2\. Breaks the input into words and operators separated with metacharacters.](#2-breaks-the-input-into-words-and-operators-separated-with-metacharacters)
    - [3\. Breaks the tokens into simple and compound commands](#3-breaks-the-tokens-into-simple-and-compound-commands)
    - [4\. Performs the various shell expansions, breaking the expanded tokens into lists of filenames and commands, and arguments.](#4-performs-the-various-shell-expansions-breaking-the-expanded-tokens-into-lists-of-filenames-and-commands-and-arguments)
    - [5\. Performs any necessary redirections and re- moves the redirection operators and their operands from the argument list.](#5-performs-any-necessary-redirections-and-re-moves-the-redirection-operators-and-their-operands-from-the-argument-list)
    - [6\. Executes the command](#6-executes-the-command)
    - [7\. Optionally waits for the command to complete and collects its exit status](#7-optionally-waits-for-the-command-to-complete-and-collects-its-exit-status)

## 1\. Shell read input from :

- **file** (not required in the subject : no arguments for minishell program)
- **standard input**, the terminal (fd =0)

**Comments** : a word beginning with ``#`` causes that word and all remaining characters on that line to be ignored.
    
    * * *
    

## 2\. Breaks the input into **words** and **operators** separated with **metacharacters**.

*Metacharacter is a character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters:*  
`|` , `&`, `;`, `(`, `)`, `<`, or `>`.  
These separated words and operators are called **tokens**.  
3 types of quoting :

- **Escape character** `\`: preserves the literal value of the next character except for newline -> \\newline != \\\newline
- **single quote** `''`: preserves the literal value of each character within the quotes. Can’t write single quote into single quotes `'''`
- **double quote** `""`: Enclosing characters in double quotes `""` preserves the literal value of all characters within the quotes, with the exception of `$`, `‘` and `\`.
    - The characters `$` and `‘` retain their special meaning within double quotes.The backslash `\` retains its special meaning only when followed by one of the following characters: `$`, `‘`, `"`, `\`, or `newline`.
    - Within double quotes, backslashes that are followed by one of these characters are removed. Backslashes preceding characters without a special meaning are left unmodified.
    - A double quote may be quoted within double quotes by preceding it with a backslash.  
    - The special parameters `*` and `@` have special meaning when in double quotes

* * *

## 3\. Breaks the **tokens** into simple and compound **commands**

## 4\. Performs the various **shell expansions**, **breaking** the expanded **tokens** **into** lists of **filenames** and **commands**, and **arguments**.

The shell expansions are done following this **order**, from left to right : 
1. Brace expansion (not required in subject)
2.  Tilde expansion 
3.  Parameter and variable expansion 
	- A **parameter** is an entity that stores values. It can be a **name, a number**, or one of the **special characters** listed below.   
	- A **variable** is a **parameter denoted by a name**. A variable has a value and zero or more attributes. Attributes are assigned using the `export` (`declare` in bash manual) builtin command.  
	- A parameter is set if it has been assigned a value. The null string is a valid value. Once a variable is set, it may be unset only by using the `unset` builtin command.  
	- A variable may be assigned to by a statement of the form :
`name=[value]`
	- If value is not given, the variable is assigned the null string. All values undergo tilde ex- pansion, parameter and variable expansion, command substitution, arithmetic expansion, and quote removal (detailed below).  
	- If the variable has its integer attribute set, then value is evaluated as an arithmetic expression even if the `$((...))` expansion is not used
	- Word splitting is not performed, with the exception of ``"$@"`` as explained below. Filename expansion is not performed.  
	- Assignment statements may also appear as arguments to the export,  
	(not required/bonus) alias, declare, typeset,  readonly, and local builtin commands (declaration commands).  
	- Indirect Variable References (namerefs)  
	`declare -n ref=$1`
	(not required because use option `-n`)

5.  Command substitution
6.  Arithmetic expansion
7.  Word splitting 
8.  filename expansion

## 5\. **Performs** any necessary **redirections** and **re- moves the redirection operators** and their operands from the argument list.

## 6\. **Executes** the **command**
Each command in a pipeline is executed in its own subshell, which is a separate process  
The exit status of a pipeline is the exit status of the last command in the pipeline  
The shell waits for all commands in the pipeline to terminate before returning a value.  

(not required in subject) If a command is terminated by the control operator `&`, the shell executes the command asynchronously in a subshell. This is known as executing the command in the background, and these are referred to as asynchronous commands. The shell does not wait for the command to finish, and the return status is 0 (true).

## 7\. **Optionally waits** for the **command** to complete and collects its **exit status**

### Definitions:
**control operator** :
A token that performs a control function. It is a newline or one of the following: `;`, `|`.  
(BONUS):`;;`, `;&`, `;;&`,`|&`, `||`, `&&`, `&`, `(`, or `)`.  
**exit status** :
The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255.
**signal** : A mechanism by which a process may be notified by the kernel of an event occurring in the system.  
**token** :  A sequence of characters considered a single unit by the shell. It is either a word or an operator.
word A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.  
**Pipeline** : a sequence of one or more commands separated by one of the control operators ``|`` or  
(BONUS) ``|&``.  
**Lists of Commands** : A list is a sequence of one or more pipelines separated by one of the operators `;`, `&`.  
(BONUS)`&&`, or `||`, and optionally terminated by one of `;`, `&`, or a newline.

Sources: https://www.gnu.org/software/bash/manual/bash.pdf