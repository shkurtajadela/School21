import argparse
import json
import redis


def process_message(msg, bad_guys):
    message = json.loads(msg)
    from_account = message['metadata']['from']
    to_account = message['metadata']['to']
    amount = message['amount']

    if bad_guys and to_account in bad_guys and amount > 0:
        message['metadata']['from'] = to_account
        message['metadata']['to'] = from_account

    return json.dumps(message)


def main(bad_guys):
    redis_conn = redis.Redis(host='localhost', port=6379, db=0)
    pubsub = redis_conn.pubsub()
    pubsub.subscribe('transactions')

    for msg in pubsub.listen():
        if msg['type'] == 'message':
            processed_msg = process_message(msg['data'], bad_guys)
            print(processed_msg)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', type=str, help='comma-separated list of bad guys account numbers')

    args, unknown = parser.parse_known_args()

    if unknown:
        print(f"Error: Unexpected arguments: {' '.join(unknown)}")
        exit(1)

    bad_guys = set(args.e.split(',')) if args.e else set()

    main(bad_guys)
