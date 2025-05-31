#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>
#include "cliente.h"

using namespace std;

class VentaDetalle {
public:
    int id_venta, id_producto, cantidad;
    double precio_unitario;

    inline VentaDetalle(int idv, int idp, int cant, double precio) {
        id_venta = idv;
        id_producto = idp;
        cantidad = cant;
        precio_unitario = precio;
    }

    inline void guardarDetalle(MYSQL* conn) {
        string query = "INSERT INTO ventas_detalle(id_venta, id_producto, cantidad, precio_unitario) VALUES(" +
            to_string(id_venta) + "," + to_string(id_producto) + "," + to_string(cantidad) + "," +
            to_string(precio_unitario) + ");";

        if (mysql_query(conn, query.c_str()) != 0) {
            cerr << "Error al insertar detalle: " << mysql_error(conn) << endl;
        }
    }
};

class Venta {
public:
    inline void realizarVenta();
    inline void mostrarVentas();
    inline void actualizarFechaFactura();
    inline void eliminarVenta();

private:
    inline int buscarClientePorNIT(MYSQL* conn, string nit);
};

// ======================== IMPLEMENTACIONES ============================

inline int Venta::buscarClientePorNIT(MYSQL* conn, string nit) {
    string query = "SELECT id_cliente FROM clientes WHERE nit = '" + nit + "'";
    if (mysql_query(conn, query.c_str()) != 0) {
        cerr << "Error al buscar cliente por NIT: " << mysql_error(conn) << endl;
        return 0;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    int resultado = 0;
    if (row) resultado = stoi(row[0]);
    mysql_free_result(res);
    return resultado;
}

inline void Venta::realizarVenta() {
    ConexionBD cn;
    cn.abrir_conexion();
    MYSQL* conn = cn.gecConector();

    // Activar autocommit para guardar automáticamente los cambios
    mysql_autocommit(conn, 1);

    string nit, nombre, apellido;
    cout << "Ingrese NIT del cliente: ";
    cin.ignore();
    getline(cin, nit);

    int id_cliente = buscarClientePorNIT(conn, nit);
    if (id_cliente == 0) {
        cout << "Cliente no encontrado. Registrando nuevo cliente..." << endl;
        cout << "Nombres: "; getline(cin, nombre);
        cout << "Apellidos: "; getline(cin, apellido);
        string telefono, correo;
        cout << "Teléfono: "; getline(cin, telefono);
        cout << "Correo electrónico: "; getline(cin, correo);
        string insert = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso) "
            "VALUES('" + nombre + "','" + apellido + "','" + nit + "',0,'" + telefono + "','" + correo + "',NOW());";

        if (mysql_query(conn, insert.c_str()) != 0) {
            cerr << "Error al insertar nuevo cliente: " << mysql_error(conn) << endl;
        }
        id_cliente = static_cast<int>(mysql_insert_id(conn));
    }
    else {
        string consulta = "SELECT nombres, apellidos FROM clientes WHERE id_cliente = " + to_string(id_cliente);
        if (mysql_query(conn, consulta.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr) {
                nombre = row[0];
                apellido = row[1];
            }
            mysql_free_result(res);
        }
        else {
            cerr << "Error al consultar datos del cliente: " << mysql_error(conn) << endl;
        }
    }

    int id_empleado;
    cout << "ID del empleado que realiza la venta: ";
    cin >> id_empleado;

    string serie = "A";

    // Generar número de factura automático:
    string queryMax = "SELECT IFNULL(MAX(No_factura), 0) FROM ventas";
    mysql_query(conn, queryMax.c_str());
    MYSQL_RES* resMax = mysql_store_result(conn);
    MYSQL_ROW rowMax = mysql_fetch_row(resMax);
    int numero_factura_auto = 1;
    if (rowMax && rowMax[0] != nullptr) {
        numero_factura_auto = stoi(rowMax[0]) + 1;
    }
    mysql_free_result(resMax);

    string insert_venta = "INSERT INTO ventas(serie, No_factura, fecha_factura, id_cliente, id_empleado) VALUES('" +
        serie + "'," + to_string(numero_factura_auto) + ",NOW()," + to_string(id_cliente) + "," + to_string(id_empleado) + ")";

    if (mysql_query(conn, insert_venta.c_str()) != 0) {
        cerr << "Error al insertar venta: " << mysql_error(conn) << endl;
    }
    unsigned long long id_venta_u64 = mysql_insert_id(conn);
    int id_venta = static_cast<int>(id_venta_u64);

    vector<VentaDetalle> detalles;
    double total = 0;
    char otro;
    do {
        int id_producto, cantidad;
        cout << "ID Producto: "; cin >> id_producto;
        cout << "Cantidad: "; cin >> cantidad;

        string query = "SELECT producto, precio_venta FROM productos WHERE id_producto = " + to_string(id_producto);
        if (mysql_query(conn, query.c_str()) != 0) {
            cerr << "Error al consultar producto: " << mysql_error(conn) << endl;
            continue;
        }
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        if (!row) {
            cerr << "Producto no encontrado.\n";
            mysql_free_result(res);
            continue;
        }

        string nombre_producto = row[0];
        double precio = atof(row[1]);
        double subtotal = precio * cantidad;
        total += subtotal;

        detalles.push_back(VentaDetalle(id_venta, id_producto, cantidad, precio));

        cout << "Producto agregado: " << nombre_producto << " x" << cantidad << " = Q" << subtotal << endl;
        cout << "¿Desea agregar otro producto? (s/n): ";
        cin >> otro;

        mysql_free_result(res);
    } while (otro == 's' || otro == 'S');

    for (auto& det : detalles) {
        det.guardarDetalle(conn);
    }

    cout << "\n================ FACTURA ================\n";
    cout << "Factura No. " << numero_factura_auto << " | Serie " << serie << endl;
    cout << "Cliente: " << nombre << " " << apellido << " | NIT: " << nit << endl;
    cout << "Productos:" << endl;
    for (auto& det : detalles) {
        cout << "- Producto ID " << det.id_producto << " x" << det.cantidad << " = Q" << fixed << setprecision(2)
            << (det.cantidad * det.precio_unitario) << endl;
    }
    cout << "TOTAL: Q" << fixed << setprecision(2) << total << endl;
    cout << "Gracias por su compra.\n";

    cn.cerrar_conexion();
}


inline void Venta::mostrarVentas() {
    ConexionBD cn;
    cn.abrir_conexion();
    MYSQL* conn = cn.gecConector();

    string query = "SELECT v.id_venta, v.no_factura, v.fecha_factura, c.nombres, c.apellidos, p.producto, d.cantidad, d.precio_unitario "
        "FROM ventas v "
        "JOIN clientes c ON v.id_cliente = c.id_cliente "
        "JOIN ventas_detalle d ON v.id_venta = d.id_venta "
        "JOIN productos p ON d.id_producto = p.id_producto";

    if (mysql_query(conn, query.c_str()) != 0) {
        cerr << "Error al mostrar ventas: " << mysql_error(conn) << endl;
        cn.cerrar_conexion();
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "\n=========== VENTAS REGISTRADAS ===========\n";
    while ((row = mysql_fetch_row(res)) != nullptr) {
        cout << "Venta ID: " << row[0] << " | Factura: " << row[1] << " | Fecha: " << row[2] << endl;
        cout << "Cliente: " << row[3] << " " << row[4] << " | Producto: " << row[5] << " | Cantidad: " << row[6] << " | Precio: Q" << row[7] << endl;
        cout << "----------------------------------------\n";
    }
    mysql_free_result(res);
    cn.cerrar_conexion();
}

inline void Venta::actualizarFechaFactura() {
    ConexionBD cn;
    cn.abrir_conexion();
    MYSQL* conn = cn.gecConector();

    int id_venta;
    cout << "Ingrese el ID de la venta a actualizar: ";
    cin >> id_venta;

    string update = "UPDATE ventas SET fecha_factura = NOW() WHERE id_venta = " + to_string(id_venta);
    if (mysql_query(conn, update.c_str()) == 0) {
        cout << "Fecha de factura actualizada correctamente.\n";
    }
    else {
        cerr << "Error al actualizar la fecha: " << mysql_error(conn) << endl;
    }
    cn.cerrar_conexion();
}

inline void Venta::eliminarVenta() {
    ConexionBD cn;
    cn.abrir_conexion();
    MYSQL* conn = cn.gecConector();

    int id_venta;
    cout << "Ingrese el ID de la venta a eliminar: ";
    cin >> id_venta;

    string delete_detalle = "DELETE FROM ventas_detalle WHERE id_venta = " + to_string(id_venta);
    string delete_venta = "DELETE FROM ventas WHERE id_venta = " + to_string(id_venta);

    if (mysql_query(conn, delete_detalle.c_str()) == 0 && mysql_query(conn, delete_venta.c_str()) == 0) {
        cout << "Venta eliminada correctamente.\n";
    }
    else {
        cerr << "Error al eliminar la venta: " << mysql_error(conn) << endl;
    }
    cn.cerrar_conexion();
}
