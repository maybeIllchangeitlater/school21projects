import argparse
import json
import logging
from typing import List

from producer import connect_to_redis


def process_message(message, bad_guys: List[str]) -> str:
    data = json.loads(message)
    from_account = data['metadata']['from']
    to_account = data['metadata']['to']
    amount = data['amount']

    if str(to_account) in bad_guys and amount >= 0:
        data['metadata']['from'], data['metadata']['to'] = to_account, from_account

    return json.dumps(data)


def parse_args() -> List[str]:
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', '--bad_guys', required=True)
    args = parser.parse_args()

    return args.bad_guys.split(',')


def main():
    bad_guys = parse_args()
    r = connect_to_redis()
    logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
    while True:
        message = r.rpop('transactions')
        if message is None:
            break
        logging.info(f"Produced: {process_message(message, bad_guys)}")


if __name__ == "__main__":
    main()
