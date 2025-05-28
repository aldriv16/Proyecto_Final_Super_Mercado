#include "Ventas.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <regex>

using namespace std;

string fecha_factura;
// unicamente sirve para la fecha, fecha automatica
void inicializarFecha() {
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    char fecha[11];
    sprintf_s(fecha, sizeof(fecha), "%04d-%02d-%02d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday);
    fecha_factura = fecha;
}

Ventas::Ventas(MYSQL* conn) {
    this->conn = conn;
}

int Ventas::insertar() {
    inicializarFecha();
    int id_cliente, id_empleado, No_factura, serie;
    srand(static_cast<unsigned int>(time(nullptr)));
    No_factura = 1800 + rand() % 2000;
    serie = 1 + rand() % 10;


    
   string queryclientes = "SELECT id_cliente, nombres FROM clientes";
if (mysql_query(conn, queryclientes.c_str()) == 0) {
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "\nClientes disponibles:\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "ID: " << row[0] << " - Cliente : " << row[1] << endl;
    }
    mysql_free_result(res);
} else {
    cerr << "Error al consultar los clientes: " << mysql_error(conn) << endl;
}

    cout << "ID Cliente: "; cin >> id_cliente; cin.ignore();
    cout << "";
    string queryempleados= "SELECT id_empleado, nombres FROM empleados";
    if (mysql_query(conn, queryempleados.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << "\nEmpleados disponibles:\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " - Empleados: " << row[1] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error al consultar los empleados: " << mysql_error(conn) << endl;
    };

    cout << "ID Empleado: "; cin >> id_empleado; cin.ignore();
    int Pk_compuesta = stoi(to_string(No_factura) + to_string(id_empleado));
    int id_venta = Pk_compuesta;
    string query = "INSERT INTO ventas (fecha_factura, id_cliente, id_empleado, No_factura, serie, id_venta) VALUES ('" +
        fecha_factura + "', " + to_string(id_cliente) + ", " + to_string(id_empleado) + ", " +
        to_string(No_factura) + ", " + to_string(serie) + ", " + to_string(id_venta) + ")";

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Venta insertada correctamente.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
    return id_venta;
}

void Ventas::mostrar() {
    string query = "SELECT id_venta, fecha_factura, id_cliente, id_empleado, No_factura, serie FROM ventas";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID Venta: " << row[0]
                << " | Fecha: " << row[1]
                << " | ID Cliente: " << row[2]
                << " | ID Empleado: " << row[3]
                << " | No. Factura: " << row[4]
                << " | Serie: " << row[5] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void Ventas::actualizar() {
    int id_venta, id_cliente, id_empleado, No_factura;
    string fecha_factura, serie;

    cout << "ID de la venta a actualizar: "; cin >> id_venta; cin.ignore();
    cout << "Nueva fecha de factura (YYYY-MM-DD): "; getline(cin, fecha_factura);
    cout << "Nuevo ID Cliente: "; cin >> id_cliente; cin.ignore();
    cout << "Nuevo ID Empleado: "; cin >> id_empleado; cin.ignore();
    cout << "Nuevo No. Factura: "; cin >> No_factura; cin.ignore();
    cout << "Nueva serie (1 caracter): "; getline(cin, serie);

    string query = "UPDATE ventas SET fecha_factura = '" + fecha_factura +
        "', id_cliente = " + to_string(id_cliente) +
        ", id_empleado = " + to_string(id_empleado) +
        ", No_factura = " + to_string(No_factura) +
        ", serie = '" + serie +
        "' WHERE id_venta = " + to_string(id_venta);

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Venta actualizada.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void Ventas::eliminar() {
    string queryventas = "SELECT id_venta, No_factura ,id_cliente, fecha_factura FROM ventas";
    if (mysql_query(conn, queryventas.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << "\nVentas realizadas:\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " - no.factura : " << row[1] << " id_cliente "<<row[2]<<"fecha factura " <<row[3]<< endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error al consultar las ventas: " << mysql_error(conn) << endl;
    };
    int id_venta;
    cout << "ID de la venta a eliminar: ";
    cin >> id_venta;
    cin.ignore();

    string query = "DELETE FROM ventas WHERE id_venta = " + to_string(id_venta);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Venta eliminada.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}
