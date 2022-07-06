from interpreter.errors import Error

class Number:
	def __init__(self, value, file, line, lineno):
		self.value = value
		self.file = file
		self.line = line
		self.lineno = lineno

	def add(self, y):
		if isinstance(y, Number):
			return Number(self.value + y.value, self.file, self.line, self.lineno)

	def subtract(self, y):
		if isinstance(y, Number):
			return Number(self.value - y.value, self.file, self.line, self.lineno)

	def multiply(self, y):
		if isinstance(y, Number):
			return Number(self.value * y.value, self.file, self.line, self.lineno)

	def divide(self, y):
		if isinstance(y, Number):
			if y.value != 0:
				return Number(self.value / y.value, self.file, self.line, self.lineno)
			else:
				dbz = Error("DivBy0Error", "Cannot divide by zero", self.file, self.line, self.lineno)
				dbz.print_stacktrace()

	def __repr__(self):
		return f"{self.value}"