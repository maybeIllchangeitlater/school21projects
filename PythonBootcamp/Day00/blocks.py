import sys


def read_input(n: int):
    target = "00000"
    for i in range(0, n):
        line = input()
        if len(line) == 32 and line[:5] == target and line[5] != '0':
            print(line)


def main():
    n = int(sys.argv[1])
    read_input(n)


if __name__ == "__main__":
    main()
