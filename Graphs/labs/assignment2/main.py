from directed_graph import DirectedGraph

def main():
    # Example usage of DirectedGraph class and graph examples
    graph = DirectedGraph()
    print("Initial graph:")
    print(graph)

    print("\nAdding vertices 0, 1, 2, 3")
    for i in range(4):
        graph.add_vertex(i)
    graph.weighted = True
    print(graph)

    print("\nAdding edges: (0, 1), (1, 2), (2, 0), (2, 3)")
    graph.add_edge(0, 1, 3.5)
    graph.add_edge(1, 2, 2.0)
    graph.add_edge(2, 0, 1.2)
    graph.add_edge(2, 3, 4.7)
    print(graph)

    start_vertex = (0,1)
    print("Going through the graph using DFS starting from vertex", start_vertex)
    iterator = graph.iter_vertex(start_vertex)
    iterator.first()
    while iterator.valid():
        print(iterator.get_current())
        iterator.next()


    print("\nRemoving edge (2, 0)")
    graph.remove_edge(2, 0)
    print(graph)

    print("\nRemoving vertex 0")
    graph.remove_vertex(0)
    print(graph)

    print("\nOutbound edges of vertex 2:")
    print(graph.outbound_edges(2))

    print("\nInbound edges of vertex 2:")
    print(graph.inbound_edges(2))

    print("\nCreating random graph with 5 vertices and 8 edges (weighted)")
    graph.create_random(5, 8, [1, 10])
    print(graph)

    print("\nRandomizing weights with range [1, 5]")
    graph.random_weights([1, 5])
    print(graph)

    print("\nSetting weight of edge (1, 2) to 5.5")
    graph.set_weight(1, 2, 5.5)
    print(graph)

    graph.empty_graph()

    # Reading graph from file 'graph_data.txt'
    print("\nReading graph from file 'graph_data.txt'")
    graph.create_from_file("graph_data.txt")
    print(graph)

if __name__ == "__main__":
    main()
