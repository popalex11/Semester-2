from Metro.Metro import *


def test_1_0_add_remove():
    graph = Graph()

    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n\nEdges:"
    assert graph.get_m() == 0
    assert graph.get_n() == 0

    graph.add_vertex(1)
    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n1 \nEdges:"
    assert graph.get_n() == 1
    assert graph.get_m() == 0

    try:
        graph.add_vertex(1)
        assert False
    except ValueError:
        assert True

    graph.add_vertex(2)
    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n1 2 \nEdges:"
    assert graph.get_n() == 2
    assert graph.get_m() == 0

    graph.add_edge(1, 2)
    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n1 2 \nEdges:\n1 2"
    assert graph.get_n() == 2
    assert graph.get_m() == 1
    assert graph.is_edge(1, 2) is True
    assert graph.is_edge(2, 1) is False

    graph.remove_vertex(2)
    assert graph.get_n() == 1
    assert graph.get_m() == 0
    try:
        assert graph.is_edge(1, 2) is False
        assert False
    except ValueError:
        assert True
    try:
        assert graph.is_edge(2, 1) is False
        assert False
    except ValueError:
        assert True

    graph.add_vertex(3)
    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    graph.add_edge(1, 3)
    graph.add_edge(3, 1)
    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n1 3 \nEdges:\n1 3\n3 1"
    assert graph.is_edge(1, 3) is True
    assert graph.is_edge(3, 1) is True

    graph.remove_edge(1, 3)
    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n1 3 \nEdges:\n3 1"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is True

    graph.remove_edge(3, 1)
    assert str(graph) == "Directed: True\nWeighted: False\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    try:
        graph.remove_edge(3, 1)
        assert False
    except ValueError:
        assert True


def test_1_1_add_remove():
    graph = Graph(True, True)

    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n\nEdges:"
    assert graph.get_m() == 0
    assert graph.get_n() == 0

    graph.add_vertex(1)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 \nEdges:"
    assert graph.get_n() == 1
    assert graph.get_m() == 0

    try:
        graph.add_vertex(1)
        assert False
    except ValueError:
        assert True

    graph.add_vertex(2)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 2 \nEdges:"
    assert graph.get_n() == 2
    assert graph.get_m() == 0

    graph.add_edge(1, 2)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 2 \nEdges:\n1 2 1"
    assert graph.get_n() == 2
    assert graph.get_m() == 1
    assert graph.is_edge(1, 2) is True
    assert graph.is_edge(2, 1) is False

    graph.set_weight(1, 2, 3)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 2 \nEdges:\n1 2 3"
    try:
        graph.set_weight(2, 1, 2)
        assert False
    except ValueError:
        assert True

    graph.remove_vertex(2)
    assert graph.get_n() == 1
    assert graph.get_m() == 0
    try:
        assert graph.is_edge(1, 2) is False
        assert False
    except ValueError:
        assert True
    try:
        assert graph.is_edge(2, 1) is False
        assert False
    except ValueError:
        assert True

    graph.add_vertex(3)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    graph.add_edge(1, 3)
    graph.add_edge(3, 1)
    graph.set_weight(1, 3, 7)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 3 \nEdges:\n1 3 7\n3 1 1"
    assert graph.is_edge(1, 3) is True
    assert graph.is_edge(3, 1) is True

    graph.remove_edge(1, 3)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 3 \nEdges:\n3 1 1"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is True

    graph.remove_edge(3, 1)
    assert str(graph) == "Directed: True\nWeighted: True\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    try:
        graph.remove_edge(3, 1)
        assert False
    except ValueError:
        assert True


def test_0_0_add_remove():
    graph = Graph(False, False)

    assert str(graph) == "Directed: False\nWeighted: False\nVertices:\n\nEdges:"
    assert graph.get_m() == 0
    assert graph.get_n() == 0

    graph.add_vertex(1)
    assert str(graph) == "Directed: False\nWeighted: False\nVertices:\n1 \nEdges:"
    assert graph.get_n() == 1
    assert graph.get_m() == 0

    try:
        graph.add_vertex(1)
        assert False
    except ValueError:
        assert True

    graph.add_vertex(2)
    assert str(graph) == "Directed: False\nWeighted: False\nVertices:\n1 2 \nEdges:"
    assert graph.get_n() == 2
    assert graph.get_m() == 0

    graph.add_edge(1, 2)
    assert str(graph) == "Directed: False\nWeighted: False\nVertices:\n1 2 \nEdges:\n1 2"
    assert graph.get_n() == 2
    assert graph.get_m() == 1
    assert graph.is_edge(1, 2) is True
    assert graph.is_edge(2, 1) is True

    graph.remove_vertex(2)
    assert graph.get_n() == 1
    assert graph.get_m() == 0
    try:
        assert graph.is_edge(1, 2) is False
        assert False
    except ValueError:
        assert True
    try:
        assert graph.is_edge(2, 1) is False
        assert False
    except ValueError:
        assert True

    graph.add_vertex(3)
    assert str(graph) == "Directed: False\nWeighted: False\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    graph.add_edge(1, 3)
    try:
        graph.add_edge(3, 1)
        assert False
    except ValueError:
        assert True

    assert str(graph) == "Directed: False\nWeighted: False\nVertices:\n1 3 \nEdges:\n1 3"
    assert graph.is_edge(1, 3) is True
    assert graph.is_edge(3, 1) is True

    graph.remove_edge(1, 3)
    assert str(graph) == "Directed: False\nWeighted: False\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    try:
        graph.remove_edge(3, 1)
        assert False
    except ValueError:
        assert True


def test_0_1_add_remove():
    graph = Graph(False, True)

    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n\nEdges:"
    assert graph.get_m() == 0
    assert graph.get_n() == 0

    graph.add_vertex(1)
    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n1 \nEdges:"
    assert graph.get_n() == 1
    assert graph.get_m() == 0

    try:
        graph.add_vertex(1)
        assert False
    except ValueError:
        assert True

    graph.add_vertex(2)
    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n1 2 \nEdges:"
    assert graph.get_n() == 2
    assert graph.get_m() == 0

    graph.add_edge(1, 2)
    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n1 2 \nEdges:\n1 2 1"
    assert graph.get_n() == 2
    assert graph.get_m() == 1
    assert graph.is_edge(1, 2) is True
    assert graph.is_edge(2, 1) is True

    graph.set_weight(1, 2, 7)
    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n1 2 \nEdges:\n1 2 7"

    try:
        graph.set_weight(3, 1, 6)
        assert False
    except ValueError:
        assert True

    graph.remove_vertex(2)
    assert graph.get_n() == 1
    assert graph.get_m() == 0
    try:
        assert graph.is_edge(1, 2) is False
        assert False
    except ValueError:
        assert True
    try:
        assert graph.is_edge(2, 1) is False
        assert False
    except ValueError:
        assert True

    graph.add_vertex(3)
    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    graph.add_edge(1, 3)
    try:
        graph.add_edge(3, 1)
        assert False
    except ValueError:
        assert True

    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n1 3 \nEdges:\n1 3 1"
    assert graph.is_edge(1, 3) is True
    assert graph.is_edge(3, 1) is True

    graph.remove_edge(1, 3)
    assert str(graph) == "Directed: False\nWeighted: True\nVertices:\n1 3 \nEdges:"
    assert graph.is_edge(1, 3) is False
    assert graph.is_edge(3, 1) is False

    try:
        graph.remove_edge(3, 1)
        assert False
    except ValueError:
        assert True


def test_1_0_iterator():
    graph = Graph(True, False)
    graph.add_vertex(1)
    graph.add_vertex(2)
    graph.add_vertex(3)
    graph.add_vertex(4)
    graph.add_vertex(0)
    graph.add_edge(0, 1)
    graph.add_edge(1, 0)
    graph.add_edge(1, 2)
    graph.add_edge(1, 3)
    graph.add_edge(0, 4)
    graph.add_edge(2, 4)
    it = graph.iter_vertex(0)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    it = graph.iter_vertex(1)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    graph.add_edge(4, 0)
    it = graph.iter_vertex(4)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    it = graph.iter_vertex(2)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    it = graph.iter_vertex(3)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert nodes == [0, 1, 2, 4]


def test_0_0_iterator():
    graph = Graph(False, False)
    graph.add_vertex(1)
    graph.add_vertex(2)
    graph.add_vertex(3)
    graph.add_vertex(4)
    graph.add_vertex(0)
    graph.add_edge(0, 1)
    graph.add_edge(1, 2)
    graph.add_edge(1, 3)
    graph.add_edge(0, 4)
    graph.add_edge(2, 4)

    it = graph.iter_vertex(0)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    it = graph.iter_vertex(1)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    it = graph.iter_vertex(4)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    it = graph.iter_vertex(2)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert len(nodes) == 0

    it = graph.iter_vertex(3)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert nodes == []

    graph.remove_edge(2, 1)
    graph.remove_edge(0, 4)

    it = graph.iter_vertex(3)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert nodes == [2, 4]

    it = graph.iter_vertex(4)
    nodes = [0, 1, 2, 4, 3]
    while it.valid():
        nodes.remove(it.get_current())
        it.next()
    assert nodes == [0, 1, 3]


def test_graph():
    test_1_0_add_remove()
    test_1_1_add_remove()
    test_0_0_add_remove()
    test_0_1_add_remove()
    test_1_0_iterator()
    test_0_0_iterator()


def test_metro1():
    metro = Metro.read_metro("Tests/A3Test1.txt")
    assert str(metro) == ("Directed: True\nWeighted: True\n"
                          "Vertices:\n('M1', 's1') ('M1', 's2') ('M1', 's3') ('M1', 's4') ('M1', 's5') "
                          "('M1', 's6') ('M1', 's13') ('M1', 's12') ('M1', 's10') \nEdges:"
                          "\n('M1', 's1') ('M1', 's2') 2\n('M1', 's2') ('M1', 's3') 2\n"
                          "('M1', 's3') ('M1', 's4') 3\n('M1', 's4') ('M1', 's5') 2\n('M1', 's5') ('M1', 's6') 3"
                          "\n('M1', 's6') ('M1', 's13') 5\n('M1', 's13') ('M1', 's12') 2\n"
                          "('M1', 's12') ('M1', 's10') 4\n('M1', 's10') ('M1', 's4') 10")

    d = metro.bellman_ford(('M1', 's1'))
    assert d == {'s1': 0, 's2': 2, 's3': 4, 's4': 7, 's5': 9, 's6': 12, 's13': 17, 's12': 19, 's10': 23}

    d = metro.bellman_ford(('M1', "s4"))
    assert d == {'s1': math.inf, 's2': math.inf, 's3': math.inf, 's4': 0, 's5': 2, 's6': 5, 's13': 10, 's12': 12,
                 's10': 16}


def test_metro2():
    metro = Metro.read_metro("Tests/A3Test2.txt")
    assert str(metro) == ("Directed: True\nWeighted: True\nVertices:\n('M1', 's1') ('M1', 's2') ('M1', 's3') "
                          "('M1', 's4') ('M1', 's5') ('M1', 's6') ('M1', 's13') ('M1', 's12') ('M1', 's10') "
                          "('M2', 's8') ('M2', 's5') ('M2', 's9') ('M2', 's10') ('M2', 's11') ('M3', 's3') "
                          "('M3', 's4') ('M3', 's5') ('M3', 's6') ('M3', 's7') ('M3', 's14') \nEdges:\n"
                          "('M1', 's1') ('M1', 's2') 2\n('M1', 's2') ('M1', 's3') 2\n('M1', 's3') ('M1', 's4') 3\n"
                          "('M1', 's3') ('M3', 's3') 3\n('M1', 's4') ('M1', 's5') 2\n('M1', 's4') ('M3', 's4') 3\n"
                          "('M1', 's5') ('M1', 's6') 3\n('M1', 's5') ('M2', 's5') 3\n('M1', 's5') ('M3', 's5') 3\n"
                          "('M1', 's6') ('M1', 's13') 5\n('M1', 's6') ('M3', 's6') 3\n('M1', 's13') ('M1', 's12') 2\n"
                          "('M1', 's12') ('M1', 's10') 4\n('M1', 's10') ('M1', 's4') 10\n"
                          "('M1', 's10') ('M2', 's10') 3\n('M2', 's8') ('M2', 's5') 7\n('M2', 's5') ('M2', 's9') 4\n"
                          "('M2', 's5') ('M1', 's5') 3\n('M2', 's5') ('M3', 's5') 3\n('M2', 's9') ('M2', 's10') 3\n"
                          "('M2', 's10') ('M2', 's11') 4\n('M2', 's10') ('M1', 's10') 3\n('M3', 's3') ('M3', 's4') 3\n"
                          "('M3', 's3') ('M1', 's3') 3\n('M3', 's4') ('M3', 's5') 2\n('M3', 's4') ('M1', 's4') 3\n"
                          "('M3', 's5') ('M3', 's6') 3\n('M3', 's5') ('M1', 's5') 3\n('M3', 's5') ('M2', 's5') 3\n"
                          "('M3', 's6') ('M3', 's7') 5\n('M3', 's6') ('M1', 's6') 3\n('M3', 's7') ('M3', 's14') 7")
    d = metro.bellman_ford(('M1', 's1'))
    assert d == {'s1': 0, 's2': 2, 's3': 4, 's4': 7, 's5': 9, 's6': 12, 's13': 17, 's12': 19, 's10': 19, 's8': math.inf,
                 's9': 16, 's11': 23, 's7': 20, 's14': 27}

    d = metro.bellman_ford(('M2', 's8'))
    assert d == {'s1': math.inf, 's2': math.inf, 's3': math.inf, 's4': 27, 's5': 7, 's6': 13, 's13': 18, 's12': 20,
                 's10': 14, 's8': 0, 's9': 11, 's11': 18, 's7': 18, 's14': 25}


def test_metro():
    test_metro1()
    test_metro2()


if __name__ == '__main__':
    test_graph()
    test_metro()
