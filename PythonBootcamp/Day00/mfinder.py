def check_pattern() -> bool:
    lines: list[str] = []
    for i in range(0, 3):
        lines.append(input())
        if len(lines[-1]) > 5:
            print('Error')
            exit(1)
    stars_positions = [(0, 4), (0, 1, 3, 4), (0, 2, 4)]
    for line, positions in zip(lines, stars_positions):
        for i, char in enumerate(line):
            if i in positions and char != '*':
                return False
            if i not in positions and char == '*':
                return False
    return True


def main():
    if check_pattern():
        print('True')
    else:
        print('False')


if __name__ == "__main__":
    main()
