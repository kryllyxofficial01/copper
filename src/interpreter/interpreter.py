import interpreter.operations as operations
import interpreter.tokens as token

class Interpreter:
	def __init__(self, file, line, lineno):
		self.file = file
		self.line = line
		self.lineno = lineno

	def iterate_node(self, node):
		method_name = f"iterate_{type(node).__name__}"
		method = getattr(self, method_name, self.no_iterate_method)
		
		return method(node)

	def iterate_NumberNode(self, node):
		return operations.Number(node.token.value, self.file, self.line, self.lineno)

	def iterate_OperandNode(self, node):
		x = self.iterate_node(node.x)
		y = self.iterate_node(node.y)
		
		if node.token.type == token.PLUS:
			result = x.add(y)
		elif node.token.type == token.MINUS:
			result = x.subtract(y)
		elif node.token.type == token.ASTERICK:
			result = x.multiply(y)
		elif node.token.type == token.FORWARDSLASH:
			result = x.divide(y)
		
		return result

	def iterate_UnaryNode(self, node):
		number = self.iterate_node(node.node)
		
		if node.token.type == token.MINUS:
			result = number.multiply(operations.Number(-1, self.file, self.line, self.lineno))

		return result

	def no_iterate_method(self, node, context):
		raise Exception(f"No 'iterate_{type(node).__name__}()' method found.")