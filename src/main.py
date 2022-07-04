import interpreter.lexer as lex

print("Enter filepath:")
filepath = input("> ")

lines = []
with open(filepath, 'r') as f:
	for line in f.readlines():
		lines.append(line)

lexer = lex.build()

for line in lines:
    lexer.input(line)
    for token in lexer:
        print(f"{token.type}: {token.value} | {token.lineno}")