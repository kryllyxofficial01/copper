from copper.error import Error

class Object:
	def __init__(self, object, line, lineno, file) -> None:
		self.object = object
		self.line = line
		self.lineno = lineno
		self.file = file

	def isValidString(self) -> bool:
		if self.object[0] == "\"" and self.object[-1] == "\"":
			return True
		else:
			if (self.object[0] == "\"" and self.object != "\"") or (self.object[0] != "\"" and self.object == "\""):
				syntaxerror = Error(
					"SyntaxError",
					"Unterminated string",
					self.line,
					self.lineno,
					self.file
				)

				syntaxerror.print_stacktrace()

			else:
				syntaxerror = Error(
					"SyntaxError",
					"Missing quotation marks",
					self.line,
					self.lineno,
					self.file
				)

				syntaxerror.print_stacktrace()