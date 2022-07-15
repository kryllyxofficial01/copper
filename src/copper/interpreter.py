from copper.objects import Object
from copper.error import Error

class Interpreter:
    def __init__(self, tokens, vars, line, lineno, file):
        self.tokens = tokens
        self.vars = vars
        self.line = line
        self.lineno = lineno
        self.file = file
    
    def interpret(self):
        if self.tokens["KEYWORD"] == "exec":
            if self.tokens["COMMAND"] == "out":
                args = Object(self.tokens["ARGS"], self.line, self.lineno, self.file)
                
                if args.isString():
                    print(args.toString())
                else:
                    pass
            
            if self.tokens["COMMAND"] == "in":
                args = Object(self.tokens["ARGS"], self.line, self.lineno, self.file)
                
                if args.isString():
                    return input(args.toString())
                else:
                    pass
        
        elif self.tokens["KEYWORD"] == "set":
            if self.tokens["CONTENT"][:4] == "exec":
                content = list(self.tokens["CONTENT"])
                
                i = 0
                keyword = ""
                while True:
                    if keyword != content:
                        if content[i] != " ":
                            keyword += content[i]
                            i += 1
                        else:
                            break
                    else:
                        break
                
                if keyword == "exec":
                    for char in "exec":
                        content.remove(char)
                        
                    content.remove(" ")
                
                    if content[:3] == ["o", "u", "t"]:
                        error = Error("ReturnError", f"Builtin command \"out\" does not have a return value", self.line, self.lineno, self.file)
                        error.print_stacktrace()
                    
                    elif content[:2] == ["i", "n"]:
                        for char in "in":
                            content.remove(char)
                        
                        if content[0] == "(" and content[-1] == ")":
                            content.remove("(")
                            
                            i = 0
                            args = ""
                            while content[i] != ")":
                                args += content[i]
                                i += 1
                            
                            object = Object(args, self.line, self.lineno, self.file)
                            
                            if object.isString():
                                self.vars[self.tokens["VARNAME"]] = input(object.toString())
                        
                        else:
                            error = Error("SyntaxError", "Missing parentheses", self.line, self.lineno, self.file)
                            error.print_stacktrace()
                        
                    else:
                        i = 0
                        command_name = ""
                        while True:
                            if content[i] != "(":
                                command_name += content[i]
                                i += 1
                            else:
                                break
                        
                        error = Error("CommandError", f"Unknown command \"{command_name}\"", self.line, self.lineno, self.file)
                        error.print_stacktrace()
                
                else:
                    error = Error("KeywordError", f"Unknown execution keyword \"{keyword}\"", self.line, self.lineno, self.file)
                    error.print_stacktrace()

            else:
                content = Object(self.tokens["CONTENT"], self.line, self.lineno, self.file)
                
                if content.isString():
                    self.vars[self.tokens["VARNAME"]] = content.toString()
            
            print(self.vars)