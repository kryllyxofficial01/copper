from copper.error import Error
from copper.object import Object

class Interpreter:
	def __init__(self, tokens, line, lineno, file) -> None:
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

						# print("".join(string))