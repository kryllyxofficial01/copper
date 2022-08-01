from copper.error import Error
from copper.object import Object

class Interpreter:
	def __init__(self, tokens: dict, line: str, lineno: int, file: str) -> None:
		self.tokens = tokens
		self.line = line
		self.lineno = lineno
		self.file = file

	def interpret(self):
		if self.tokens["KEYWORD"] == "exec":
			if self.tokens["COMMAND"] == "out":
				output = Object(self.tokens["OUTPUT"], self.line, self.lineno, self.file)

				if output.isValidString():
					string = list(self.tokens["OUTPUT"])
					string.pop(0)
					string.pop(-1)

					print("".join(string))
      
			elif self.tokens["COMMAND"] == "in":
				inpt = Object(self.tokens["INPUT"], self.line, self.lineno, self.file)
    
				if inpt.isValidString():
					string = list(self.tokens["INPUT"])
					string.pop(0)
					string.pop(-1)

					input("".join(string))