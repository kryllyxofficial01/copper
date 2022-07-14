from copper.interpreter import Interpreter
from copper.lexer import Lexer

print("Enter filepath:")
filepath = input(">>> ")

file = open(filepath, 'r')
contents = file.readlines()

lineno = 1
for line in contents:
    if line == "\n" or line[:2] == "//":
        pass
    
    else:
        lexer = Lexer(line, lineno, filepath)
        tokens = lexer.lex()
    
        interpreter = Interpreter(tokens, line, lineno, filepath)
        interpreter.interpret()
        
    lineno += 1