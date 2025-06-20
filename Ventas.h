#pragma once
#include <mysql.h>
#include <string>
#include <iostream>

class Ventas {
    public:
        // Constructor que recibe MYSQL*
        class Ventas(MYSQL* conn);
        int insertar();
        void mostrar();
        void actualizar();
        void eliminar();

    private:
        MYSQL* conn;
};
