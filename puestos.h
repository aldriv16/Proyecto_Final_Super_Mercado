#pragma once
#ifndef PUESTO_H
#define PUESTO_H

#include <mysql.h>
#include <string>
#include <iostream>

class Puesto {
public:
    // Constructor que recibe el puntero de conexi�n a MySQL
    Puesto(MYSQL* conn);

    // M�todos para interactuar con los puestos
    void mostrar();
    void insertar();
    void actualizar();
    void eliminar();

private:
    MYSQL* conn;  // Variable para almacenar el puntero de la conexi�n MySQL
};

#endif
