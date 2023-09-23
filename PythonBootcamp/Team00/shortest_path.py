from pprint import pprint
from typing import Dict, List, Tuple
import json
import optparse


def find_current_node(graph_que: List[Dict], current_node: str) -> Dict:
    while len(graph_que):
        graph = graph_que.pop(0)
        for _, children in graph.items():
            if current_node in children.keys():
                return children[current_node]
            else:
                graph_que.append(children)
    return {}


def parse_args() -> Tuple:
    parser = optparse.OptionParser()
    parser.add_option('-f', '--from', dest='SRC_PAGENAME', help='start link')
    parser.add_option('-t', '--to', dest='DST_PAGENAME', help='target link')
    parser.add_option('-d', '--non-directed', action="store_true", dest='DIRECTED', help='is graph directed')
    (opt, arg) = parser.parse_args()
    return opt, arg


def find_shortest_path(graph: Dict, target_node: str, shortest_path: List, visited: List = None) -> Tuple[List, bool]:
    found = True
    if visited is None:
        visited = []

    for neighbor, children in graph.items():
        if neighbor not in visited:
            if not found:
                visited[-1] = neighbor
            else:
                visited.append(neighbor)
        else:
            continue
        if neighbor == target_node:
            return visited, True
        buff, found = find_shortest_path(children, target_node, shortest_path, visited.copy())
        if len(shortest_path) == 0 or len(buff) < len(shortest_path):
            shortest_path = buff
        if (len(shortest_path) == 0 or (len(visited) + 1) < len(shortest_path)) and target_node in children:
            shortest_path = visited + [target_node]

    return shortest_path, False


def main(source: str, destination: str, bidirected: bool) -> None:
    with open('wiki.json', 'r') as file:
        big_dict = json.load(file)
    que_of_dicts = [big_dict]
    big_dict1 = {source: find_current_node(que_of_dicts, source)} if list(big_dict.keys())[0] != source else big_dict
    result, fluff = find_shortest_path(big_dict1, destination, [])
    if bidirected:
        que_of_dicts = [big_dict]
        big_dict2 = {destination: find_current_node(que_of_dicts, destination)} if big_dict.keys() != destination else big_dict
        result2, fluff = find_shortest_path(big_dict2, source, [])
        if not len(result):
            pprint(result2[::-1])
        elif not len(result2):
            pprint(result)
        elif len(result) < len(result2):
            pprint(result)
        else:
            pprint(result2[::-1])
        return
    pprint(result)


if __name__ == '__main__':
    options, args = parse_args()
    src = 'https://en.wikipedia.org/wiki/' + str(options.SRC_PAGENAME) if options.SRC_PAGENAME else None
    dst = 'https://en.wikipedia.org/wiki/' + str(options.DST_PAGENAME) if options.DST_PAGENAME else None
    nondirected = True if options.DIRECTED else False
    if not src or not dst:
        raise IndexError("from and to arguments are required")
    main(src, dst, nondirected)