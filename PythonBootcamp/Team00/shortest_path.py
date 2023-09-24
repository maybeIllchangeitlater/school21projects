from typing import Dict, List, Tuple
import json
import optparse


def find_current_node(graph_que: List[Dict], current_node: str) -> Dict:
    while len(graph_que):
        graph = graph_que.pop(0)
        for _, children in graph.items():
            if current_node in children.keys():
                return {current_node: children[current_node]}
            else:
                graph_que.append(children)
    return {}


def parse_args() -> Tuple:
    parser = optparse.OptionParser()
    parser.add_option('-f', '--from', dest='SRC_PAGENAME', help='start link')
    parser.add_option('-t', '--to', dest='DST_PAGENAME', help='target link')
    parser.add_option('-d', '--non-directed', action="store_true", dest='DIRECTED', help='is graph directed')
    parser.add_option('-v', '--visited', action="store_true", dest='VISITED', help='shows path')
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


def print_result_path(result: List, path: bool) -> None:
    if not result:
        print('Path not found')
        return
    if path:
        for v in result[:-1]:
            print(v, end=' -> ')
        print(result[-1])
    else:
        print(len(result))


def main(source: str, destination: str, bidirected: bool, show_path: bool) -> None:
    with open('wiki.json', 'r') as file:
        big_dict = json.load(file)
    que_of_dicts = [big_dict]
    big_dict1 =  find_current_node(que_of_dicts, source) if list(big_dict.keys())[0] != source else big_dict
    result, fluff = find_shortest_path(big_dict1, destination, [])
    if bidirected:
        que_of_dicts = [big_dict]
        big_dict2 = find_current_node(que_of_dicts, destination) if list(big_dict.keys())[0] != destination else big_dict
        result2, fluff = find_shortest_path(big_dict2, source, [])
        result2.reverse()
        print_result_path(result2 if not len(result) or (len(result2) and len(result) > len(result2)) else result, show_path)
        return
    print_result_path(result, show_path)


if __name__ == '__main__':
    options, args = parse_args()
    src = 'https://en.wikipedia.org/wiki/' + str(options.SRC_PAGENAME).replace(' ', '_') if options.SRC_PAGENAME else None
    dst = 'https://en.wikipedia.org/wiki/' + str(options.DST_PAGENAME).replace(' ', '_') if options.DST_PAGENAME else None
    nondirected = True if options.DIRECTED else False
    log = True if options.VISITED else False
    if not src or not dst:
        raise IndexError("from and to arguments are required")
    main(src, dst, nondirected, log)