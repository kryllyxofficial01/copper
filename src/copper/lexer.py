import keyword
from copper.error import Error

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
            
            for char in "exec":
                command.remove(char)
            command.remove(" ")
            
            if command[:3] == ["o", "u", "t"]:
                self.lex_output(command)
            
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
            
            self.tokens["STRING"] = args
            self.tokens["RPAREN"] = ")"