import interpreter.tokens as token
import interpreter.errors as errors
from interpreter.parser import Parser

WHITESPACE = " \n\t"
DIGITS = "0123456789."
OPERANDS = "+-*/"

class Lexer:
	def __init__(self, line, file, lineno):
		self.text = line
		self.file = file
		self.lineno = lineno
		self.current_index = -1
		self.current_char = None

		self.next_char()

	def next_char(self):
		self.current_index += 1

		if self.current_index < len(self.text):
			self.current_char = self.text[self.current_index]
		else:
			self.current_char = None

	def generate_tokens(self):
		tokens = []
		
		while self.current_char != None:
			if self.current_char in WHITESPACE:
				self.next_char()
			elif self.current_char in DIGITS:
				tokens.append(self.generate_number())
			elif self.current_char == "+":
				tokens.append(token.Token(token.PLUS, self.current_char))
				self.next_char()
			elif self.current_char == "-":
				tokens.append(token.Token(token.MINUS, self.current_char))
				self.next_char()
			elif self.current_char == "*":
				tokens.append(token.Token(token.ASTERICK, self.current_char))
				self.next_char()
			elif self.current_char == "/":
				tokens.append(token.Token(token.FORWARDSLASH, self.current_char))
				self.next_char()
			elif self.current_char == "(":
				tokens.append(token.Token(token.LPAREN, self.current_char))
				self.next_char()
			elif self.current_char == ")":
				tokens.append(token.Token(token.RPAREN, self.current_char))
				self.next_char()
			else:
				ice = errors.Error("IllegalCharacterError", f"Unknown character '{self.current_char}'", self.file, self.text, self.lineno)
				ice.print_stacktrace()

		tokens.append(token.Token(token.EOF))
		return tokens

	def generate_number(self):
		number = ""
		num_decimals = 0
		
		while self.current_char != None and self.current_char in DIGITS:
			if self.current_char == ".":
				num_decimals += 1
				if num_decimals > 1:
					break

			number += self.current_char
			self.next_char()
		
		if "." in number:
			return token.Token(token.FLOAT, float(number))
		else:
			return token.Token(token.INTEGER, int(number))

def build(line, file, lineno):
    lexer = Lexer(line, file, lineno)
    tokens = lexer.generate_tokens()
    
    parser = Parser(tokens, file, line, lineno)
    ast = parser.build()
    
    return ast.node