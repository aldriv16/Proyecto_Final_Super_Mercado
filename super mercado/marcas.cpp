#include "Marcas.h"
#include <iostream>

using namespace std;

Marca::Marca(MYSQL* conn) {
    this->conn = conn;
}

void Marca::insertar() {
    string marca;
    cout << "Ingrese nombre de la marca: ";
    getline(cin, marca);

    string query = "INSERT INTO marcas (marca) VALUES ('" + marca + "')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Marca insertada correctamente.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void Marca::mostrar() {
    string query = "SELECT * FROM marcas";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " | Marca: " << row[1] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void Marca::actualizar() {
    int id;
    string nuevoNombre;
    cout << "ID de la marca: ";
    cin >> id;
    cin.ignore();
    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);

    string query = "UPDATE marcas SET marca = '" + nuevoNombre + "' WHERE id_marca = " + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Marca actualizada.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void Marca::eliminar() {
    int id;
    cout << "ID de la marca a eliminar: ";
    cin >> id;
    cin.ignore();

    string query = "DELETE FROM marcas WHERE id_marca = " + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Marca eliminada.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}
