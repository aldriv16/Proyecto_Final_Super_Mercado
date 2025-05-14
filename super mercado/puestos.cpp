
#include "Puestos.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

// Constructor
Puesto::Puesto(MYSQL* conn) {
    this->conn = conn;
}

// Método para mostrar los puestos
void Puesto::mostrar() {
    string query = "SELECT * FROM puestos";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        cout << "Lista de puestos:\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " | Puesto: " << row[1] << "\n";
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error al consultar los puestos: " << mysql_error(conn) << endl;
    }
}

// Método para insertar un puesto
void Puesto::insertar() {
    string puesto;
    cout << "Ingrese el nombre del puesto: ";
    getline(cin, puesto);

    string query = "INSERT INTO puestos (puesto) VALUES ('" + puesto + "')";
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Puesto insertado correctamente.\n";
    }
    else {
        cerr << "Error al insertar puesto: " << mysql_error(conn) << endl;
    }
}

// Método para actualizar un puesto
void Puesto::actualizar() {
    int id;
    string puesto;
    cout << "ID del puesto a actualizar: ";
    cin >> id;
    cin.ignore(); // Limpiar el buffer de entrada
    cout << "Nuevo nombre del puesto: ";
    getline(cin, puesto);

    string query = "UPDATE puestos SET puesto = '" + puesto + "' WHERE id_puesto = " + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Puesto actualizado correctamente.\n";
    }
    else {
        cerr << "Error al actualizar puesto: " << mysql_error(conn) << endl;
    }
}

// Método para eliminar un puesto
void Puesto::eliminar() {
    int id;
    cout << "ID del puesto a eliminar: ";
    cin >> id;
    cin.ignore(); // Limpiar el buffer de entrada

    string query = "DELETE FROM puestos WHERE id_puesto = " + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Puesto eliminado correctamente.\n";
    }
    else {
        cerr << "Error al eliminar puesto: " << mysql_error(conn) << endl;
    }
}
