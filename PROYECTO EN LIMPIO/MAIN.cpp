
#include "marca.h"
#include "producto.h"
#include "cliente.h"
#include "empleado.h"
#include "puesto.h"
#include "proveedores.h"
#include "venta.h"  
#include "compra.h" 
#include <string>
#include <sstream>  
#include <iostream>
using namespace std;

int main() {
    int opcion_general;
    do {
        cout << "\n================= MENU PRINCIPAL =================\n";
        cout << "1. Marcas\n";
        cout << "2. Productos\n";
        cout << "3. Clientes\n";
        cout << "4. Empleados\n";
        cout << "5. Puestos\n";
        cout << "6. Proveedores\n";
        cout << "7. Ventas (maestro-detalle)\n";
        cout << "8. Compras (maestro-detalle)\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion_general;
        cin.ignore();

        switch (opcion_general) {
        case 1: {
            Marca m;
            int op;
            cout << "1. Crear Marca\n2. Leer Marcas\n3. Actualizar Marca\n4. Eliminar Marca\nOpcion: "; cin >> op;

            if (op == 1) {
                string nombre;
                cout << "Nombre de marca: "; cin.ignore(); getline(cin, nombre);
                m = Marca(0, nombre);
                m.crear();
            }
            else if (op == 2) {
                m.leer();
            }
            else if (op == 3) {
                int id;
                string nombre;
                cout << "ID a actualizar: "; cin >> id;
                cout << "Nuevo nombre: "; cin.ignore(); getline(cin, nombre);
                m = Marca(id, nombre);
                m.actualizar();
            }
            else if (op == 4) {
                int id;
                cout << "ID a eliminar: "; cin >> id;
                m.eliminar(id);  
            }
            break;
        }

        
        case 2: {
            Producto p;
            int op;
            cout << "1. Crear Producto\n2. Leer Productos\n3. Actualizar Producto\n4. Eliminar Producto\nOpcion: "; cin >> op;
            if (op == 1) {
                string nombre, desc, img;
                int id_marca, ex;
                float pc, pv;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Descripcion: "; getline(cin, desc);
                cout << "Imagen: "; getline(cin, img);
                cout << "ID Marca: "; cin >> id_marca;
                cout << "Precio Costo: "; cin >> pc;
                cout << "Precio Venta: "; cin >> pv;
                cout << "Existencia: "; cin >> ex;
                p = Producto(nombre, id_marca, desc, img, pc, pv, ex);
                p.crear();
            }
            else if (op == 2) p.leer();
            else if (op == 3) {
                int id;
                string nombre, desc, img;
                int id_marca, ex;
                float pc, pv;
                cout << "ID Producto a actualizar: "; cin >> id;
                cin.ignore();
                cout << "Nuevo Nombre: "; getline(cin, nombre);
                cout << "Descripcion: "; getline(cin, desc);
                cout << "Imagen: "; getline(cin, img);
                cout << "ID Marca: "; cin >> id_marca;
                cout << "Precio Costo: "; cin >> pc;
                cout << "Precio Venta: "; cin >> pv;
                cout << "Existencia: "; cin >> ex;
                p = Producto(nombre, id_marca, desc, img, pc, pv, ex);
                p.actualizar(id);
            }
            else if (op == 4) {
                int id;
                cout << "ID a eliminar: "; cin >> id;
                p.eliminar(id);
            }
            break;
        }
        case 3: {
            Cliente c;
            int op;
            cout << "1. Crear Cliente\n2. Leer Clientes\n3. Actualizar Cliente\n4. Eliminar Cliente\nOpcion: "; cin >> op;
            if (op == 1) {
                string nom, ape, nit, tel, cor;
                bool gen;
                cin.ignore();
                cout << "Nombres: "; getline(cin, nom);
                cout << "Apellidos: "; getline(cin, ape);
                cout << "NIT: "; getline(cin, nit);
                cout << "Genero (0=M / 1=F): "; cin >> gen;
                cin.ignore();
                cout << "Telefono: "; getline(cin, tel);
                cout << "Correo: "; getline(cin, cor);
                c = Cliente(nom, ape, nit, gen, tel, cor);
                c.crear();
            }
            else if (op == 2) c.leer();
            else if (op == 3) {
                int id;
                string nom, ape, nit, tel, cor;
                bool gen;
                cout << "ID Cliente a actualizar: "; cin >> id;
                cin.ignore();
                cout << "Nombres: "; getline(cin, nom);
                cout << "Apellidos: "; getline(cin, ape);
                cout << "NIT: "; getline(cin, nit);
                cout << "Genero (0=M / 1=F): "; cin >> gen;
                cin.ignore();
                cout << "Telefono: "; getline(cin, tel);
                cout << "Correo: "; getline(cin, cor);
                c = Cliente(nom, ape, nit, gen, tel, cor);
                c.actualizar(id);
            }
            else if (op == 4) {
                int id;
                cout << "ID Cliente a eliminar: "; cin >> id;
                c.eliminar(id);
            }
            break;
        }
        case 4: {
            Empleado e;
            int op;
            cout << "1. Crear Empleado\n2. Leer Empleados\n3. Actualizar Empleado\n4. Eliminar Empleado\nOpcion: ";
            cin >> op;
            cin.ignore();

            if (op == 1) {
                string nombres, apellidos, direccion, telefono, DPI;
                int id_puesto;
                bool genero;

                cout << "Nombres: "; getline(cin, nombres);
                cout << "Apellidos: "; getline(cin, apellidos);
                cout << "Direccion: "; getline(cin, direccion);
                cout << "Telefono: "; getline(cin, telefono);
                cout << "DPI: "; getline(cin, DPI);
                cout << "ID Puesto: "; cin >> id_puesto;
                cout << "Genero (0=M / 1=F): "; cin >> genero;
                cin.ignore();

                e = Empleado(nombres, apellidos, direccion, telefono, DPI, id_puesto, genero);
                e.crear();
            }
            else if (op == 2) {
                e.leer();
            }
            else if (op == 3) {
                int id_empleado;
                string nombres, apellidos, direccion, telefono, DPI;
                int id_puesto;
                bool genero;

                cout << "ID Empleado a actualizar: "; cin >> id_empleado;
                cin.ignore();

                cout << "Nombres: "; getline(cin, nombres);
                cout << "Apellidos: "; getline(cin, apellidos);
                cout << "Direccion: "; getline(cin, direccion);
                cout << "Telefono: "; getline(cin, telefono);
                cout << "DPI: "; getline(cin, DPI);
                cout << "ID Puesto: "; cin >> id_puesto;
                cout << "Genero (0=M / 1=F): "; cin >> genero;
                cin.ignore();

                e = Empleado(nombres, apellidos, direccion, telefono, DPI, id_puesto, genero);
                e.actualizar(id_empleado);
            }
            else if (op == 4) {
                int id_empleado;
                cout << "ID Empleado a eliminar: "; cin >> id_empleado;
                e.eliminar(id_empleado);
            }
            break;
        }

        
        
        case 5: {
            int sub_opcion, id_puesto;
            string nombre_puesto;

            do {
                system("cls");
                cout << "===== MENU PUESTOS =====" << endl;
                cout << "1. Crear puesto" << endl;
                cout << "2. Leer puestos" << endl;
                cout << "3. Actualizar puesto" << endl;
                cout << "4. Eliminar puesto" << endl;
                cout << "0. Volver al menú principal" << endl;
                cout << "Seleccione una opción: ";
                cin >> sub_opcion;
                cin.ignore();

                switch (sub_opcion) {
                case 1:
                    cout << "Ingrese nombre del puesto: ";
                    getline(cin, nombre_puesto);
                    {
                        Puesto nuevo_puesto(nombre_puesto);
                        nuevo_puesto.crear();
                    }
                    system("pause");
                    break;

                case 2:
                {
                    Puesto p;
                    p.leer();
                }
                system("pause");
                break;

                case 3:
                    cout << "Ingrese ID del puesto a actualizar: ";
                    cin >> id_puesto;
                    cin.ignore();
                    cout << "Ingrese nuevo nombre del puesto: ";
                    getline(cin, nombre_puesto);
                    {
                        Puesto puesto_actualizado(nombre_puesto);
                        puesto_actualizado.actualizar(id_puesto);
                    }
                    system("pause");
                    break;

                case 4:
                    cout << "Ingrese ID del puesto a eliminar: ";
                    cin >> id_puesto;
                    {
                        Puesto puesto_a_eliminar;
                        puesto_a_eliminar.eliminar(id_puesto);
                    }
                    system("pause");
                    break;

                case 0:
                    break;

                default:
                    cout << "Opción inválida" << endl;
                    system("pause");
                }
            } while (sub_opcion != 0);

            break;
        }

        

        
        case 6: {
            Proveedor p;
            int op;
            cout << "1. Crear Proveedor\n2. Leer Proveedores\n3. Actualizar Proveedor\n4. Eliminar Proveedor\nOpcion: "; cin >> op;
            if (op == 1) {
                string nombre, nit, direccion, telefono;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "NIT: "; getline(cin, nit);
                cout << "Direccion: "; getline(cin, direccion);
                cout << "Telefono: "; getline(cin, telefono);
                p = Proveedor(nombre, nit, direccion, telefono);
                p.crear();
            }
            else if (op == 2) p.leer();
            else if (op == 3) {
                int id;
                string nombre, nit, direccion, telefono;
                cout << "ID Proveedor a actualizar: "; cin >> id;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "NIT: "; getline(cin, nit);
                cout << "Direccion: "; getline(cin, direccion);
                cout << "Telefono: "; getline(cin, telefono);
                p = Proveedor(nombre, nit, direccion, telefono);
                p.actualizar(id);
            }
            else if (op == 4) {
                int id;
                cout << "ID Proveedor a eliminar: "; cin >> id;
                p.eliminar(id);
            }
            break;
        }
        case 7: {
            Venta objVenta;
            int opcionVenta;
            do {
                cout << "\n======= MENU VENTAS (MAESTRO DETALLE) =======\n";
                cout << "1. Realizar venta\n";
                cout << "2. Mostrar ventas\n";
                cout << "3. Actualizar \n";
                cout << "4. Eliminar venta\n";
                cout << "0. Regresar al menú principal\n";
                cout << "Seleccione una opción: ";
                cin >> opcionVenta;

                switch (opcionVenta) {
                case 1: objVenta.realizarVenta(); break;
                case 2: objVenta.mostrarVentas(); break;
                case 3: objVenta.actualizarFechaFactura(); break;
                case 4: objVenta.eliminarVenta(); break;
                case 0: cout << "Regresando al menú principal...\n"; break;
                default: cout << "Opción no válida. Intente de nuevo.\n"; break;
                }
            } while (opcionVenta != 0);
            break;
        }

        
        case 8: {
            Compra c;
            int opcion_compra;
            do {
                cout << "\n======= MENU COMPRAS (MAESTRO DETALLE) =======\n";
                cout << "1. Realizar compra\n";
                cout << "2. Mostrar compras\n";
                cout << "3. Actualizar compra\n";
                cout << "4. Eliminar compra\n";
                cout << "0. Regresar al menu principal\n";
                cout << "Seleccione una opcion: ";
                cin >> opcion_compra;

                switch (opcion_compra) {
                case 1:
                    c.realizarCompra();
                    break;
                case 2:
                    c.mostrarCompras();
                    break;
                case 3:
                    c.actualizarCompra();
                    break;
                case 4:
                    c.eliminarCompra();
                    break;
                case 0:
                    cout << "Regresando al menu principal...\n";
                    break;
                default:
                    cout << "Opcion no valida.\n";
                }
            } while (opcion_compra != 0);
            break;
        }

        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion_general != 0);

    return 0;
}
