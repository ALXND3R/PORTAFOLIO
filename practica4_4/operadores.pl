% Operadores aritméticos en Prolog

calc :-
    X is 100 + 200,
    write('100 + 200 = '),
    write(X),
    nl,

    Y is 400 - 150,
    write('400 - 150 = '),
    write(Y),
    nl,

    Z is 10 * 30,
    write('10 * 30 = '),
    write(Z),
    nl,

    A is 100 / 4,
    write('100 / 4 = '),
    write(A),
    nl,

    B is 100 // 30,
    write('100 // 30 = '),
    write(B),
    nl,

    C is 100 mod 30,
    write('100 mod 30 = '),
    write(C),
    nl.