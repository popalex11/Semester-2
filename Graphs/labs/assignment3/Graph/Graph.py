import random
from copy import deepcopy
from Graph.Iterator import Iterator


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

    def add_edge(self, initial_vertex, terminal_vertex):
        # Complexity: O(n+m/n)
        if initial_vertex == terminal_vertex or initial_vertex not in self._nodes or terminal_vertex not in self._nodes:
            raise ValueError(f'Invalid vertices {initial_vertex} {terminal_vertex}!')
        if terminal_vertex in self._nodes[initial_vertex]:
            raise ValueError(f'Edge {initial_vertex, terminal_vertex} already exists!')
        self._nodes[initial_vertex].append(terminal_vertex)
        if not self.__directed:
            self._nodes[terminal_vertex].append(initial_vertex)
        if self.__weighted:
            self._weights[(initial_vertex, terminal_vertex)] = 1
            if not self.__directed:
                self._weights[(terminal_vertex, initial_vertex)] = 1

    def remove_edge(self, initial_vertex, terminal_vertex):
        # Complexity: O(n+m/n)
        if (initial_vertex not in self._nodes.keys() or
                terminal_vertex not in self._nodes.keys() or initial_vertex == terminal_vertex):
            raise ValueError("Invalid vertices!")
        if terminal_vertex not in self._nodes[initial_vertex]:
            raise ValueError("Edge does not exist!")
        self._nodes[initial_vertex].remove(terminal_vertex)
        if not self.__directed:
            self._nodes[terminal_vertex].remove(initial_vertex)
        if self.__weighted:
            self._weights.pop((initial_vertex, terminal_vertex))
            if not self.__directed:
                self._weights.pop((terminal_vertex, initial_vertex))

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

    def __str__(self):
        # Complexity: Theta(n+m)
        s = f'Directed: {self.__directed}\nWeighted: {self.__weighted}\n'
        s += "Vertices:\n"
        for key in self._nodes.keys():
            s = s + str(key) + " "
        s += "\nEdges:"
        if self.__directed:
            for node in self._nodes:
                for edge in self._nodes[node]:
                    s += f'\n{node} {edge}'
                    if self.__weighted:
                        s += f' {self._weights[(node, edge)]}'
        else:
            edges = []
            for node in self._nodes:
                for edge in self._nodes[node]:
                    if (edge, node) not in edges:
                        edges.append((edge, node))
                        edges.append((node, edge))
                        s += f'\n{node} {edge}'
                        if self.__weighted:
                            s += f' {self._weights[(node, edge)]}'
        return s
