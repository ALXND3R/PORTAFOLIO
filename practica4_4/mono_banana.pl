% Problema del mono y la banana

puede_tomar(estado(_, _, _, _, tiene)) :-
    write('El mono ya tiene la banana.'),
    nl.

puede_tomar(Estado) :-
    mover(Estado, Accion, NuevoEstado),
    write(Accion),
    nl,
    puede_tomar(NuevoEstado).

mover(
    estado(_, en_puerta, Caja, en_suelo, no_tiene),
    caminar(en_puerta, centro),
    estado(_, centro, Caja, en_suelo, no_tiene)
).

mover(
    estado(_, centro, en_ventana, en_suelo, no_tiene),
    caminar(centro, en_ventana),
    estado(_, en_ventana, en_ventana, en_suelo, no_tiene)
).

mover(
    estado(_, en_ventana, en_ventana, en_suelo, no_tiene),
    empujar_caja(en_ventana, centro),
    estado(_, centro, centro, en_suelo, no_tiene)
).

mover(
    estado(_, centro, centro, en_suelo, no_tiene),
    subir_caja,
    estado(_, centro, centro, en_caja, no_tiene)
).

mover(
    estado(_, centro, centro, en_caja, no_tiene),
    tomar_banana,
    estado(_, centro, centro, en_caja, tiene)
).