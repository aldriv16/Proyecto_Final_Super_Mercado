#pragma once
#include "puestos.h"
#include "ConexionBD.h"
#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <mysql.h>
#include <string>

class Empleado {
public:
    Empleado(MYSQL* conn);
    void insertar();
    void mostrar(); 
    void actualizar();
    void eliminar();

private:
    MYSQL* conn;
};

#endif
