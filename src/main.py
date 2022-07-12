from copper.lexer import Lexer

print("Enter filepath:")
filepath = input(">>> ")

file = open(filepath, 'r')
contents = file.readlines()

for line in contents:
    line = list(line)
    
    if line[-1] == "\n":
        line.pop()
        
    line = "".join(line)

lineno = 1
for line in contents:
    if line == "\n" or line[:2] == "//":
        pass
    
    else:
        lexer = Lexer(line, lineno, filepath)
        tokens = lexer.lex()
    
    print(tokens)
        
    lineno += 1