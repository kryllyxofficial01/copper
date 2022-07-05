import interpreter.lexer as lexer

print("Enter filepath:")
filepath = input("> ")

lines = []
with open(filepath, 'r') as f:
	for line in f.readlines():
		lines.append(line)

for line in lines:
    tokens = lexer.build(line)
    print(tokens)