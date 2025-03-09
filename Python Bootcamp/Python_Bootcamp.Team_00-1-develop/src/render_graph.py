import os
import json
import logging
import networkx as nx
import matplotlib.pyplot as plt
from bokeh.io import output_file, save
from bokeh.plotting import figure, from_networkx
from bokeh.models import HoverTool
from bokeh.models import ColumnDataSource

logging.basicConfig(level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s")

WIKI_FILE = os.getenv("WIKI_FILE", "wiki.json")
PNG_OUTPUT_FILE = "wiki_graph.png"
HTML_OUTPUT_FILE = "wiki_graph.html"

def load_wiki_graph():
    if not os.path.exists(WIKI_FILE):
        logging.error("Database not found")
        exit(1)
    
    with open(WIKI_FILE, "r", encoding="utf-8") as f:
        return json.load(f)

def render_graph(graph_data):
    G = nx.DiGraph()
    
    for page, links in graph_data.items():
        for link in links:
            G.add_edge(link, page) 
    
    in_degrees = dict(G.in_degree()) 
    max_degree = max(in_degrees.values(), default=1)
    node_sizes = [300 + (in_degrees[node] / max_degree) * 2000 for node in G.nodes]
    
    plt.figure(figsize=(12, 8))
    pos = nx.spring_layout(G, k=0.3, seed=42)
    nx.draw(G, pos, with_labels=True, node_size=node_sizes, edge_color="gray", alpha=0.7, font_size=8)
    
    plt.savefig(PNG_OUTPUT_FILE, dpi=300, bbox_inches='tight')
    logging.info(f"Graph visualization saved as {PNG_OUTPUT_FILE}")
    plt.close()

def render_interactive_graph(graph_data):
    """Render the Wikipedia graph as an interactive HTML visualization."""
    G = nx.DiGraph()
    
    for page, links in graph_data.items():
        for link in links:
            G.add_edge(link, page) 

    in_degrees = dict(G.in_degree())
    max_degree = max(in_degrees.values(), default=1)
    node_sizes = [10 + (in_degrees[node] / max_degree) * 50 for node in G.nodes]
    
    plot = figure(title="Wikipedia Graph", x_range=(-1.5,1.5), y_range=(-1.5,1.5), tools="pan,wheel_zoom,save,reset")
    plot.add_tools(HoverTool(tooltips=[("Page", "@index")]))
    
    pos = nx.spring_layout(G, seed=42)
    graph_renderer = from_networkx(G, pos, scale=1, center=(0,0))
    
    node_data = {"index": list(G.nodes), "size": node_sizes}
    graph_renderer.node_renderer.data_source = ColumnDataSource(node_data)

    graph_renderer.node_renderer.glyph.size = "size"

    plot.renderers.append(graph_renderer)
    
    output_file(HTML_OUTPUT_FILE)
    save(plot)
    logging.info(f"Interactive graph saved as {HTML_OUTPUT_FILE}")


def main():
    graph_data = load_wiki_graph()
    render_graph(graph_data)
    render_interactive_graph(graph_data)

if __name__ == "__main__":
    main()
