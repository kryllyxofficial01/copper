from copper.error import Error

class Lexer:
    def __init__(self, line: list, lineno: int, file: str) -> None:
        self.line = line
        self.lineno = lineno
        self.file = file
        
        self.full_line = "".join(line)
        self.tokens = {}
    
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

        else:
            i = 0
            keyword = ""
            while self.line[i] != " " or keyword != "".join(self.line):
                keyword += self.line[i]
                i += 1

            keyworderror = Error(
                "KeywordError",
                f"Unknown keyword \"{keyword}\"",
                self.full_line,
                self.lineno,
                self.file
            )

            keyworderror.print_stacktrace()