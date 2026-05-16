% Operaciones básicas con listas

list_member(X, [X|_]).

list_member(X, [_|Tail]) :-
    list_member(X, Tail).

list_length([], 0).

list_length([_|Tail], N) :-
    list_length(Tail, N1),
    N is N1 + 1.

list_concat([], L, L).

list_concat([X|L1], L2, [X|L3]) :-
    list_concat(L1, L2, L3).

list_delete(X, [X], []).

list_delete(X, [X|L1], L1).

list_delete(X, [Y|L2], [Y|L1]) :-
    list_delete(X, L2, L1).