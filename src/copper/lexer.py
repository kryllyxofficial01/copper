class Lexer:
    def __init__(self, line, lineno, file) -> None:
        self.line = line
        self.lineno = lineno
        self.file = file
        
        self.tokens = {}
    
    def lex(self) -> None:
        pass