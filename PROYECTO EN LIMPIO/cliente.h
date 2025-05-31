#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include "ConexionBD.h"

using namespace std;

class Cliente {
private:
    string nombres, apellidos, nit, correo, telefono;
    bool genero;
public:
    Cliente() {}

    Cliente(string nom, string ape, string n, bool g, string tel, string cor) {
        nombres = nom;
        apellidos = ape;
        nit = n;
        genero = g;
        telefono = tel;
        correo = cor;
    }

    void crear() {
        ConexionBD cn;
        cn.abrir_conexion();

        string insert = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso) VALUES ('" +
            nombres + "', '" + apellidos + "', '" + nit + "', " + to_string(genero) + ", '" + telefono + "', '" + correo + "', NOW());";

        int estado = mysql_query(cn.gecConector(), insert.c_str());

        if (!estado)
            cout << "Cliente registrado correctamente.\n";
        else
            cout << "Error al registrar cliente: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        mysql_query(cn.gecConector(), "SELECT * FROM clientes;");
        resultado = mysql_store_result(cn.gecConector());

        cout << "\n------ CLIENTES ------\n";
        while ((fila = mysql_fetch_row(resultado))) {
            cout << "ID: " << fila[0] << " | " << fila[1] << " " << fila[2] << " | NIT: " << fila[3] << endl;
        }

        cn.cerrar_conexion();
    }

    void actualizar(int id_cliente) {
        ConexionBD cn;
        cn.abrir_conexion();

        string update = "UPDATE clientes SET nombres = '" + nombres + "', apellidos = '" + apellidos + "', nit = '" + nit +
            "', genero = " + to_string(genero) + ", telefono = '" + telefono + "', correo_electronico = '" + correo +
            "' WHERE id_cliente = " + to_string(id_cliente) + ";";

        int estado = mysql_query(cn.gecConector(), update.c_str());

        if (!estado)
            cout << "Cliente actualizado correctamente.\n";
        else
            cout << "Error al actualizar cliente: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void eliminar(int id_cliente) {
        ConexionBD cn;
        cn.abrir_conexion();

        string eliminar = "DELETE FROM clientes WHERE id_cliente = " + to_string(id_cliente) + ";";
        int estado = mysql_query(cn.gecConector(), eliminar.c_str());

        if (!estado)
            cout << "Cliente eliminado correctamente.\n";
        else
            cout << "Error al eliminar cliente: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }
};
