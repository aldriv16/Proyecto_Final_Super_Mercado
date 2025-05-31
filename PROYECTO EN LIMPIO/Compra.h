#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <mysql.h>
#include "ConexionBD.h"

using namespace std;

class CompraDetalle {
public:
    int id_compra, id_producto, cantidad;
    double precio_costo_unitario;

    CompraDetalle(int idc, int idp, int cant, double precio)
        : id_compra(idc), id_producto(idp), cantidad(cant), precio_costo_unitario(precio) {
    }

    void guardarDetalle(MYSQL* conn) {
        string query = "INSERT INTO compras_detalle(id_compra, id_producto, cantidad, precio_costo_unitario) VALUES(" +
            to_string(id_compra) + "," + to_string(id_producto) + "," + to_string(cantidad) + "," +
            to_string(precio_costo_unitario) + ");";
        if (mysql_query(conn, query.c_str()) != 0) {
            cerr << "Error al insertar detalle: " << mysql_error(conn) << endl;
        }
    }
};

class Compra {
public:
    void realizarCompra() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conn = cn.gecConector();

        int id_proveedor;
        cout << "ID Proveedor: ";
        cin >> id_proveedor;

        // Obtener el próximo número de orden de compra
        string query_max_orden = "SELECT IFNULL(MAX(No_orden_compra), 0) + 1 AS nuevo_orden FROM compras;";
        if (mysql_query(conn, query_max_orden.c_str())) {
            cout << "Error al obtener No. Orden: " << mysql_error(conn) << endl;
            cn.cerrar_conexion();
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        int nuevo_orden = atoi(row[0]);
        mysql_free_result(res);

        // Insertar la compra (maestro)
        string insert_compra = "INSERT INTO compras(No_orden_compra, id_proveedore, fecha_orden, fecha_ingreso) VALUES(" +
            to_string(nuevo_orden) + ", " + to_string(id_proveedor) + ", NOW(), NOW());";

        if (mysql_query(conn, insert_compra.c_str())) {
            cout << "Error al insertar compra: " << mysql_error(conn) << endl;
            cn.cerrar_conexion();
            return;
        }

        unsigned long long id_compra = mysql_insert_id(conn);

        // Ingreso de un solo producto (detalle)
        int id_producto, cantidad;
        double precio_costo_unitario;

        cout << "ID del producto: ";
        cin >> id_producto;
        cout << "Cantidad: ";
        cin >> cantidad;
        cout << "Precio costo unitario: ";
        cin >> precio_costo_unitario;

        string insert_detalle = "INSERT INTO compras_detalle(id_compra, id_producto, cantidad, precio_costo_unitario) VALUES(" +
            to_string((int)id_compra) + ", " +
            to_string(id_producto) + ", " +
            to_string(cantidad) + ", " +
            to_string(precio_costo_unitario) + ");";

        if (mysql_query(conn, insert_detalle.c_str())) {
            cout << "Error al insertar detalle: " << mysql_error(conn) << endl;
        }
        else {
            cout << "Compra realizada con éxito. ID Compra: " << id_compra << ", No. Orden: " << nuevo_orden << endl;
        }

        cn.cerrar_conexion();
    }






      void mostrarCompras() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conn = cn.gecConector();

        string consulta =
            "SELECT c.id_compra, c.No_orden_compra, p.proveedor, c.fecha_orden, c.fecha_ingreso "
            "FROM compras c "
            "JOIN proveedores p ON c.id_proveedore = p.id_proveedore;";

        if (mysql_query(conn, consulta.c_str()) != 0) {
            cerr << "Error al consultar compras: " << mysql_error(conn) << endl;
            cn.cerrar_conexion();
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "Error al obtener resultados: " << mysql_error(conn) << endl;
            cn.cerrar_conexion();
            return;
        }

        cout << "ID Compra | No. Orden | Proveedor | Fecha Orden | Fecha Ingreso" << endl;
        cout << "-----------------------------------------------------------" << endl;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != nullptr) {
            cout << row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << " | " << row[4] << endl;
        }

        mysql_free_result(res);
        cn.cerrar_conexion();
    }

      void actualizarCompra() {
          ConexionBD cn;
          cn.abrir_conexion();
          MYSQL* conn = cn.gecConector();

          int id_compra, nuevo_id_proveedor;
          cout << "ID de la compra a actualizar: ";
          cin >> id_compra;

          cout << "Nuevo ID del proveedor: ";
          cin >> nuevo_id_proveedor;

          string query = "UPDATE compras SET id_proveedore = " + to_string(nuevo_id_proveedor) +
              " WHERE id_compra = " + to_string(id_compra) + ";";

          if (mysql_query(conn, query.c_str()) != 0) {
              cerr << "Error al actualizar compra: " << mysql_error(conn) << endl;
          }
          else {
              cout << "Compra actualizada correctamente." << endl;
          }

          cn.cerrar_conexion();
      }

    void eliminarCompra() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conn = cn.gecConector();

        int id_compra;
        cout << "Ingrese ID de la compra a eliminar: ";
        cin >> id_compra;

        // Primero borrar detalles para mantener integridad referencial
        string deleteDetalles = "DELETE FROM compras_detalle WHERE id_compra = " + to_string(id_compra);
        if (mysql_query(conn, deleteDetalles.c_str()) != 0) {
            cerr << "Error al eliminar detalles: " << mysql_error(conn) << endl;
            cn.cerrar_conexion();
            return;
        }

        // Luego borrar compra
        string deleteCompra = "DELETE FROM compras WHERE id_compra = " + to_string(id_compra);
        if (mysql_query(conn, deleteCompra.c_str()) != 0) {
            cerr << "Error al eliminar compra: " << mysql_error(conn) << endl;
            cn.cerrar_conexion();
            return;
        }

        cout << "Compra eliminada correctamente.\n";

        cn.cerrar_conexion();
    }
};
