from copper.objects import Object

class Interpreter:
    def __init__(self, tokens, line, lineno, file):
        self.tokens = tokens
        self.line = line
        self.lineno = lineno
        self.file = file
    
    def interpret(self):
        if self.tokens["KEYWORD"] == "exec":
            if self.tokens["COMMAND"] == "out":
                args = Object(self.tokens["ARGS"], self.line, self.lineno, self.file)
                
                if args.isString():
                    string = list(args.args)
                    string.pop(0)
                    string.pop()
                    print("".join(string))
                    
                else:
                    pass
            
            if self.tokens["COMMAND"] == "in":
                args = Object(self.tokens["ARGS"], self.line, self.lineno, self.file)
                
                if args.isString():
                    string = list(args.args)
                    string.pop(0)
                    string.pop()
                    return input("".join(string))
                
                else:
                    pass