import enum


def sayHello1():
    print("Hello from python 1")


def sayHello2():
    print("Hello from python 2")


def sayHello3():
    print("Hello from python 3")


class Handedness(enum.Enum):
    right = 1
    left = 2


class Person:
    name = ""
    age = 0
    hand = Handedness.right

    def __init__(self):
        pass

if __name__ == "__main__":
    sayHello1()
    sayHello2()
    sayHello3()
