class Error:
    def __init__(self, error_name, reason, file, line, lineno):
        self.error_name = error_name
        self.reason = reason
        self.file = file
        self.line = line
        self.lineno = lineno
        
    def print_stacktrace(self):
        print(f"\033[1;31m\n\tError: {self.error_name} - {self.reason} (line {self.lineno}, in <{self.file}>)\n\t> {self.line} <\n\033[0m")