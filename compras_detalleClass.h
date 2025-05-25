#pragma once
#include <mysql.h>
#include <string>

class compras_detalleClass {
public:
    compras_detalleClass(MYSQL* conn);
    int insertar(int id_compra);
    void mostrar();
    void mostrarPorCompra(int id_compra);
    void actualizar();
    void eliminar();
private:
    MYSQL* conn;
};

