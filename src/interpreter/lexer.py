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
        pass