from copper.lexer import Lexer

print("Enter filepath:")
filepath = input(">>> ")

try:
	file = open(filepath, 'r')
except FileNotFoundError:
    print(f"\033[0;31m\nUnknownFileError: Couldn't find the file \"{filepath}\"\033[0m\n")
else:
	contents = file.readlines()

	lineno = 1
	for line in contents:
		line = list(line)
		
		if line[-1] == "\n":
			line.pop()
		
		lexer = Lexer(line, lineno, filepath)
		tokens = lexer.lex()
  
		print(tokens)