from interpreter.tokens import Token, TokenTypes

WHITESPACE = " \n\t"
LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Lexer:
    def __init__(self, text):
        self.text = iter(text)
        self.advance_char()
        self.num_quotes = 0
        
    def generate_tokens(self):
        while self.current_char != None:
            if self.current_char in WHITESPACE:
                self.advance_char()
            if self.current_char == '"':
                yield self.generate_string()
    
    def advance_char(self):
        try:
            self.current_char = next(self.text)
        except StopIteration:
            self.current_char = None
            
    def generate_string(self):
        num_quotes = 0
        
        string = self.current_char
        self.advance_char()
  
        while self.current_char != None and (self.current_char == '"' or self.current_char in LETTERS):
            if self.current_char == '"':
                num_quotes += 1
                if num_quotes > 2:
                    break
            
            string += self.current_char
            self.advance_char()
            
        if string.startswith('"') == False or string.endswith('"') == False:
            pass
        
        return Token(TokenTypes.STRING, string)