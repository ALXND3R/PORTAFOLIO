% Torres de Hanoi

hanoi(1, Origen, Destino, _) :-
    write('Mover disco de '),
    write(Origen),
    write(' a '),
    write(Destino),
    nl.

hanoi(N, Origen, Destino, Auxiliar) :-
    N > 1,
    M is N - 1,
    hanoi(M, Origen, Auxiliar, Destino),
    hanoi(1, Origen, Destino, Auxiliar),
    hanoi(M, Auxiliar, Destino, Origen).
    