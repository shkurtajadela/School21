import requests
import json
import logging
import argparse
import time
from urllib.parse import urljoin
from bs4 import BeautifulSoup
from neo4j import GraphDatabase

# python cache_wiki.py -p "Erdős number" -d 3 --neo4j

neo4j_logger = logging.getLogger("neo4j")
neo4j_logger.setLevel(logging.WARNING)

logging.basicConfig(level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s")

WIKI_BASE_URL = "https://en.wikipedia.org"
DEFAULT_START_PAGE = "Python (programming language)"
MAX_PAGES = 1000
MIN_PAGES = 20

# Neo4j Database Configuration
NEO4J_URI = "bolt://localhost:7687" 
NEO4J_USER = "neo4j"
NEO4J_PASS = "adela-123" 

# neo4j start/stop, check graph: MATCH (a:Page)-[:LINKS_TO]->(b:Page) RETURN a, b LIMIT 20;
class WikiGraph:
    def __init__(self, neo4j_uri, neo4j_user, neo4j_password):
        self.driver = GraphDatabase.driver(neo4j_uri, auth=(neo4j_user, neo4j_password))

    def close(self):
        self.driver.close()

    def save_to_neo4j(self, graph):
        with self.driver.session() as session:
            with session.begin_transaction() as tx:
                for page, links in graph.items():
                    tx.run("MERGE (:Page {title: $title})", title=page) 

                    for link in links:
                        tx.run("MERGE (:Page {title: $title})", title=link)
                        tx.run("""
                            MATCH (a:Page {title: $from_page}), (b:Page {title: $to_page})
                            MERGE (a)-[:LINKS_TO]->(b)
                        """, from_page=page, to_page=link)

                tx.commit() 


    @staticmethod
    def _create_page(tx, page):
        """Create a Wikipedia Page node."""
        tx.run("MERGE (:Page {title: $title})", title=page)

    @staticmethod
    def _create_link(tx, page_from, page_to):
        """Create a directed relationship between Wikipedia pages."""
        tx.run(
            """
            MATCH (a:Page {title: $from_page}), (b:Page {title: $to_page})
            MERGE (a)-[:LINKS_TO]->(b)
            """,
            from_page=page_from, 
            to_page=page_to
        )


def get_wiki_links(page_title):
    url = f"{WIKI_BASE_URL}/wiki/{page_title.replace(' ', ' ')}"  # Ensure spaces are preserved
    
    for attempt in range(3):  
        try:
            response = requests.get(url, timeout=10)
            if response.status_code == 429:  
                wait_time = 2 ** attempt + random.uniform(0, 1)
                logging.warning(f"Rate limited. Retrying in {wait_time:.2f} seconds...")
                time.sleep(wait_time)
                continue

            if response.status_code != 200:
                logging.error(f"Failed to fetch {url} (Status: {response.status_code})")
                return []

            soup = BeautifulSoup(response.text, "html.parser")
            links = {a.get("href").split("/")[-1].replace('_', ' ') for a in soup.select("#bodyContent a[href]") if a.get("href").startswith("/wiki/") and ":" not in a.get("href")}
            return list(links)

        except requests.exceptions.RequestException as e:
            logging.error(f"Request error for {url}: {e}")

    return []

def build_wiki_graph(start_page, depth):
    """Build a Wikipedia graph representation from the start page up to a given depth."""
    graph = {}
    visited = set()
    queue = [(start_page, 0)]
    
    while queue and len(visited) < MAX_PAGES:        
        current_page, current_depth = queue.pop(0)
        if current_page in visited or current_depth > depth:
            continue
        
        logging.info(f"Visiting: {current_page} (Depth: {current_depth})")
        visited.add(current_page)
        links = get_wiki_links(current_page)
        
        if not links:
            logging.warning(f"No links found on {current_page}. Skipping.")
            continue
        
        graph[current_page] = links
        
        for link in links:
            if link not in visited and len(visited) < MAX_PAGES:
                queue.append((link, current_depth + 1))    

        if not queue:
            logging.info("No more links to follow. Stopping execution.")
            break

    logging.info(f"Total pages visited: {len(visited)}")
    return graph

def save_graph(graph, filename="wiki.json"):
    """Save the graph as a JSON file."""
    with open(filename, "w", encoding="utf-8") as f:
        json.dump(graph, f, indent=4)
    logging.info(f"Graph saved to {filename}")

def main():
    parser = argparse.ArgumentParser(description="Wikipedia Link Crawler with Neo4j")
    parser.add_argument("-p", "--page", type=str, default=DEFAULT_START_PAGE, help="Starting Wikipedia page")
    parser.add_argument("-d", "--depth", type=int, default=3, help="Depth of link crawling")
    parser.add_argument("--neo4j", action="store_true", help="Store results in Neo4j")
    args = parser.parse_args()

    graph = build_wiki_graph(args.page, args.depth)

    if len(graph) < MIN_PAGES:
        logging.warning("Too few pages collected, consider using another start page.")

    save_graph(graph)

    if args.neo4j:
        wiki_db = WikiGraph(NEO4J_URI, NEO4J_USER, NEO4J_PASS)
        wiki_db.save_to_neo4j(graph)
        wiki_db.close()
        logging.info("Graph successfully stored in Neo4j.")

if __name__ == "__main__":
    main()
