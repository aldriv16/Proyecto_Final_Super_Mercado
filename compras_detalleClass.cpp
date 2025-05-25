#include "compras_detalleClass.h"
#include <iostream>
using namespace std;

compras_detalleClass::compras_detalleClass(MYSQL* conn) {
    this->conn = conn;
}

int compras_detalleClass::insertar(int id_compra) {
    int id_producto, cantidad;
    double precio_costo_unitario;

    cout << "ID Producto: "; cin >> id_producto; cin.ignore();
    cout << "Cantidad: "; cin >> cantidad; cin.ignore();
    cout << "Precio costo unitario: "; cin >> precio_costo_unitario; cin.ignore();

    string query = "INSERT INTO compras_detalle (id_compra, id_producto, cantidad, precio_costo_unitario) VALUES (" +
        to_string(id_compra) + ", " + to_string(id_producto) + ", " + to_string(cantidad) + ", " +
        to_string(precio_costo_unitario) + ")";

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Detalle de compra insertado correctamente.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;

    int id_compras_detalle = static_cast<int>(mysql_insert_id(conn));
    return id_compras_detalle;
}

void compras_detalleClass::mostrar() {
    string query = "SELECT id_compras_detalle, id_compra, id_producto, cantidad, precio_costo_unitario FROM compras_detalle";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID Detalle: " << row[0]
                << " | ID Compra: " << row[1]
                << " | ID Producto: " << row[2]
                << " | Cantidad: " << row[3]
                << " | Precio Costo Unitario: " << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void compras_detalleClass::mostrarPorCompra(int id_compra) {
    string query = "SELECT id_compras_detalle, id_compra, id_producto, cantidad, precio_costo_unitario FROM compras_detalle WHERE id_compra = " + to_string(id_compra);
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        cout << "Detalles de la compra " << id_compra << ":\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID Detalle: " << row[0]
                << " | ID Producto: " << row[2]
                << " | Cantidad: " << row[3]
                << " | Precio Costo Unitario: " << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void compras_detalleClass::actualizar() {
    int id_compras_detalle, id_producto, cantidad;
    double precio_costo_unitario;

    cout << "ID del detalle a actualizar: "; cin >> id_compras_detalle; cin.ignore();
    cout << "Nuevo ID Producto: "; cin >> id_producto; cin.ignore();
    cout << "Nueva cantidad: "; cin >> cantidad; cin.ignore();
    cout << "Nuevo precio costo unitario: "; cin >> precio_costo_unitario; cin.ignore();

    string query = "UPDATE compras_detalle SET id_producto = " + to_string(id_producto) +
        ", cantidad = " + to_string(cantidad) +
        ", precio_costo_unitario = " + to_string(precio_costo_unitario) +
        " WHERE id_compras_detalle = " + to_string(id_compras_detalle);

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Detalle de compra actualizado.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void compras_detalleClass::eliminar() {
    int id_compras_detalle;
    cout << "ID del detalle a eliminar: ";
    cin >> id_compras_detalle; cin.ignore();

    string query = "DELETE FROM compras_detalle WHERE id_compras_detalle = " + to_string(id_compras_detalle);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Detalle de compra eliminado.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}
