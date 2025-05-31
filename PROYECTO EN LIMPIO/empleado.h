#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include "ConexionBD.h"

using namespace std;

class Empleado {
private:
    string nombres, apellidos, direccion, telefono, DPI, fecha_nacimiento;
    int id_puesto;
    bool genero;

public:
    Empleado() {}

    // Constructor completo con fecha_nacimiento
    Empleado(string nom, string ape, string dir, string tel, string dpi, string fecha_nac, int puesto, bool gen) {
        nombres = nom;
        apellidos = ape;
        direccion = dir;
        telefono = tel;
        DPI = dpi;
        fecha_nacimiento = fecha_nac;
        id_puesto = puesto;
        genero = gen;
    }

    // Constructor antiguo (retrocompatibilidad, no usará fecha_nacimiento)
    Empleado(string nom, string ape, string dir, string tel, string dpi, int puesto, bool gen) {
        nombres = nom;
        apellidos = ape;
        direccion = dir;
        telefono = tel;
        DPI = dpi;
        id_puesto = puesto;
        genero = gen;
        fecha_nacimiento = "2000-01-01"; // valor por defecto válido
    }

    void crear() {
        ConexionBD cn;
        cn.abrir_conexion();

        string insert = "INSERT INTO empleados(nombres, apellidos, direccion, telefono, DPI, genero, fecha_nacimiento, id_puesto, fecha_inicio_labores, fecha_ingreso) VALUES ('" +
            nombres + "', '" + apellidos + "', '" + direccion + "', '" + telefono + "', '" + DPI + "', " + to_string(genero) + ", '" +
            fecha_nacimiento + "', " + to_string(id_puesto) + ", NOW(), NOW());";

        int estado = mysql_query(cn.gecConector(), insert.c_str());

        if (!estado)
            cout << "Empleado agregado correctamente.\n";
        else
            cout << "Error al agregar empleado: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        mysql_query(cn.gecConector(), "SELECT * FROM empleados;");
        resultado = mysql_store_result(cn.gecConector());

        cout << "\n------ EMPLEADOS ------\n";
        while ((fila = mysql_fetch_row(resultado))) {
            cout << "ID: " << fila[0] << " | " << fila[1] << " " << fila[2] << " | Puesto ID: " << fila[9] << endl;
        }

        cn.cerrar_conexion();
    }

    void actualizar(int id_empleado) {
        ConexionBD cn;
        cn.abrir_conexion();

        string update = "UPDATE empleados SET nombres = '" + nombres + "', apellidos = '" + apellidos + "', direccion = '" + direccion +
            "', telefono = '" + telefono + "', DPI = '" + DPI + "', genero = " + to_string(genero) +
            ", fecha_nacimiento = '" + fecha_nacimiento + "', id_puesto = " + to_string(id_puesto) +
            " WHERE id_empleado = " + to_string(id_empleado) + ";";

        int estado = mysql_query(cn.gecConector(), update.c_str());

        if (!estado)
            cout << "Empleado actualizado correctamente.\n";
        else
            cout << "Error al actualizar empleado: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void eliminar(int id_empleado) {
        ConexionBD cn;
        cn.abrir_conexion();

        string eliminar = "DELETE FROM empleados WHERE id_empleado = " + to_string(id_empleado) + ";";
        int estado = mysql_query(cn.gecConector(), eliminar.c_str());

        if (!estado)
            cout << "Empleado eliminado correctamente.\n";
        else
            cout << "Error al eliminar empleado: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }
};
