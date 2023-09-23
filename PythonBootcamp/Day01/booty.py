from typing import List, Dict


def my_decorator(func):
    def wrapper(*args):
        print('SQUEAK')
        return func(*args)

    return wrapper


@my_decorator
def add_ingot(purse: Dict[str, int]) -> Dict[str, int]:
    new_purse = purse.copy()
    new_purse['gold_ingots'] += 1
    return new_purse


@my_decorator
def get_ingot(purse: Dict[str, int]) -> Dict[str, int]:
    new_purse = purse.copy()
    if new_purse['gold_ingots'] != 0:
        new_purse['gold_ingots'] -= 1
    return new_purse


@my_decorator
def empty(purse: Dict[str, int]) -> Dict[str, int]:
    return {}


def split_booty(*args) -> List[Dict[str, int]]:
    all_gold = 0
    gold_purse: List[Dict[str, int]] = []
    result_purse: List[Dict[str, int]] = []
    amount_of_booty = len(args)
    for purse in args:
        if 'gold_ingots' in purse:
            all_gold += purse['gold_ingots']
        purse = empty(purse)
        gold_purse.append(purse)
    max_per_purse = all_gold // amount_of_booty
    need_to_split = all_gold % amount_of_booty
    for dct in gold_purse:
        if need_to_split != 0:
            dct['gold_ingots'] = max_per_purse + 1
            need_to_split -= 1
        else:
            dct['gold_ingots'] = max_per_purse
        result_purse.append(dct)
    return result_purse


def main():
    boba = {'gold_ingots': 5}
    biba = {'gold_ingots': 6}
    aboba = {'apples': 10}
    print(split_booty(boba, biba, aboba))
    for i in range (0, 5):
        boba = add_ingot(boba)
    boba = get_ingot(boba)
    print(boba)


if __name__ == '__main__':
    main()
