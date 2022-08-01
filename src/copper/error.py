import os
import sys

class Error:
	def __init__(self, error_name: str, reason: str, line: str, lineno: int, file: str) -> None:
		self.error_name = error_name
		self.reason = reason
		self.line = line
		self.lineno = lineno
		self.file = os.path.abspath(os.path.join(file, os.pardir)) + f"/{file}"

	def print_stacktrace(self) -> None:
		print(f"\033[0;31m\nError - at line {self.lineno} in file \"{self.file}\"")
		print(f"  {self.line}")
		print(f"\n{self.error_name}: {self.reason}\033[0m\n")

		sys.exit()