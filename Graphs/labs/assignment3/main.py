from Metro.Metro import *


def regular_main_menu():
    main_menu = ("\n0. Create a new empty graph.\n"
                 "1. Add new vertex.\n"
                 "2. Add new edge.\n"
                 "3. Remove an edge.\n"
                 "4. Remove a vertex.\n"
                 "5. Create a random graph (deletes the already existing graph).\n"
                 "6. Get the number of vertices.\n"
                 "7. Get the number of edges.\n"
                 "8. Get the degree of a vertex.\n"
                 "9. Check if there is an edge between two vertices.\n"
                 "10. Get the outbound edges of a vertex.\n"
                 "11. Get the inbound edges of a vertex.\n"
                 "12. Copy the graph.\n"
                 "13. Print the graph.\n"
                 "14. Iterate through the graph via DFS.\n"
                 "15. Set the weight of an edge.\n"
                 "16. Give all edges random weights\n"
                 "17. Exit.\n"
                 "Option: ")
    opt = -1
    try:
        graph = Graph.read_graph("InputFile.txt")
        while opt != 17:
            try:

                if opt != -1:
                    input()
                opt = int(input(main_menu))

                if opt == 0:
                    graph = Graph(graph.is_directed(), graph.is_weighted())

                elif opt == 1:
                    vertex = int(input("Vertex: "))
                    graph.add_vertex(vertex)

                elif opt == 2:
                    in_vertex = int(input("Initial vertex: "))
                    out_vertex = int(input("Terminal vertex: "))
                    graph.add_edge(in_vertex, out_vertex)

                elif opt == 3:
                    in_vertex = int(input("Initial vertex: "))
                    out_vertex = int(input("Terminal vertex: "))
                    graph.remove_edge(in_vertex, out_vertex)

                elif opt == 4:
                    vertex = int(input("Vertex: "))
                    graph.remove_vertex(vertex)

                elif opt == 5:
                    n = int(input("Number of vertices: "))
                    m = int(input("Number of edges: "))
                    if graph.is_weighted():
                        b = int(input("Add weight range? (1/0): "))
                        if b == 1:
                            lower = int(input("Lower bound: "))
                            upper = int(input("Upper bound: "))
                            graph = graph.create_random(n, m, (lower, upper))
                        elif b == 0:
                            graph = graph.create_random(n, m)
                        else:
                            raise ValueError("Invalid command!")
                    else:
                        graph = graph.create_random(n, m)

                elif opt == 6:
                    print(graph.get_n())

                elif opt == 7:
                    print(graph.get_m())

                elif opt == 8:
                    vertex = int(input("Vertex: "))
                    controller = int(input("Controller (0:total degree,1:out-degree,2:in-degree): "))
                    print(graph.deg(vertex, controller))

                elif opt == 9:
                    in_vertex = int(input("Initial vertex: "))
                    out_vertex = int(input("Terminal vertex: "))
                    print(graph.is_edge(in_vertex, out_vertex))

                elif opt == 10:
                    vertex = int(input("Vertex: "))
                    print(graph.outbound_edges(vertex))

                elif opt == 11:
                    vertex = int(input("Vertex: "))
                    print(graph.inbound_edges(vertex))

                elif opt == 12:
                    graph = graph.copy_graph()

                elif opt == 13:
                    print(graph)

                elif opt == 14:
                    vertex = int(input("Start vertex: "))
                    iterator = graph.iter_vertex(vertex)
                    iterator.first()
                    while iterator.valid():
                        print(iterator.get_current())
                        iterator.next()

                elif opt == 15:
                    if not graph.is_weighted():
                        raise ValueError("Graph is not weighted!")
                    initial = int(input("Initial vertex: "))
                    terminal = int(input("Terminal vertex: "))
                    weight = int(input("Weight: "))
                    graph.set_weight(initial, terminal, weight)

                elif opt == 16:
                    min_w = int(input("Minimum weight:"))
                    max_w = int(input("Maximum weight:"))
                    graph.random_weights((min_w, max_w))

                elif opt == 17:
                    print("Exiting.")

                else:
                    raise ValueError("Invalid command!\n")

            except Exception as e:
                print(f'Error: {e}')
    except Exception as e:
        print(f'Error: {e}')


def metro_menu():
    metro = Metro.read_metro("Metro/A3_Input.txt")
    while True:
        try:
            line = input("Line: ")
            station = input("Station: ")
            d = metro.bellman_ford((line, station))
            print(f'Distances:\n{d}\n')
        except Exception as e:
            print(f'An error occurred:{e}')


if __name__ == '__main__':
    metro_menu()
