class GraphIterator:
    def __init__(self, graph, start_vertex, traversal_type="BFS"):
        self.graph = graph
        self.current_vertex = start_vertex
        self.visited = {v: False for v in self.graph.vertices}
        self.first = True
        self.traversal_type = traversal_type

    def first(self):
        self.current_vertex = self.start_vertex
        self.visited = {v: False for v in self.graph.vertices}
        self.visited[self.current_vertex] = True
        self.first = True

    def get_current(self):
        if not self.valid():
            raise ValueError("Iterator is not valid")
        return self.current_vertex

    def next(self):
        if not self.valid():
            raise ValueError("Iterator is not valid")
        neighbors = self.graph.vertices[self.current_vertex]
        for neighbor in neighbors:
            if not self.visited[neighbor]:
                self.visited[neighbor] = True
                self.current_vertex = neighbor
                return
        self.current_vertex = None

    def valid(self):
        return self.current_vertex is not None

    def __iter__(self):
        return self

    def __next__(self):
        if not self.valid():
            raise StopIteration
        self.next()
        if self.valid():
            return self.get_current()
        else:
            raise StopIteration
