class RatePolicy:
    def calculate(self, hours, vehicle):
        raise NotImplementedError


class HourlyRate(RatePolicy):
    def calculate(self, hours, vehicle):
        if vehicle.get_type() == "Car":
            return hours * 20
        else:
            return hours * 10


class FlatRate(RatePolicy):
    def calculate(self, hours, vehicle):
        return 50