from interpreter.tokens import Token, TokenTypes

WHITESPACE = " \n\t"
LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
DIGITS = "0123456789"
BOOLCHARS = "truefals"

class Lexer:
    def __init__(self, text):
        self.text = iter(text)
        self.next_char()
        self.num_quotes = 0
        
    def generate_tokens(self):
        while self.current_char != None:
            if self.current_char in WHITESPACE:
                self.next_char()
            elif self.current_char == '"':
                yield self.generate_string()
            elif self.current_char in DIGITS:
                yield self.generate_integer()
            elif self.current_char == "t" or self.current_char == "f":
                yield self.generate_bool()
    
    def next_char(self):
        try:
            self.current_char = next(self.text)
        except StopIteration:
            self.current_char = None
            
    def generate_string(self):
        num_quotes = 0
        
        string = self.current_char
        self.next_char()
  
        while self.current_char != None and (self.current_char == '"' or self.current_char in LETTERS):
            if self.current_char == '"':
                num_quotes += 1
                if num_quotes > 2:
                    break
            
            string += self.current_char
            self.next_char()
            
        if string.startswith('"') == False or string.endswith('"') == False:
            pass
        
        return Token(TokenTypes.STRING, string)
    
    def generate_integer(self):
        integer = self.current_char
        self.next_char()
        
        while self.current_char != None and self.current_char in DIGITS:
            integer += self.current_char
            self.next_char()
            
        return Token(TokenTypes.INTEGER, integer)
    
    def generate_bool(self):
        boolean = self.current_char
        self.next_char()
        
        while self.current_char != None and self.current_char in BOOLCHARS:
            boolean += self.current_char
            self.next_char()
        
        if boolean == "true":
            return Token(TokenTypes.BOOLEAN, boolean)
        elif boolean == "false":
            return Token(TokenTypes.BOOLEAN, boolean)
        else:
            pass