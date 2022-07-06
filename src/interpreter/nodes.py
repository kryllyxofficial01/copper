class NumberNode:
	def __init__(self, token):
		self.token = token

	def __repr__(self):
		return f"{self.token}"

class OperandNode:
	def __init__(self, x, y, token):
		self.x = x
		self.y = y
		self.token = token

	def __repr__(self):
		return f"({self.x}, {self.token}, {self.y})"

class UnaryNode:
    def __init__(self, token, node):
        self.token = token
        self.node = node
    
    def __repr__(self):
        return f"({self.token}, {self.node})"