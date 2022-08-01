from copper.error import Error

class Object:
	def __init__(self, object, line, lineno, file) -> None:
		self.object = object
		self.line = line
		self.lineno = lineno
		self.file = file

	def checkType(self) -> str:
		if self.object[0] == "\"" and self.object[-1] == "\"":
			return "string"
		else:
			try:
				self.object = int(self.object)
			except ValueError:
				print(self.object)
			else:
				return "int"