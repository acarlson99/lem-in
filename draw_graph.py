#!/usr/bin/env python3
import argparse
import contextlib
import sys
from time import time

try:
    with contextlib.redirect_stdout(None):
        import matplotlib.pyplot as plt
        import networkx as nx
        from networkx.algorithms.flow import (boykov_kolmogorov, dinitz,
                                              edmonds_karp, max_flow_min_cost,
                                              preflow_push,
                                              shortest_augmenting_path)
except ModuleNotFoundError:
    print("""Ensure that the required modules are installed:
        *networkx
        *matplotlib""")
    exit(1)

ANTS_ERR = 1
ROOM_ERR = 2
CONN_ERR = 3
MOVE_ERR = 4
READ_ERR = 5
col_path = ['green', 'red', 'orange', 'magenta', 'cyan', 'brown', 'blue', 'black',
            '#f08c00', '#308bc0', '#f9c030', '#23f012', '#497663', '#ec5952', '#db8fb0',
            '#afc58c', '#08ea07', '#3e60f3', '#9d5d80', '#701488', '#a78923', '#d461f8',
            '#0628c4', '#2f8bdc', '#1abf73', '#04edc1', '#dffe5d', '#fbfbad', '#b26258',
            '#d2881e', '#95d6ae', 'grey']


class Lemon:
    def __init__(self, name=None, G=None, draw_grey=None, debug=None, pos=None):
        if name is None:
            self.name = "Graph"
        else:
            self.name = name
        if G is None:
            self.G = nx.Graph(name=self.name)
        else:
            self.G = G
        if draw_grey is None:
            self.draw_grey = False
        else:
            self.draw_grey = draw_grey
        if debug is None:
            self.debug = 0
        else:
            self.debug = debug
        if pos is None:
            self.pos = "spring"
        else:
            self.pos = pos
        self.connections = []
        self.nodes = []
        self.start = None
        self.end = None
        self.num_ants = 0
        self.max_moves = None
        self.max_flow = None
        self.ants = {}
        self.antmoves = []
        self.paths = []
        self.nodes_colors = []
        self.edges_colors = []

    def add_room(self, line, start_end):
        if self.debug >= 3:
            print("add_room")
        if line is None or len(line) == 0:
            print_err(CONN_ERR)
        self.nodes.append(line)
        n = line.split(' ')
        if start_end == -1 and 'red' not in self.nodes_colors:
            self.G.add_node(n[0], weight=2)
            self.end = n[0]
            self.nodes_colors.append('red')
        elif start_end == 1 and 'green' not in self.nodes_colors:
            self.G.add_node(n[0], weight=2)
            self.start = n[0]
            self.nodes_colors.append('green')
        else:
            self.G.add_node(n[0], weight=1)
            self.nodes_colors.append('grey')

    def add_edge(self, line):
        if self.debug >= 3:
            print("add_edge")
        if line is None or len(line) == 0:
            print_err(CONN_ERR)
        self.connections.append(line)
        n = line.split('-')
        self.G.add_edge(n[0], n[1], capacity=1, weight=1)
        self.edges_colors.append("grey")

    def draw_graph_nodes(self, G, paths, pos, col_path, draw_grey):
        n = 0
        flag = False
        for node in G.nodes:
            if node == paths[0][0]:
                nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                    node_color=col_path[0], node_size=20)
            elif node == paths[0][1]:
                nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                    node_color=col_path[1], node_size=20)
            for i in range(1, len(paths)):
                if node in paths[i]:
                    nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                        node_color=col_path[i+1], node_size=20)
                    flag = False
                    break
                else:
                    flag = True
            if flag and draw_grey:
                nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                    node_color=col_path[-1],
                                    node_size=2, alpha=0.1)
            flag = False
            n += 1
            if n == len(G.nodes):
                break
        # print("num_nodes: " + str(len(G.nodes)) + " n: " + str(n))

    def draw_graph_edges(self, G, paths, pos, col_path, draw_grey):
        e = 0
        flag = False
        for edge in G.edges:
            for i in range(1, len(paths)):
                if (
                        (edge[0] in paths[i] and edge[1] in paths[i])
                        or (edge[0] in paths[0] and edge[1] in paths[i])
                        or (edge[0] in paths[i] and edge[1] in paths[0])
                ):
                    nx.draw_networkx_edges(G, pos, edgelist=[edge],
                                        edge_color=col_path[i+1])
                    flag = False
                    break
                else:
                    flag = True
            if flag and draw_grey:
                nx.draw_networkx_edges(G, pos, edgelist=[edge],
                                    edge_color=col_path[-1], alpha=0.1)
            flag = False
            e += 1
            if e == len(G.edges):
                break
        # print("num_edges: " + str(len(G.edges)) + " e: " + str(e))

    def add_ant(self, line):
        if self.debug == 3:
            print("add_ant")
        if line is None or len(line) == 0:
            print_err(ANTS_ERR)
        for move in line.split(" "):
            a = move.split("-")
            if a[0] not in self.ants:
                self.ants[a[0]] = [a[1]]
            else:
                self.ants[a[0]].append(a[1])

    def read_input(self, argfile):
        if argfile is None:
            print_err(READ_ERR)
        start_end = 0
        lines = [line.rstrip("\n") for line in argfile]
        num_lines = len(lines)
        if self.debug >= 2:
            print("num_lines: " + str(num_lines))
        n = 0
        for line in lines:
            if line == "":
                if self.debug >= 2:
                    print("pass")
                pass
            elif n == 0 and line.isdigit():
                self.num_ants = int(line)
                if self.debug >= 2:
                    print("num_ants: " + str(self.num_ants))
            elif line[0] == '#':
                if line == "##start":
                    start_end = 1
                elif line == "##end":
                    start_end = -1
                else:
                    start_end = 0
            elif line.count(" ") == 2:
                self.add_room(line, start_end)
            elif "L" not in line and "-" in line:
                self.add_edge(line)
            elif "L" in line and "-" in line:
                self.antmoves.append(line)
                self.add_ant(line)
            n += 1
        tmp = []
        if (len(self.antmoves) > 0):
            for move in self.antmoves[0].split(" "):
                tmp.append(move.split("-")[0])
        self.paths.append([self.start, self.end])
        for ant in tmp:
            self.paths.append(self.ants[ant][:-1])
        if self.debug >= 2:
            print("paths: " + str(len(self.paths)))
            print("antmoves: " + str(len(self.antmoves)))
            print("lines: " + str(len(lines)))
            print("ants: " + str(self.ants))
            print("num_edges: " + str(len(self.G.edges)) +
                  " ecolors: " + str(len(self.edges_colors)))
            print("num_nodes: " + str(len(self.G.nodes)) +
                  " ncolors: " + str(len(self.nodes_colors)))

    def get_flow(self):
        try:
            R = nx.algorithms.flow.edmonds_karp(
                self.G,
                self.start,
                self.end,
            )
            flow_val = nx.maximum_flow_value(self.G, self.start, self.end)
            if self.debug >= 2:
                print(f"max_flow: {flow_val}")
                print(flow_val == R.graph['flow_value'])
        except nx.exception.NetworkXError:
            print("self.G.nodes() is None")

    def draw_graph(self):
        if self.debug >= 2:
            print(nx.info(self.G))
        if self.pos == "spring":
            pos = nx.spring_layout(self.G)
        elif self.pos == "circular":
            pos = nx.circular_layout(self.G)
        elif self.pos == "kamada":
            pos = nx.kamada_kawai_layout(self.G)
        elif self.pos == "random":
            pos = nx.random_layout(self.G)
        elif self.pos == "shell":
            pos = nx.shell_layout(self.G)
        elif self.pos == "spectral":
            pos = nx.spectral_layout(self.G)
        else:
            pos = nx.spring_layout(self.G)
        if self.debug >= 1:
            print("Drawing graph nodes...")
        self.draw_graph_nodes(self.G, self.paths, pos, col_path, self.draw_grey)
        if self.debug >= 1:
            print("Drawing graph edges...")
        self.draw_graph_edges(self.G, self.paths, pos, col_path, self.draw_grey)
        # nx.draw_networkx_labels(self.G, pos)
        plt.axis('off')
        if self.debug >= 1:
            print("Displaying graph")
        plt.show()

    def test_max_flow(self):
        params = (self.G, self.start, self.end)
        t = time()
        max_flow, max_flowD = nx.maximum_flow(*params)
        max_flow_t = time() - t
        t = time()
        max_flow_value = nx.maximum_flow_value(*params)
        max_flow_value_t = time() - t
        t = time()
        mf_ekG = edmonds_karp(*params)
        mf_ek_t = time() - t
        mf_ek = mf_ekG.graph['flow_value']
        t = time()
        mf_sapG = shortest_augmenting_path(*params)
        mf_sap_t = time() - t
        mf_sap = mf_sapG.graph['flow_value']
        t = time()
        mf_pfpG = preflow_push(*params)
        mf_pfp_t = time() - t
        mf_pfp = mf_pfpG.graph['flow_value']
        t = time()
        mf_dG = dinitz(*params)
        mf_d_t = time() - t
        mf_d = mf_dG.graph['flow_value']
        t = time()
        mf_bkG = boykov_kolmogorov(*params)
        mf_bk_t = time() - t
        mf_bk = mf_bkG.graph['flow_value']
        t = time()
        mf_mcD = max_flow_min_cost(*params)
        mf_mc_t = time() - t
        mf_mc = nx.cost_of_flow(self.G, mf_mcD)
        print(
            f"""stats: start:{self.start}, end:{self.end}, moves:{self.max_moves}, ants:{self.num_ants}
            {'maximum_flow':24s}:{max_flow}, elapsed:{max_flow_t}
            {'maximum_flow_value':24s}:{max_flow_value}, elapsed:{max_flow_value_t}
            {'edmonds_karp':24s}:{mf_ek}, elapsed:{mf_ek_t}
            {'shortest_augmenting_path':24s}:{mf_sap}, elapsed:{mf_sap_t}
            {'preflow_push':24s}:{mf_pfp}, elapsed:{mf_pfp_t}
            {'dinitz':24s}:{mf_d}, elapsed:{mf_d_t}
            {'boykov_kolmogorov':24s}:{mf_bk}, elapsed:{mf_bk_t}
            {'max_flow_min_cost':24s}:{mf_mc}, elapsed:{mf_mc_t}
            """
        )


def print_err(code):
    if code == ANTS_ERR:
        print("draw_graph.py: Error: Ant error")
    elif code == ROOM_ERR:
        print("draw_graph.py: Error: Room error")
    elif code == CONN_ERR:
        print("draw_graph.py: Error: Connection error")
    elif code == MOVE_ERR:
        print("draw_graph.py: Error: Move error")
    elif code == READ_ERR:
        print("draw_graph.py: Error: File not found")
    sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description="Visualize the output of a lem-in binary using GraphViz and NetworkX")
    layout = parser.add_mutually_exclusive_group()
    layout.add_argument("-c", "--circular", help="Use the circular graph layout", action="store_true")
    layout.add_argument("-k", "--kamada", help="Use the Kamada-Kawai force-directed graph layout", action="store_true")
    layout.add_argument("-r", "--random", help="Use the random graph layout", action="store_true")
    layout.add_argument("-l", "--shell", help="Use the shell graph layout", action="store_true")
    layout.add_argument("-e", "--spectral", help="Use the spectral force-directed graph graph layout", action="store_true")
    layout.add_argument("-p", "--spring", help="Use the spring force-directed graph layout", action="store_true")
    parser.add_argument("-f", "--file", type=str, help="Redirected stdout contents from a lem-in binary (defaults to stdin)", default="stdin")
    parser.add_argument("-a", "--draw-all", help="Draw unused nodes and edges", action="store_true")
    parser.add_argument("-n", "--no-draw", help="Do not draw anything", action="store_true")
    parser.add_argument("-d", "--debug", help="Increase debug output level", action="count")
    args = parser.parse_args()
    if args.spectral:
        layoutold = "spectral"
    elif args.kamada:
        layoutold = "kamada"
    elif args.spring:
        layoutold = "spring"
    elif args.circular:
        layoutold = "circular"
    elif args.shell:
        layoutold = "shell"
    elif args.random:
        layoutold = "random"
    else:
        layoutold = "spring"
    loops = Lemon(name=args.file, debug=args.debug, draw_grey=args.draw_all, pos=layoutold)
    if args.file != "stdin":
        if args.debug is not None and args.debug >= 3:
            print("reading from file")
        try:
            f = open(loops.name)
            loops.read_input(f)
            f.close()
            loops.get_flow()
            if not args.no_draw:
                loops.draw_graph()
        except FileNotFoundError:
            print_err(READ_ERR)
    else:
        if args.debug is not None and args.debug >= 3:
            print("reading from stdin")
        try:
            loops.read_input(sys.stdin)
            if not args.no_draw():
                loops.draw_graph()
        except FileNotFoundError:
            print_err(READ_ERR)
    loops.test_max_flow()
    # nx.write_gml(loops.G, './greph.gml')


if __name__ == '__main__':
    main()
