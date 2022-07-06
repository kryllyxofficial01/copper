import interpreter.tokens as Token
import interpreter.nodes as nodes
import interpreter.errors as error

class Parser:
    def __init__(self, tokens, file, line, lineno):
        self.tokens = tokens
        self.file = file
        self.line = line
        self.lineno = lineno
        self.index = -1
        self.next_token()
  
    def next_token(self):
        self.index += 1

        if self.index < len(self.tokens):
            self.current_token = self.tokens[self.index]

        return self.current_token

    def expression(self):
        return self.operation(self.term, (Token.PLUS, Token.MINUS))

    def term(self):
        return self.operation(self.factor, (Token.ASTERICK, Token.FORWARDSLASH))

    def factor(self):
        result = ParserResult()
        token = self.current_token
        
        if token.type in (Token.PLUS, Token.MINUS):
            result.register(self.next_token())
            factor = result.register(self.factor())
            
            if result.error:
                return result
            else:
                return result.check(node=nodes.UnaryNode(token, factor))

        elif token.type in (Token.INTEGER, Token.FLOAT):
            result.register(self.next_token())
            return result.check(node=nodes.NumberNode(token))
        
        elif token.type == Token.LPAREN:
            result.register(self.next_token())
            expression = result.register(self.expression())
            
            if result.error:
                return result
            else:
                if self.current_token.type == Token.RPAREN:
                    result.register(self.next_token())
                    return result.check(node=expression)
                else:
                    ise = error.Error("InvalidSyntaxError", "Expected ')'", self.file, self.line, self.lineno)
                    result.check(error="InvalidSyntaxErrror")
                    ise.print_stacktrace()
        
        else:
            ise = error.Error("InvalidSyntaxError", "Expected type 'int' or 'float'", self.file, self.line, self.lineno)
            ise.print_stacktrace()
        
    def operation(self, expression, tokens):
        result = ParserResult()
        x = result.register(expression())
        
        if result.error:
            return result
  
        while self.current_token.type in tokens:
            operand = self.current_token
            result.register(self.next_token())
            y = result.register(expression())
            
            if result.error:
                return result
            
            x = nodes.OperandNode(x, y, operand)
        
        return result.check(node=x)
    
    def build(self):
        result = self.expression()
        
        if not result.error and self.current_token.type != Token.EOF:
            ise = error.Error("InvalidSyntaxError", "Expected '+', '-', '*', or '/'", self.file, self.line, self.lineno)
            result.check(error="InvalidSyntaxError")
            ise.print_stacktrace()
        else:
            return result
            
class ParserResult:
    def __init__(self):
        self.error = None
        self.node = None
    
    def register(self, result):
        if isinstance(result, ParserResult):
            if result.error:
                self.error = result.error
            
            return result.node
        
        return result
    
    def check(self, node=None, error=None):
        if node != None:
            self.node = node
        elif error != None:
            self.error = error
        
        return self