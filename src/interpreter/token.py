OUTPUT = "OUTPUT"
INPUT = "INPUT"
VARTYPE = "VARTYPE"
VARNAME = "VARNAME"
VARVALUE = "VARVALUE"
STRING = "STRING"
INTEGER = "INTEGER"
BOOLEAN = "BOOLEAN"
FLOAT = "FLOAT"
LPAREN = "("
RPAREN = ")"
EQUALS = "="

class Token:
    def __init__(self, type, value):
        self.type = type
        self.value = value
        
    def __repr__(self):
        if self.value:
            return f"{self.type}: {self.value}"
        else:
            return self.type