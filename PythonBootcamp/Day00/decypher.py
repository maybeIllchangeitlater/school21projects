import sys


def decipher(input_str: list[str]):
    answer = ""
    for s in input_str[1:]:
        answer += s[0]
    print(answer)


def main():
    input_strings = sys.argv
    decipher(input_strings)


if __name__ == "__main__":
    main()
