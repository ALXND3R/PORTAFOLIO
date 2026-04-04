import os
from models.vehicle import Vehicle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import RatePolicy


def clear():
    os.system("cls" if os.name == "nt" else "clear")

def pause():
    input("\nPresiona ENTER para continuar...")


def header():
    print("-" * 40)
    print("     SISTEMA DE ESTACIONAMIENTO")
    print("-" * 40)

def main():
    spots = [ParkingSpot(f"A{i}", "Car") for i in range(5)]
    spots += [ParkingSpot(f"M{i}", "Motorcycle") for i in range(5)]

    lot = ParkingLot(spots, RatePolicy())

    while True:
        clear()
        header()

        print("\n1) Registrar entrada")
        print("2) Registrar salida")
        print("3) Ver ocupación")
        print("4) Ver tickets activos")
        print("5) Salir")

        op = input("\nOPCION: ")

        if op == "1":
            clear()
            header()

            plates = input("PLACAS: ").strip()
            vtype = input("TIPO (Car/Motorcycle): ").strip()

            if vtype not in ["Car", "Motorcycle"]:
                print("\nERROR: TIPO INVALIDO")
                pause()
                continue

            v = Vehicle(plates, vtype)
            t = lot.enter(v)

            if t:
                print(f"\nTICKET #{t.get_id()} asignado")
                print(f"LUGAR: {t.get_spot().get_id()}")
            else:
                print("\nLo sentimos no hay espacios disponibles :(")

            pause()

        elif op == "2":
            clear()
            header()

            try:
                tid = int(input("TICKET: "))
                hours = int(input("HORAS: "))
            except:
                print("\nERROR: ENTRADA INVALIDA...")
                pause()
                continue

            cost = lot.exit(tid, hours)

            if cost is not None:
                print(f"\nTOTAL A PAGAR: ${cost}")
            else:
                print("\nERROR: TICKET INVALIDO O YA CERRADO...")

            pause()

        elif op == "3":
            clear()
            header()

            print("\nESTADO DEL ESTACIONAMIENTO\n")
            free_car, free_moto = lot.status()

            print(f"ESPACIOS LIBRES PARA CARROS: {free_car}")
            print(f"ESPACIOS LIBRES PARA MOTOS: {free_moto}")

            pause()

        elif op == "4":
            clear()
            header()

            tickets = lot.active_tickets()

            print("\nTICKETS ACTIVOS:")
            if tickets:
                for t in tickets:
                    print(f" - TICKET #{t}")
            else:
                print("SIN TICKETS ACTIVOS")

            pause()

        elif op == "5":
            clear()
            print("SALIENDO...\n")
            break

        else:
            print("ERROR: OPCION INVALIDA...")
            pause()


if __name__ == "__main__":
    main()
