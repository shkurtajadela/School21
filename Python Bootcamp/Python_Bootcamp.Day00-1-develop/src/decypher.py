import sys

def process_input(input_text):
    print(f"{''.join(input_text.split(' '))}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python decypher.py \"input text\"", file=sys.stderr)
        sys.exit(1)
    
    input_text = sys.argv[1]
    
    process_input(input_text)
