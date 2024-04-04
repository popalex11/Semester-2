import random

class DirectedGraph:
    def __init__(self):
        # Time complexity: O(1)
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

    def add_edge(self, start_vertex, end_vertex):
        # Time complexity: O(E) where E is the number of edges
        if start_vertex not in self.vertices or end_vertex not in self.vertices:
            raise ValueError("Vertices do not exist")
        if (start_vertex, end_vertex) in self.edges:
            raise ValueError("Edge already exists")
        self.edges[(start_vertex, end_vertex)] = len(self.edges) + 1
        self.vertices[start_vertex].append(end_vertex)
        self.num_edges += 1

    def remove_edge(self, edge_id=None, edge=None):
        # Time complexity: O(V) where V is the number of vertices
        if edge_id is not None:
            edge = None
            for k, v in self.edges.items():
                if v == edge_id:
                    edge = k
                    break
            if edge is None:
                raise ValueError("Edge ID not found")

        if edge not in self.edges:
            raise ValueError("Edge does not exist")
        del self.edges[edge]
        self.vertices[edge[0]].remove(edge[1])
        self.num_edges -= 1

    def remove_vertex(self, vertex):
        # Time complexity: O(V + E) where V is the number of vertices and E is the number of edges
        if vertex not in self.vertices:
            raise ValueError("Vertex does not exist")

        # Remove edges that contain the vertex
        edges_to_remove = [edge for edge in self.edges if vertex in edge]
        for edge in edges_to_remove:
            del self.edges[edge]
            self.vertices[edge[0]].remove(edge[1])
            self.num_edges -= 1

        # Remove the vertex itself
        del self.vertices[vertex]
        self.num_vertices -= 1

    def create_random(self, n, m):
        # Time complexity: O(n^2)
        if m > n*(n-1):
            raise ValueError("Number of edges exceeds maximum")
        self.vertices = {v: [] for v in range(n)}
        self.num_vertices = n
        edges = set()
        while len(edges) < m:
            start = random.randint(0, n-1)
            end = random.randint(0, n-1)
            if start != end:
                edges.add((start, end))
        self.edges = {edge: i+1 for i, edge in enumerate(edges)}
        for edge in edges:
            self.vertices[edge[0]].append(edge[1])
        self.num_edges = m

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
        if start_vertex not in self.vertices or end_vertex not in self.vertices:
            raise ValueError("Vertices not found")
        edge = (start_vertex, end_vertex)
        if edge in self.edges:
            return self.edges[edge]
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
    
    def edge_endpoints(self, edge_id):
        # Time complexity: O(E) where E is the number of edges
        for edge, eid in self.edges.items():
            if eid == edge_id:
                return edge
        raise ValueError("Edge ID not found")
    
    def __str__(self):
        # Time complexity: O(V + E) where V is the number of vertices and E is the number of edges
        result = ""
        result += " ".join(str(v) for v in self.vertices) + "\n"
        for edge, eid in self.edges.items():
            result += f"e{eid}: {edge[0]} {edge[1]}\n"
        return result


# Example Usage:
graph = DirectedGraph()
graph.add_vertex(0)
graph.add_vertex(1)
graph.add_vertex(2)
graph.add_vertex(3)
graph.add_edge(0, 1)
graph.add_edge(1, 2)
graph.add_edge(2, 0)
graph.add_edge(2, 3)
print(graph)

print("Degree of vertex 2:", graph.deg(2))
print("Degree of vertex 3:", graph.deg(3))
print()

print("Number of vertices:", graph.get_num_vertices())
print("Number of edges:", graph.get_num_edges())

print("Outbound edges of vertex 2:", graph.outbound_edges(2))
print("Inbound edges of vertex 2:", graph.inbound_edges(2))


print("Edge ID of (2, 3):", graph.is_edge(2, 3))
print("Edge ID of (3, 2):", graph.is_edge(3, 2))

graph.remove_edge(edge=(2, 0))
print("After removing edge (2, 0):")
print(graph)

graph.remove_vertex(0)
print("After removing vertex 0:")
print(graph)

print("Copy of the graph:")
print(graph)

graph.create_random(5, 10)
print("Random graph:")
print(graph)