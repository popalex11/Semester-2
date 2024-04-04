class GraphEdge:
    def __init__(self, start_vertex, end_vertex, weight=None):
        self.start_vertex = start_vertex
        self.end_vertex = end_vertex
        self.weight = weight

    def __str__(self):
        if self.weight is not None:
            return f"{self.start_vertex} --({self.weight})--> {self.end_vertex}"
        else:
            return f"{self.start_vertex} --> {self.end_vertex}"
