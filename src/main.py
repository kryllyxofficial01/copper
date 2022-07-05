import interpreter.lexer as lexer

print("Enter filepath:")
filepath = input("> ")

lines = []
with open(filepath, 'r') as f:
	for line in f.readlines():
		lines.append(line)

i = 1
for line in lines:
    tokens = lexer.build(line, filepath, i)
    print(tokens)
    i += 1