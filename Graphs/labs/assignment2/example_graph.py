import random
from directed_graph import DirectedGraph

def get_example_graph():
    graph = DirectedGraph(directed=True, weighted=True)
    graph.add_vertex(0)
    graph.add_vertex(1)
    graph.add_vertex(2)
    graph.add_vertex(3)
    graph.add_edge(0, 1, 3.5)
    graph.add_edge(1, 2, 2.0)
    graph.add_edge(2, 0, 1.2)
    graph.add_edge(2, 3, 4.7)
    return graph
