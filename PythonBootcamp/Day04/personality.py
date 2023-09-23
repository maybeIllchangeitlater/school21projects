import random


def turret_generator():
    personality_traits = ['neuroticism', 'openness', 'conscientiousness', 'extroversion', 'agreeableness']

    def shoot(self) -> None:
        print('Shooting')

    def search(self) -> None:
        print('Searching')

    def talk(self) -> None:
        print('Talking')

    methods = {"shoot": shoot, "search": search, "talk": talk}

    def init(self):
        total = 100
        self.traits = {}
        for trait in personality_traits:
            if trait == personality_traits[-1]:
                self.traits[trait] = total
            else:
                self.traits[trait] = random.randint(0, total)
                total -= self.traits[trait]

    turret = type("Turret", (), {"__init__": init, **methods})

    return turret


if __name__ == '__main__':
    t = turret_generator()
    new_fren = t()
    new_fren.search()
    new_fren.talk()
    new_fren.shoot()
    print(new_fren.traits)