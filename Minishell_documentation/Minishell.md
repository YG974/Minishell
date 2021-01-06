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

env : These strings have the form name=value; names shall not contain the character '='. For values to be portable across systems conforming to IEEE Std 1003.1-2001, the value shall be composed of characters from the portable character set (except NUL and as indicated below).
Environment variable names used by the utilities in the Shell and Utilities volume of IEEE Std 1003.1-2001 consist solely of uppercase letters, digits, and the '_' (underscore) from the characters defined in Portable Character Set and do not begin with a digit. Other characters may be permitted by an implementation; applications shall tolerate the presence of such names.


2.10 Shell Grammar
The following grammar defines the Shell Command Language. This formal syntax shall take precedence over the preceding text syntax description.

2.10.1 Shell Grammar Lexical Conventions
The input language to the shell must be first recognized at the character level. The resulting tokens shall be classified by their immediate context according to the following rules (applied in order). These rules shall be used to determine what a "token" is that is subject to parsing at the token level. The rules for token recognition in Token Recognition shall apply.

A <newline> shall be returned as the token identifier NEWLINE.

If the token is an operator, the token identifier for that operator shall result.

If the string consists solely of digits and the delimiter character is one of '<' or '>', the token identifier IO_NUMBER shall be returned.

Otherwise, the token identifier TOKEN results.

Further distinction on TOKEN is context-dependent. It may be that the same TOKEN yields WORD, a NAME, an ASSIGNMENT, or one of the reserved words below, dependent upon the context. Some of the productions in the grammar below are annotated with a rule number from the following list. When a TOKEN is seen where one of those annotated productions could be used to reduce the symbol, the applicable rule shall be applied to convert the token identifier type of the TOKEN to a token identifier acceptable at that point in the grammar. The reduction shall then proceed based upon the token identifier type yielded by the rule applied. When more than one rule applies, the highest numbered rule shall apply (which in turn may refer to another rule). (Note that except in rule 7, the presence of an '=' in the token has no effect.)

The WORD tokens shall have the word expansion rules applied to them immediately before the associated command is executed, not at the time the command is parsed.

2.10.2 Shell Grammar Rules
[Command Name]

When the TOKEN is exactly a reserved word, the token identifier for that reserved word shall result. Otherwise, the token WORD shall be returned. Also, if the parser is in any state where only a reserved word could be the next correct token, proceed as above.

Note:
Because at this point quote marks are retained in the token, quoted strings cannot be recognized as reserved words. This rule also implies that reserved words are not recognized except in certain positions in the input, such as after a <newline> or semicolon; the grammar presumes that if the reserved word is intended, it is properly delimited by the user, and does not attempt to reflect that requirement directly. Also note that line joining is done before tokenization, as described in Escape Character (Backslash) , so escaped <newline>s are already removed at this point.
Rule 1 is not directly referenced in the grammar, but is referred to by other rules, or applies globally.

[Redirection to or from filename]

The expansions specified in Redirection shall occur. As specified there, exactly one field can result (or the result is unspecified), and there are additional requirements on pathname expansion.

[Redirection from here-document]

Quote removal shall be applied to the word to determine the delimiter that is used to find the end of the here-document that begins after the next <newline>.

[Case statement termination]

When the TOKEN is exactly the reserved word esac, the token identifier for esac shall result. Otherwise, the token WORD shall be returned.

[ NAME in for]

When the TOKEN meets the requirements for a name (see the Base Definitions volume of IEEE Std 1003.1-2001, Section 3.230, Name), the token identifier NAME shall result. Otherwise, the token WORD shall be returned.

[Third word of for and case]

[ case only]

When the TOKEN is exactly the reserved word in, the token identifier for in shall result. Otherwise, the token WORD shall be returned.

[ for only]

When the TOKEN is exactly the reserved word in or do, the token identifier for in or do shall result, respectively. Otherwise, the token WORD shall be returned.

(For a. and b.: As indicated in the grammar, a linebreak precedes the tokens in and do. If <newline>s are present at the indicated location, it is the token after them that is treated in this fashion.)

[Assignment preceding command name]

[When the first word]

If the TOKEN does not contain the character '=', rule 1 is applied. Otherwise, 7b shall be applied.

[Not the first word]

If the TOKEN contains the equal sign character:

If it begins with '=', the token WORD shall be returned.

If all the characters preceding '=' form a valid name (see the Base Definitions volume of IEEE Std 1003.1-2001, Section 3.230, Name), the token ASSIGNMENT_WORD shall be returned. (Quoted characters cannot participate in forming a valid name.)

Otherwise, it is unspecified whether it is ASSIGNMENT_WORD or WORD that is returned.

Assignment to the NAME shall occur as specified in Simple Commands.

[ NAME in function]

When the TOKEN is exactly a reserved word, the token identifier for that reserved word shall result. Otherwise, when the TOKEN meets the requirements for a name, the token identifier NAME shall result. Otherwise, rule 7 applies.

[Body of function]

Word expansion and assignment shall never occur, even when required by the rules above, when this rule is being parsed. Each TOKEN that might either be expanded or have assignment applied to it shall instead be returned as a single WORD consisting only of characters that are exactly the token described in Token Recognition.


/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */


%token  WORD
%token  ASSIGNMENT_WORD
%token  NAME
%token  NEWLINE
%token  IO_NUMBER


/* The following are the operators mentioned above. */


%token  AND_IF    OR_IF    DSEMI
/*      '&&'      '||'     ';;'    */


%token  DLESS  DGREAT  LESSAND  GREATAND  LESSGREAT  DLESSDASH
/*      '<<'   '>>'    '<&'     '>&'      '<>'       '<<-'   */


%token  CLOBBER
/*      '>|'   */


/* The following are the reserved words. */


%token  If    Then    Else    Elif    Fi    Do    Done
/*      'if'  'then'  'else'  'elif'  'fi'  'do'  'done'   */


%token  Case    Esac    While    Until    For
/*      'case'  'esac'  'while'  'until'  'for'   */


/* These are reserved words, not operator tokens, and are
   recognized when reserved words are recognized. */


%token  Lbrace    Rbrace    Bang
/*      '{'       '}'       '!'   */


%token  In
/*      'in'   */


/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */


%start  complete_command
%%
complete_command : list separator
                 | list
                 ;
list             : list separator_op and_or
                 |                   and_or
                 ;
and_or           :                         pipeline
                 | and_or AND_IF linebreak pipeline
                 | and_or OR_IF  linebreak pipeline
                 ;
pipeline         :      pipe_sequence
                 | Bang pipe_sequence
                 ;
pipe_sequence    :                             command
                 | pipe_sequence '|' linebreak command
                 ;
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
                 | function_definition
                 ;
compound_command : brace_group
                 | subshell
                 | for_clause
                 | case_clause
                 | if_clause
                 | while_clause
                 | until_clause
                 ;
subshell         : '(' compound_list ')'
                 ;
compound_list    :              term
                 | newline_list term
                 |              term separator
                 | newline_list term separator
                 ;
term             : term separator and_or
                 |                and_or
                 ;
for_clause       : For name linebreak                            do_group
                 | For name linebreak in          sequential_sep do_group
                 | For name linebreak in wordlist sequential_sep do_group
                 ;
name             : NAME                     /* Apply rule 5 */
                 ;
in               : In                       /* Apply rule 6 */
                 ;
wordlist         : wordlist WORD
                 |          WORD
                 ;
case_clause      : Case WORD linebreak in linebreak case_list    Esac
                 | Case WORD linebreak in linebreak case_list_ns Esac
                 | Case WORD linebreak in linebreak              Esac
                 ;
case_list_ns     : case_list case_item_ns
                 |           case_item_ns
                 ;
case_list        : case_list case_item
                 |           case_item
                 ;
case_item_ns     :     pattern ')'               linebreak
                 |     pattern ')' compound_list linebreak
                 | '(' pattern ')'               linebreak
                 | '(' pattern ')' compound_list linebreak
                 ;
case_item        :     pattern ')' linebreak     DSEMI linebreak
                 |     pattern ')' compound_list DSEMI linebreak
                 | '(' pattern ')' linebreak     DSEMI linebreak
                 | '(' pattern ')' compound_list DSEMI linebreak
                 ;
pattern          :             WORD         /* Apply rule 4 */
                 | pattern '|' WORD         /* Do not apply rule 4 */
                 ;
if_clause        : If compound_list Then compound_list else_part Fi
                 | If compound_list Then compound_list           Fi
                 ;
else_part        : Elif compound_list Then else_part
                 | Else compound_list
                 ;
while_clause     : While compound_list do_group
                 ;
until_clause     : Until compound_list do_group
                 ;
function_definition : fname '(' ')' linebreak function_body
                 ;
function_body    : compound_command                /* Apply rule 9 */
                 | compound_command redirect_list  /* Apply rule 9 */
                 ;
fname            : NAME                            /* Apply rule 8 */
                 ;
brace_group      : Lbrace compound_list Rbrace
                 ;
do_group         : Do compound_list Done           /* Apply rule 6 */
                 ;
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
cmd_name         : WORD                   /* Apply rule 7a */
                 ;
cmd_word         : WORD                   /* Apply rule 7b */
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here
                 | IO_NUMBER io_here
                 ;
io_file          : '<'       filename
                 | LESSAND   filename
                 | '>'       filename
                 | GREATAND  filename
                 | DGREAT    filename
                 | LESSGREAT filename
                 | CLOBBER   filename
                 ;
filename         : WORD                      /* Apply rule 2 */
                 ;
io_here          : DLESS     here_end
                 | DLESSDASH here_end
                 ;
here_end         : WORD                      /* Apply rule 3 */
                 ;
newline_list     :              NEWLINE
                 | newline_list NEWLINE
                 ;
linebreak        : newline_list
                 | /* empty */
                 ;
separator_op     : '&'
                 | ';'
                 ;
separator        : separator_op linebreak
                 | newline_list
                 ;
sequential_sep   : ';' linebreak
                 | newline_list
                 ;
