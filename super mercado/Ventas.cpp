#include "Ventas.h"
#include "Ventas.h"
#include <iostream>

using namespace std;

Ventas::Ventas(MYSQL* conn) {
    this->conn = conn;
}

void Ventas::insertar() {
    int id_cliente, id_empleado, No_factura;
    string fecha_factura, serie;

    cout << "Fecha de factura (YYYY-MM-DD): "; getline(cin, fecha_factura);
    cout << "ID Cliente: "; cin >> id_cliente; cin.ignore();
    cout << "ID Empleado: "; cin >> id_empleado; cin.ignore();
    cout << "No. Factura: "; cin >> No_factura; cin.ignore();
    cout << "Serie (1 caracter): "; getline(cin, serie);

    string query = "INSERT INTO ventas (fecha_factura, id_cliente, id_empleado, No_factura, serie) VALUES ('" +
        fecha_factura + "', " + to_string(id_cliente) + ", " + to_string(id_empleado) + ", " +
        to_string(No_factura) + ", '" + serie + "')";

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Venta insertada correctamente.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
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
