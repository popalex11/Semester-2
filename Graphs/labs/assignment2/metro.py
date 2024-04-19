from directed_graph import Graph
import math

class Metro(Graph):
    def __init__(self):
        super().__init__(True , True)
        self.stations={}

    def read_metro(file):
        metro = Metro()
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
                    if s[0] not in metro.stations.keys():
                        metro.stations[s[0]] = []
                    metro.stations[s[0]].append(bits[0])
                    try:
                        metro.add_vertex((bits[0], s[0]))
                    except:
                        pass
                    if int(s[1]) != 0:
                        metro.add_edge((bits[0], prev), (bits[0], s[0]))
                        metro.set_weight((bits[0], prev), (bits[0], s[0]), int(s[1]))
                    j = j + 1
                    prev = s[0]
                i = i + 1
            for station in metro.stations.keys():
                for line in metro.stations[station]:
                    for line2 in metro.stations[station]:
                        if line != line2:
                            try:
                                metro.add_edge((line, station), (line2, station))
                            except:
                                pass
                            metro.set_weight((line, station), (line2, station), 3)
        return metro
    
    def bellman_ford(self, start):

        if start not in self.stations.keys():
            raise ValueError("Station does not exist")
        dist = {}
        prev = {}
        for station in self.stations.keys():
            if station == start:
                dist[station] = 0
            else:
                dist[station] = math.inf
            prev[station] = None
        for i in range(len(self.stations) - 1):
            for edge in self.get_edges():
                if dist[edge[0]] + self.get_weight(edge[0], edge[1]) < dist[edge[1]]:
                    dist[edge[1]] = dist[edge[0]] + self.get_weight(edge[0], edge[1])
                    prev[edge[1]] = edge[0]
        return (dist, prev)
    
