#pragma once
#include <mysql.h>
#include <string>

class Compras {
public:
    Compras(MYSQL* conn);
    int insertar();
    void mostrar();
    void actualizar();
    void eliminar();
private:
    MYSQL* conn;
};
