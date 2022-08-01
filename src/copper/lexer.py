from copper.error import Error

class Lexer:
    def __init__(self, line: list, lineno: int, file: str, content: list=[]) -> None:
        if content:
            self.line = content
        else:
            self.line = line

        self.lineno = lineno
        self.file = file
        self.full_line = "".join(line)
        self.tokens = {}
        
        self.letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        self.digits = "1234567890"
        self.valid_symbols = "_-"
        self.reserved_symbols = "!#%^&*()+=[]:\"<,>?/"
    
    def lex(self) -> dict:
        if "".join(self.line[:4]) == "exec":
            self.tokens["KEYWORD"] = "exec"

            for char in "exec":
                self.line.remove(char)

            if self.line[0] == " ":
                self.line.pop(0)

                if "".join(self.line[:3]) == "out":
                    self.tokens["COMMAND"] = "out"

                    for char in "out":
                        self.line.remove(char)

                    if self.line[0] == "(" and self.line[-1] == ")":
                        self.line.pop(0)
                        self.line.pop()

                        self.tokens["OUTPUT"] = "".join(self.line)

                        return self.tokens

                    else:
                        syntaxerror = Error(
                            "SyntaxError",
                            "Missing parentheses",
                            self.full_line,
                            self.lineno,
                            self.file
                        )

                        syntaxerror.print_stacktrace()

                elif "".join(self.line[:2]) == "in":
                    self.tokens["COMMAND"] = "in"
                    
                    for char in "in":
                        self.line.remove(char)
                    
                    if self.line[0] == "(" and self.line[-1] == ")":
                        self.line.pop(0)
                        self.line.pop()

                        self.tokens["INPUT"] = "".join(self.line)

                        return self.tokens

                    else:
                        syntaxerror = Error(
                            "SyntaxError",
                            "Missing parentheses",
                            self.full_line,
                            self.lineno,
                            self.file
                        )

                        syntaxerror.print_stacktrace()

                else:
                    i = 0
                    command = ""
                    while True:
                        if self.line[i] == "(" or command == "".join(self.line):
                            break

                        else:
                            command += self.line[i]
                            i += 1
                            continue

                    unknowncmderror = Error(
                        "UnknownCommandError",
                        f"Unknown command \"{command}\"",
                        self.full_line,
                        self.lineno,
                        self.file
                    )

                    unknowncmderror.print_stacktrace()

            else:
                syntaxerror = Error(
                    "SyntaxError",
                    "Missing separation between keyword and command call",
                    self.full_line,
                    self.lineno,
                    self.file
                )

                syntaxerror.print_stacktrace()

        elif "".join(self.line[:3]) == "set":
            self.tokens["KEYWORD"] = "set"
            
            for char in "set":
                self.line.remove(char)
            
            if self.line[0] == " ":
                self.line.pop(0)
                
                i = 0
                var = ""
                while True:
                    if self.line[i] == "=" or self.line[i] == " ":
                        break
                    else:
                        var += self.line[i]
                        i += 1
                
                self.tokens["VARNAME"] = var
                
                for char in var:
                    self.line.remove(char)
                
                self.line = "".join(self.line)
                self.line = self.line.strip()
                self.line = list(self.line)
                
                if self.line[0] == "=":
                    self.line.pop(0)
                    
                    self.line = "".join(self.line)
                    self.line = self.line.strip()
                    self.line = list(self.line)
                    
                    self.tokens["CONTENT"] = "".join(self.line)
                    
                    return self.tokens
                
                else:
                    syntaxerror = Error(
                        "SyntaxError",
                        "Missing equals sign in variable assignment",
                        self.full_line,
                        self.lineno,
                        self.file
                    )
                    
                    syntaxerror.print_stacktrace()
            
            else:
                syntaxerror = Error(
                    "SyntaxError",
                    "Missing separation between keyword and variable name",
                    self.full_line,
                    self.lineno,
                    self.file
                )
                
                syntaxerror.print_stacktrace()
        
        else:
            i = 0
            keyword = ""
            while True:
                if self.line[i] == "(" or keyword == "".join(self.line):
                    break

                else:
                    keyword += self.line[i]
                    i += 1
                    continue

            keyworderror = Error(
                "KeywordError",
                f"Unknown keyword \"{keyword}\"",
                self.full_line,
                self.lineno,
                self.file
            )

            keyworderror.print_stacktrace()