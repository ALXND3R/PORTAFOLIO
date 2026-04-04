#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trabajo
{
    int id;             //  NUMERO AUTOINCREMENTAL
    char usuario[32];   // NOMBRE DEL USUARIO QUE ENVIO LA IMPRESION
    char documento[42]; // TITULO DEL DOCUMENTO
    int total_pgs;      // NUMERO TOTAL DE PAGINAS
    int restante_pgs;   // PAGINAS RESTANTES POR IMPRIMIR
    int copias;         // COPIAS POR IMPRIMIR

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
/********************************************************+ */

typedef struct
{
    Trabajo trabajos[10];
    int frente;
    int final;
    int tamano;
    int sig_id;

} Cola;

/********************************************************+ */
int msges();
void menu();

void agregar_trabajo(Cola *cola);
void q_print(Cola *cola);
int q_dequeue(Cola *cola, Trabajo *nuevo);
int q_peek(Cola *cola, Trabajo *nuevo);
int q_enqueue(Cola *cola, Trabajo nuevo);
int q_is_full(Cola *cola);
int q_is_empty(Cola *cola);
void q_init(Cola *cola);

void leerCadena(char *cadena, int longitud, const char *mensaje);
int leerEntero(const char *msg);

/********************************************************+ */
int main()
{
    menu();
}
/********************************************************+ */
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
            {
                printf("Siguiente: [ID:%d | %s | %s | %d pags]\n", aux.id, aux.usuario, aux.documento, aux.total_pgs);
            }
            else
            {
                printf("Cola vacia.\n");
            }
            system("PAUSE");
            break;

        case 3:
            system("CLS");
            if (q_dequeue(&cola, &aux))
            {
                printf("Procesado: ID %d (%s)\n", aux.id, aux.documento);
            }
            else
            {
                printf("Cola vacia.\n");
            }
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
}
/********************************************************+ */

void q_init(Cola *cola)
{
    cola->frente = 0;
    cola->final = -1;
    cola->tamano = 0;
    cola->sig_id = 1;
}
/********************************************************+ */
int q_is_empty(Cola *cola)
{
    return cola->tamano == 0;
}
/********************************************************+ */
int q_is_full(Cola *cola)
{
    return cola->tamano == 10;
}
/********************************************************+ */
int q_enqueue(Cola *cola, Trabajo trab)
{
    if (q_is_full(cola))
    {
        return 0;
    }

    cola->final = (cola->final + 1) % 10;
    cola->trabajos[cola->final] = trab;
    cola->tamano++;
    return 1;
}
/********************************************************+ */
int q_dequeue(Cola *cola, Trabajo *trab)
{
    if (q_is_empty(cola))
    {
        return 0;
    }

    *trab = cola->trabajos[cola->frente];
    cola->frente = (cola->frente + 1) % 10;
    cola->tamano--;
    return 1;
}
/********************************************************+ */
int q_peek(Cola *cola, Trabajo *trab)
{
    if (q_is_empty(cola))
    {
        return 0;
    }

    *trab = cola->trabajos[cola->frente];
    return 1;
}
/********************************************************+ */
void q_print(Cola *cola)
{
    if (q_is_empty(cola))
    {
        printf("Cola vacia\n");
        return;
    }

    int idx = cola->frente;

    for (int i = 0; i < cola->tamano; i++)
    {
        Trabajo trab = cola->trabajos[idx];
        printf("ID: %d  | Usuario: %s | Doc: %s | Pags: %d\n",
               trab.id, trab.usuario, trab.documento, trab.total_pgs);
        idx = (idx + 1) % 10;
    }
}
/********************************************************+ */
void agregar_trabajo(Cola *cola)
{
    system("CLS");

    if (q_is_full(cola))
    {
        printf("Cola llena\n");
        system("PAUSE");
        return;
    }

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

/********************************************************************* */
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
            printf("La entrada no puede estar vacia\n");
        }

    } while (strlen(buffer) == 0);
}
/********************************************************+ */
int leerEntero(const char *msg)
{
    char buffer[20];
    int valor;

    while (1)
    {
        leerCadena(buffer, sizeof(buffer), msg);
        valor = atoi(buffer);

        if (valor > 0)
            return valor;

        printf("Entrada invalida\n");
    }
}