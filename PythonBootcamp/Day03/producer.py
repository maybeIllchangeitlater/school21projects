import redis
import json
import random
import logging


def connect_to_redis() -> redis.client.Redis:
    return redis.Redis(host='localhost', port=6379, db=0)


def generate_account_number() -> str:
    return str(random.randint(10 ** 9, 10 ** 10 - 1))


def generate_json_message() -> str:
    from_account = generate_account_number()
    to_account = generate_account_number()
    amount = random.randint(-100000, 100000)

    message = {
        "metadata": {
            "from": from_account,
            "to": to_account
        },
        "amount": amount
    }

    return json.dumps(message)


def main():
    logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
    r = connect_to_redis()
    for _ in range(10):
        message = generate_json_message()
        logging.info(f"Produced: {message}")
        r.lpush('transactions', message)


if __name__ == "__main__":
    main()

# python3 -m http.server
# redis-server --daemonize yes

# print(f"Type of 'r': {type(r)}") for typings
