from queue import LifoQueue
from directed_graph import *


class Iterator:
    def __init__(self, graph, start_vertex):
        # Theta(1)
        self.__graph = graph
        self.__start = start_vertex
        self.__stack = LifoQueue(10000)
        self.__current = self.__start
        self.__visited = [self.__current]
        self.__over = False
        self.first()

    def first(self):
        self.__current = self.__start
        self.__stack = LifoQueue(self.__graph.get_m())
        self.__visited = [self.__current]
        for node in self.__graph.outbound_edges(self.__current):
            self.__stack.put(node)

    def get_current(self):
        # Theta(1)
        if self.valid():
            return self.__current
        raise ValueError("Invalid iterator!")

    def next(self):
        # O(n)
        if not self.valid():
            raise ValueError("Invalid iterator!")
        if self.__stack.empty():
            self.__over = True
        else:
            self.__current = self.__stack.get()
            while self.__current in self.__visited and not self.__stack.empty():
                self.__current = self.__stack.get()
            if self.__current not in self.__visited:
                self.__visited.append(self.__current)
                for node in self.__graph.outbound_edges(self.__current):
                    if node not in self.__visited:
                        self.__stack.put(node)
            else:
                self.__over = True

    def valid(self):
        # Theta(1)
        return not self.__over
