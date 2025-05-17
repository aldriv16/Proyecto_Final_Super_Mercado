
#include <iostream>
#include "conexionBD.h"
#include "Clientes.h"
#include "Puestos.h"
#include "Marcas.h"
#include "Empleados.h"
#include "Ventas.h"
#include "Ventas_detalle.h"

using namespace std;

// Menús individuales por entidad
void menuClientes(MYSQL* conn) {
    Cliente cliente(conn);
    int opcion;
    do {
        cout << "\n--- MENU CLIENTES ---\n";
        cout << "1. Mostrar\n";
        cout << "2. Insertar\n";
        cout << "3. Actualizar\n";
        cout << "4. Eliminar\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: cliente.mostrar(); break;
        case 2: cliente.insertar(); break;
        case 3: cliente.actualizar(); break;
        case 4: cliente.eliminar(); break;
        case 0: break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 0);
}

void menuPuestos(MYSQL* conn) {
    Puesto puesto(conn);
    int opcion;
    do {
        cout << "\n--- MENU PUESTOS ---\n";
        cout << "1. Mostrar\n";
        cout << "2. Insertar\n";
        cout << "3. Actualizar\n";
        cout << "4. Eliminar\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: puesto.mostrar(); break;
        case 2: puesto.insertar(); break;
        case 3: puesto.actualizar(); break;
        case 4: puesto.eliminar(); break;
        case 0: break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 0);
}

void menuMarcas(MYSQL* conn) {
    Marca marca(conn);
    int opcion;
    do {
        cout << "\n--- MENU MARCAS ---\n";
        cout << "1. Mostrar\n";
        cout << "2. Insertar\n";
        cout << "3. Actualizar\n";
        cout << "4. Eliminar\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: marca.mostrar(); break;
        case 2: marca.insertar(); break;
        case 3: marca.actualizar(); break;
        case 4: marca.eliminar(); break;
        case 0: break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 0);
}

void menuEmpleados(MYSQL* conn) {
    Empleado empleado(conn);
    int opcion;
    do {
        cout << "\n--- MENU EMPLEADOS ---\n";
        cout << "1. Mostrar\n";
        cout << "2. Insertar\n";
        cout << "3. Actualizar\n";
        cout << "4. Eliminar\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: empleado.mostrar(); break;
        case 2: empleado.insertar(); break;
        case 3: empleado.actualizar(); break;
        case 4: empleado.eliminar(); break;
        case 0: break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 0);
}

void menuVentas(MYSQL* conn) {
    Ventas ventas(conn);
    Ventas_detalle detalle(conn);
    int opcion;
    do {
        cout << "\n--- MENU VENTAS (MAESTRO-DETALLE) ---\n";
        cout << "1. Insertar venta y detalles\n";
        cout << "2. Mostrar ventas y detalles\n";
        cout << "3. Actualizar venta\n";
        cout << "4. Eliminar venta\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            ventas.insertar();
            char agregarMas;
            do {
                detalle.insertar();
                cout << "¿Agregar otro detalle a esta venta? (s/n): ";
                cin >> agregarMas; cin.ignore();
            } while (agregarMas == 's' || agregarMas == 'S');
            break;
        }
        case 2:
            ventas.mostrar();
            // Puedes agregar aquí un método para mostrar detalles por venta
            break;
        case 3:
            ventas.actualizar();
            break;
        case 4:
            ventas.eliminar();
            break;
        case 0: break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 0);
}


// Menú principal
int main() {
    conexionBD conexion;
    conexion.abrir_conexion();

    MYSQL* conn = conexion.getconector();
    int opcion;

    do {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Clientes\n";
        cout << "2. Puestos\n";
        cout << "3. Marcas\n";
        cout << "4. Empleados\n";
        cout << "5. ventas y detalle (master)";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: menuClientes(conn); break;
        case 2: menuPuestos(conn); break;
        case 3: menuMarcas(conn); break;
        case 4: menuEmpleados(conn); break;
        case 5: menuVentas(conn); break;
        case 0: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Opcion invalida. Intente de nuevo.\n"; break;
        }

    } while (opcion != 0);

    conexion.cerrar_conexion();
    return 0;
}
