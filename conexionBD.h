#pragma once
#include <mysql.h>
#include <iostream>

class conexionBD
{
private: MYSQL* conector;
public :
	void abrir_conexion() {
		conector = mysql_init(0);
		conector = mysql_real_connect(conector, "localhost", "root", "12345678", "super_mercado", 3306, NULL, 0);


	}
	MYSQL* getconector() {
		return conector;
	}
	void cerrar_conexion() {
		mysql_close(conector);
	}
};



