from itertools import zip_longest
from typing import Iterable, List


def fix_wiring(cables: Iterable, sockets: Iterable, plugs: Iterable) -> List[str]:
    return [f"plug {cable} into {socket} using {plug}" if i < len(
        [[item for item in sublist if isinstance(item,
                                                 str) and 'cable' in item and sublist is cables or 'socket' in item and
          sublist is sockets or 'plug' in item and sublist is plugs]
         for sublist in [cables, sockets, plugs]][2]) else f"weld {cable} to {socket} without plug"
            for i, (cable, socket, plug) in enumerate(zip_longest(*[[item for item in sublist if isinstance(item,
                                                                                                            str)
                                                                     and 'cable' in item and sublist is cables or
                                                                     'socket' in item and sublist is sockets or 'plug'
                                                                     in item and sublist is plugs]
                                                                    for sublist in [cables, sockets, plugs]],
                                                                  fillvalue=None)) if
            i < min(len([[item for item in sublist if isinstance(item,
                                                                 str) and 'cable' in item and sublist is cables
                          or 'socket' in item and sublist is sockets or 'plug' in item and sublist is plugs]
                         for sublist in [cables, sockets, plugs]][0]),
                    len([[item for item in sublist if isinstance(item,
                                                                 str) and 'cable' in item and sublist is cables
                          or 'socket' in item and sublist is sockets or 'plug' in item and sublist is plugs]
                         for sublist in [cables, sockets, plugs]][1]))]


def main():
    c = fix_wiring(['cable1', 'xyz', 'cable3', 'cableZ', 'plugkek'], ['socketX', 'socketY', 'socketZ', 'socketBoba'],
                   ['plugP', 'plugLul'])
    for val in c:
        print(val)

if __name__ == '__main__':
    main()