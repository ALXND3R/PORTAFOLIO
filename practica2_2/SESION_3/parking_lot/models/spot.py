class ParkingSpot:
    def __init__(self, spot_id, allowed_type):
        self._id = spot_id
        self._allowed_type = allowed_type
        self._occupied = False

    def is_free(self):
        return not self._occupied

    def can_fit(self, vehicle):
        return vehicle.get_type() == self._allowed_type

    def occupy(self):
        self._occupied = True

    def free(self):
        self._occupied = False

    def get_id(self):
        return self._id