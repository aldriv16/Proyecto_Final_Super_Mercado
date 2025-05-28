#include "Compras.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

string fecha_ingreso;
string fecha_orden;
int idcompra;
void inicializarFechasCompra() {
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);

    char fechaHora[20];
    char fecha[11];
    // fecha_ingreso: YYYY-MM-DD HH:MM:SS
    strftime(fechaHora, sizeof(fechaHora), "%Y-%m-%d %H:%M:%S", &now);
    fecha_ingreso = fechaHora;
    // fecha_orden: YYYY-MM-DD
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", &now);
    fecha_orden = fecha;
}

Compras::Compras(MYSQL* conn) {
    this->conn = conn;
}

int Compras::insertar() {
    srand(static_cast<unsigned int>(time(nullptr)));
    idcompra = 3800 + rand() % 4000;
    inicializarFechasCompra();
    int id_proveedor, No_orden_compra;
    //solo sirve para mostrar lo que tengo en la base de datos;
   
    string queryProveedores = "SELECT id_proveedore, proveedor FROM proveedores";
    if (mysql_query(conn, queryProveedores.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << "\nProveedores disponibles:\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " - Proveedor: " << row[1] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error al consultar los proveedores: " << mysql_error(conn) << endl;
    }

    cout << "ID Proveedor: "; cin >> id_proveedor; cin.ignore();
    cout << "No. Orden de Compra: "; cin >> No_orden_compra; cin.ignore();

    string query = "INSERT INTO compras (fecha_ingreso, fecha_orden, id_proveedore, No_orden_compra,id_compra) VALUES ('" +
        fecha_ingreso + "', '" + fecha_orden + "', " + to_string(id_proveedor) + ", " + to_string(No_orden_compra) + ", " + to_string(idcompra) + ",)";

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Compra insertada correctamente.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;

    // id_compra es autoincremental, 
    int id_compra = static_cast<int>(mysql_insert_id(conn));
    return id_compra;
}

void Compras::mostrar() {
    string query = "SELECT id_compra, fecha_ingreso, fecha_orden, id_proveedor, No_orden_compra FROM compras";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID Compra: " << row[0]
                << " | Fecha Ingreso: " << row[1]
                << " | Fecha Orden: " << row[2]
                << " | ID Proveedor: " << row[3]
                << " | No. Orden Compra: " << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void Compras::actualizar() {
    int id_compra, id_proveedor, No_orden_compra;
    string nueva_fecha_ingreso, nueva_fecha_orden;

    cout << "ID de la compra a actualizar: "; cin >> id_compra; cin.ignore();
    cout << "Nueva fecha de ingreso (YYYY-MM-DD HH:MM:SS): "; getline(cin, nueva_fecha_ingreso);
    cout << "Nueva fecha de orden (YYYY-MM-DD): "; getline(cin, nueva_fecha_orden);
    cout << "Nuevo ID Proveedor: "; cin >> id_proveedor; cin.ignore();
    cout << "Nuevo No. Orden de Compra: "; cin >> No_orden_compra; cin.ignore();

    string query = "UPDATE compras SET fecha_ingreso = '" + nueva_fecha_ingreso +
        "', fecha_orden = '" + nueva_fecha_orden +
        "', id_proveedor = " + to_string(id_proveedor) +
        ", No_orden_compra = " + to_string(No_orden_compra) +
        " WHERE id_compra = " + to_string(id_compra);

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Compra actualizada.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void Compras::eliminar() {
    int id_compra;
    cout << "ID de la compra a eliminar: ";
    cin >> id_compra;
    cin.ignore();

    string query = "DELETE FROM compras WHERE id_compra = " + to_string(id_compra);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Compra eliminada.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}
