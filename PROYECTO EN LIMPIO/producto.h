#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>  // para convertir números a string
#include "ConexionBD.h"

using namespace std;

template<typename T>
string toString(const T& value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

class Producto {
private:
    int id_marca, existencia;
    string producto, descripcion, imagen;
    float precio_costo, precio_venta;
public:
    Producto() {}
    Producto(string p, int idm, string d, string img, float pc, float pv, int ex) {
        producto = p;
        id_marca = idm;
        descripcion = d;
        imagen = img;
        precio_costo = pc;
        precio_venta = pv;
        existencia = ex;
    }

    void crear() {
        ConexionBD cn;
        cn.abrir_conexion();

        string insert = "INSERT INTO productos(producto, id_marca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES ('" +
            producto + "', " + toString(id_marca) + ", '" + descripcion + "', '" + imagen + "', " +
            toString(precio_costo) + ", " + toString(precio_venta) + ", " + toString(existencia) + ", NOW());";

        const char* q = insert.c_str();
        int estado = mysql_query(cn.gecConector(), q);

        if (!estado)
            cout << "Producto agregado correctamente.\n";
        else
            cout << "Error al agregar producto: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        const char* query = "SELECT * FROM productos;";
        int estado = mysql_query(cn.gecConector(), query);

        if (!estado) {
            resultado = mysql_store_result(cn.gecConector());
            cout << "\n------ LISTA DE PRODUCTOS ------\n";
            while ((fila = mysql_fetch_row(resultado))) {
                cout << "ID: " << fila[0] << ", Producto: " << fila[1] << ", Marca ID: " << fila[2] << ", Precio Venta: " << fila[6] << endl;
            }
        }
        else {
            cout << "Error al leer productos: " << mysql_error(cn.gecConector()) << endl;
        }

        cn.cerrar_conexion();
    }

    void actualizar(int id_producto) {
        ConexionBD cn;
        cn.abrir_conexion();

        string update = "UPDATE productos SET producto = '" + producto + "', id_marca = " + toString(id_marca) +
            ", descripcion = '" + descripcion + "', imagen = '" + imagen + "', precio_costo = " + toString(precio_costo) +
            ", precio_venta = " + toString(precio_venta) + ", existencia = " + toString(existencia) +
            " WHERE id_producto = " + toString(id_producto) + ";";

        const char* q = update.c_str();
        int estado = mysql_query(cn.gecConector(), q);

        if (!estado)
            cout << "Producto actualizado correctamente.\n";
        else
            cout << "Error al actualizar producto: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }

    void eliminar(int id_producto) {
        ConexionBD cn;
        cn.abrir_conexion();

        string eliminar = "DELETE FROM productos WHERE id_producto = " + toString(id_producto) + ";";
        const char* q = eliminar.c_str();
        int estado = mysql_query(cn.gecConector(), q);

        if (!estado)
            cout << "Producto eliminado correctamente.\n";
        else
            cout << "Error al eliminar producto: " << mysql_error(cn.gecConector()) << endl;

        cn.cerrar_conexion();
    }
};
