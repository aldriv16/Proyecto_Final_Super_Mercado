#include "Clientes.h"
#include <iostream>
#include <mysql.h>
#include <string>


using namespace std;

Cliente::Cliente(MYSQL* conn) {
    this->conn = conn;
}

void Cliente::insertar() {
    string nombres, apellidos, nit, telefono, correo;
    int genero;

    cout << "Ingrese nombres: ";
    getline(cin, nombres);
    cout << "Ingrese apellidos: ";
    getline(cin, apellidos); 
    cout << "Ingrese NIT: ";
    getline(cin, nit);
    cout << "Ingrese genero (0 = F, 1 = M): ";
    cin >> genero;
    cin.ignore();
    cout << "Ingrese telefono: ";
    getline(cin, telefono);
    cout << "Ingrese correo: ";
    getline(cin, correo);


    string query = "INSERT INTO clientes (nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso) "
        "VALUES ('" + nombres + "', '" + apellidos + "', '" + nit + "', " + to_string(genero) + ", '"
        + telefono + "', '" + correo + "', NOW())";

    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Cliente insertado correctamente.\n";
    }
    else {
        cerr << "Error al insertar cliente: " << mysql_error(conn) << endl;
    }
}

void Cliente::mostrar() {
    string query = "SELECT * FROM clientes";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        cout << "Listado de clientes:\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " | Nombre: " << row[1] << " " << row[2]  
                << " | NIT: " << row[3] << " | Teléfono: " << row[5]
                << " | Correo: " << row[6] << "\n";
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error al consultar clientes: " << mysql_error(conn) << endl;
    }
}

void Cliente::actualizar() {
    int id;
    string telefono, correo;
    cout << "ID del cliente a actualizar: ";
    cin >> id;
    cin.ignore();
    cout << "Nuevo teléfono: ";
    getline(cin, telefono);
    cout << "Nuevo correo: ";
    getline(cin, correo);


    string query = "UPDATE clientes SET telefono = '" + telefono + "', correo_electronico = '" + correo + "' WHERE id_cliente = " + to_string(id);

    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Cliente actualizado correctamente.\n";
    }
    else {
        cerr << "Error al actualizar cliente: " << mysql_error(conn) << endl;
    }
}

void Cliente::eliminar() {
    int id;
    cout << "ID del cliente a eliminar: ";
    cin >> id;
    cin.ignore();

    string query = "DELETE FROM clientes WHERE id_cliente = " + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Cliente eliminado correctamente.\n";
    }
    else {
        cerr << "Error al eliminar cliente: " << mysql_error(conn) << endl;
    }
}
