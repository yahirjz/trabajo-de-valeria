#include <iostream>
#include <string>
using namespace std;

int main() {
  // -------------------------
  // VALIDACIÓN DE NIP
  // -------------------------
  int nip;
  cout << "Ingresa tu NIP de 4 digitos: ";
  cin >> nip;

  if (nip < 1000 || nip > 9999) {
    cout << "NIP invalido. Debe ser de 4 digitos." << endl;
    return 0; // Finaliza el programa
  }

  // -------------------------
  // ARREGLOS DEL INVENTARIO
  // -------------------------
  const int MAX = 10;
  string nombres[MAX];
  int codigos[MAX];
  int cantidades[MAX];
  float precios[MAX];

  int totalProductos = 0; // Contador real de productos registrados

  // -------------------------
  // MENU DEL SISTEMA
  // -------------------------
  int opcion;

  do {
    cout << "\n===== MENU DEL INVENTARIO =====\n";
    cout << "1. Registrar producto\n";
    cout << "2. Modificar producto\n";
    cout << "3. Eliminar producto\n";
    cout << "4. Mostrar inventario\n";
    cout << "5. Consultar valor total del inventario\n";
    cout << "6. Salir\n";
    cout << "Selecciona una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
      // ----Validación si el inventario esta lleno
      if (totalProductos >= MAX) {
        cout << "No es posible registrar mas productos. El inventario esta "
                "lleno.\n";
        break;
      }

      // ---- Validación del codigo
      int codigo;
      while (true) {
        cout << "Ingresa el codigo del producto: ";
        if (!(cin >> codigo)) { // Validar que sea un numero
          cout << "Error: Debes ingresar un numero valido.\n";
          cin.clear();             // Limpiar estado de error
          cin.ignore(10000, '\n'); // Limpiar buffer
          continue;
        }

        // ---- Verificar si el código ya existe
        bool existe = false;
        for (int i = 0; i < totalProductos; i++) {
          if (codigos[i] == codigo) {
            existe = true;
            break;
          }
        }

        if (existe) {
          cout << "Error: ya existe un producto con ese codigo. Intenta con "
                  "otro.\n";
        } else {
          break; // El codigo es valido y unico, seguimos
        }
      }

      // ---- Validación del nombre
      cin.ignore(); // Limpiar buffer antes de leer cadenas
      while (true) {
        cout << "Ingresa el nombre del producto: ";
        getline(cin, nombres[totalProductos]);

        // Validacion: No puede estar vacio
        if (nombres[totalProductos].empty()) {
          cout << "El nombre no puede estar vacio. Intenta de nuevo.\n";
          continue;
        }

        // Validacion: Advertir si parece un numero
        bool soloNumeros = true;
        for (int i = 0; i < nombres[totalProductos].length(); i++) {
          char c = nombres[totalProductos][i];
          if (c < '0' || c > '9') { // Checamos si NO es un digito
            soloNumeros = false;
            break;
          }
        }

        if (soloNumeros) {
          cout << "El valor ingresado parece ser un numero, no un texto.\n";
          cin.clear();             // Limpiar estado de error
          cin.ignore(10000, '\n'); // Limpiar buffer
          continue;
        }
        break; // Es un texto normal, salimos del bucle
      }

      // ---- Validación de la cantidad
      // ---- Validación de la cantidad
      int cantidad;
      while (true) {
        cout << "Ingresa la cantidad: ";
        if (!(cin >> cantidad)) {
          cout << "Error: Debes ingresar un numero valido.\n";
          cin.clear();
          cin.ignore(10000, '\n');
          continue;
        }

        if (cantidad < 0) {
          cout << "Error: la cantidad debe ser positiva .\n";
          continue;
        } else if (cantidad > MAX) {
          cout << "Error: la cantidad no puede ser mayor a " << MAX << ".\n";
          continue;
        }
        break; // Cantidad valida
      }

      // ---- Validación del precio
      float precio;
      cout << "Ingresa el precio unitario: ";
      cin >> precio;

      if (precio < 0) {
        cout << "Error: el precio debe ser positivo.\n";
        break;
      }

      // Registrar datos en los arreglos
      codigos[totalProductos] = codigo;
      cantidades[totalProductos] = cantidad;
      precios[totalProductos] = precio;

      cout << "Producto registrado correctamente.\n";

      totalProductos++; // Incrementamos la cantidad real de productos
      break;
    }

    case 2: {
      // Modificar producto
      int codigoModificar; // variable para guardar el codigo del producto a
                           // modificar
      cout << "Ingresa el codigo del producto a modificar: ";
      cin >> codigoModificar;

      int indiceEncontrado =
          -1; // variable para guardar el indice del producto encontrado
      for (int i = 0; i < totalProductos; i++) {
        if (codigos[i] == codigoModificar) {
          indiceEncontrado = i;
          break;
        }
      }

      if (indiceEncontrado == -1) {
        cout << "Error: Producto no encontrado.\n";
      } else {
        cout << "Producto encontrado: " << nombres[indiceEncontrado] << endl;

        // ---- Modificar cantidad
        char respuesta;
        cout << "¿Deseas modificar la cantidad? (s/n): ";
        cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S') {
          int nuevaCantidad; // variable para guardar la nueva cantidad
          while (true) {
            cout << "Ingresa la nueva cantidad: ";
            if (!(cin >> nuevaCantidad)) {
              cout << "Error: Debes ingresar un numero valido.\n";
              cin.clear();
              cin.ignore(10000, '\n');
              continue;
            }
            if (nuevaCantidad < 0) {
              cout << "Error: La cantidad no puede ser negativa.\n";
              continue;
            } else if (nuevaCantidad > MAX) {
              cout << "Error: La cantidad no puede ser mayor a " << MAX
                   << ".\n";
              continue;
            }
            cantidades[indiceEncontrado] =
                nuevaCantidad; // Actualizamos solo si el usuario quiso
                               // cambiarla
            break;
          }
        }

        // ---- Modificar precio
        cout << "¿Deseas modificar el precio? (s/n): ";
        cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S') {
          float nuevoPrecio;
          while (true) {
            cout << "Ingresa el nuevo precio: ";
            if (!(cin >> nuevoPrecio)) {
              cout << "Error: Debes ingresar un numero valido.\n";
              cin.clear();
              cin.ignore(10000, '\n');
              continue;
            }
            if (nuevoPrecio < 0) {
              cout << "Error: El precio no puede ser negativo.\n";
              continue;
            }
            precios[indiceEncontrado] =
                nuevoPrecio; // Actualizamos solo si el usuario quiso cambiarlo
            break;
          }
        }

        cout << "Producto modificado exitosamente.\n";
      }
      break;
    }
    case 3: {
      // Eliminar producto
      int codigoEliminar;
      cout << "Ingresa el codigo del producto a eliminar: ";
      cin >> codigoEliminar;

      int indiceEliminar = -1;
      for (int i = 0; i < totalProductos; i++) {
        if (codigos[i] == codigoEliminar) {
          indiceEliminar = i;
          break;
        }
      }

      if (indiceEliminar == -1) {
        cout << "Error: Producto no encontrado.\n";
      } else {
        cout << "Producto encontrado: " << nombres[indiceEliminar] << endl;
        cout << "¿Estas seguro de eliminarlo? (s/n): ";
        char confirmacion;
        cin >> confirmacion;

        if (confirmacion == 's' || confirmacion == 'S') {
          // Eliminar moviendo los elementos una posicion atras
          for (int i = indiceEliminar; i < totalProductos - 1; i++) {
            codigos[i] = codigos[i + 1];
            nombres[i] = nombres[i + 1];
            cantidades[i] = cantidades[i + 1];
            precios[i] = precios[i + 1];
          }
          totalProductos--; // Reducimos el contador
          cout << "Producto eliminado correctamente.\n";
        } else {
          cout << "Operacion cancelada.\n";
        }
      }
      break;
    }
    case 4: {
      if (totalProductos == 0) {
        cout << "\n--- El inventario esta vacio ---\n";
      } else {
        cout << "\n===== LISTA DE PRODUCTOS =====\n";
        cout << "Codigo\tNombre\t\tCant.\tPrecio\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < totalProductos; i++) {
          cout << codigos[i] << "\t" << nombres[i] << "\t\t" << cantidades[i]
               << "\t$" << precios[i] << endl;
        }
        cout << "----------------------------------------\n";
      }
      break;
    }
    case 5: {
      float valorTotal = 0;
      for (int i = 0; i < totalProductos; i++) {
        valorTotal += cantidades[i] * precios[i];
      }
      cout << "\n===== VALOR TOTAL DEL INVENTARIO =====\n";
      cout << "Valor total: $" << valorTotal << endl;
      break;
    }
    case 6:
      cout << "Saliendo del sistema..." << endl;
      break;

    default:
      cout << "Opcion invalida. Intenta nuevamente.\n";
    }

  } while (opcion != 6);

  return 0;
}