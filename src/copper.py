import utils.parser as parser

print("Enter path to file:")
filepath = input("> ")

print(parser.parse(filepath))