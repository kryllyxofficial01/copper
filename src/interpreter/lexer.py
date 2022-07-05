import interpreter.token as token

WHITESPACE = " \t"
DIGITS = "0123456789."
OPERANDS = "+-*/"

class Lexer:
	def __init__(self, line):
		self.text = line
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
				tokens.append(token.Token(token.ILLEGALCHAR, self.current_char))
				self.next_char()

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

def build(line):
    lexer = Lexer(line)
    tokens = lexer.generate_tokens()
    return tokens