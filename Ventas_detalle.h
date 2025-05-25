#pragma once
#include <cstdlib>
#include <mysql.h>
#include <string>
#include <iostream>

class Ventas_detalle {
    public:
        // Constructor que recibe MYSQL*
        class Ventas_detalle(MYSQL* conn);
        void insertar(int id_venta);
        void mostrar();
        void actualizar();
        void eliminar();
        void mostrarPorVenta(int id_venta);


    private:
        MYSQL* conn;
};
