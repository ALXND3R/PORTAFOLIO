#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/****************************************************************** */

typedef struct Trabajo
{
    int id;
    char usuario[32];
    char documento[42];
    int total_pgs;
    int restante_pgs;
    int copias;

    enum prioridad
    {
        NORMAL,
        URGENTE
    } Prioridad;

    enum estado
    {
        EN_COLA,
        IMPRIMIENDO,
        COMPLETADO,
        CANCELADO
    } Estado;

} Trabajo;

/****************************************************************** */

typedef struct Nodo
{
    Trabajo trabajo;
    struct Nodo *sig;
} Nodo;

typedef struct
{
    Nodo *frente;
    Nodo *final;
    int tamano;
    int sig_id;
} Cola;

/****************************************************************** */

int msges();
void menu();

void agregar_trabajo(Cola *cola);
void q_print(Cola *cola);
int q_dequeue(Cola *cola, Trabajo *t);
int q_peek(Cola *cola, Trabajo *t);
int q_enqueue(Cola *cola, Trabajo t);
int q_is_empty(Cola *cola);
void q_init(Cola *cola);
void qd_destroy(Cola *cola);

void simular_impresion(Trabajo *t);
void simular_cola_completa(Cola *cola);

void leerCadena(char *cadena, int longitud, const char *mensaje);
int leerEnteroRango(const char *msg, int min, int max);

/****************************************************************** */

int main()
{
    menu();
    return 0;
}

/****************************************************************** */

int msges()
{
    char entrada[30];
    int op;

    system("CLS");
    printf("--- S I S T E M A   D E   I M P R E S I O N ---\n");
    printf("1. Agregar trabajo\n");
    printf("2. Ver siguiente trabajo (Peek)\n");
    printf("3. Procesar siguiente trabajo (Dequeue)\n");
    printf("4. Listar cola\n");
    printf("5. SIMULAR IMPRESION DE TODA LA COLA\n");
    printf("6. Salir\n\n");

    op = leerEnteroRango("ESCOGE: ", 1, 6);
    return op;
}

/****************************************************************** */

void menu()
{
    Cola cola;
    q_init(&cola);

    int op;
    Trabajo aux;

    do
    {
        op = msges();

        switch (op)
        {
        case 1:
            agregar_trabajo(&cola);
            break;

        case 2:
            system("CLS");
            if (q_peek(&cola, &aux))
                printf("Siguiente: [ID:%d | %s | %s | %d pags | %s]\n",
                       aux.id, aux.usuario, aux.documento, aux.total_pgs,
                       aux.Prioridad == URGENTE ? "URGENTE" : "NORMAL");
            else
                printf("Cola vacia.\n");
            system("PAUSE");
            break;

        case 3:
            system("CLS");
            if (q_dequeue(&cola, &aux))
            {
                simular_impresion(&aux);
            }
            else
            {
                printf("Cola vacia. Nada que procesar.\n");
            }
            system("PAUSE");
            break;

        case 4:
            system("CLS");
            q_print(&cola);
            system("PAUSE");
            break;

        case 5:
            simular_cola_completa(&cola);
            system("PAUSE");
            break;

        case 6:
            printf("Saliendo...\n");
            break;
        }

    } while (op != 6);

    qd_destroy(&cola);
}

/****************************************************************** */

void q_init(Cola *c)
{
    c->frente = NULL;
    c->final = NULL;
    c->tamano = 0;
    c->sig_id = 1;
}
/****************************************************************** */
int q_is_empty(Cola *c)
{
    return c->tamano == 0;
}

/****************************************************************** */

int q_enqueue(Cola *c, Trabajo t)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL)
    {
        printf("Error: No hay memoria disponible.\n");
        return 0;
    }

    nuevo->trabajo = t;
    nuevo->sig = NULL;

    if (q_is_empty(c))
    {
        c->frente = nuevo;
        c->final = nuevo;
    }
    else if (t.Prioridad == URGENTE)
    {
        if (c->frente->trabajo.Prioridad == NORMAL)
        {
            nuevo->sig = c->frente;
            c->frente = nuevo;
        }
        else
        {
            Nodo *act = c->frente;
            while (act->sig != NULL && act->sig->trabajo.Prioridad == URGENTE)
            {
                act = act->sig;
            }
            nuevo->sig = act->sig;
            act->sig = nuevo;

            if (nuevo->sig == NULL)
            {
                c->final = nuevo;
            }
        }
    }
    else
    {
        c->final->sig = nuevo;
        c->final = nuevo;
    }

    c->tamano++;
    return 1;
}

/****************************************************************** */

int q_dequeue(Cola *c, Trabajo *t)
{
    if (q_is_empty(c))
    {
        return 0;
    }

    Nodo *temp = c->frente;
    *t = temp->trabajo;
    c->frente = temp->sig;

    if (c->frente == NULL)
    {
        c->final = NULL;
    }

    free(temp);
    c->tamano--;
    return 1;
}
/**************************************************** */
int q_peek(Cola *c, Trabajo *t)
{
    if (q_is_empty(c))
    {
        return 0;
    }

    *t = c->frente->trabajo;
    return 1;
}
/********************************************************************* */
void q_print(Cola *c)
{
    if (q_is_empty(c))
    {
        printf("Cola vacia\n");
        return;
    }

    Nodo *actual = c->frente;
    printf("--- COLA DE IMPRESION ---\n");
    while (actual != NULL)
    {
        Trabajo t = actual->trabajo;
        printf("[ID: %d] | %s | Doc: %s | Pags: %d | [%s]\n",
               t.id, t.usuario, t.documento, t.total_pgs,
               t.Prioridad == URGENTE ? "URGENTE" : "NORMAL");
        actual = actual->sig;
    }
}
/*************************************************************** */
void qd_destroy(Cola *c)
{
    Nodo *actual = c->frente;
    while (actual != NULL)
    {
        Nodo *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    c->frente = NULL;
    c->final = NULL;
    c->tamano = 0;
}

/****************************************************************** */

void agregar_trabajo(Cola *cola)
{
    system("CLS");
    Trabajo nuevo;

    nuevo.id = cola->sig_id++;

    leerCadena(nuevo.usuario, 30, "Usuario: ");
    leerCadena(nuevo.documento, 40, "Documento: ");

    nuevo.total_pgs = leerEnteroRango("Total paginas: ", 1, 10000);
    nuevo.restante_pgs = nuevo.total_pgs;
    nuevo.copias = leerEnteroRango("Numero de copias: ", 1, 100);

    int p = leerEnteroRango("Prioridad (0=Normal, 1=Urgente): ", 0, 1);
    nuevo.Prioridad = (p == 1) ? URGENTE : NORMAL;
    nuevo.Estado = EN_COLA;

    if (q_enqueue(cola, nuevo))
    {
        printf("\nTrabajo agregado con exito! (ID: %d)\n", nuevo.id);
    }

    system("PAUSE");
}

/****************************************************************** */
void leerCadena(char *buffer, int size, const char *msg)
{
    do
    {
        printf("%s", msg);
        if (fgets(buffer, size, stdin) == NULL)
        {
            buffer[0] = '\0';
            return;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0)
        {
            printf("Error: La entrada no puede estar vacia.\n");
        }

    } while (strlen(buffer) == 0);
}

int leerEnteroRango(const char *msg, int min, int max)
{
    char buffer[20];
    char *endptr;
    long valor;

    while (1)
    {
        leerCadena(buffer, sizeof(buffer), msg);
        valor = strtol(buffer, &endptr, 10);

        if (endptr != buffer && *endptr == '\0' && valor >= min && valor <= max)
        {
            return (int)valor;
        }
        printf("Error: Entrada invalida. Ingresa un numero entre %d y %d.\n", min, max);
    }
}

/********************************************************** */

void simular_impresion(Trabajo *t)
{
    printf("\n>>> Trabajo ID %d: EN COLA -> IMPRIMIENDO <<<\n", t->id);
    t->Estado = IMPRIMIENDO;

    printf("Documento: %s | Usuario: %s | [%s]\n",
           t->documento, t->usuario, t->Prioridad == URGENTE ? "URGENTE" : "NORMAL");

    for (int c = 1; c <= t->copias; c++)
    {
        if (t->copias > 1)
        {
            printf("- Copia %d de %d -\n", c, t->copias);
        }

        for (int i = 1; i <= t->total_pgs; i++)
        {
            printf("  Imprimiendo pagina %d de %d...\n", i, t->total_pgs);
            Sleep(400);
            t->restante_pgs--;
        }
    }

    t->Estado = COMPLETADO;
    printf(">>> Trabajo ID %d: IMPRIMIENDO -> COMPLETADO <<<\n\n", t->id);
}

void simular_cola_completa(Cola *cola)
{
    system("CLS");
    if (q_is_empty(cola))
    {
        printf("La cola esta vacia. No hay nada que simular.\n");
        return;
    }

    int trabajos_completados = 0;
    int paginas_impresas = 0;
    Trabajo aux;

    printf("----- INICIANDO SIMULACION DE LA COLA ------\n");

    while (q_dequeue(cola, &aux))
    {
        simular_impresion(&aux);
        trabajos_completados++;
        paginas_impresas += (aux.total_pgs * aux.copias);
        printf("---------------------------------------------------\n");
    }

    printf("\n----- SIMULACION FINALIZADA ------\n");
    printf("Estadisticas de la sesion:\n");
    printf(" - Trabajos completados: %d\n", trabajos_completados);
    printf(" - Total de paginas impresas: %d\n\n", paginas_impresas);
}