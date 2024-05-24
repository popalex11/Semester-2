import random
from copy import deepcopy
from graph_iterator import Iterator

class DisjointSet:
    def __init__(self, vertices):
        self.parent = {vertex: vertex for vertex in vertices}
        self.rank = {vertex: 0 for vertex in vertices}

    def find(self, vertex):
        if self.parent[vertex] != vertex:
            self.parent[vertex] = self.find(self.parent[vertex])
        return self.parent[vertex]

    def union(self, vertex1, vertex2):
        root1 = self.find(vertex1)
        root2 = self.find(vertex2)
        if root1 != root2:
            if self.rank[root1] < self.rank[root2]:
                self.parent[root1] = root2
            elif self.rank[root1] > self.rank[root2]:
                self.parent[root2] = root1
            else:
                self.parent[root2] = root1
                self.rank[root1] += 1


class Graph:
    def __init__(self, directed=True, weighted=False):
        # Complexity:Theta(1)
        self._nodes = {}
        self.__directed = directed
        self.__weighted = weighted
        if weighted:
            self._weights = {}

    def is_directed(self):
        # Theta(1)
        return self.__directed

    def is_weighted(self):
        # Theta(1)
        return self.__weighted

    def add_vertex(self, vertex_id):
        # Complexity: O(n)
        if vertex_id in self._nodes:
            raise ValueError(f'Vertex {vertex_id} already exists!')
        self._nodes[vertex_id] = []

    def add_edge(self, vertex1, vertex2):
        # Complexity: O(n+m/n)
        if vertex1 == vertex2 or vertex1 not in self._nodes or vertex2 not in self._nodes:
            raise ValueError(f'Invalid vertices {vertex1} {vertex2}!')
        # if terminal_vertex in self._nodes[initial_vertex]:
            # raise ValueError(f'Edge {initial_vertex, terminal_vertex} already exists!')
        if vertex2 not in self._nodes[vertex1]:
            self._nodes[vertex1].append(vertex2)
        if not self.__directed and vertex1 not in self._nodes[vertex2]:
            self._nodes[vertex2].append(vertex1)

        if self.__weighted:
            self._weights[(vertex1, vertex2)] = 1
            if not self.__directed:
                self._weights[(vertex2, vertex1)] = 1

    def remove_vertex(self, vertex):
        if vertex not in self._nodes.keys():
            raise ValueError("Vertex does not exist!")
        
        if not self.__directed:
            for node, edges in self._nodes.items():
                if vertex in edges:
                    edges.remove(vertex)

        self._nodes.pop(vertex, None)

        if self.__weighted:
            for node in self._nodes.keys():
                self._weights.pop((vertex, node), None)
                if not self.__directed:
                    self._weights.pop((node, vertex), None)

    def remove_vertex(self, vertex):
        # Complexity: O(n+m)
        if vertex not in self._nodes.keys():
            raise ValueError("Vertex does not exist!")
        self._nodes.pop(vertex)
        for nodes in self._nodes.values():
            if vertex in nodes:
                nodes.remove(vertex)
        if self.__weighted:
            for node in self._nodes.keys():
                if (vertex, node) in self._weights.keys():
                    self._weights.pop((vertex, node))
                    if not self.__directed:
                        self._weights.pop((node, vertex))

    def create_random(self, n, m, weight_range=(0, 10)):
        # Complexity: roughly Theta(n*n+m*(n+m/n))
        if n < 0:
            raise ValueError("Number of nodes cannot be negative!")
        if m < 0:
            raise ValueError("Number of edges cannot be negative!")
        if self.__directed and m > n * (n - 1):
            raise ValueError("Too many edges!")
        if not self.__directed and m > n * (n - 1) / 2:
            raise ValueError("Too many edges!")
        g = Graph(self.__directed, self.__weighted)
        for i in range(0, n):
            g.add_vertex(i)
        while m > 0:
            try:
                initial = random.randrange(0, n)
                terminal = random.randrange(0, n)
                g.add_edge(initial, terminal)
                if self.__weighted:
                    g.set_weight(initial, terminal, random.randrange(weight_range[0], weight_range[1] + 1))
                m = m - 1
            finally:
                continue
        return g

    def get_edges(self):
    # Complexity: O(n*m)
        if not self.__directed:
            return [(i, j, 1) for i in self._nodes.keys() for j in self._nodes[i]]
        return [(i, j, 1) for i in self._nodes.keys() for j in self._nodes[i]]

    def get_n(self):
        # Complexity:Theta(1)
        return len(self._nodes.keys())

    def get_m(self):
        # Complexity:Theta(n)
        s = 0
        for edges in self._nodes.values():
            s += len(edges)
        if not self.__directed:
            s = s // 2
        return s

    def deg(self, vertex, controller=1):
        # Complexity: O(n+n*m)
        if vertex not in self._nodes.keys():
            raise ValueError("Vertex does not exist!")
        if not self.__directed:
            return len(self._nodes[vertex])
        if controller == 0:
            return len(self._nodes[vertex]) + len(self.inbound_edges(vertex))
        if controller == 1 and self.__directed:
            return len(self._nodes[vertex])
        if controller == 2 and self.__directed:
            return len(self.inbound_edges(vertex))
        raise ValueError("Invalid controller!")

    def is_edge(self, initial_vertex, terminal_vertex):
        # Complexity: O(n+m/n)
        if initial_vertex not in self._nodes.keys() or terminal_vertex not in self._nodes.keys():
            raise ValueError("Invalid vertices!")
        return terminal_vertex in self._nodes[initial_vertex]

    def set_weight(self, initial_vertex, terminal_vertex, new_weight):
        # O(n+m)
        if not self.__weighted:
            raise ValueError("Graph is not weighted!")
        if not self.is_edge(initial_vertex, terminal_vertex):
            raise ValueError("Edge does not exist!")
        self._weights[(initial_vertex, terminal_vertex)] = new_weight
        if not self.__directed:
            self._weights[(terminal_vertex, initial_vertex)] = new_weight

    def random_weights(self, weight_range=(1, 5)):
        if not isinstance(weight_range, tuple):
            raise ValueError("Weight range must be a tuple!")
        if not self.__weighted:
            self.__weighted = True
            self._weights = {}
        for node in self._nodes.keys():
            for terminal in self._nodes[node]:
                self._weights[(node, terminal)] = random.randrange(weight_range[0], weight_range[1] + 1)

    def outbound_edges(self, vertex):
        # Complexity: Theta(n)
        if vertex not in self._nodes.keys():
            raise ValueError("Vertex does not exist!")
        return self._nodes[vertex][:]

    def inbound_edges(self, vertex):
        # Complexity: O(n*m)
        if vertex not in self._nodes.keys():
            raise ValueError("Vertex does not exist!")
        if not self.__directed:
            return self._nodes[vertex][:]
        inbound = []
        for node in self._nodes.keys():
            if vertex in self._nodes[node]:
                inbound.append(node)
        return inbound[:]

    def iter_vertex(self, vertex):
        if vertex not in self._nodes.keys():
            raise ValueError("Invalid vertex!")
        return Iterator(self, vertex)

    def copy_graph(self):
        # Complexity: O(n)
        return deepcopy(self)

    @staticmethod
    def read_graph(file):
        with open(file, 'r') as f:
            lines = f.readlines()
            bits = lines[0].split()
            if len(bits) != 4:
                raise ValueError("Invalid input file!")
            nr_of_nodes = int(bits[0])
            nr_of_lines = int(bits[1])
            weighted = False
            directed = True
            if bits[2] == 'F':
                directed = False
            elif bits[2] != 'T':
                raise ValueError("Invalid input file!")
            if bits[3] == 'T':
                weighted = True
            elif bits[3] != 'F':
                raise ValueError("Invalid input file!")
            g = Graph(directed=directed, weighted=weighted)
            for i in range(nr_of_nodes):
                g.add_vertex(i)
            for i in range(1, nr_of_lines + 1):
                if i >= len(lines):
                    raise ValueError("Invalid input file!")
                bits = lines[i].split()
                g.add_edge(int(bits[0]), int(bits[1]))
                if weighted:
                    if len(bits) != 3:
                        raise ValueError("Invalid input file!")
                    g.set_weight(int(bits[0]), int(bits[1]), int(bits[2]))
                    if not directed:
                        g.set_weight(int(bits[1]), int(bits[0]), int(bits[2]))
                elif len(bits) != 2:
                    raise ValueError("Invalid input file!")
                i += 1
        return g
    
    def kruskal(self):
        # Instantiate disjoint set with vertices
        disjoint_set = DisjointSet(self._nodes.keys())

        minimum_spanning_tree = []

        # Sort edges by weight
        edges = sorted(self.get_edges(), key=lambda x: x[2])

        for edge in edges:
            vertex1, vertex2, weight = edge

            # Find the roots of the sets containing vertex1 and vertex2
            root1 = disjoint_set.find(vertex1)
            root2 = disjoint_set.find(vertex2)

            if root1 != root2:
                minimum_spanning_tree.append(edge)
                disjoint_set.union(vertex1, vertex2)

        return minimum_spanning_tree    

    def get_height_of_tree(self):
        # Get the minimum spanning tree using Kruskal's algorithm
        minimum_spanning_tree = self.kruskal()

        # Create an adjacency list representation of the tree
        tree = {}
        for vertex1, vertex2, weight in minimum_spanning_tree:
            if vertex1 not in tree:
                tree[vertex1] = []
            tree[vertex1].append(vertex2)
            if vertex2 not in tree:
                tree[vertex2] = []
            tree[vertex2].append(vertex1)

        # Perform depth-first search (DFS) to find the height of the tree
        max_depth = 0

        def dfs(node, depth, visited):
            nonlocal max_depth
            visited.add(node)
            max_depth = max(max_depth, depth)
            for neighbor in tree[node]:
                if neighbor not in visited:
                    dfs(neighbor, depth + 1, visited)

        # Start DFS from an arbitrary node in the tree
        start_node = next(iter(tree.keys()))
        dfs(start_node, 0, set())

        return max_depth    


    def __str__(self):
        s = f'Directed: {self.__directed}\nWeighted: {self.__weighted}\n'
        s += "Vertices:\n"
        for key in sorted(self._nodes.keys()):  # Sort vertices in ascending order
            s = s + str(key) + " "
        s += "\nEdges:"

        visited_edges = set()  # To avoid printing duplicate edges

        def dfs(node, current_s):
            edges = sorted(self._nodes[node])
            for edge in edges:
                forward_edge = (node, edge)
                backward_edge = (edge, node)
                if forward_edge not in visited_edges and backward_edge not in visited_edges:
                    current_s += f'\n{node} {edge}'
                    if not self.__directed:
                        current_s += f'\n{edge} {node}'  # Include the reverse direction of the edge
                    visited_edges.add(forward_edge)
                    visited_edges.add(backward_edge)
                    current_s = dfs(edge, current_s)  # Recursively call dfs and update current_s
            return current_s

        for node in sorted(self._nodes.keys()):  # Sort vertices in ascending order
            s = dfs(node, s)  # Pass s to the dfs function to update it

        return s

