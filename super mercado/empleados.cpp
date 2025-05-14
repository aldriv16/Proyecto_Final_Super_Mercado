#include "empleados.h"
#include <iostream>

using namespace std;

Empleado::Empleado(MYSQL* conn) {
    this->conn = conn;
}

void Empleado::insertar() {
    string nombres, apellidos, direccion, telefono, dpi, fecha_nacimiento;
    int genero, id_puesto;

    cout << "Nombres: "; getline(cin, nombres);
    cout << "Apellidos: "; getline(cin, apellidos);
    cout << "Dirección: "; getline(cin, direccion);
    cout << "Telefono: "; getline(cin, telefono);
    cout << "DPI: "; getline(cin, dpi);
    cout << "Genero (0 = F, 1 = M): "; cin >> genero; cin.ignore();
    cout << "Fecha de nacimiento (YYYY-MM-DD): "; getline(cin, fecha_nacimiento);
    cout << "ID del puesto: "; cin >> id_puesto; cin.ignore();

    string query = "INSERT INTO empleados (nombres, apellidos, direccion, telefono, DPI, genero, fecha_nacimiento, id_puesto, fecha_inicio_labores, fecha_ingreso) "
        "VALUES ('" + nombres + "', '" + apellidos + "', '" + direccion + "', '" + telefono + "', '" + dpi + "', " + to_string(genero) +
        ", '" + fecha_nacimiento + "', " + to_string(id_puesto) + ", NOW(), NOW())";

    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Empleado insertado correctamente.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void Empleado::mostrar() {
    string query = "SELECT e.id_empleado, e.nombres, e.apellidos, e.telefono, e.DPI, e.genero, e.fecha_nacimiento, p.puesto "
        "FROM empleados e JOIN puestos p ON e.id_puesto = p.id_puesto";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " | Nombre: " << row[1] << " " << row[2]
                << " | Tel: " << row[3] << " | DPI: " << row[4]
                << " | Genero: " << (string(row[5]) == "1" ? "M" : "F")
                << " | Nacimiento: " << row[6]
                << " | Puesto: " << row[7] << endl;
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error: " << mysql_error(conn) << endl;
    }
}

void Empleado::actualizar() {
    int id;
    string telefono, direccion;
    cout << "ID del empleado a actualizar: "; cin >> id; cin.ignore();
    cout << "Nuevo telefono: "; getline(cin, telefono);
    cout << "Nueva direccion: "; getline(cin, direccion);

    string query = "UPDATE empleados SET telefono = '" + telefono + "', direccion = '" + direccion + "' WHERE id_empleado = " + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Empleado actualizado.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void Empleado::eliminar() {
    int id;
    cout << "ID del empleado a eliminar: ";
    cin >> id;
    cin.ignore();

    string query = "DELETE FROM empleados WHERE id_empleado = " + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Empleado eliminado.\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

