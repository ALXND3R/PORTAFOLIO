class Vehicle:
    def __init__(self, plates):
        self._plates = plates

    def get_type(self):
        raise NotImplementedError


class Car(Vehicle):
    def get_type(self):
        return "Car"


class Motorcycle(Vehicle):
    def get_type(self):
        return "Motorcycle"
