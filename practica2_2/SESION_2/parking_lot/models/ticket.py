class Ticket:
    def __init__(self, tid, vehicle, spot):
        self._id = tid
        self._vehicle = vehicle
        self._spot = spot
        self._active = True

    def close(self):
        self._active = False

    def is_active(self):
        return self._active

    def get_id(self):
        return self._id

    def get_spot(self):
        return self._spot

    def get_vehicle(self):
        return self._vehicle