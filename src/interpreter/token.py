PROCESSS = "PROCESS"
CMD = "CMD"
STRING = "STRING"
INTEGER = "INTEGER"
BOOLEAN = "BOOLEAN"
FLOAT = "FLOAT"
LPAREN = "("
RPAREN = ")"
DOUBLEQUOTE = "DOUBLEQUOTE"

class Token:
    def __init__(self, token_type, value=None):
        self.type = token_type
        self.value = value
        
    def __repr__(self):
        if self.value:
            return f"{self.type}: {self.value}"
        else:
            return self.type