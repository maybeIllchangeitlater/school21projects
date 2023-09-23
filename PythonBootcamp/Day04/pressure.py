import random


def emit_gel(step: int):

    def valve(self) -> None:
        for val in self.all:
            print(val)
            if val == self.all[-1]:
                self.send()

    def send(self) -> None:
        self.all[-1] *= -1

    methods = {"valve": valve, "send": send}

    def init(self):
        self.all = []
        current_pressure = random.randint(0, step)
        self.all.append(current_pressure)
        while 10 < current_pressure < 90:
            current_pressure = random.randint(0, step)
            if current_pressure <= 20 or current_pressure >= 80:
                self.valve()
            self.all.append(current_pressure)

    liquid_stream = type("gel", (), {"__init__": init, **methods})

    return liquid_stream


if __name__ == '__main__':
    sticky_white_stuff = emit_gel(50)
    thick = sticky_white_stuff()
