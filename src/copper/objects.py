from copper.error import Error

class Object:
    def __init__(self, args, line, lineno, file):
        self.args = args
        self.line = line
        self.lineno = lineno
        self.file = file
    
    def isString(self):
        if self.args[0] == "\"" and self.args[-1] == "\"":
            return True
        elif (self.args[0] == "\"" and self.args[-1] != "\"") or (self.args[0] != "\"" and self.args[-1] == "\""):
            error = Error("SyntaxError", "Unterminated string", self.line, self.lineno, self.file)
            error.print_stacktrace()

class String(Object):
    def __init__(self, string, line, lineno, file):
        super().__init__(string, line, lineno, file)
        