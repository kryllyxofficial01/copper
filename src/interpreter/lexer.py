import ply.lex as lex

reserved = {
    "out": "OUTPUT",
    "true": "BOOLEAN",
    "false": "BOOLEAN",
}

tokens = [
    "OUTPUT",
    "STRING",
    "INTEGER",
    "BOOLEAN",
    "FLOAT",
    "LPAREN",
    "RPAREN",
    "DOUBLEQUOTE",
]

t_LPAREN = r"\("
t_RPAREN = r"\)"
t_DOUBLEQUOTE = r"\""
t_ignore = " \t"

def t_OUTPUT(t):
    r"out\(\"\w\"\)"
    t.type = reserved.get(t.value, "OUTPUT")
    return t

def t_STRING(t):
    r"[A-Za-z0-9]+"
    t.value = str(t.value)
    return t

def t_INTEGER(t):
    r"[0-9]+"
    t.value = int(t.value)
    return t

def t_newline(t):
    r"\n+"
    t.lexer.lineno += len(t.value)

def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)

def build():
    lexer = lex.lex()
    return lexer