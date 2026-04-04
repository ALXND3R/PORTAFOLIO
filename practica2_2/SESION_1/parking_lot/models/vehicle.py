class Vehicle:
    def __init__(self, plates, vtype):
        self._plates = plates
        self._type = vtype

    def get_type(self):
        return self._type

    def get_plates(self):
        return self._plates
