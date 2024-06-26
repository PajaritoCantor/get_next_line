# GET_NEXT_LINE

La función get_next_line lee una línea desde un descriptor de archivo dado. 
* La línea se define como una secuencia de caracteres terminada por '\n' o EOF (fin de archivo).
* La función se utiliza en un bucle para leer un archivo línea por línea.

# INDICE

1. [Funciones auxiliares](#Funciones-auxiliares)
   
   1.1 [ft_memcpy](#ft_memcpy)
   
## Funciones auxiliares

### ft_memcpy

Esta función se utiliza para copiar bloques de memoria de un lugar a otro. En el contexto de get_next_line, se utiliza en la función que inicia la línea, para copiar una cadena a una nueva cadena de texto.

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

* Asigna un puntero al inicio de la cadena de destino.
* Asigna un puntero al inicio de la cadena de origen.
* Comrpueba que destino e inicio no estén vacías. Si es así, returna NULL
* Castea las cadenas como *unsigned char*
* copia *n* bytes de la cadena de origen a la cadena de destino.
* Devuelve *la cadena de destino*


#### ft_bzero

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

* Vr a un puntero de tipo void


* Establece los primeros n bytes de memoria a '\0'.

Esta función se utiliza para inicializar bloques de memoria. Se utiliza en la función donde leemos y extraemos una línea de texto, para inicializar el buffer antes de leer del archivo y para limpiar cuando se ha llegado al final del archivo

###












































































. ft_strlcpy_gnl**

void	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

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
}

Esta función se utiliza para copiar una cadena a otra. Se utiliza en la función que inicializa una línea de texto para copiar el buffer a la línea de texto y en la función principal get_next_line, para copiar el resto del buffer despuès del carácter de fin de línea al buffer.

* Comprueba si el tamaño de la cadena de deestino es mayor que 0
* Copia hasta dstsize -1 caracteres de la cadena de origen a la cadena de destino
* Termina la cadena de destino con '\0'


#### **2. 1. 4.**

char	*ft_strjoin_gnl(char *s1, char *s2, int *eol_loc)
{
	char	*result;
	size_t	len1;
	size_t	len2;

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

Esta función se utiliza para concatenar dos cadenas. En get_next_line, se utiliza en la función que extrae y lee una línea de texto, para concatenar el buffer leído del archivo a la línea.

* Calcula la longitud de las dos cadenas de entrada.
* Asigna memoria para la nueva cadena, que es la suma de las longitudes de las dos cadenas de entrada más 1 para el carácter nulo de terminación.
* Copia la primera cadena a la nueva cadena.
* Copia la segunda cadena a la nueva cadena, comenzando donde terminó la primera cadena.
* Devuelve la nueva cadena.


## 3. **Funciones principales**

### **Algunos conceptos:**

* buffer_tmp: Es una cadena estática que almacena caracteres leídos, los cuales aún no se han devuelto. Se llena en cada llamada a la función get_next_line.
* eol_position: Es un puntero a entero que indica la ubicación del carácter de fin de línea ('\n') en buffer. Si no hay '\n', se establece en -1.
* line_text: Es una cadena que se devolverá. Se inicializa a partir de buffer_tmp y se le concatenan más caracteres hasta que se encuentra un '\n' o se llega al final del archivo.
* buffer: Es una región de memoria que almacena temporalmente los datos leídos. En get_next_line, se lee un bloque de datos en buffer, se busca un '\n', se extrae la línea y se prepara buffer para la próxima lectura. Esto permite la lectura en bloques y el manejo de líneas que son más largas que el tamaño de buffer.
* size_t: Es un tipo de ***dato entero sin signo*** que se utiliza para representar tamaños de objetos. Es el tipo de resultado devuelto por el operador sizeof.
* ssize_t: Es un tipo de dato entero con signo que se utiliza en ciertas funciones que pueden devolver un valor negativo, como read o write, donde un valor negativo indica un error.
* &: En el lenguaje de programación C, el operador & se utiliza para obtener la dirección de memoria de una variable o de un elemento específico en una matriz. Proporciona un puntero a la ubicación de memoria de la variable o elemento, permitiendo operaciones directas sobre esa ubicación de memoria.

### **Acerca del Header**

***#ifndef GET_NEXT_LINE_BONUS_H*** y ***#define GET_NEXT_LINE_BONUS_H***: Este es un mecanismo de protección contra la inclusión múltiple. Si el archivo de encabezado ya ha sido incluido previamente, la macro ***GET_NEXT_LINE_BONUS_H*** estará definida y el preprocesador ignorará el contenido del archivo hasta encontrar el #endif correspondiente. Esto previene problemas de redefinición y otros conflictos que pueden surgir por la inclusión múltiple de un archivo de encabezado.

***#ifndef BUFFER_SIZE*** y ***#define BUFFER_SIZE*** 512: Este bloque verifica si la macro BUFFER_SIZE ya está definida. Si no lo está, se define con el valor 512. BUFFER_SIZE puede ser utilizada en el código para especificar el tamaño de un buffer.

***#if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1 y #undef BUFFER_SIZE y #define BUFFER_SIZE*** 512: Este bloque verifica si el valor de BUFFER_SIZE es mayor que 125000 o menor que 1. Si alguna de estas condiciones se cumple, BUFFER_SIZE se redefine con el valor 512. Esto asegura que BUFFER_SIZE siempre tenga un valor válido.

***#ifndef MAX_OPEN_FILES*** y ***#define MAX_OPEN_FILES*** 512: Este bloque verifica si la macro MAX_OPEN_FILES ya está definida. Si no lo está, se define con el valor 512. MAX_OPEN_FILES puede ser utilizada en el código para limitar el número de archivos que el programa puede tener abiertos simultáneamente.

### **Acerca del pre-procesador**

* El preprocesador en C es una fase inicial en el proceso de compilación que maneja ciertas características del código fuente antes de que este sea pasado al compilador. Las directivas del preprocesador son líneas en el código fuente que comienzan con un signo de **#**.

* Las tareas principales del preprocesador incluyen:

* Inclusión de archivos: A través de la directiva #include, el preprocesador inserta el contenido de un archivo especificado en el lugar donde se encuentra la directiva.

*  Definición de macros: Mediante la directiva #define, el preprocesador puede reemplazar una macro por un valor o una expresión especificada.

* Condiciones de compilación: Con las directivas #if, #ifdef, #ifndef, #else, #elif y #endif, el preprocesador puede incluir o excluir partes del código fuente en la compilación, dependiendo de si ciertas condiciones se cumplen.

* Eliminación de comentarios: El preprocesador elimina todos los comentarios del código fuente.


### **3. 1.** 

char	*init_stash_line(char *temp_buffer, int *eol_loc)
{
	size_t	len;
	char	*line_text;

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

Esta función se utiliza para inicializar una cadena de texto a partir de un buffer temporal.
La función busca el primer carácter de fin de línea en el buffer temporal y **copia** hasta ese punto en la línea.

* Se declaran las variables que se utilizarán en la función.
	* Una variable de tipo **size_t** se utilizará para almacenar la longitud de la línea que se está inicializando.
	* una variable tipo **char puntero** será la línea de texto que se devolverá.

* Inicializamos nuestra variable tipo **size_t** a 0.
* Hacemos un bucle para calcular la *longitud* de nuestro buffer temporal hasta el primer carácter de nueva línea ('\n') o hasta el final de la cadena
* Incrementamos nuestra variable *size_t* en 1 para tener el *carácter de nueva línea* en consideración
* Asignamos *memoria* para nuestra *línea de texto* con el tamaño de longitud + 1 para tener en cuenta el caracter nulo de terminación.
* Copiamos la *longitud* de nuestro *buffer_temporal* a nuestra *linea de texto*.
* Terminamos nuestra *linea de texto* con un *carácter nulo*
* Si la cadena **line_text** no está vacía, y su último carácter es un salto de línea, se establece ***eol_point** a **len - 1**, que es la ubicación del carácter de fin de línea en **line_text**
* Finalmente, se retorna **line_text**.

### **3. 2.**

size_t	find_eol_position(char *line)
{
	size_t	i;

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

* Se declara e inicializa la variable i, que se utilizará para iterar sobre la cadena.
* Comprobamos si line es NULL. Si es así, devuelve -1. Esto es una precaución para evitar errores si se llama a locale_eol con un argumento NULL.
* Hacemos un bucle que se utiliza para iterar sobre la cadena. Este se detiene cuando *i* alcanza BUFFER_SIZE, lo que significa que ha llegado al final del buffer.
* Dentro del bucle, esta comprobamos si el carácter actual es un carácter de fin de línea ('\n') o un carácter nulo ('\0'). Si es así, devuelve i + 1, que es la ubicación del carácter de fin de línea en la cadena o el final de la cadena si no se encontró un carácter de fin de línea-
* Luego se incrementa i en cada iteración del bucle
* Si el bucle termina sin encontrar un carácter de fin de línea o un carácter nulo, se devuelve i, que es igual a BUFFER_SIZE. Esto indica qque se ha llegado al final del buffer sin encontrar unn carácter de fin de línea.

### **3. 3.**

char	*read_and_extract_line (char *line, char *buffer_tmp, int *eol_position, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	read_check;
	size_t	line_size;

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

* Se inicializa un buffer de lectura de tamaño fijo.
* Se inicializa una variable para almacenar el número de bytes leídos de la llamada a la función de lectura.
* Se inicializa una variable para almacenar la longitud de la línea que se está extrayendo del buffer.
* Se ejecuta un bucle mientras no se haya encontrado un carácter de fin de línea en la línea actual.
* Se llama a una función para establecer a cero todos los bytes en el buffer.
* Se llama a la función de lectura para leer hasta un número fijo de bytes de datos del archivo en el buffer. El resultado de la operación de lectura se almacena en la variable correspondiente.
* Si se produce un error al leer del archivo, se libera la memoria asignada a la línea, se limpia el buffer y se devuelve NULL.
* Se llama a una función para encontrar la ubicación del carácter de fin de línea en el buffer.
* Se utiliza una función para transferir cualquier dato no procesado en el buffer, que se encuentra después de una posición específica, a un buffer temporal para su procesamiento en la próxima llamada a la función.
* Se termina el buffer con un carácter nulo en la ubicación del carácter de fin de línea.
* Se concatena la cadena del buffer hasta una posición específica a la cadena de línea existente. El resultado se almacena de nuevo en la cadena de línea.
* Si se ha llegado al final del archivo, se limpia el buffer y se sale del bucle.
* Finalmente, se devuelve la cadena de línea.

### **3. 4.** 

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			eol_loc;

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

* Se inicializa un buffer estático para almacenar cualquier dato no procesado de lecturas anteriores.
* Se inicializa una variable para almacenar la línea que se está leyendo.
* Se inicializa una variable para almacenar la ubicación del carácter de fin de línea.
* Se comprueba si el descriptor de archivo es válido y si el tamaño del buffer es mayor que cero. Si alguna de estas condiciones no se cumple, se devuelve NULL.
* Se asigna un valor inicial a la variable que almacena la ubicación del carácter de fin de línea.
* Se llama a una función para inicializar la línea con cualquier dato no procesado en el buffer estático. Si la inicialización falla, se devuelve NULL.
* Se copia cualquier dato no procesado en el buffer estático, que se encuentra después de la ubicación del carácter de fin de línea, de vuelta al buffer estático para su procesamiento en la próxima llamada a la función.
* Se llama a una función para leer del archivo y extraer una línea.
* Si la línea es NULL o está vacía, se libera la memoria asignada a la línea y se devuelve NULL.
* Finalmente, se devuelve la línea leída.
