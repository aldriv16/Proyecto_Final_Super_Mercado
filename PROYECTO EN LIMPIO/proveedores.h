#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>
#include "ConexionBD.h"

using namespace std;

class Proveedor {
private:
    string proveedor, nit, direccion, telefono;

public:
    Proveedor() {}

    Proveedor(string _proveedor, string _nit, string _direccion, string _telefono) :
        proveedor(_proveedor), nit(_nit), direccion(_direccion), telefono(_telefono) {
    }

    void crear() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conectar = cn.gecConector();
        if (conectar) {
            ostringstream query;
            query << "INSERT INTO proveedores(proveedor, nit, direccion, telefono) VALUES('"
                << proveedor << "', '"
                << nit << "', '"
                << direccion << "', '"
                << telefono << "')";

            const char* q = query.str().c_str();
            if (mysql_query(conectar, q) == 0) {
                cout << "Proveedor ingresado correctamente." << endl;
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
            mysql_query(conectar, "SELECT * FROM proveedores");
            resultado = mysql_store_result(conectar);
            cout << "ID | Proveedor | NIT | Dirección | Teléfono" << endl;
            while ((fila = mysql_fetch_row(resultado))) {
                cout << fila[0] << " | " << fila[1] << " | " << fila[2]
                    << " | " << fila[3] << " | " << fila[4] << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void actualizar(int id_proveedore) {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conectar = cn.gecConector();
        if (conectar) {
            ostringstream query;
            query << "UPDATE proveedores SET proveedor = '" << proveedor
                << "', nit = '" << nit
                << "', direccion = '" << direccion
                << "', telefono = '" << telefono
                << "' WHERE id_proveedore = " << id_proveedore;

            const char* q = query.str().c_str();
            if (mysql_query(conectar, q) == 0) {
                cout << "Proveedor actualizado correctamente." << endl;
            }
            else {
                cerr << "Error al actualizar: " << mysql_error(conectar) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void eliminar(int id_proveedore) {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conectar = cn.gecConector();
        if (conectar) {
            ostringstream query;
            query << "DELETE FROM proveedores WHERE id_proveedore = " << id_proveedore;

            const char* q = query.str().c_str();
            if (mysql_query(conectar, q) == 0) {
                cout << "Proveedor eliminado correctamente." << endl;
            }
            else {
                cerr << "Error al eliminar: " << mysql_error(conectar) << endl;
            }
        }
        cn.cerrar_conexion();
    }
};
