import sys

def is_m_pattern(image):
    m_pattern = [
        "*   *",
        "** **",
        "* * *"
    ]
    
    if len(image) != 3 or any(len(row) != 5 for row in image):
        return "Error"
    
    for pattern_row, image_row in zip(m_pattern, image):
        for p_char, i_char in zip(pattern_row, image_row):
            if (p_char == "*" and i_char != "*") or (p_char != "*" and i_char == "*"):
                return "False"
    
    return "True"

def read_image(filename):
    try:
        with open(filename, 'r') as file:
            return [line.strip() for line in file.readlines()]
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python mfinder.py filename.txt", file=sys.stderr)
        sys.exit(1)
    
    filename = sys.argv[1]
    
    image = read_image(filename)
    
    result = is_m_pattern(image)
    print(result)
