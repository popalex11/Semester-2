import random
import math
from graph_edge import GraphEdge
from graph_iterator import GraphIterator

class DirectedGraph:
    def __init__(self, directed = True, weighted = False):
        # Time complexity: O(1)
        self.directed = directed
        self.weighted = weighted
        self.vertices = {}
        self.edges = {}
        self.num_vertices = 0
        self.num_edges = 0

    def add_vertex(self, vertex):
        # Time complexity: O(1)
        if vertex in self.vertices:
            raise ValueError("Vertex already exists")
        self.vertices[vertex] = []
        self.num_vertices += 1

    def add_edge(self, start_vertex, end_vertex, weight=None):
        # Time complexity: O(E) where E is the number of edges
        if start_vertex not in self.vertices or end_vertex not in self.vertices:
            raise ValueError("Vertices do not exist")
        if (start_vertex, end_vertex) in self.edges:
            raise ValueError("Edge already exists")
        self.edges[(start_vertex, end_vertex)] = GraphEdge(start_vertex, end_vertex, weight)
        self.vertices[start_vertex].append(end_vertex)
        self.num_edges += 1

    def remove_edge(self, start_vertex, end_vertex):
        # Time complexity: O(V) where V is the number of vertices
        if (start_vertex, end_vertex) not in self.edges:
            raise ValueError("Vertices do not exist")
        del self.edges[(start_vertex, end_vertex)]
        self.vertices[start_vertex].remove(end_vertex)
        self.num_edges -= 1

    def remove_vertex(self, vertex):
        # Time complexity: O(V + E) where V is the number of vertices and E is the number of edges
        if vertex not in self.vertices:
            raise ValueError("Vertex does not exist")

        # Remove edges that contain the vertex
        edges_to_remove = [edge for edge in self.edges if edge[0] == vertex or edge[1] == vertex]
        for edge in edges_to_remove:
            del self.edges[edge]
            if edge[1] in self.vertices[edge[0]]:
                self.vertices[edge[0]].remove(edge[1])
            if not self.directed and edge[0] in self.vertices[edge[1]]:
                self.vertices[edge[1]].remove(edge[0])
            self.num_edges -= 1
            
        # Remove the vertex itself
        del self.vertices[vertex]
        self.num_vertices -= 1

    def create_random(self, n, m, weights_range):
        # Time complexity: O(n^2)
        if m > n * (n - 1):
            raise ValueError("Number of edges exceeds maximum")

        # Add vertices if they don't exist
        for vertex in range(n):
            if vertex not in self.vertices:
                self.add_vertex(vertex)

        # Create a list of all possible edges
        all_edges = [(i, j) for i in range(n) for j in range(n) if i != j]

        # Shuffle the list of edges
        random.shuffle(all_edges)

        # Take the first `m` unique edges
        selected_edges = []
        for start_vertex, end_vertex in all_edges:
            if len(selected_edges) == m:
                break
            if (start_vertex, end_vertex) not in self.edges and (end_vertex, start_vertex) not in self.edges:
                selected_edges.append((start_vertex, end_vertex))

        for start_vertex, end_vertex in selected_edges:
            weight = None
            if weights_range is not None:
                weight = random.uniform(weights_range[0], weights_range[1])
            self.add_edge(start_vertex, end_vertex, math.floor(weight*10)/10
)
        self.num_vertices = n
        self.num_edges = m


    def random_weights(self, weights_range):
        for edge in self.edges.values():
            if edge.weight is None:
                edge.weight = random.uniform(weights_range[0], weights_range[1])

    def set_weight(self, start_vertex, end_vertex, weight):
        # if not self.weighted:
            # raise ValueError("Graph is not weighted")
        if (start_vertex, end_vertex) not in self.edges:
            raise ValueError("Edge does not exist")
        self.edges[(start_vertex, end_vertex)].weight = math.floor(weight*10)/10


    def get_num_vertices(self):
        # Time complexity: O(1)
        return self.num_vertices

    def get_num_edges(self):
        # Time complexity: O(1)
        return self.num_edges

    def deg(self, vertex):
        # Time complexity: O(1)
        if vertex not in self.vertices:
            raise ValueError("Vertex does not exist")
        return len(self.vertices[vertex])

    def is_edge(self, start_vertex, end_vertex):
        # Time complexity: O(V) where V is the number of vertices
        if (start_vertex, end_vertex) not in self.vertices:
            raise ValueError("Vertices not found")
        if (start_vertex, end_vertex) in self.edges:
            return True
        else:
            return None

    def outbound_edges(self, vertex):
        # Time complexity: O(1)
        if vertex not in self.vertices:
            raise ValueError("Vertex not found")
        outbound = []
        for edge in self.edges:
            if edge[0] == vertex:
                if edge in self.edges:
                    outbound.append(self.edges[edge])
                else:
                    outbound.append(edge[1])
        return outbound
    
    def outbound_neighbors(self, vertex):
        return self.vertices[vertex]

    def inbound_edges(self, vertex):
        # Time complexity: O(V) where V is the number of vertices
        if vertex not in self.vertices:
            raise ValueError("Vertex not found")
        inbound = []
        for edge in self.edges:
            if edge[1] == vertex:
                if edge in self.edges:
                    inbound.append(self.edges[edge])
                else:
                    inbound.append(edge[0])
        return inbound
    
    def create_from_file(self, filename):
        with open(filename, 'r') as file:
            lines = file.readlines()

        n, m, directed, weighted = lines[0].strip().split()
        n, m = int(n), int(m)
        directed = directed == "T"
        weighted = weighted == "T"

        self.directed = directed
        self.weighted = weighted
        self.vertices = {v: [] for v in range(n)}
        self.num_vertices = n
        self.num_edges = m

        for line in lines[1:]:
            parts = line.strip().split()
            start_vertex, end_vertex = int(parts[0]), int(parts[1])
            if weighted:
                weight = float(parts[2])
                self.weighted = True  # Mark the graph as weighted
            else:
                weight = None
            self.add_edge(start_vertex, end_vertex, weight)

    def empty_graph(self):
        self.directed = True
        self.weighted = False
        self.vertices = {}
        self.edges = {}
        self.num_vertices = 0
        self.num_edges = 0

    def iter_vertex(self, start_vertex):
        return GraphIterator(self, start_vertex)
    
    def __str__(self):
        result = "Directed: " + str(self.directed) + "\n"
        result += "Weighted: " + str(self.weighted) + "\n"
        result += "Vertices: " + str(self.vertices) + "\n"
        result += "Edges:\n"
        for edge, graph_edge in self.edges.items():
            result += f"({edge[0]}, {edge[1]})"
            if self.weighted:
                result += f" - Weight: {graph_edge.weight}"
            result += "\n"
        return result
    