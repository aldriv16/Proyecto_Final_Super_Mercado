#pragma once
#include "ConexionBD.h"
#ifndef MARCA_H
#define MARCA_H

#include <mysql.h>
#include <string>

class Marca {
public:
    Marca(MYSQL* conn);
    void insertar();
    void mostrar();
    void actualizar();
    void eliminar();

private:
    MYSQL* conn;
};

#endif
