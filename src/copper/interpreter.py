from copper.error import Error
from copper.object import Object
from copper.lexer import Lexer

class Interpreter:
	def __init__(self, tokens: dict, vars: dict, line: str, lineno: int, file: str) -> None:
		self.tokens = tokens
		self.vars = vars
		self.line = line
		self.lineno = lineno
		self.file = file

	def interpret(self) -> dict:
		if self.tokens["KEYWORD"] == "exec":
			if self.tokens["COMMAND"] == "out":
				output = Object(self.tokens["OUTPUT"], self.line, self.lineno, self.file)

				if output.checkType() == "string":
					string = list(self.tokens["OUTPUT"])
					string.pop(0)
					string.pop(-1)

					print("".join(string))
      
			elif self.tokens["COMMAND"] == "in":
				inpt = Object(self.tokens["INPUT"], self.line, self.lineno, self.file)
    
				if inpt.checkType() == "string":
					string = list(self.tokens["INPUT"])
					string.pop(0)
					string.pop(-1)

					input("".join(string))

		elif self.tokens["KEYWORD"] == "set":
			if self.tokens["CONTENT"][:4] == "exec":
				lexer = Lexer(list(self.line), self.lineno, self.file, content=list(self.tokens["CONTENT"]))
				content_tokens = lexer.lex()

				if content_tokens["COMMAND"] == "in":
					inpt = Object(content_tokens["INPUT"], self.line, self.lineno, self.file)

					if inpt.checkType() == "string":
						string = list(content_tokens["INPUT"])
						string.pop(0)
						string.pop(-1)

						self.vars[self.tokens["VARNAME"]] = input("".join(string))
						
						return self.vars

			else:
				content = Object(self.tokens["CONTENT"], self.line, self.lineno, self.file)

				if content.checkType() == "string":
					string = list(self.tokens["CONTENT"])
					string.pop(0)
					string.pop(-1)

					self.vars[self.tokens["VARNAME"]] = "".join(string)
					
					return self.vars