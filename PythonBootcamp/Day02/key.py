class Key:
    def __new__(cls) -> object:
        inst = object.__new__(cls)
        return inst

    def __init__(self) -> None:
        self.passphrase = "zax2rulez"

    def __len__(self) -> int:
        return 1337

    def __str__(self) -> str:
        return "GeneralTsoKeycard"

    def __gt__(self, other) -> bool:
        return 9001 > other

    def __getitem__(self, item) -> int:
        return 3


def main() -> None:
    k = Key()
    assert len(k) == 1337
    assert k[404] == 3
    assert k > 9000
    assert k.passphrase == 'zax2rulez'
    assert str(k) == 'GeneralTsoKeycard'
    print('Ok')


if __name__ == '__main__':
    main()