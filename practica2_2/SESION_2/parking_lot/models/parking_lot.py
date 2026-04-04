from models.ticket import Ticket


class ParkingLot:
    def __init__(self, spots, rate_policy):
        self._spots = spots
        self._tickets = {}
        self._counter = 1
        self._rate = rate_policy

    def enter(self, vehicle):
        for spot in self._spots:
            if spot.is_free() and spot.can_fit(vehicle):
                spot.occupy()
                ticket = Ticket(self._counter, vehicle, spot)
                self._tickets[self._counter] = ticket
                self._counter += 1
                return ticket
        return None

    def exit(self, tid, hours):
        if tid not in self._tickets:
            return None

        ticket = self._tickets[tid]
        if not ticket.is_active():
            return None

        ticket.close()
        ticket.get_spot().free()

        cost = self._rate.calculate(hours, ticket.get_vehicle())
        return cost

    def status(self):
        free = sum(1 for s in self._spots if s.is_free())
        occupied = len(self._spots) - free
        return free, occupied

    def active_tickets(self):
        return [t.get_id() for t in self._tickets.values() if t.is_active()]
