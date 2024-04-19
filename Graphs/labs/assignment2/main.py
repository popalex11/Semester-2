from directed_graph import Graph
from metro import Metro

def print_menu(graph):
    print("1. Add vertex")
    print("2. Add edge")
    print("3. Remove vertex")
    print("4. Remove edge")
    print("5. Create random graph")
    print("6. Get degree of vertex")
    print("7. Check if the edge exists")
    print("8. Copy graph")
    print("9. Show the graph")
    print("10. DFS(Depth First Search)")
    print("11. Path length")
    print("0. Exit")
    print("The graph is " + ("Directed" if graph.is_reversible() else "Undirected") +", " + ("Weighted" if graph.is_weighted() else "Unweighted"))

def main():
    graph = Graph.create_from_file("graph_data.txt")
    while True:
        try:
            print_menu(graph)
            command = input("Option: ")
            if command == "1":
                graph.add_vertex()
                print(graph)
                print()
                print("Vertex successfully added.")
            elif command == "2":
                vertex1 = int(input("Enter first vertex: "))
                vertex2 = int(input("Enter second vertex: "))
                if graph.is_weighted():
                    weight = float(input("Enter weight: "))
                    graph.add_edge(vertex1, vertex2, weight)
                else:
                    graph.add_edge(vertex1, vertex2)
                print(graph)
                print()
                print("Edge {vertex1} -> {vertex2} successfully added.")
            elif command == "3":
                vertex = int(input("Enter vertex to remove: "))
                graph.remove_vertex(vertex)
                print(graph)
                print()
                print(f"Vertex {vertex} successfully removed.")
            elif command == "4":
                vertex1 = int(input("Enter first vertex: "))
                vertex2 = int(input("Enter second vertex: "))
                graph.remove_edge(vertex1, vertex2)
                print(graph)
                print()
                print("Edge {vertex1} -> {vertex2} successfully removed.")
            elif command == "5":
                n = int(input("Enter number of vertices: "))
                graph.create_random(n)
                print(graph)
                print()
                print("Random graph successfully created.")
            elif command == "6":
                vertex = int(input("Enter vertex: "))
                print(f"Degree of vertex {vertex}: {graph.deg(vertex)}")
            elif command == "7":
                vertex1 = int(input("Enter first vertex: "))
                vertex2 = int(input("Enter second vertex: "))
                if str(graph.is_edge(vertex1, vertex2)) == "True":
                    print("Edge does exist.")
                else:
                    print("Edge does not exist.")
            elif command == "8":
                copy = graph.copy_graph()
                print("Graph successfully copied.")
            elif command == "9":
                print(graph)
            elif command == "10":
                start_vertex = int(input("Enter start vertex: "))
                iterator = graph.iter_vertex(start_vertex)
                iterator.first()
                while iterator.valid():
                    print(iterator.get_current())
                    iterator.next()
            elif command == "11":
                start_vertex = int(input("Enter start vertex: "))
                iterator = graph.iter_vertex(start_vertex)
                iterator.first()
                while iterator.valid():
                    print(iterator.get_path_length())
                    iterator.next()
            elif command == "0":
                break
            else:
                print("Invalid command")
        except Exception as e:
            print(e)
            print()

def metro_menu():
    metro = Metro.read_metro("asgn3input.txt")
    while True:
        try:
            line = input("Line: ")
            station = input("Station: ")
            d = metro.bellman_ford((line, station))
            print(f'Distances:\n{d}\n')
        except Exception as e:
            print(f'An error occurred:{e}')

if __name__ == "__main__":
    metro_menu()