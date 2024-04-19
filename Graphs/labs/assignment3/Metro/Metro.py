from Graph.Graph import *
import math


class Metro(Graph):
    def __init__(self):
        super().__init__(True, True)
        self.__station_lines = {}

    @staticmethod
    def read_metro(file):
        g = Metro()
        with open(file, 'r') as f:
            lines = f.readlines()
            i = 0
            while i < len(lines):
                tmp = lines[i].strip("\n")
                bits = tmp.split(",")
                j = 1
                prev = None
                while j < len(bits):
                    tmp = bits[j].strip("()\n")
                    s = tmp.split(";")
                    if s[0] not in g.__station_lines.keys():
                        g.__station_lines[s[0]] = []
                    g.__station_lines[s[0]].append(bits[0])
                    try:
                        g.add_vertex((bits[0], s[0]))
                    except:
                        pass
                    if int(s[1]) != 0:
                        g.add_edge((bits[0], prev), (bits[0], s[0]))
                        g.set_weight((bits[0], prev), (bits[0], s[0]), int(s[1]))
                    j = j + 1
                    prev = s[0]
                i = i + 1
            for station in g.__station_lines.keys():
                for line in g.__station_lines[station]:
                    for line2 in g.__station_lines[station]:
                        if line != line2:
                            try:
                                g.add_edge((line, station), (line2, station))
                            except:
                                pass
                            g.set_weight((line, station), (line2, station), 3)
        return g

    def bellman_ford(self, start):

        if start not in self._nodes.keys():
            raise ValueError(f'{start} is invalid start !')
        dist = {}
        min_dist = {}
        for node in self._nodes.keys():
            dist[node] = math.inf
        for station in self.__station_lines.keys():
            min_dist[station] = math.inf
        dist[start] = 0
        min_dist[start[1]] = 0

        changed = True
        while changed:
            changed = False
            for edge in self._weights.keys():
                if dist[edge[1]] > dist[edge[0]] + self._weights[edge]:
                    dist[edge[1]] = dist[edge[0]] + self._weights[edge]
                    if min_dist[edge[1][1]] > dist[edge[1]]:
                        min_dist[edge[1][1]] = dist[edge[1]]
                    changed = True
        return min_dist
