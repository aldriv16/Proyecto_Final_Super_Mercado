#include "Ventas_detalle.h"
#include <iostream>

using namespace std;

Ventas_detalle::Ventas_detalle(MYSQL* conn) {
    this->conn = conn;
}

// esta parte es para mostrar el detalle por venta 
void Ventas_detalle::mostrarPorVenta(int id_venta) {
    string query = "SELECT * FROM ventas_detalle WHERE id_venta = " + to_string(id_venta);
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        cout << "Detalles de la venta " << id_venta << ":\n";
        while ((row = mysql_fetch_row(res))) {
            // Ajusta los índices según tu tabla
            cout << "ID Detalle: " << row[0]
                << " | ID Venta: " << row[1]
                << " | ID Producto: " << row[2]
                << " | Cantidad: " << row[3]
                << " | Precio: " << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void Ventas_detalle::insertar(int id_venta) {
    long int id_ventadetalle;
    srand(static_cast<unsigned int>(time(nullptr)));
    id_ventadetalle = 2800 + rand() % 3000;

    int cantidad;
    int id_producto;
    double precio_unitario = 0.0;

    cout << "Cantidad: "; cin >> cantidad;
    cout << "ID Producto: "; cin >> id_producto; cin.ignore();

    // Buscar el precio del producto en la tabla productos
    string query_precio = "SELECT precio FROM productos WHERE id_producto = " + to_string(id_producto);
    if (mysql_query(conn, query_precio.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row && row[0]) {
            precio_unitario = atof(row[0]);
            cout << "Precio unitario encontrado: " << precio_unitario << endl;
        }
        else {
            cerr << "No se encontró el producto con ese ID.\n";
            mysql_free_result(res);
            return;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error al consultar el precio: " << mysql_error(conn) << endl;
        return;
    }

   
    string query = "INSERT INTO ventas_detalle (cantidad, id_producto, id_venta, precio_unitario, idventa_detalle) VALUES (" +
        to_string(cantidad) + ", " + to_string(id_producto) + ", " + to_string(id_venta) + ", " +
        to_string(precio_unitario) + ", " + to_string(id_ventadetalle) + ")";

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Detalle de venta insertado correctamente.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}


void Ventas_detalle::mostrar() {
    string query = "SELECT id_ventas_detalle, cantidad, id_producto, id_venta, precio_unitario FROM ventas_detalle";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID Detalle: " << row[0]
                << " | Cantidad: " << row[1]
                << " | ID Producto: " << row[2]
                << " | ID Venta: " << row[3]
                << " | Precio Unitario: " << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void Ventas_detalle::actualizar() {
    long long id_ventas_detalle;
    string cantidad;
    int id_producto, id_venta;
    double precio_unitario;

    cout << "ID del detalle a actualizar: "; cin >> id_ventas_detalle; cin.ignore();
    cout << "Nueva cantidad: "; getline(cin, cantidad);
    cout << "Nuevo ID Producto: "; cin >> id_producto; cin.ignore();
    cout << "Nuevo ID Venta: "; cin >> id_venta; cin.ignore();
    cout << "Nuevo precio unitario: "; cin >> precio_unitario; cin.ignore();

    string query = "UPDATE ventas_detalle SET cantidad = '" + cantidad +
        "', id_producto = " + to_string(id_producto) +
        ", id_venta = " + to_string(id_venta) +
        ", precio_unitario = " + to_string(precio_unitario) +
        " WHERE id_ventas_detalle = " + to_string(id_ventas_detalle);

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Detalle de venta actualizado.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void Ventas_detalle::eliminar() {
    long long id_ventas_detalle;
    cout << "ID del detalle a eliminar: ";
    cin >> id_ventas_detalle;
    cin.ignore();

    string query = "DELETE FROM ventas_detalle WHERE id_ventas_detalle = " + to_string(id_ventas_detalle);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Detalle de venta eliminado.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}
