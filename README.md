# INDICE

1. [Introducción a los descriptores de archivo](#Introducción-a-los-descriptores-de-archivo)

   2 [Descriptores de archivos estandar](#Descriptores-de-archivos-estandar)
   
3. [Funciones](#funciones)

    2.1. [Open](#open)
   
    2.2. [Read](#read)
   
4. [Variables estáticas en C](#variables-estaticas-en-C)

## Introducción a los descriptores de archivo

Los descriptores de archivo son una parte integral de cómo los sistemas operativos interactúan con los archivos. Son identificadores únicos, generalmente representados como números enteros, que se asignan a un archivo abierto o a un flujo de datos.
Cada vez que un archivo se abre en un sistema operativo, se crea un descriptor de archivo. Este descriptor se utiliza luego para leer, escribir o realizar otras operaciones con el archivo. Cuando el archivo se cierra, el descriptor de archivo se libera y puede ser reutilizado. Los descriptores de archivo no sólo se utilizan para los archivos regulares, sino también para otros tipos de recursos, como los sockets de red y los tubos (pipes). En todos estos casos, el descriptor de archivo proporciona una forma de referirse al recurso abierto. En el contexto de la programación, los descriptores de archivo se utilizan en varias funciones de la biblioteca estándar de C, como open, read, write y close, que permiten al programador interactuar con los archivos. Es importante tener en cuenta que los descriptores de archivo son específicos del proceso. Esto significa que dos procesos diferentes pueden tener descriptores de archivo con el mismo número, pero cada uno de ellos se refiere a un archivo diferente.

   ### Descriptores de archivos estándar

0: este descriptor de archivo representa la entrada estándar (=> entrada estándar, el terminal). Este es el descriptor de archivo utilizado al leer la entrada del usuario desde el terminal.

1: este descriptor de archivo representa la salida estándar (=> salida estándar, el terminal). Este es el descriptor de archivo utilizado al escribir en la terminal.

2: este descriptor de archivo representa el stderr (=> salida de error estándar, el terminal). Este es el descriptor de archivo que se utiliza al escribir un error en la terminal; la información se escribe de la misma manera, pero un programa que registra errores en un archivo puede redirigir todo lo escrito en el descriptor de archivo stderr a un archivo. El sistema operativo lo gestiona de otra manera.

## Funciones

## 2.1. Open()

#include <fcntl.h>

Open es una función que se utiliza para abrir un archivo en un modo específico (como lectura, escritura, etc.). 

* Se le proporciona un path al archivo y flags que determinan el modo de apertura.

        int open (const char path, int flags [, int mode ]);
  
### 2.1.1 Componentes

#### - Path

Corresponde al título del archivo que desea abrir/crear.

También se refiere a la ubicación del archivo. Si no está trabajando en el mismo directorio que el archivo, puede proporcionar una ruta absoluta que comience con "/"

#### - Flags

Tienes que decirle a tu función qué tipo de acceso deseas. Esto se hace con banderas. Aquí está la lista con la información de cada bandera:

**O_RDONLY** : En modo de solo lectura, abra el archivo.

**O_WRONLY** : En modo de solo escritura, abra el archivo

**O_RDWR** : Abre el archivo en modo lectura y escritura.

**O_CREAT** : Este indicador se aplica para crear un archivo si no existe en la ruta o directorio especificado.

**O_EXCL** : Impide la creación de archivos si ya existe en el directorio o ubicación.

#### - Valor de retorno

El valor de retorno de open() es un descriptor de archivo, un pequeño entero no negativo que es un índice de una entrada en la tabla de descriptores de archivos abiertos del proceso. Si hay un error en alguna parte, la función devolverá -1 como sinónimo de error.

## 2.2. Read()
La función tiene un prototipo de esta manera:

        ssize_t read(int fildes, void buf, size_t nbyte);

Esta función intenta leer nbytebytes de datos del objeto al que hace referencia el descriptor fildesen el búfer al que apunta buf. La función read() comienza en una posición dada por el puntero asociado con fildes. Al final, el puntero se incrementa según el número de bytes ( nbyte) realmente leídos.


## 3. Variables estáticas en C

Las variables estáticas tienen la propiedad de preservar su valor incluso después de que estén fuera de su alcance. Por lo tanto, una variable estática conserva su valor anterior en su ámbito anterior y no se inicializa nuevamente en el nuevo ámbito. 

Sintaxis:

**static data_type var_name = var_value;**

**1)** Una variable int estática permanece en la memoria mientras se ejecuta el programa. Una variable normal o automática se destruye cuando finaliza una llamada a una función donde se declaró la variable.

**2)** A las variables estáticas se les asigna memoria en el segmento de datos, no en el segmento de stack.

**3)** Las variables estáticas (como las variables globales) se inicializan como 0 si no se inicializan explícitamente.

**4)** En C, las variables estáticas solo se pueden inicializar utilizando literales constantes.

**5)** Las variables y funciones globales estáticas también son posibles en C/C++. El propósito de estos es limitar el alcance de una variable o función a un archivo. 

**6)** Las variables estáticas no deben declararse dentro de una estructura. 
* La razón es que el compilador de C requiere que todos los elementos de la estructura se coloquen juntos (es decir, que la asignación de memoria para los miembros de la estructura debe ser contigua).
 * Es posible declarar la estructura dentro de la función (segmento de pila) o asignar memoria dinámicamente (segmento de montón) o incluso puede ser global (BSS o segmento de datos).
  * Cualquiera que sea el caso, todos los miembros de la estructura deben residir en el mismo segmento de memoria porque el valor del elemento de la estructura se obtiene contando el desplazamiento del elemento desde la dirección inicial de la estructura.
   * Separar un solo miembro en un segmento de datos anula el propósito de la estructura y es posible tener una estructura completa como estática.

## Dynamic Memory Allocation in C **(Asignación de memoria dinámica en C)**

Es el procedimiento en el que el tamaño de una estructura de datos (como una matriz) se cambia durante el tiempo de ejecución. Existen **cuatro funciones** en C definidas en el archivo de encabezado **<stdlib.h>** para facilitar este proceso.

**1. malloc:** Se utiliza para asignar dinámicamente un único bloque grande de memoria con el tamaño especificado. 
*  Devuelve un puntero de tipo void que se puede convertir en un puntero de cualquier forma. No inicializa la memoria en el momento de la ejecución, por lo que inicialmente ha inicializado cada bloque con el valor basura predeterminado. 

Ejemplo:

***ptr = (cast-type) malloc(byte-size)**

**2. calloc:** El método "calloc" o "asignación contigua" en C se utiliza apra asignar dinamicamente el número especificado de bloques de memoria del tipo especificado. 
 * Es muy similar a malloc() pero tiene dos puntos diferentes y estos son:
- inicializa cada bloque con un valor predeterminado '0'
- Tiene dos parámetros o argumentos en comparación con malloc()

***ptr = (cast-type*)calloc(n, element-size);**

Ejemplo:

***ptr = (float*)calloc(25, sizeof(float));**
Este parámetro asigna espacio contiguo en una memoria de 25 elementos cada uno con el tamaño de float

**3 free**: 

free(ptr);

Se utiliza para desasignar dinámicamente la memoria. La memoria asignada mediante las funciones malloc() y calloc() no se desasigna por sí sola. Por lo tanto, se utiliza el método free() siempre que se realiza la asignación de memoria dinámica. Ayuda a reducir el desperdicio de memoria liberándola.

**4 realloc:**

Se utiliza para cambiar dinámicamente la asignación de memoria de una memoria previamente asignada. En otras palabras, si la memoria previamente asignada con la ayuda de malloc o calloc es insuficiente, se puede utilizar realloc para reasignar memoria dinámicamente . La reasignación de memoria mantiene el valor ya presente y los nuevos bloques se inicializarán con el valor basura predeterminado.

***ptr = realloc(ptr, newSize);**

## Diseño de memoria de programas C

Una representación de memoria típica de un programa C consta de las siguientes secciones.

1. Text segment  (i.e. instructions)
2. Initialized data segment 
3. Uninitialized data segment  (bss)
4. Heap 
5. Stack

**1. Segmento de texto:**  Un segmento de texto, también conocido como segmento de código o simplemente como texto, es una de las secciones de un programa en un archivo objeto o en la memoria, que contiene instrucciones ejecutables.
Como región de memoria, se puede colocar un segmento de texto debajo del *heap* o el *stack* para evitar que los montones y los desbordamientos de pila lo sobrescriban.

Por lo general, el segmento de texto se puede compartir, por lo que solo es necesario que haya una copia en la memoria para los programas que se ejecutan con frecuencia, como los editores de texto, el compilador de C, los shells, etc. Además, el segmento de texto suele ser de sólo lectura, para evitar que un programa modifique accidentalmente sus instrucciones.

**2. Segmento de datos inicializados:**  Segmento de datos inicializados, generalmente llamado simplemente *segmento de datos*. 
* Un segmento de datos es una parte del espacio de direcciones virtuales de un programa, que contiene *las variables globales* y *las variables estáticas* que inicializa el programador.
 * Ten en cuenta que el segmento de datos no es de solo lectura, ya que los valores de las variables se pueden modificar en tiempo de ejecución.
  * Este segmento se puede clasificar además en el área de solo lectura inicializada y el área de lectura-escritura inicializada.

**3. Segmento de datos no inicializados:**  Segmento de datos no inicializados a menudo llamado segmento " bss ", que lleva el nombre de un antiguo operador ensamblador que significaba " bloque iniciado por símbolo ". 
* El núcleo inicializa los datos de este segmento en aritmética 0 antes de que el programa comience a ejecutar los datos no inicializados que comienzan al final del segmento de datos y contienen todas las variables globales y variables estáticas que se inicializan a cero o no tienen una inicialización explícita en el código fuente.

**4. Pila (stack):**  El área del *stack* tradicionalmente estaba contigua al área del montón y crecía en la dirección opuesta; cuando el puntero del *stack* se encuentra con el puntero del montón, se agota la memoria libre. 
 * Con los grandes espacios de direcciones modernos y las técnicas de memoria virtual, se pueden colocar casi en cualquier lugar, pero normalmente siguen creciendo en direcciones opuestas.

* El área de stack contiene la pila de programas, una estructura LIFO, normalmente ubicada en las partes superiores de la memoria. 
 * En la arquitectura de computadora PC x86 estándar, crece hacia la dirección cero; en algunas otras arquitecturas, crece en la dirección opuesta.
  * Un registro de “puntero de pila” rastrea la parte superior del stack; se ajusta cada vez que se “empuja” un valor a la pila.
   * El conjunto de valores enviados para una llamada de función se denomina "marco de pila"; Un marco de pila consta como mínimo de una dirección de remitente.

En resumen, es donde se almacenan las variables automáticas, junto con la información que se guarda cada vez que se llama a una función. 
* Cada vez que se llama a una función, la dirección a dónde regresar y cierta información sobre el entorno de la persona que llama, como algunos de los registros de la máquina, se guardan en la pila.
 * La función recién llamada asigna espacio en la pila para sus variables automáticas.
  * Así es como pueden funcionar las funciones recursivas en C. Cada vez que una función recursiva se llama a sí misma, se utiliza un nuevo marco de pila, por lo que un conjunto de variables no interfiere con las variables de otra instancia de la función.

**5. Montón (heap):**  El heap es el segmento donde suele tener lugar la asignación de memoria dinámica.
* El área del heap comienza al final del segmento BSS y crece hasta direcciones más grandes desde allí.
 * El área del *heap* es administrada por *malloc*, *realloc* y *free*, que pueden usar las llamadas al sistema brk y sbrk para ajustar su tamaño (tenga en cuenta que el uso de brk/sbrk y un único “área del montón” no es necesario para cumplir el contrato de *malloc*/*realloc*/*free*; también se pueden implementar usando *map* para reservar regiones potencialmente no contiguas de memoria virtual en el espacio de direcciones virtuales del proceso).
 * El área del *heap* es compartida por todas las bibliotecas compartidas y los módulos cargados dinámicamente en un proceso.

Fuente: https://42-cursus.gitbook.io/guide/rank-01/get_next_line
