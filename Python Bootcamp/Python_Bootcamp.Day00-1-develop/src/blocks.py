import sys

def read_lines_from_stdin(num_lines):
    for i, line in enumerate(sys.stdin):
        if i >= num_lines:
            break
        if line.startswith('00000') and not line.startswith('000000') and len(line.rstrip("\n")) == 32:
            print(line, end='')

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: cat file_name.txt | python blocks.py <num_lines>", file=sys.stderr)
        sys.exit(1)
    
    try:
        num_lines = int(sys.argv[1])
    except ValueError:
        print("Error: <num_lines> must be an integer.", file=sys.stderr)
        sys.exit(1)
    
    read_lines_from_stdin(num_lines)
