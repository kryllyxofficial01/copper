def parse(file: str) -> list:
    lines = []
    with open(file, 'r') as f:
        for line in f.readlines():
            lines.append(line)
    
    return lines