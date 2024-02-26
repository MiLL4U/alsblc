from .mymodule import Person as CPerson


class Person:
    def __init__(self, name: str, height: float, weight: float) -> None:
        self.__cperson = CPerson(name, height, weight)

    @property
    def name(self) -> str:
        return self.__cperson.name

    @property
    def height(self) -> float:
        return self.__cperson.height

    @property
    def weight(self) -> float:
        return self.__cperson.weight

    def get_bmi(self) -> float:
        return self.__cperson.get_bmi()

    def set_name(self, name: str) -> None:
        self.__cperson.set_name(name)
