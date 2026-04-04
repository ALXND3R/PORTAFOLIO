#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void leerCadena(char *cadena, int longitud, const char *mensaje);
int leerEntero(const char *msg);
/****************************************************************** */

int main()
{
    menu();
}

/****************************************************************** */

int msges()
{
    char entrada[30];
    int op;

    system("CLS");
    printf("--- M  E  N  U ---\n");
    printf("1. Agregar trabajo\n");
    printf("2. Ver siguiente trabajo\n");
    printf("3. Procesar trabajo\n");
    printf("4. Listar cola\n");
    printf("5. Salir\n\n");

    leerCadena(entrada, 13, "ESCOGE: ");
    op = atoi(entrada);

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
                printf("Siguiente: [ID:%d | %s | %s | %d pags]\n",
                       aux.id, aux.usuario, aux.documento, aux.total_pgs);
            else
                printf("Cola vacia.\n");
            system("PAUSE");
            break;

        case 3:
            system("CLS");
            if (q_dequeue(&cola, &aux))
                printf("Procesado: ID %d (%s)\n", aux.id, aux.documento);
            else
                printf("Cola vacia.\n");
            system("PAUSE");
            break;

        case 4:
            system("CLS");
            q_print(&cola);
            system("PAUSE");
            break;

        case 5:
            printf("Saliendo...\n");
            break;

        default:
            printf("Opcion invalida.\n");
            system("PAUSE");
        }

    } while (op != 5);

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

int q_enqueue(Cola *c, Trabajo t) // PONER EL MALLOC
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
/****************************************************************** */

int q_peek(Cola *c, Trabajo *t)
{
    if (q_is_empty(c))
    {
        return 0;
    }

    *t = c->frente->trabajo;
    return 1;
}
/****************************************************************** */

void q_print(Cola *c)
{
    if (q_is_empty(c))
    {
        printf("Cola vacia\n");
        return;
    }

    Nodo *actual = c->frente;

    while (actual != NULL)
    {
        Trabajo t = actual->trabajo;
        printf("ID: %d | Usuario: %s | Doc: %s | Pags: %d\n",
               t.id, t.usuario, t.documento, t.total_pgs);
        actual = actual->sig;
    }
}
/****************************************************************** */

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
    leerCadena(nuevo.documento, 30, "Documento: ");

    nuevo.total_pgs = leerEntero("Total paginas: ");
    nuevo.restante_pgs = nuevo.total_pgs;
    nuevo.copias = 1;

    nuevo.Prioridad = NORMAL;
    nuevo.Estado = EN_COLA;

    if (q_enqueue(cola, nuevo))
    {
        printf("Trabajo agregado con ID %d\n", nuevo.id);
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
            printf("La entrada no puede estar vacia.\n");
        }

    } while (strlen(buffer) == 0);
}
/*************************************************************************** */
int leerEntero(const char *msg)
{
    char buffer[20];
    int valor;

    while (1)
    {
        leerCadena(buffer, sizeof(buffer), msg);
        valor = atoi(buffer);

        if (valor > 0)
        {
            return valor;
        }

        printf("Entrada invalida\n");
    }
}