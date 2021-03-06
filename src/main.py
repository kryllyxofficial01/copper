from copper.lexer import Lexer
from copper.interpreter import Interpreter

print("Enter filepath:")
filepath = input(">>> ")

try:
    file = open(filepath, 'r')
except FileNotFoundError:
    print(
        f"\033[0;31m\nUnknownFileError: Couldn't find the file \"{filepath}\"\033[0m\n")
else:
	contents = file.readlines()

	lineno = 1
	for item in contents:
		if item == "\n":
			pass
		else:
			line = list(item)

			if line[-1] == "\n":
				line.pop()

			lexer = Lexer(line, lineno, filepath)
			tokens = lexer.lex()

			interpreter = Interpreter(tokens, item, lineno, filepath)
			variables = interpreter.interpret()