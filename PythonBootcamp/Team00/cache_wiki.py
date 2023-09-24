import json
import logging
import optparse
from typing import Dict, Set, List, Tuple
import requests
from bs4 import BeautifulSoup


def main():
    dict_of_lists = {}
    (options, args) = parse_args()

    visited = set()

    depth = int(options.DEPTH) if options.DEPTH else 3
    start_url =  'https://en.wikipedia.org/wiki/' + str(options.PAGENAME).replace(' ', '_') if options.PAGENAME else 'https://en.wikipedia.org/wiki/Python_(' \
                                                               'programming_language) '

    recursive_crawl(start_url, dict_of_lists, visited, depth)
    logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
    logging.info(f'visited: {dict_of_lists}')
    dump_to_json(dict_of_lists)


def recursive_crawl(url: str, dict_of_dicts: Dict, visited: Set, depth: int):
    if depth <= 0 or len(visited) >= 1000:
        return
    if url not in visited and depth > 1:
        visited.add(url)
        page = grab_page(url)
        list_of_links = make_link_soup(page, url)
    else:
        list_of_links = []
    dict_of_lists = {}
    for link in list_of_links:
        recursive_crawl(link, dict_of_lists, visited, depth - 1)
    dict_of_dicts[url] = dict_of_lists

def parse_args() -> Tuple:
    parser = optparse.OptionParser()
    parser.add_option('-p', '--path', dest='PAGENAME', help='start with specific link')
    parser.add_option('-d', '--depth', dest='DEPTH', help='go to a specific depth')
    (options, args) = parser.parse_args()
    return options, args


def grab_page(url: str = 'https://en.wikipedia.org/wiki/Python_(programming_language)', tries: int = 3, timeout: int = 5) -> requests.Response:
    for i in range(0, tries):
        try:
            return requests.get(url, timeout=timeout)
        except requests.exceptions.RequestException:
            continue
    raise LookupError(f'Failed to fetch {url}')


def unzashquar_link(link: str):
    if ':' in link:
        return None
    link = 'https://en.wikipedia.org' + link
    return link


def make_link_soup(req: requests.Response, headlink: str) -> List[str]:
    soup = BeautifulSoup(req.text, 'lxml')
    link_soup = []
    for link in soup.find(id="bodyContent").find_all('a', href=True):
        if link['href'].startswith('/wiki/'):
            fixed_link = unzashquar_link(link['href'])
            if len(link_soup) > 10:
                return link_soup
            if fixed_link is not None and fixed_link != headlink and fixed_link not in link_soup:
                link_soup.append(fixed_link)
    return link_soup


def dump_to_json(dicts: Dict):
    with open("wiki.json", "w") as outfile:
        json.dump(dicts, outfile, indent=4)


if __name__ == "__main__":
    main()