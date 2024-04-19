import random
from graph_iterator import GraphIterator


class Graph:
    def __init__(self, reversible: bool, weighted: bool = False):
        self.__nodes = 0
        self.__reversible = reversible
        self.__weighted = weighted  
        self.__graph = []

    def get_graph(self):
        return self.__graph

    def add_vertex(self):
        self.__nodes += 1
        for row in self.__graph:
            row.append(0)  # Use 0 to indicate no connection
        self.__graph.append([0] * self.__nodes)

    def is_tuple(self, vertex):
        return isinstance(vertex, tuple)
    

    def add_edge(self, vertex1, vertex2, weight=1):
        '''
        I want to first verify if vertex1 and vertex2 ar tuples or integers and then add the edge in each case
        '''
        if self.is_tuple(vertex1) and self.is_tuple(vertex2):
            vertex1, vertex2 = int(vertex1[0]), int(vertex2[0])

        if vertex1 < 0 or vertex2 < 0 or vertex1 >= self.__nodes or vertex2 >= self.__nodes:
            raise ValueError("One or both of the vertices are not in the graph")
        if not self.__weighted:
            weight = 1  # Ensures compatibility with unweighted graphs
        self.__graph[vertex1][vertex2] = weight
        if self.__reversible:
            self.__graph[vertex2][vertex1] = weight

    def remove_edge(self, vertex1, vertex2):
        self.__graph[vertex1][vertex2] = 0
        if self.__reversible:
            self.__graph[vertex2][vertex1] = 0

    def remove_vertex(self, vertex):
        if vertex < 0 or vertex >= self.__nodes:
            raise ValueError("The vertex is not in the graph")
        self.__nodes -= 1
        self.__graph.pop(vertex)
        for row in self.__graph:
            row.pop(vertex)

    def create_random(self, n, max_weight=10):
        self.__nodes = n
        self.__graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(i + 1, n):
                if random.random() < 0.5:
                    weight = random.randint(1, max_weight) if self.__weighted else 1
                    self.add_edge(i, j, weight)

    def get_n(self):
        return self.__nodes

    def get_edges(self):
        edges = []
        for i in range(self.__nodes):
            for j in range(self.__nodes):
                if self.__graph[i][j] != 0:
                    edges.append((i, j, self.__graph[i][j]) if self.__weighted else (i, j))
        return edges

    def deg(self, x):
        return sum(1 for weight in self.__graph[x] if weight != 0)

    def is_edge(self, x, y):
        return self.__graph[x][y] != 0

    def outbound_edges(self, x):
        if self.__reversible:
            return "This function is only available for non-reversible graphs"
        return [(x, i, self.__graph[x][i]) for i in range(self.__nodes) if self.__graph[x][i] != 0] if self.__weighted \
            else [i for i in range(self.__nodes) if self.__graph[x][i] != 0]

    def inbound_edges(self, x):
        if self.__reversible:
            return "This function is only available for non-reversible graphs."
        return [(i, x, self.__graph[i][x]) for i in range(self.__nodes) if self.__graph[i][x] != 0] if self.__weighted \
            else [i for i in range(self.__nodes) if self.__graph[i][x] != 0]

    def copy_graph(self):
        new_graph = Graph(self.__reversible, self.__weighted)
        new_graph.__nodes = self.__nodes
        new_graph.__graph = [row[:] for row in self.__graph]
        return new_graph

    def is_reversible(self):
        return self.__reversible

    def iter_vertex(self, start_vertex):
        return GraphIterator(self, start_vertex)

    def is_weighted(self):
        return self.__weighted

    @staticmethod
    def create_from_file(file_name):
        with open(file_name, "r") as file:
            n, m, reversible, weighted = file.readline().strip().split()
            n, m = int(n), int(m)
            reversible = True if reversible == "T" else False
            weighted = True if weighted == "T" else False

            graph = Graph(reversible, weighted)

            for _ in range(n):
                graph.add_vertex()

            for _ in range(m):
                edge_data = file.readline().strip().split()
                if weighted:
                    vertex1, vertex2, weight = int(edge_data[0]), int(edge_data[1]), int(edge_data[2])
                    graph.add_edge(vertex1, vertex2, weight)
                else:
                    vertex1, vertex2 = int(edge_data[0]), int(edge_data[1])
                    graph.add_edge(vertex1, vertex2)

            return graph

    def __str__(self):
        graph_str = ""
        for i in range(self.__nodes):
            for j in range(self.__nodes):
                if self.__graph[i][j] != 0:
                    weight_str = f" Weight: {self.__graph[i][j]}" if self.__weighted else ""
                    graph_str += f"Edge: {i} -> {j}{weight_str}\n"
        return graph_str.strip()

    def __repr__(self):
        return self.__str__()