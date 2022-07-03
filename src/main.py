from interpreter.lexer import Lexer

print("Enter filepath:")
filepath = input("> ")

lines = []
with open(filepath, 'r') as f:
	for line in f.readlines():
		lines.append(line)

tokens = []

for line in lines:
	lexer = Lexer(line)
	token = lexer.generate_tokens()
	tokens.append(list(token))
	print(tokens)