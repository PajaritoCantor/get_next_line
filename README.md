# get_next_line
## Descriptores de archivos (FD)

Un descriptor de archivo es una int variable que identifica de forma única un archivo abierto.

### Descriptor de archivo

Este es el índice de la entrada de la tabla de archivos en la tabla de descriptores de archivos.

### Tabla de descriptores de archivos

Esta es una matriz de entradas de tabla de archivos, cada proceso obtiene su propia tabla de descriptores de archivos.

### Entrada de tabla de archivos

Una entrada de tabla de archivos es una estructura que contiene información sobre un archivo.

### Tabla de archivos globales

Esta es una tabla para todo el sistema que contiene todos los archivos. (No puede contener todos los archivos a la vez, pero el sistema operativo actualizará automáticamente la tabla si solicita un archivo que no está en esta tabla).

Cuando utilizas un descriptor de archivo, con la read(2)función por ejemplo, sucederá lo siguiente:

Busque el archivo en la tabla de archivos globales

Si se encuentra el archivo, vaya al siguiente paso.

Si no se encuentra el archivo, el sistema operativo actualizará la tabla de archivos globales para que el archivo solicitado esté disponible y luego volverá al paso 1.

Cree una entrada en la tabla Archivo en la tabla Descriptor de archivo para el archivo solicitado.

Asigne el primer descriptor de archivo no utilizado a la entrada de la tabla de archivos creada.

## Descriptores de archivos estándar

**0:** este descriptor de archivo representa la entrada estándar (=> entrada estándar, el terminal). Este es el descriptor de archivo utilizado al leer la entrada del usuario desde el terminal.

**1:** este descriptor de archivo representa la salida estándar (=> salida estándar, el terminal). Este es el descriptor de archivo utilizado al escribir en la terminal.

**2:** este descriptor de archivo representa el stderr (=> salida de error estándar, el terminal). Este es el descriptor de archivo que se utiliza al escribir un error en la terminal; la información se escribe de la misma manera, pero un programa que registra errores en un archivo puede redirigir todo lo escrito en el descriptor de archivo stderr a un archivo. El sistema operativo lo gestiona de otra manera.

## Open ()

**#include <fcntl.h>**

Esta función le permitirá abrir y acceder a un archivo. Está prototipado de esta manera:

**int open (const char* path, int flags [, int mode ]);**

**path**

Corresponde al título del archivo que desea abrir/crear.

También se refiere a la ubicación del archivo. Si no está trabajando en el mismo directorio que el archivo, puede proporcionar una ruta absoluta que comience con "/"

**flags**

Tienes que decirle a tu función qué tipo de acceso deseas. Esto se hace con banderas. Aquí está la lista con la información de cada bandera:

**O_RDONLY** : en modo de solo lectura, abra el archivo.

**O_WRONLY** : en modo de solo escritura, abra el archivo

**O_RDWR** : abre el archivo en modo lectura y escritura.

**O_CREAT** : este indicador se aplica para crear un archivo si no existe en la ruta o directorio especificado.

**O_EXCL** : Impide la creación de archivos si ya existe en el directorio o ubicación.

**Valor de retorno**

El valor de retorno de open() es un descriptor de archivo, un pequeño entero no negativo que es un índice de una entrada en la tabla de descriptores de archivos abiertos del proceso. Si hay un error en alguna parte, la función devolverá -1 como sinónimo de error.

## Static Variables in C

Las variables estáticas tienen la propiedad de preservar su valor incluso después de que estén fuera de su alcance. Por lo tanto, una variable estática conserva su valor anterior en su ámbito anterior y no se inicializa nuevamente en el nuevo ámbito. 

Sintaxis:

**static data_type var_name = var_value;**

**1)** Una variable int estática permanece en la memoria mientras se ejecuta el programa. Una variable normal o automática se destruye cuando finaliza una llamada a una función donde se declaró la variable.

**2)** A las variables estáticas se les asigna memoria en el segmento de datos, no en el segmento de pila. Consulte el diseño de la memoria de los programas C para obtener más detalles.

**3)** Las variables estáticas (como las variables globales) se inicializan como 0 si no se inicializan explícitamente. Por ejemplo, en el siguiente programa, el valor de x se imprime como 0, mientras que el valor de y es algo basura. Vea esto para más detalles. 

**4)** En C, las variables estáticas solo se pueden inicializar utilizando literales constantes. Por ejemplo, el siguiente programa falla en la compilación. Vea esto para más detalles.

**5)** Las variables y funciones globales estáticas también son posibles en C/C++. El propósito de estos es limitar el alcance de una variable o función a un archivo. Consulte Funciones estáticas en C para obtener más detalles.

**6)** Las variables estáticas no deben declararse dentro de una estructura. La razón es que el compilador de C requiere que todos los elementos de la estructura se coloquen juntos (es decir, que la asignación de memoria para los miembros de la estructura debe ser contigua). Es posible declarar la estructura dentro de la función (segmento de pila) o asignar memoria dinámicamente (segmento de montón) o incluso puede ser global (BSS o segmento de datos). Cualquiera que sea el caso, todos los miembros de la estructura deben residir en el mismo segmento de memoria porque el valor del elemento de la estructura se obtiene contando el desplazamiento del elemento desde la dirección inicial de la estructura. Separar un solo miembro en un segmento de datos anula el propósito de la estructura y es posible tener una estructura completa como estática
 
