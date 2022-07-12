from copper.lexer import Lexer

print("Enter filepath:")
filepath = input(">>> ")

file = open(filepath, 'r')
contents = file.readlines()

for line in contents:
    line = list(line)
    line.pop()
    line = str(line)

lineno = 1
for line in contents:
    lexer = Lexer(line, lineno, filepath)
    tokens = lexer.lex()
    
    lineno += 1