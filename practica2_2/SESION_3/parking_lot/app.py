from flask import Flask, render_template, request, redirect
from models.parking_lot import ParkingLot
from models.spot import ParkingSpot
from models.vehicle import Car, Motorcycle
from models.rates import HourlyRate

app = Flask(__name__)

spots = [ParkingSpot(f"A{i}", "Car") for i in range(5)]
spots += [ParkingSpot(f"M{i}", "Motorcycle") for i in range(5)]

lot = ParkingLot(spots, HourlyRate())


@app.route("/")
def dashboard():
    free, occ = lot.status()
    tickets = lot.active_tickets()
    return render_template("dashboard.html", free=free, occ=occ, tickets=tickets)


@app.route("/entry", methods=["GET", "POST"])
def entry():
    if request.method == "POST":
        plates = request.form["plates"]
        vtype = request.form["type"]

        if vtype == "Car":
            v = Car(plates)
        elif vtype == "Motorcycle":
            v = Motorcycle(plates)
        else:
            return redirect("/")
        lot.enter(v)

        return redirect("/")

    return render_template("entry.html")


@app.route("/exit", methods=["GET", "POST"])
def exit_vehicle():
    if request.method == "POST":
        try:
            tid = int(request.form["ticket"])
            hours = int(request.form["hours"])
        except:
            return redirect("/")
        
        cost = lot.exit(tid, hours)
        return render_template("exit.html", cost=cost)

    return render_template("exit.html")


if __name__ == "__main__":
    app.run(debug=True)
