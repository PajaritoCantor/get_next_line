# INDICE

1. [Introducción básica a los descriptores de archivo-fd](#Introducción-a-los-descriptores-de-archivo-fd)
   
2. [Funciones](#funciones)

   2.1. [Open](#Open)

    2.2. [Componentes](#Componentes)
   
   2.3. [Read](#Read)
   
3. [Variables estáticas en C](#variables-estáticas-en-C)

4. [Asignación de memoria dinámica en C](#Asignación-de-memoria-dinámica-en-C)

   4.1. [Malloc](#Malloc)
   
   4.2. [Calloc](#Calloc)

   4.3. [Free](#free)

   4.3. [Realloc](#Realloc)

5. [Diseño de memoria de programas C](#Diseño-de-memoria-de-programas-C)

   5.1. [Segmento de datos inicializados](#Segmento-de-datos-inicializados)
   
   5.2. [Segmento de datos no inicializados](#Segmento-de-datos-no-inicializados)
   
   5.3. [Stack](#Stack)
   
   5.4. [Heap](#Heap)

6. [GET_NEXT_LINE](#get_next_line)
   
    [Aclaración](#Aclaración)
   
   6.1. [Funciones auxiliares](#Funciones-auxiliares)

   6.1.1. [ft_memcpy](#ft_memcpy)
   
   6.1.2. [ft_bzero](#ft_bzero)

   6.1.3. [ft_strlcpy_gnl](#ft_strlcpy_gnl)
   
   6.1.4 [ft_strjoin_gnl](#ft_strjoin_gnl)

   6.2 [Funciones_principales](#Funciones-principales)

   6.2.1. [Algunos_conceptos_básicos](#Algunos-conceptos-básicos)

   6.2.2. [Aclaraciones_sobre_mi_archivo_.h](#Aclaraciones-sobre-mi-archivo-.h)

## Introducción a los descriptores de archivo (fd)

Los descriptores de archivo son una parte integral de cómo los sistemas operativos interactúan con los archivos. 

*   Son identificadores únicos, generalmente representados como números enteros, que se asignan a un archivo abierto o a un flujo de datos.
*   Cada vez que un archivo se abre en un sistema operativo, se crea un descriptor de archivo. Este descriptor se utiliza luego para leer, escribir o realizar otras operaciones con el archivo. Cuando el archivo se cierra, el descriptor de archivo se libera y puede ser reutilizado. Los descriptores de  *   archivo no sólo se utilizan para los archivos regulares, sino también para otros tipos de recursos, como los sockets de red y los tubos (pipes).
*   En todos estos casos, el descriptor de archivo proporciona una forma de referirse al recurso abierto. En el contexto de la programación, los descriptores de archivo se utilizan en varias funciones de la biblioteca estándar de C, como open, read, write y close, que permiten al programador interactuar con los archivos.
*   Es importante tener en cuenta que los descriptores de archivo son específicos del proceso. Esto significa que dos procesos diferentes pueden tener descriptores de archivo con el mismo número, pero cada uno de ellos se refiere a un archivo diferente.

**0**: este descriptor de archivo representa la entrada estándar (=> entrada estándar, el terminal). Este es el descriptor de archivo utilizado al leer la entrada del usuario desde el terminal.

**1**: este descriptor de archivo representa la salida estándar (=> salida estándar, el terminal). Este es el descriptor de archivo utilizado al escribir en la terminal*.

**2**: este descriptor de archivo representa el stderr (=> salida de error estándar, el terminal). Este es el descriptor de archivo que se utiliza al escribir un error en la terminal; la información se escribe de la misma manera, pero un programa que registra errores en un archivo puede redirigir todo lo escrito en el descriptor de archivo stderr a un archivo. El sistema operativo lo gestiona de otra manera.

## Funciones

## Open()

      #include <fcntl.h>

Open es una función que se utiliza para abrir un archivo en un modo específico (como lectura, escritura, etc.). 

* Se le proporciona un path al archivo y flags que determinan el modo de apertura.

        int open (const char path, int flags [, int mode ]);
  
### Componentes

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

## Read()
La función tiene un prototipo de esta manera:

        ssize_t read(int fildes, void buf, size_t nbyte);

Esta función intenta leer nbytebytes de datos del objeto al que hace referencia el descriptor fildesen el búfer al que apunta buf. La función read() comienza en una posición dada por el puntero asociado con fildes. Al final, el puntero se incrementa según el número de bytes ( nbyte) realmente leídos.


## Variables estáticas en C

Las variables estáticas tienen la propiedad de preservar su valor incluso después de que estén fuera de su alcance. Por lo tanto, una variable estática conserva su valor anterior en su ámbito anterior y no se inicializa nuevamente en el nuevo ámbito. 

Sintaxis:

      static data_type var_name = var_value;

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

## Asignación de memoria dinámica en C

Es el procedimiento en el que el tamaño de una estructura de datos (como una matriz) se cambia durante el tiempo de ejecución. Existen **cuatro funciones** en C definidas en el archivo de encabezado **<stdlib.h>** para facilitar este proceso.

### Malloc: 
Se utiliza para asignar dinámicamente un único bloque grande de memoria con el tamaño especificado. 
*  Devuelve un puntero de tipo void que se puede convertir en un puntero de cualquier forma. No inicializa la memoria en el momento de la ejecución, por lo que inicialmente ha inicializado cada bloque con el valor basura predeterminado. 

Ejemplo:

      ptr = (cast-type) malloc(byte-size)**

### Calloc: 
El método "calloc" o "asignación contigua" en C se utiliza apra asignar dinamicamente el número especificado de bloques de memoria del tipo especificado. 
* Es muy similar a malloc(), pero tiene dos puntos diferentes:
* inicializa cada bloque con un valor predeterminado '0'
* Tiene dos parámetros o argumentos en comparación con malloc()

        ptr = (cast-type*)calloc(n, element-size);**

Ejemplo:

       ptr = (float*)calloc(25, sizeof(float));**
* Este parámetro asigna espacio contiguo en una memoria de 25 elementos cada uno con el tamaño de float

### Free: 

      free(ptr);

Se utiliza para desasignar dinámicamente la memoria. La memoria asignada mediante las funciones malloc() y calloc() no se desasigna por sí sola. Por lo tanto, se utiliza el método free() siempre que se realiza la asignación de memoria dinámica. Ayuda a reducir el desperdicio de memoria liberándola.

### Realloc:

Se utiliza para cambiar dinámicamente la asignación de memoria de una memoria previamente asignada. 
* En otras palabras, si la memoria previamente asignada con la ayuda de malloc o calloc es insuficiente, se puede utilizar realloc para reasignar memoria dinámicamente. 
* La reasignación de memoria mantiene el valor ya presente y los nuevos bloques se inicializarán con el valor basura predeterminado.

      ptr = realloc(ptr, newSize);**

## Diseño de memoria de programas C

Una representación de memoria típica de un programa C consta de las siguientes secciones.

### Segmento de texto:  

Un segmento de texto, también conocido como segmento de código o simplemente como texto, es una de las secciones de un programa en un archivo objeto o en la memoria, que contiene instrucciones ejecutables.
   * Como región de memoria, se puede colocar un segmento de texto debajo del *heap* o el *stack* para evitar que los montones y los desbordamientos de pila lo sobrescriban.

Por lo general, el segmento de texto se puede compartir, por lo que solo es necesario que haya una copia en la memoria para los programas que se ejecutan con frecuencia, como los editores de texto, el compilador de C, los shells, etc. Además, el segmento de texto suele ser de sólo lectura, para evitar que un programa modifique accidentalmente sus instrucciones.

### Segmento de datos inicializados:  
Segmento de datos inicializados, generalmente llamado simplemente *segmento de datos*. 
* Un segmento de datos es una parte del espacio de direcciones virtuales de un programa, que contiene *las variables globales* y *las variables estáticas* que inicializa el programador.
 * Ten en cuenta que el segmento de datos no es de solo lectura, ya que los valores de las variables se pueden modificar en tiempo de ejecución.
  * Este segmento se puede clasificar además en el área de solo lectura inicializada y el área de lectura-escritura inicializada.

### Segmento de datos no inicializados: 
Segmento de datos no inicializados a menudo llamado segmento " bss ", que lleva el nombre de un antiguo operador ensamblador que significaba " bloque iniciado por símbolo ". 
* El núcleo inicializa los datos de este segmento en aritmética 0 antes de que el programa comience a ejecutar los datos no inicializados que comienzan al final del segmento de datos y contienen todas las variables globales y variables estáticas que se inicializan a cero o no tienen una inicialización explícita en el código fuente.

### Stack:  
El área del *stack* tradicionalmente estaba contigua al área del montón y crecía en la dirección opuesta; cuando el puntero del *stack* se encuentra con el puntero del montón, se agota la memoria libre. 
 * Con los grandes espacios de direcciones modernos y las técnicas de memoria virtual, se pueden colocar casi en cualquier lugar, pero normalmente siguen creciendo en direcciones opuestas.

* El área de stack contiene la pila de programas, una estructura LIFO, normalmente ubicada en las partes superiores de la memoria. 
 * En la arquitectura de computadora PC x86 estándar, crece hacia la dirección cero; en algunas otras arquitecturas, crece en la dirección opuesta.
  * Un registro de “puntero de pila” rastrea la parte superior del stack; se ajusta cada vez que se “empuja” un valor a la pila.
   * El conjunto de valores enviados para una llamada de función se denomina "marco de pila"; Un marco de pila consta como mínimo de una dirección de remitente.

En resumen, es donde se almacenan las variables automáticas, junto con la información que se guarda cada vez que se llama a una función. 
* Cada vez que se llama a una función, la dirección a dónde regresar y cierta información sobre el entorno de la persona que llama, así como, algunos de los registros de la máquina, se guardan en el *stack*.
 * La función recién llamada asigna espacio en la pila para sus variables automáticas.
  * Así es como pueden funcionar las funciones recursivas en C. Cada vez que una función recursiva se llama a sí misma, se utiliza un nuevo marco de *stack*, por lo que un conjunto de variables no interfiere con las variables de otra instancia de la función.

### Heap:  
El heap es el segmento donde suele tener lugar la asignación de memoria dinámica.
* El área del heap comienza al final del segmento BSS y crece hasta direcciones más grandes desde allí.
 * El área del *heap* es administrada por *malloc*, *realloc* y *free*, que pueden usar las llamadas al sistema brk y sbrk para ajustar su tamaño.
 * Tenga en cuenta que el uso de brk/sbrk y un único “área del heap” no es necesario para cumplir con *malloc*/*realloc*/*free*.
 * también se pueden implementar usando *map* para reservar regiones potencialmente no contiguas de memoria virtual en el espacio de direcciones virtuales del proceso).
 * El área del *heap* es compartida por todas las bibliotecas compartidas y los módulos cargados dinámicamente en un proceso.

Fuente: https://42-cursus.gitbook.io/guide/rank-01/get_next_line

# GET_NEXT_LINE

La función get_next_line lee una línea desde un descriptor de archivo dado.
- La línea se define como una secuencia de caracteres terminada por '\n' o EOF (fin de archivo).
- La función se utiliza en un bucle para leer un archivo línea por línea.

## Aclaración:

El desarrollo de la función 'get next line' presentado en este manual es solo una de las múltiples formas posibles de implementarlo. 
* La programación es un campo amplio y flexible, y siempre hay múltiples enfoques para resolver un problema.
* Este método ha sido elegido por su simplicidad y facilidad de comprensión, teniendo en cuenta mi nivel de experiencia como principiante.
* He priorizado la claridad y la robustez del código, lo que me ha permitido aprender y solucionar errores de manera efectiva.
* Aunque es cierto que algunas líneas podrían ser reducidas y las funciones auxiliares podrían ser más dinámicas para hacer el código más compacto, he optado por un enfoque que maximiza la protección contra errores.
* Sin embargo, animo a quienes acudais a este manual a explorar y entender otras posibles soluciones que puedan optimizar aún más el código.

## Funciones auxiliares

### ft_memcpy

Esta función se utiliza para copiar bloques de memoria de un lugar a otro. 
* En el contexto de get_next_line, se utiliza en la función que inicia la línea, para copiar una cadena a una nueva cadena de texto.

	void	*ft_memcpy(void *dst, const void *src, size_t n)
	{
		unsigned char	*d;
		unsigned char	*s;
	
		if (!dst && !src)
			return (NULL);
		d = (unsigned char *)dst;
		s = (unsigned char *)src;
		while (n--)
			*d++ = *s++;
		return (dst);
	}
 
* Asignas un puntero al inicio de la cadena de destino.
* Asigna un puntero al inicio de la cadena de origen.
* Comrpueba que destino e inicio no estén vacías. Si es así, returna NULL
* Castea las cadenas como unsigned char
* copia n bytes de la cadena de origen a la cadena de destino.
* Devuelve la cadena de destino


### ft_bzero

* Aplicada a get_next_line, esta función se utiliza para limpiar el buffer antes de leer datos en él con la función read. 
* Esto es importante para asegurarse de que los datos de lecturas anteriores no interfieran con los datos actuales que se están leyendo.
* También se utiliza para limpiar el buffer temporal cuando se encuentra un error de lectura o al final de la lectura.
* Esto ayuda a mantener la integridad de los datos y a evitar posibles errores o comportamientos inesperados.

  
		void ft_bzero(void *s, size_t n) 
		{ 
		while (n--) 
		*(char *)s++ = 0; 
		}

#### Ventajas:

**Control preciso:** 

* ft_bzero te permite tener un control preciso sobre cuántos bytes quieres poner a cero. 
* Esto es útil cuando solo necesitas limpiar una parte específica de la memoria.
  
**Rapidez:**
* ft_bzero es generalmente más rápido que calloc para bloques de memoria pequeños porque no necesita asignar memoria.

#### Desventajas:

* No asigna memoria: A diferencia de *calloc*, ft_bzero no asigna memoria.
* Solo pone a cero la memoria ya asignada.
* Si necesitas asignar y poner a cero la memoria al mismo tiempo, tendrías que usar una función de asignación de memoria (como malloc) y luego ft_bzero, lo cual requiere dos llamadas a funciones en lugar de una.


### ft_strlcpy_gnl

* En tu código get_next_line, esta función se utiliza en dos lugares:
* Para copiar el resto de la línea después del final de la línea al buffe temporal para su uso en la próxima llamada a get_next_line.
* Para copiar la línea actual del buffer temporal a la línea de texto antes de leer más datos en el buffer temporal.
  

		void ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize) 
		{ 
		size_t i;
		
		i = 0;
		if (dstsize > 0)
		{
			while (src[i] && i < dstsize - 1)
			{
				dst[i] = src[i];
				i++;
			}
			dst[i] = '\0';
		}

* Compruebas si el tamaño de la cadena de destino es mayor que 0.
* Copias hasta dstsize -1 caracteres de la cadena de origen a la cadena de destino.
* Terminas la cadena de destino con '\0'

### ft_strjoin_gnl

* Esta función se utiliza para concatenar dos cadenas.
* En get next line esta función se utiliza para unir la línea actual de texto con el buffer leído.
* Esto es útil cuando una línea se extiende más allá del tamaño del buffer, por lo que necesitas leer el buffer varias veces y unir los resultados para obtener la línea completa.

		char *ft_strjoin_gnl(char *s1, char *s2, int *eol_loc) { char *result; size_t len1; size_t len2;
		
		if (!s1 || !s2)
			return (NULL);
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (!result)
		{
			free(s1);
			return (NULL);
		}
		ft_memcpy(result, s1, len1);
		free(s1);
		ft_memcpy(result + len1, s2, len2 + 1);
		if (len1 + len2 > 0 && *(result + len1 + len2 - 1) == '\n')
			*eol_loc = 0;
		return (result);
		}

* Calcula la longitud de las dos cadenas de entrada.
* Asigna memoria para la nueva cadena, que es la suma de las longitudes de las dos cadenas de entrada más 1 para el carácter nulo de terminación.
* Copia la primera cadena a la nueva cadena.
* Copia la segunda cadena a la nueva cadena, comenzando donde terminó la primera cadena.
* Devuelve la nueva cadena.

## Funciones principales
   
### Algunos conceptos básicos:

**buffer_tmp:** Esta variable representa una cadena estática que almacena caracteres leídos, los cuales aún no se han devuelto. Se llena en cada llamada a la función get_next_line.

**eol_position:** Esta variable representa un puntero a entero que indica la ubicación del carácter de fin de línea ('\n') en buffer. Si no hay '\n', se establece en -1.

**line_text:** Esta variable representa una cadena que se devolverá. Se inicializa a partir de buffer_tmp y se le concatenan más caracteres hasta que se encuentra un '\n' o se llega al final del archivo.

**buffer:** Es una región de memoria que almacena temporalmente los datos leídos. En get_next_line, se lee un bloque de datos en buffer, se busca un '\n', se extrae la línea y se prepara buffer para la próxima lectura. 
* Esto permite la lectura en bloques y el manejo de líneas que son más largas que el tamaño de buffer.
  
**size_t:** Es un tipo de dato entero sin signo que se utiliza para representar tamaños de objetos. Es el tipo de resultado devuelto por el operador sizeof.

**ssize_t:** Es un tipo de dato entero con signo que se utiliza en ciertas funciones que pueden devolver un valor negativo, como read o write, donde un valor negativo indica un error.

**&:** En el lenguaje de programación C, el operador & se utiliza para obtener la dirección de memoria de una variable o de un elemento específico en una matriz. 
* Proporciona un puntero a la ubicación de memoria de la variable o elemento, permitiendo operaciones directas sobre esa ubicación de memoria.

**static:** Es una palabra clave en C que se utiliza para dar a las variables una duración de almacenamiento estático, lo que significa que mantienen su valor entre las llamadas a funciones.

### Aclaraciones sobre mi archivo .h

#ifndef BUFFER_SIZE y #define BUFFER_SIZE 512: Este bloque verifica si la macro BUFFER_SIZE ya está definida. Si no lo está, se define con el valor 512. BUFFER_SIZE puede ser utilizada en el código para especificar el tamaño de un buffer.

#if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1 y #undef BUFFER_SIZE y #define BUFFER_SIZE 512: Este bloque verifica si el valor de BUFFER_SIZE es mayor que 125000 o menor que 1. Si alguna de estas condiciones se cumple, BUFFER_SIZE se redefine con el valor 512. Esto asegura que BUFFER_SIZE siempre tenga un valor válido.

#ifndef MAX_OPEN_FILES y #define MAX_OPEN_FILES 512: Este bloque verifica si la macro MAX_OPEN_FILES ya está definida. Si no lo está, se define con el valor 512. MAX_OPEN_FILES puede ser utilizada en el código para limitar el número de archivos que el programa puede tener abiertos simultáneamente.

Acerca del pre-procesador
El preprocesador en C es una fase inicial en el proceso de compilación que maneja ciertas características del código fuente antes de que este sea pasado al compilador. Las directivas del preprocesador son líneas en el código fuente que comienzan con un signo de #.

Las tareas principales del preprocesador incluyen:

Inclusión de archivos: A través de la directiva #include, el preprocesador inserta el contenido de un archivo especificado en el lugar donde se encuentra la directiva.

Definición de macros: Mediante la directiva #define, el preprocesador puede reemplazar una macro por un valor o una expresión especificada.

Condiciones de compilación: Con las directivas #if, #ifdef, #ifndef, #else, #elif y #endif, el preprocesador puede incluir o excluir partes del código fuente en la compilación, dependiendo de si ciertas condiciones se cumplen.

Eliminación de comentarios: El preprocesador elimina todos los comentarios del código fuente.

3. 1.
char *init_stash_line(char *temp_buffer, int *eol_loc) { size_t len; char *line_text;

len = 0;
while (temp_buffer[len] && temp_buffer[len] != '\n')
	len++;
len++;
line = malloc(sizeof(char) * (len + 1));
if (!line_text)
	return (NULL);
ft_memcpy(line_text, temp_buffer, len);
line_text[len] = '\0';
if (len > 0 && line_text[len - 1] == '\n')
	*eol_loc = len - 1;
return (line_text);
}

Esta función se utiliza para inicializar una cadena de texto a partir de un buffer temporal. La función busca el primer carácter de fin de línea en el buffer temporal y copia hasta ese punto en la línea.

Se declaran las variables que se utilizarán en la función.

Una variable de tipo size_t se utilizará para almacenar la longitud de la línea que se está inicializando.
una variable tipo char puntero será la línea de texto que se devolverá.
Inicializamos nuestra variable tipo size_t a 0.

Hacemos un bucle para calcular la longitud de nuestro buffer temporal hasta el primer carácter de nueva línea ('\n') o hasta el final de la cadena

Incrementamos nuestra variable size_t en 1 para tener el carácter de nueva línea en consideración

Asignamos memoria para nuestra línea de texto con el tamaño de longitud + 1 para tener en cuenta el caracter nulo de terminación.

Copiamos la longitud de nuestro buffer_temporal a nuestra linea de texto.

Terminamos nuestra linea de texto con un carácter nulo

Si la cadena line_text no está vacía, y su último carácter es un salto de línea, se establece *eol_point a len - 1, que es la ubicación del carácter de fin de línea en line_text

Finalmente, se retorna line_text.

3. 2.
size_t find_eol_position(char *line) { size_t i;

i = 0;
if (!line)
	return (-1);
while (i < BUFFER_SIZE)
{
	if (line[i] == '\n' || line[i] == '\0')
		return (i + 1);
	i++;
}
return (i);
}

Esta función se utiliza para encontrar la ubicación del carácter de fin de línea ('\n') en el buffer de lectura. Esta ubicación se utiliza para determinar cuántos caracteres del buffer se deben concatenar a la línea actual y cuántos caracteres se deben mover al inicio del buffer para la próxima lectura.

Se declara e inicializa la variable i, que se utilizará para iterar sobre la cadena.
Comprobamos si line es NULL. Si es así, devuelve -1. Esto es una precaución para evitar errores si se llama a locale_eol con un argumento NULL.
Hacemos un bucle que se utiliza para iterar sobre la cadena. Este se detiene cuando i alcanza BUFFER_SIZE, lo que significa que ha llegado al final del buffer.
Dentro del bucle, esta comprobamos si el carácter actual es un carácter de fin de línea ('\n') o un carácter nulo ('\0'). Si es así, devuelve i + 1, que es la ubicación del carácter de fin de línea en la cadena o el final de la cadena si no se encontró un carácter de fin de línea-
Luego se incrementa i en cada iteración del bucle
Si el bucle termina sin encontrar un carácter de fin de línea o un carácter nulo, se devuelve i, que es igual a BUFFER_SIZE. Esto indica qque se ha llegado al final del buffer sin encontrar unn carácter de fin de línea.
3. 3.
char *read_and_extract_line (char *line, char *buffer_tmp, int *eol_position, int fd) { char buffer[BUFFER_SIZE + 1]; ssize_t read_check; size_t line_size;

while (*eol_loc == -1)
{
	ft_bzero(buffer, (BUFFER_SIZE + 1));
	read_check = read(fd, buffer, BUFFER_SIZE);
	if (read_check == -1)
	{
		free(line);
		ft_bzero(stash, (BUFFER_SIZE + 1));
		return (NULL);
	}
	line_size = find_eol_position(buffer);
	ft_strlcpy_gnl(stash, &buffer[line_size], (BUFFER_SIZE + 1));
	buffer[line_size] = '\0';
	line = ft_strjoin_gnl(line, buffer, eol_loc);
	if (read_check == 0)
	{
		ft_bzero(stash, BUFFER_SIZE + 1);
		break ;
	}
}
return (line);
}

Esta función se utiliza para leer de un archivo y extraer líneas del buffer de lectura. Trabaja en conjunto con varias funciones auxiliares para implementar la funcionalidad de lectura línea por línea.

Se inicializa un buffer de lectura de tamaño fijo.
Se inicializa una variable para almacenar el número de bytes leídos de la llamada a la función de lectura.
Se inicializa una variable para almacenar la longitud de la línea que se está extrayendo del buffer.
Se ejecuta un bucle mientras no se haya encontrado un carácter de fin de línea en la línea actual.
Se llama a una función para establecer a cero todos los bytes en el buffer.
Se llama a la función de lectura para leer hasta un número fijo de bytes de datos del archivo en el buffer. El resultado de la operación de lectura se almacena en la variable correspondiente.
Si se produce un error al leer del archivo, se libera la memoria asignada a la línea, se limpia el buffer y se devuelve NULL.
Se llama a una función para encontrar la ubicación del carácter de fin de línea en el buffer.
Se utiliza una función para transferir cualquier dato no procesado en el buffer, que se encuentra después de una posición específica, a un buffer temporal para su procesamiento en la próxima llamada a la función.
Se termina el buffer con un carácter nulo en la ubicación del carácter de fin de línea.
Se concatena la cadena del buffer hasta una posición específica a la cadena de línea existente. El resultado se almacena de nuevo en la cadena de línea.
Si se ha llegado al final del archivo, se limpia el buffer y se sale del bucle.
Finalmente, se devuelve la cadena de línea.
3. 4.
char *get_next_line(int fd) { static char stash[BUFFER_SIZE + 1]; char *line; int eol_loc;

if (fd < 0 || BUFFER_SIZE <= 0)
	return (NULL);
eol_loc = -1;
line = init_line(stash, &eol_loc);
if (!line)
	return (NULL);
ft_strlcpy_gnl(stash, &stash[eol_loc + 1], BUFFER_SIZE + 1);
line = extract_line(line, stash, &eol_loc, fd);
if (!line || line[0] == '\0')
{
	free(line);
	return (NULL);
}
return (line);
}

Esta función se utiliza para leer una línea a la vez de un archivo. Aquí está la descripción genérica y concisa para tu manual de procesos:

Se inicializa un buffer estático para almacenar cualquier dato no procesado de lecturas anteriores.
Se inicializa una variable para almacenar la línea que se está leyendo.
Se inicializa una variable para almacenar la ubicación del carácter de fin de línea.
Se comprueba si el descriptor de archivo es válido y si el tamaño del buffer es mayor que cero. Si alguna de estas condiciones no se cumple, se devuelve NULL.
Se asigna un valor inicial a la variable que almacena la ubicación del carácter de fin de línea.
Se llama a una función para inicializar la línea con cualquier dato no procesado en el buffer estático. Si la inicialización falla, se devuelve NULL.
Se copia cualquier dato no procesado en el buffer estático, que se encuentra después de la ubicación del carácter de fin de línea, de vuelta al buffer estático para su procesamiento en la próxima llamada a la función.
Se llama a una función para leer del archivo y extraer una línea.
Si la línea es NULL o está vacía, se libera la memoria asignada a la línea y se devuelve NULL.
Finalmente, se devuelve la línea leída.
