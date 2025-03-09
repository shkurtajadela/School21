# Python Bootcamp: Web Scraping, Graph Representation, and Visualization

This repository contains the work I completed during my Python bootcamp, where I explored the fundamentals of Python programming, web scraping, graph data structures, and data visualization. Through various tasks and exercises, I gained hands-on experience with Python libraries and tools for building real-world applications.

## What I Learned

Throughout the bootcamp, I focused on mastering the following Python concepts and tools:

- **Basic Python Syntax**: Gained proficiency in core Python concepts such as variables, loops, conditionals, functions, and error handling.
- **Web Scraping**: Learned how to extract data from websites using libraries like `requests` and `BeautifulSoup`. For example, I worked on a project where I wrote a script that scrapes Wikipedia pages to collect links and save them as a graph.
- **Graph Representation**: Explored how to model and store relationships between data using graphs. In one task, I created a graph representation of Wikipedia pages and links, saving the graph as a JSON file to capture page relationships.
- **Visualization**: Developed skills in visualizing data using libraries like `networkx` and `matplotlib`. I created a visualization of a web graph, where nodes represented Wikipedia pages and edges represented links between those pages. Additionally, I learned to adjust node sizes based on the number of incoming connections to highlight key nodes in the graph.
- **Logging and Debugging**: Utilized the `logging` module to track program activity and ensure that each page visited by my scraping script was properly logged for debugging and transparency.

## Key Projects and Tasks

Here are some of the tasks I worked on during the bootcamp:

1. **Cache Wikipedia Pages**: I created a Python script that downloaded Wikipedia pages, extracted links from the "See Also" sections, and built a graph representing the pages and their connections. The data was stored as a JSON file, allowing me to work with graph data for future tasks.
  
2. **Render Graph Visualization**: I developed a script to visualize the web graph I created in the previous task. The graph was rendered as a PNG image where node sizes were proportional to the number of links pointing to each page. I also explored generating interactive visualizations using libraries like `Altair` or `Bokeh`.

## Technologies Used

- **Python 3.x**
- **requests**: For making HTTP requests to scrape website data.
- **BeautifulSoup**: For parsing HTML content and extracting useful information.
- **networkx**: For creating and manipulating graph data structures.
- **matplotlib**: For static graph visualizations.
- **Bokeh**: For creating interactive visualizations.
- **logging**: For tracking events during web scraping.
- **Neo4j**: Explored integrating with the Neo4j graph database for storing and querying the graph data.

---

This bootcamp provided me with a solid foundation in Python programming and practical experience in building data-driven applications. By working on web scraping, graph manipulation, and data visualization tasks, I have gained valuable skills that I can apply to a wide range of real-world projects.

