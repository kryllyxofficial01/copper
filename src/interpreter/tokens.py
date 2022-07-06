CMD = "CMD"
STRING = "STRING"
INTEGER = "INTEGER"
BOOLEAN = "BOOLEAN"
FLOAT = "FLOAT"
LPAREN = "LPAREN"
RPAREN = "RPAREN"
DOUBLEQUOTE = "DOUBLEQUOTE"
PLUS = "PLUS"
MINUS = "MINUS"
ASTERICK = "ASTERICK"
FORWARDSLASH = "FORWARDSLASH"
EOF = "EOF"

class Token:
    def __init__(self, token_type, value=None):
        self.type = token_type
        self.value = value
        
    def __repr__(self):
        return f"{self.type}: {self.value}"