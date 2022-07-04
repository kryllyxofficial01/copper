print("Enter filepath:")
filepath = input("> ")

lines = []
with open(filepath, 'r') as f:
	for line in f.readlines():
		lines.append(line)