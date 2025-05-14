#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H

#include <mysql.h>
#include <string>
#include <iostream>

class Cliente {
public:
    // Constructor que recibe MYSQL*
    Cliente(MYSQL* conn);
    void insertar();
    void mostrar();
    void actualizar();
    void eliminar();

private:
    MYSQL* conn;
};

#endif
