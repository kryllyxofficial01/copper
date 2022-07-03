from dataclasses import dataclass
from enum import Enum

class TokenTypes(Enum):
    COMMAND = 0
    KEYWORD = 1
    STRING = 2
    INTEGER = 3
    BOOLEAN = 4
    FLOAT = 5
    DOUBLEQUOTE = 6
    LEFTPAREN = 7
    RIGHTPAREN = 8
    EQUALS = 9
    COLON = 10

@dataclass
class Token:
    type: TokenTypes
    value: any = None

    def __repr__(self):
        return self.type.name + (f":{self.value}" if self.value != None else "")
