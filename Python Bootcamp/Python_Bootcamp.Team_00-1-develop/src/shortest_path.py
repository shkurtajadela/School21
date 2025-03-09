import os
import json
import argparse
import logging
from collections import deque

logging.basicConfig(level=logging.WARNING, format="%(asctime)s - %(levelname)s - %(message)s")

WIKI_FILE = os.getenv("WIKI_FILE", "wiki.json")

def load_wiki_graph():
    """Load the Wikipedia graph from a JSON file."""
    if not os.path.exists(WIKI_FILE):
        print("database not found")
        exit(1)
    
    with open(WIKI_FILE, "r", encoding="utf-8") as f:
        return json.load(f)

def find_shortest_path(graph, start, end, non_directed=False):
    """Find the shortest path between two Wikipedia pages using BFS, ensuring all pages are recognized."""
    all_pages = set(graph.keys())
    for links in graph.values():
        all_pages.update(links)  

    if start not in all_pages or end not in all_pages:
        print("path not found")
        return None

    queue = deque([(start, [start])])
    visited = set()

    while queue:
        current, path = queue.popleft()
        if current == end:
            return path

        if current in visited:
            continue
        visited.add(current)

        neighbors = graph.get(current, [])
        if non_directed:
            for node in graph:
                if current in graph[node] and node not in neighbors:
                    neighbors.append(node)

        for neighbor in neighbors:
            if neighbor not in visited:
                queue.append((neighbor, path + [neighbor]))

    print("path not found")
    return None

def main():
    parser = argparse.ArgumentParser(description="Find the shortest path between two Wikipedia pages.")
    parser.add_argument("--from", dest="start", type=str, required=True, help="Starting Wikipedia page")
    parser.add_argument("--to", dest="end", type=str, required=True, help="Target Wikipedia page")
    parser.add_argument("--non-directed", action="store_true", help="Treat links as bidirectional")
    parser.add_argument("-v", "--verbose", action="store_true", help="Enable path logging")
    args = parser.parse_args()
    
    graph = load_wiki_graph()
    path = find_shortest_path(graph, args.start, args.end, args.non_directed)
    
    if path:
        if args.verbose:
            print(" -> ".join(path))
        print(len(path) - 1)

if __name__ == "__main__":
    main()


# export WIKI_FILE="wiki.json" 
