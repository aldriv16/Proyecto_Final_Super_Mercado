 #include <iostream>
#include "conexionBD.h"
#include "Clientes.h"
#include "Puestos.h"
#include "Marcas.h"
#include "Empleados.h"
#include "Ventas.h"
#include "Ventas_detalle.h"
#include <regex>

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
            // verifador nit
            string nitIngresado;
            cout << "Ingrese el NIT del cliente: ";
            getline(cin, nitIngresado);

            // nit debe ser de 8 dijitos cuidado companeros 
            while (!(nitIngresado == "C/F" || nitIngresado == "c/f" ||
                regex_match(nitIngresado, regex("^\\d{6,8}-\\d{1}$")))) {
                cout << "NIT inválido. Formato esperado: ########-# o C/F\n";
                cout << "Ingrese nuevamente el NIT: ";
                getline(cin, nitIngresado);
            }

            // crea una consulta para ver si existe 
            int id_cliente = -1;
            string queryBuscar = "SELECT id_cliente, CONCAT(nombres, ' ', apellidos) AS nombre_completo "
                "FROM clientes WHERE nit = '" + nitIngresado + "'";
            if (mysql_query(conn, queryBuscar.c_str()) == 0) {
                MYSQL_RES* res = mysql_store_result(conn);
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row) {
                    id_cliente = stoi(row[0]);
                    cout << "Cliente encontrado: " << row[1] << endl;
                }
                else {
                    cout << "Cliente no encontrado. Registre los siguientes datos.\n";
                    string nombres, apellidos, telefono, correo;
                    cout << "Nombres: ";        getline(cin, nombres);
                    cout << "Apellidos: ";      getline(cin, apellidos);
                    cout << "Teléfono: ";       getline(cin, telefono);
                    cout << "Correo electrónico: "; getline(cin, correo);

                    string queryInsertar = "INSERT INTO clientes (nombres, apellidos, nit, telefono, correo_electronico, fecha_ingreso) VALUES ('" +
                        nombres + "', '" + apellidos + "', '" + nitIngresado + "', '" +
                        telefono + "', '" + correo + "', NOW())";
                    if (mysql_query(conn, queryInsertar.c_str()) == 0) {
                        id_cliente = static_cast<int>(mysql_insert_id(conn));
                        cout << "Cliente registrado exitosamente.\n";
                    }
                    else {
                        cerr << "Error al insertar cliente: " << mysql_error(conn) << endl;
                        break;  // Abortamos la inserción de la venta
                    }
                }
                mysql_free_result(res);
            }
            else {
                cerr << "Error al consultar cliente: " << mysql_error(conn) << endl;
                break;
            }

             int id_venta = ventas.insertar();
            // si o funciona borara aqui
            char agregarMas;
            do {
                detalle.insertar(id_venta);
                cout << "¿Agregar otro detalle a esta venta? (s/n): ";
                cin >> agregarMas;
                cin.ignore();
            } while (agregarMas == 's' || agregarMas == 'S');

            break;
        }
        case 2: {
            ventas.mostrar();
            int id_venta_detalle;
            cout << "Ingrese el ID de la venta para ver sus detalles (0 para omitir): ";
            cin >> id_venta_detalle;
            cin.ignore();
            if (id_venta_detalle != 0) {
                detalle.mostrarPorVenta(id_venta_detalle);
            }
            break;
        }
        case 3:
            ventas.actualizar();
            break;
        case 4:
            ventas.eliminar();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
            break;
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
