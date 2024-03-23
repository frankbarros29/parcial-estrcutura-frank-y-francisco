#include <iostream>

using namespace std;

struct Cliente {
    string nombre;
    int numeroCuenta;
    int tipoCuenta; 
    Cliente* siguiente;
};

struct FilaEspera {
    Cliente* primero;
    Cliente* ultimo;
};
FilaEspera filaPre = {NULL, NULL};
FilaEspera filaTra = {NULL, NULL};

void registroCliente() {
    Cliente* nuevoCliente = (Cliente*)malloc(sizeof(Cliente));
    cout << endl<<"ingrese el nombre del cliente: ";
    cin >> nuevoCliente->nombre;
    cout << "ingrese el numero de cuenta del cliente: ";
    cin >> nuevoCliente->numeroCuenta;
    do {
        cout << "Ingrese el tipo de cuenta del cliente (1: Preferencial, 2: Tradicional): ";
        cin >> nuevoCliente->tipoCuenta;
    } while (nuevoCliente->tipoCuenta != 1 && nuevoCliente->tipoCuenta != 2);

    
    if (nuevoCliente->tipoCuenta == 1) {
        if (filaPre.primero == NULL) {
            filaPre.primero = nuevoCliente;
        } else {
            filaPre.ultimo->siguiente = nuevoCliente;
        }
        filaPre.ultimo = nuevoCliente;
    } else {
        if (filaTra.primero == NULL) {
            filaTra.primero = nuevoCliente;
        } else {
            filaTra.ultimo->siguiente = nuevoCliente;
        }
        filaTra.ultimo = nuevoCliente;
    }
    nuevoCliente->siguiente = NULL;

    if (filaTra.primero != NULL && filaPre.primero != NULL) {
        int tradicional = 0;
        int preferencial = 0;
        Cliente* temp = filaTra.primero;
        while (temp != NULL) {
            tradicional++;
            temp = temp->siguiente;
        }
        temp = filaPre.primero;
        while (temp != NULL) {
            preferencial++;
            temp = temp->siguiente;
        }

        if (tradicional >= 5 && preferencial <= 2) {
           
            Cliente* clienteTransferido = filaTra.primero->siguiente->siguiente;
            filaTra.primero->siguiente->siguiente = filaTra.primero->siguiente->siguiente->siguiente;
            clienteTransferido->siguiente = NULL;

            
            if (filaPre.primero == NULL) {
                filaPre.primero = clienteTransferido;
            } else {
                filaPre.ultimo->siguiente = clienteTransferido;
            }
            filaPre.ultimo = clienteTransferido;
        }
    }
}


void mostrarFila(Cliente* primero) {
    if (primero == NULL) {
        cout << "La fila esta vacia." << endl;
        return;
    }
    Cliente* actual = primero;
    int turno = 1;
    while (actual != NULL) {
        cout << "turno " << turno++ << ": ";
        cout << "nombre: " << actual->nombre << ", ";
        cout << "numero de la cuenta: " << actual->numeroCuenta << endl;
        actual = actual->siguiente;
    }
}

int main() {
    int opcion;
    do {
        cout <<endl <<"Menu:"<<endl;
        cout << "1. registrar cliente"<<endl;
        cout << "2. mostrar fila preferencial"<<endl;
        cout << "3. mostrar fila tradicional"<<endl;
        cout << "4. salir"<<endl;
        cout << "seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registroCliente();
                break;
            case 2:
                cout << endl<<"fila preferencial: "<<endl;
                mostrarFila(filaPre.primero);
                break;
            case 3:
                cout << endl<<"fila tradicional: "<<endl;
                mostrarFila(filaTra.primero);
                break;
            case 4:
                cout << "saliendo..."<<endl;
                break;
            default:
                cout << "opcion incorrecta. Intente de nuevo."<<endl;
        }
    } while (opcion != 4);

    
    Cliente* actual = filaPre.primero;
    while (actual != NULL) {
        Cliente* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    actual = filaTra.primero;
    while (actual != NULL) {
        Cliente* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }

    return 0;
}
