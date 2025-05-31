#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>
#include "ConexionBD.h"

using namespace std;

class Puesto {
private:
    string puesto;

public:
    Puesto() {}

    Puesto(string _puesto) : puesto(_puesto) {}

    void crear() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conectar = cn.gecConector();
        if (conectar) {
            ostringstream query;
            query << "INSERT INTO puestos(puesto) VALUES('" << puesto << "')";
            const char* q = query.str().c_str();
            if (mysql_query(conectar, q) == 0) {
                cout << "Puesto ingresado correctamente." << endl;
            }
            else {
                cerr << "Error al insertar: " << mysql_error(conectar) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conectar = cn.gecConector();
        if (conectar) {
            MYSQL_ROW fila;
            MYSQL_RES* resultado;
            mysql_query(conectar, "SELECT * FROM puestos");
            resultado = mysql_store_result(conectar);
            cout << "ID | Puesto" << endl;
            while ((fila = mysql_fetch_row(resultado))) {
                cout << fila[0] << " | " << fila[1] << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void actualizar(int id_puesto) {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conectar = cn.gecConector();
        if (conectar) {
            ostringstream query;
            query << "UPDATE puestos SET puesto = '" << puesto
                << "' WHERE id_puesto = " << id_puesto;

            const char* q = query.str().c_str();
            if (mysql_query(conectar, q) == 0) {
                cout << "Puesto actualizado correctamente." << endl;
            }
            else {
                cerr << "Error al actualizar: " << mysql_error(conectar) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void eliminar(int id_puesto) {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conectar = cn.gecConector();
        if (conectar) {
            ostringstream query;
            query << "DELETE FROM puestos WHERE id_puesto = " << id_puesto;

            const char* q = query.str().c_str();
            if (mysql_query(conectar, q) == 0) {
                cout << "Puesto eliminado correctamente." << endl;
            }
            else {
                cerr << "Error al eliminar: " << mysql_error(conectar) << endl;
            }
        }
        cn.cerrar_conexion();
    }
};
