class GraphIterator:
    def __init__(self, graph, start_vertex):
        self.graph = graph
        self.start_vertex = start_vertex
        self.current_vertex = start_vertex
        self.visited = {v: False for v in graph.vertices}
        self.stack = [start_vertex]

    def first(self):
        self.visited = {v: False for v in self.graph.vertices}
        self.stack = [self.start_vertex]
        self.visited[self.start_vertex] = True
        self.current_vertex = self.start_vertex
        self.next()

    def next(self):
        if not self.stack:
            self.current_vertex = None
            return
        
        self.current_vertex = self.stack.pop()
        for neighbor in self.graph.outbound_neighbors(self.current_vertex):
            if not self.visited[neighbor]:
                self.stack.append(neighbor)
                self.visited[neighbor] = True

    def valid(self):
        return self.current_vertex is not None and len(self.stack) > 0

    def get_current(self):
        if not self.valid():
            raise ValueError("Iterator is not valid")
        return self.current_vertex