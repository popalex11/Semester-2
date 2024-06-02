from graph import *


class Color:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    RESET = '\033[0m'

def regular_main_menu():
    main_menu_assignment2 = ("\n0 - Create a new empty graph.\n"
                 "1 - Add new vertex.\n"
                 "2 - Add new edge.\n"
                 "3 - Remove an edge.\n"
                 "4 - Remove a vertex.\n"
                 "5 - Create a random graph (deletes the already existing graph).\n"
                 "6 - Get the number of vertices.\n"
                 "7 - Get the number of edges.\n"
                 "8 - Get the degree of a vertex.\n"
                 "9 - Check if there is an edge between two vertices.\n"
                 "10 - Get the outbound edges of a vertex.\n"
                 "11 - Get the inbound edges of a vertex.\n"
                 "12 - Copy the graph.\n"
                 "13 - Print the graph.\n"
                 "14 - Iterate through the graph via DFS.\n"
                 "15 - Set the weight of an edge.\n"
                 "16 - Give all edges random weights\n"
                 "17 - Exit.\n"
                 "Option: ")
    
    main_menu_assignment4 = ("\n1. Create and print the minimal spanning tree. \n"
                             "2. Give the height of the tree. \n"
                             "3. Go back to the main menu. \n"
                             "Option: ")
    
    main_menu_assignment5 = ("\n1. Check if is Eulerian Graph. \n"
                             "2. Find an Eulerian circuit using Hierholzer's algorithm. \n"
                             "3. Go back to the main menu. \n"
                             "Option: ")

    main_menu_assignment6 = ("\n1. Find all independent sets of size k (using backtracking). \n"
                             "2. Go back to the main menu. \n"
                             "Option: ")
    
    menu = ("1. Assignment 2 options.\n"
            "2. Assignment 4 options. \n"
            "3. Assignment 5 options. \n"
            "4. Assignment 6 options. \n"
            "5. Exit. \n"
            "Option: ")

    option = -1

    try:
        graph = Graph.read_graph("graph_data.txt")
        
        while option != 5:
            try: 

                if option != -1:
                    input()
                option = int(input(Color.BLUE + menu))

                if option ==1:
                    opt = -1
                    while opt != 17:
                        try:

                            if opt != -1:
                                input()
                            opt = int(input(Color.GREEN + main_menu_assignment2))

                            if opt == 0:
                                graph = graph(graph.is_directed(), graph.is_weighted())

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
                                print(Color.MAGENTA + str(graph.get_n()))

                            elif opt == 7:
                                print(Color.MAGENTA + str(graph.get_m()))

                            elif opt == 8:
                                vertex = int(input("Vertex: "))
                                controller = int(input("Controller (0:total degree,1:out-degree,2:in-degree): "))
                                print(Color.MAGENTA +str(graph.deg(vertex, controller)))

                            elif opt == 9:
                                in_vertex = int(input("Initial vertex: "))
                                out_vertex = int(input("Terminal vertex: "))
                                print(Color.MAGENTA +str(graph.is_edge(in_vertex, out_vertex)))

                            elif opt == 10:
                                vertex = int(input("Vertex: "))
                                print(Color.MAGENTA +str(graph.outbound_edges(vertex)))

                            elif opt == 11:
                                vertex = int(input("Vertex: "))
                                print(Color.MAGENTA +str(graph.inbound_edges(vertex)))

                            elif opt == 12:
                                graph = graph.copy_graph()

                            elif opt == 13:
                                print(Color.MAGENTA +str(graph) )

                            elif opt == 14:
                                vertex = int(input("Start vertex: "))
                                iterator = graph.iter_vertex(vertex)
                                iterator.first()
                                while iterator.valid():
                                    print(Color.MAGENTA +str(iterator.get_current()))
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

                elif option == 2:
                    opt = -1
                    while opt != 3:
                        try:
                            if opt != -1:
                                input()
                            opt = int(input(Color.YELLOW + main_menu_assignment4))
                            if opt == 1:
                                print(Color.MAGENTA + str(graph.kruskal()))
                            elif opt == 2:
                                print(Color.MAGENTA + str(graph.get_height_of_tree()))
                            elif opt == 3:
                                print("Exiting.")

                            else:
                                raise ValueError("Invalid command! \n")
                        
                        except Exception as e:
                            print(f'Error: {e}')
                
                elif option == 3:
                    opt = -1
                    while opt != 3:
                        try:
                            if opt != -1:
                                input()
                            opt = int(input(Color.CYAN + main_menu_assignment5))
                            if opt == 1:
                                print(Color.MAGENTA + str(graph.is_eulerian()))
                            elif opt == 2:
                                print(Color.MAGENTA + str(graph.get_eulerian_circuit()))
                            elif opt == 3:
                                print("Exiting.")

                            else:
                                raise ValueError("Invalid command! \n")
                        except Exception as e:
                            print(f'Error: {e}')
                
                elif option == 4:
                    opt = -1
                    while opt != 2:
                        try:
                            if opt != -1:
                                input()
                            opt = int(input(Color.CYAN + main_menu_assignment6))
                            if opt == 1:
                                k = int(input("k: "))
                                print(Color.MAGENTA + str(graph.independent_sets(k)))
                            elif opt == 2:
                                print("Exiting.")

                            else:
                                raise ValueError("Invalid command! \n")
                        except Exception as e:
                            print(f'Error: {e}')

                elif option == 5:
                    print("Exiting.")


                else:
                    raise ValueError("Invalid command!\n")
    
            except Exception as e:
                print(f'Error: {e}')

    except Exception as e:
        print(f'Error: {e}')


if __name__ == '__main__':
    regular_main_menu()

# Standard Graph
# 7 10 F F
# 0 1
# 0 2
# 1 0
# 1 3
# 2 0
# 2 5
# 3 1
# 3 4
# 4 3
# 4 6
# 5 2
# 6 4

# To check Eulerian 
# 4 4 F F
# 0 1
# 1 2
# 2 3
# 3 0