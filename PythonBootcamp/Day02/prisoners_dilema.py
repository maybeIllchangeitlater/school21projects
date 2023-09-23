from collections import Counter



class Player(object):

    def make_decision(self, other: bool) -> bool:
        raise NotImplementedError()


class Cheater(Player):

    def make_decision(self, other: bool) -> bool:
        return False


class Cooperator(Player):

    def make_decision(self, other: bool) -> bool:
        return True


class Copycat(Player):

    def make_decision(self, other: bool) -> bool:
        return other


class Grudger(Player):

    def __init__(self) -> None:
        self.decision = True

    def make_decision(self, other: bool) -> bool:
        if not other:
            self.decision = False
        return self.decision


class Detective(Player):

    def __init__(self) -> None:
        self.decision = True
        self.turncounter = 0
        self.naebali = False

    def make_decision(self, other: bool) -> bool:

        if self.turncounter < 4:
            self.turncounter += 1
            if not other:
                self.naebali = True
            if self.turncounter == 2:
                self.decision = False
            else:
                self.decision = True
        else:
            if self.naebali:
                self.decision = other
            else:
                self.decision = False
        return self.decision


class Cultist(Player):
    def __init__(self, player_to_brainwash: Player) -> None:
        self.decision = False
        self.player_to_brainwash = player_to_brainwash

    def make_decision(self, other: bool) -> bool:
        def brainwashed_make_decision(self, other: bool) -> bool:
            return True
        self.player_to_brainwash.make_decision = brainwashed_make_decision.__get__(self.player_to_brainwash, Player)
        return False
    

class Game(object):

    def __init__(self, matches: int = 10) -> None:
        self.matches = matches
        self.registry = Counter()

    def play(self, player1: Player, player2: Player) -> None:
        pre_decision1 = True
        pre_decision2 = True
        for i in range(0, self.matches):
            p1d = player1.make_decision(pre_decision2)
            p2d = player2.make_decision(pre_decision1)
            if p1d and p2d:
                self.registry[player1.__class__.__name__] += 2
                self.registry[player2.__class__.__name__] += 2
            elif p1d and not p2d:
                self.registry[player1.__class__.__name__] -= 1
                self.registry[player2.__class__.__name__] += 3
            elif not p1d and p2d:
                self.registry[player1.__class__.__name__] += 3
                self.registry[player2.__class__.__name__] -= 1
            elif not p1d and not p2d:
                self.registry[player1.__class__.__name__] += 0
                self.registry[player2.__class__.__name__] += 0
            pre_decision1 = p1d
            pre_decision2 = p2d

    def top3(self) -> None:
        counter = 0
        for val in sorted(self.registry.items(), key=lambda obj: obj[1], reverse=True):
            if counter < 3:
                print(val)
                counter += 1


def main():
    g = Game()
    p1 = Detective()
    p2 = Copycat()
    p4 = Cheater()
    p3 = Cultist(p4)
    p5 = Grudger()
    p6 = Cooperator()
    g.play(p1, p2)
    g.play(p3, p4)
    g.play(p1, p3)
    g.play(p2, p3)
    g.play(p1, p4)
    g.play(p2, p4)
    g.play(p5, p3)
    g.play(p1, p3)
    g.play(p2, p6)
    g.play(p3, p5)
    g.top3()

if __name__ == '__main__':
    main()