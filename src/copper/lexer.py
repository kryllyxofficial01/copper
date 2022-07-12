import keyword
from copper.error import Error

DIGITS = "0123456789"
LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Lexer:
    def __init__(self, line, lineno, file):
        self.line = line
        self.lineno = lineno
        self.file = file
        
        self.tokens = {}
    
    def lex(self):
        if self.line[:4] == "exec":
            self.tokens["KEYWORD"] = "exec"
            command = list(self.line)
            command.pop()
            
            for char in "exec":
                command.remove(char)
            command.remove(" ")
            
            if command[:3] == ["o", "u", "t"]:
                self.lex_output(command)
            
            elif command[:2] == ["i", "n"]:
                self.lex_input(command)
            
            else:
                i = 0
                command_name = ""
                while True:
                    if command[i] != "(":
                        command_name += command[i]
                        i += 1
                    else:
                        break
                
                error = Error("CommandError", f"Unknown command \"{command_name}\"", self.line, self.lineno, self.file)
                error.print_stacktrace()
        
        elif self.line[:3] == "set":
            self.tokens["KEYWORD"] = "set"
            command = list(self.line)
        
            for char in "set":
                command.remove(char)
            command.remove(" ")
            
            self.lex_vars(command)
        
        else:
            i = 0
            keyword = ""
            while True:
                if keyword != self.line:
                    if self.line[i] != " ":
                        keyword += self.line[i]
                        i += 1
                    else:
                        break
                else:
                    break
            
            error = Error("KeywordError", f"Unknown execution keyword \"{keyword}\"", self.line, self.lineno, self.file)
            error.print_stacktrace()
            
        return self.tokens
    
    def lex_output(self, command):
        self.tokens["COMMAND"] = "out"
        
        for char in "out":
            command.remove(char)
        
        if command[0] == "(" and command[-1] == ")":
            self.tokens["LPAREN"] = "("
            command.remove("(")
            
            i = 0
            args = ""
            while command[i] != ")":
                args += command[i]
                i += 1
            
            self.tokens["STRING"] = "".join(args)
            self.tokens["RPAREN"] = ")"
        
        else:
            error = Error("SyntaxError", "Missing parentheses", self.line, self.lineno, self.file)
            error.print_stacktrace()
    
    def lex_input(self, command):
        self.tokens["COMMAND"] = "in"
        
        for char in "in":
            command.remove(char)
        
        if command[0] == "(" and command[-1] == ")":
            self.tokens["LPAREN"] = "("
            command.remove("(")
            
            i = 0
            args = ""
            while command[i] != ")":
                args += command[i]
                i += 1
            
            self.tokens["STRING"] = "".join(args)
            self.tokens["RPAREN"] = ")"
            
        else:
            error = Error("SyntaxError", "Missing parentheses", self.line, self.lineno, self.file)
            error.print_stacktrace()
    
    def lex_vars(self, command):
        i = 0
        var_name = ""
        while True:
            if command[i] == "=" or command[i] == " ":
                break
            else:
                var_name += command[i]
                i += 1
        
        self.tokens["VARNAME"] = var_name
        
        for char in var_name:
            command.remove(char)
        if command[0] == " ":
            command.remove(" ")
        
        if command[0] == "=":
            self.tokens["EQUALS"] = "="
        else:
            error = Error("SyntaxError", "Missing equals sign", self.line, self.lineno, self.file)
            error.print_stacktrace()
        
        if command[1] == " ":
            command.remove("=")
            command.remove(" ")
        else:
            command.remove("=")
        
        self.tokens["CONTENT"] = "".join(command)