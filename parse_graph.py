import sys
from collections import defaultdict
from io import FileIO
from time import time

import networkx as nx
from networkx.algorithms.flow import (
    boykov_kolmogorov,
    dinitz,
    edmonds_karp,
    max_flow_min_cost,
    preflow_push,
    shortest_augmenting_path,
)


class LemonInput:
    def __init__(self, name: str = None, infile=None, parse_inp: bool = False):
        if name is None:
            if isinstance(infile, str) and infile.index("\n") < 0:
                name = infile
                infile = open(infile)
            elif isinstance(infile, FileIO):
                name = infile.name
            else:
                name = "Graph"
        if infile is None:
            infile = sys.stdin
        self.name = name
        self.infile = infile
        self.G = nx.Graph(name=self.name)
        self.start = None
        self.end = None
        self.max_moves = 0
        self.max_flow = 0
        self.ants = defaultdict(list)
        self.num_ants = 0
        self.parsed = False
        if parse_inp:
            self.parse_input()

    def parse_node_line(ln: str) -> tuple[str, int, int]:
        n, x, y = ln.split(" ")
        return n, int(x), int(y)

    def parse_input(self):
        if self.parsed:
            return
        self.num_ants = int(self.infile.readline().rstrip("\n"))
        cur = self.infile.readline().rstrip("\n")
        while True:
            if cur.count(" ") == 2:
                node = LemonInput.parse_node_line(cur)
                self.G.add_node(node[0], ix=node[1], iy=node[2], color="grey")
            elif cur.count("-") == 1:
                src, snk = cur.split("-")
                self.G.add_edge(src, snk, color="grey", capacity=1)
            elif cur.startswith("#Here is the number of lines required: "):
                self.max_moves = int(cur[39:])
            elif cur.startswith("##"):
                nxt = self.infile.readline().rstrip("\n")
                node = LemonInput.parse_node_line(nxt)
                if cur.endswith("start"):
                    self.G.add_node(node[0], ix=node[1], iy=node[2], color="green")
                    self.start = node[0]
                if cur.endswith("end"):
                    self.G.add_node(node[0], ix=node[1], iy=node[2], color="red")
                    self.end = node[0]
            elif cur == "":
                break
            elif cur[0] == "L" and cur.count("-") > 0 and cur.count(" ") > 0:
                # parse ant moves
                for a in cur.split(" "):
                    i, n = a.split("-")
                    self.ants[int(i)].append(n)
            cur = self.infile.readline().rstrip("\n")
        self.infile.close()
        self.parsed = True

    def max_goof(self):
        t = time()
        mfv = nx.shortest_simple_paths(self.G, self.start, self.end)
        elapsed = time() - t
        pth = next(mfv)
        print(f"elapsed: {elapsed}\n" f"num simple paths: {pth}")

    def goof_troop(self):
        t = time()
        mfv = nx.maximum_flow_value(self.G, self.start, self.end)
        elapsed = time() - t
        print(f"elapsed: {elapsed}" f"num simple paths: {mfv}")

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
        mf_ek = mf_ekG.graph["flow_value"]
        t = time()
        mf_sapG = shortest_augmenting_path(*params)
        mf_sap_t = time() - t
        mf_sap = mf_sapG.graph["flow_value"]
        t = time()
        mf_pfpG = preflow_push(*params)
        mf_pfp_t = time() - t
        mf_pfp = mf_pfpG.graph["flow_value"]
        t = time()
        mf_dG = dinitz(*params)
        mf_d_t = time() - t
        mf_d = mf_dG.graph["flow_value"]
        t = time()
        mf_bkG = boykov_kolmogorov(*params)
        mf_bk_t = time() - t
        mf_bk = mf_bkG.graph["flow_value"]
        t = time()
        mf_mcD = max_flow_min_cost(*params)
        mf_mc_t = time() - t
        mf_mc = nx.cost_of_flow(self.G, mf_mcD)
        print(
            f"""nodes:{len(self.G.nodes)}, edges:{len(self.G.edges)}
            start:{self.start}, end:{self.end}
            moves:{self.max_moves}, ants:{self.num_ants}
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


if __name__ == "__main__":
    lm = LemonInput(name="gen_big", infile=open("test_maps/gen_big"), parse_inp=True)
    lm.parse_input()
    lm.max_goof()
