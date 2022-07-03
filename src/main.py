from interpreter.lexer import Lexer

print("Enter filepath:")
filepath = input("> ")

lines = []
with open(filepath, 'r') as f:
	for line in f.readlines():
		lines.append(line)

for line in lines:
	lexer = Lexer(line)
	tokens = lexer.generate_tokens()
	print(list(tokens))