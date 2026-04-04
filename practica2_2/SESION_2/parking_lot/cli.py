import os
from models.vehicle import Car, Motorcycle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import HourlyRate


def clear():
    os.system("cls" if os.name == "nt" else "clear")


def pause():
    input("\nPRESIONA ENTER PARA CONTINUAR...")


def header():
    print("-" * 40)
    print("     SISTEMA DE ESTACIONAMIENTO")
    print("-" * 40)


def dashboard(lot):
    free, occ = lot.status()
    total = free + occ

    print("\nESTADO GENERAL\n")
    print(f"LIBRES   : {free}")
    print(f"OCUPADOS : {occ}")

    barra = "#" * occ + "-" * free
    print(f"\n[{barra}] ({occ}/{total})")


def main():
    spots = [ParkingSpot(f"A{i}", "Car") for i in range(5)]
    spots += [ParkingSpot(f"M{i}", "Motorcycle") for i in range(5)]

    lot = ParkingLot(spots, HourlyRate())

    while True:
        clear()
        header()

        print("\nMENU\n")
        print("1) REGISTRAR ENTRADA")
        print("2) REGISTRAR SALIDA")
        print("3) VER OCUPACION")
        print("4) VER TICKETS ACTIVOS")
        print("5) SALIR")

        op = input("\nOPCION: ").strip()

        if op == "1":
            clear()
            header()

            plates = input("PLACAS: ").strip()
            vtype = input("TIPO (Car/Motorcycle): ").strip()

            if vtype not in ["Car", "Motorcycle"]:
                print("\nERROR: TIPO INVALIDO")
                pause()
                continue

            if vtype == "Car":
                v = Car(plates)
            elif vtype == "Motorcycle":
                v = Motorcycle(plates)
            else:
                print("\nERROR: TIPO INVALIDO")
                pause()
                continue
            t = lot.enter(v)

            if t:
                print(f"\nTICKET #{t.get_id()} ASIGNADO")
                print(f"LUGAR: {t.get_spot().get_id()}")
            else:
                print(
                    "\nLO SENTIMOS YA NO HAY ESPACIOS DISPONIBLES PARA ESTE TIPO DE VEHICULO"
                )

            pause()

        elif op == "2":
            clear()
            header()

            try:
                tid = int(input("TICKET: "))
                hours = int(input("HORAS: "))
            except:
                print("\nERROR: ENTRADA INVALIDA")
                pause()
                continue

            cost = lot.exit(tid, hours)

            if cost is not None:
                print(f"\nTOTAL A PAGAR: ${cost}")
            else:
                print("\nERROR: TICKET INVALIDO O YA CERRADO")

            pause()

        elif op == "3":
            clear()
            header()
            dashboard(lot)
            pause()

        elif op == "4":
            clear()
            header()

            tickets = lot.active_tickets()

            print("\nTICKETS ACTIVOS:\n")
            if tickets:
                for t in tickets:
                    print(f"TICKET #{t}")
            else:
                print("SIN TICKETS ACTIVOS")

            pause()

        elif op == "5":
            clear()
            print("SALIENDO...\n")
            break

        else:
            print("\nERROR: OPCION INVALIDA")
            pause()


if __name__ == "__main__":
    main()
