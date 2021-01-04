Code steps

1. init signal() --> handle signals  
init env () -->  
copy env() -->  
- count variables in  
- malloc env  size
- parse env : `integer` / `char`   
- copy env  


2. print prompt() -->   
- print "`minishell $>`"
- read input (fd=0 if interactive else fd=file)  

3. parse_line()  
- handle `'\n'`  
- copy_line()
	1. split_operators_into_tokens() --> into linked chain or **char  
 `new line`, `|` , `;`, `(`, `)`, `<`, or `>`.   
 check if the metacharacter is not quoted  
 check quoting exceptions
		1.1 Check Quotes (", ', \) : " and/or ' need to be even or equal to 0. If not, a quote is not close, so return error.
	2. split_words_into_tokens() --> into linked chain or **char  
 `space`, `tab`  
	3. convert_tokens_into_commands()
	4. Brace_expansion()
	5. Tilde_expansion()
	6. Parameter_and_variable_expansion()
	7. Command_substitution()
	8. Arithmetic_expansion()
	9. Word_splitting() 
	10. filename_expansion()

4. redirections()
5. execute_command()
	1. command_is_builtin()
	2. if not find_bin_path()
	3. try_bin()
	4. execute_command
6. wait_exit_status
	