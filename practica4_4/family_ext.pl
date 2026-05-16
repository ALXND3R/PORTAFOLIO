% Relaciones familiares extendidas

female(pam).
female(liz).
female(pat).
female(ann).

male(jim).
male(bob).
male(tom).
male(pete).

parent(pam, bob).
parent(tom, bob).
parent(tom, liz).
parent(bob, ann).
parent(bob, pat).
parent(pat, jim).
parent(pete, jim).

mother(X, Y) :-
    parent(X, Y),
    female(X).

father(X, Y) :-
    parent(X, Y),
    male(X).

brother(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    male(X),
    X \== Y.

grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

grandmother(X, Y) :-
    mother(X, Z),
    parent(Z, Y).

grandfather(X, Y) :-
    father(X, Z),
    parent(Z, Y).

wife(X, Y) :-
    parent(X, Z),
    parent(Y, Z),
    female(X),
    male(Y).

uncle(X, Y) :-
    brother(X, Z),
    parent(Z, Y).