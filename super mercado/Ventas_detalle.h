#pragma once

#include <mysql.h>
#include <string>
#include <iostream>

class Ventas_detalle {
    public:
        // Constructor que recibe MYSQL*
        class Ventas_detalle(MYSQL* conn);
        void insertar();
        void mostrar();
        void actualizar();
        void eliminar();

    private:
        MYSQL* conn;
};
