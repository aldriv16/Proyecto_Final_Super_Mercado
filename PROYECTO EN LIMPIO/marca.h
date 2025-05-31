#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>   // Para reemplazo de to_string
#include "ConexionBD.h"

using namespace std;

class Marca {
private:
    int id_marca;
    string marca;
public:
    Marca() {}

    Marca(int id, string m) {
        id_marca = id;
        marca = m;
    }

    void setId(int id) { id_marca = id; }
    void setMarca(string m) { marca = m; }

    int getId() { return id_marca; }
    string getMarca() { return marca; }

    // Función auxiliar para int a string
    string intToString(int val) {
        stringstream ss;
        ss << val;
        return ss.str();
    }

    void crear() {
        ConexionBD cn;
        cn.abrir_conexion();

        string insert = "INSERT INTO marcas(marca) VALUES('" + marca + "');";
        const char* query = insert.c_str();
        int estado = mysql_query(cn.gecConector(), query);

        if (!estado)
            cout << "Marca agregada exitosamente." << endl;
        else
            cout << "Error al agregar marca: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        const char* query = "SELECT * FROM marcas;";
        int estado = mysql_query(cn.gecConector(), query);

        if (!estado) {
            resultado = mysql_store_result(cn.gecConector());
            cout << "------ MARCAS ------" << endl;
            while ((fila = mysql_fetch_row(resultado))) {
                cout << "ID: " << fila[0] << " | Marca: " << fila[1] << endl;
            }
        }
        else {
            cout << "Error al leer marcas: " << mysql_error(cn.gecConector()) << endl;
        }

        cn.cerrar_conexion();
    }

    void actualizar() {
        ConexionBD cn;
        cn.abrir_conexion();

        string update = "UPDATE marcas SET marca = '" + marca + "' WHERE id_marca = " + intToString(id_marca) + ";";
        const char* query = update.c_str();
        int estado = mysql_query(cn.gecConector(), query);

        if (!estado)
            cout << "Marca actualizada exitosamente." << endl;
        else
            cout << "Error al actualizar marca: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void eliminar(int id) {
        ConexionBD cn;
        cn.abrir_conexion();

        string del = "DELETE FROM marcas WHERE id_marca = " + intToString(id) + ";";
        const char* query = del.c_str();
        int estado = mysql_query(cn.gecConector(), query);

        if (!estado)
            cout << "Marca eliminada exitosamente." << endl;
        else
            cout << "Error al eliminar marca: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

};
