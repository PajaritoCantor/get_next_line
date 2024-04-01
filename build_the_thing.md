1. GET_NEXT_LINE
La función get_next_line lee una línea desde un descriptor de archivo dado. La línea se define como una secuencia de caracteres terminada por '\n' o EOF (fin de archivo). La función se utiliza en un bucle para leer un archivo línea por línea.

2. Orden de construcción de las funciones auxiliares

2. 1. Funciones auxiliares

2. 1. 1. ft_memcpy

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
* Asigna un puntero al inicio de la cadena de destino
* Asigna un puntero al inicio de la cadena de origen
* copia n bytes de la cadena de origen a la cadena de destino
* Devuelve la cadena de destino

Esta función se utiliza para copiar bloques de memoria de un lugar a otro. En el contexto de get_next_line, se utiliza en la función init_line para copiar la cadena stash a la nueva cadena line

 2. 1. 2. ft_bzero

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

* Asigna un puntero al inicio de memoria
* Establece los primeros n bytes de memoria a '\0'

Esta función se utiliza para inicializar bloques de memoria. En get_next_line, se utiliza en la función extract_line para inicializar el buffer antes de leer del archivo y para limpiar el stash cuando se ha llegado al final del archivo

2. 1. 3. ft_strlcpy_gnl

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

* Comprueba si el tamaño de la cadena de deestino es mayor que 0
* Copia hasta dstsize -1 caracteres de la cadena de origen a la cadena de destino
* Termina la cadena de destino con '\0'

Esta función se utiliza para copiar una cadena a otra. En get_next_line, se utiliza en init_line para copiar el stash a la line y en get_next_line para copiar el resto del stash despuès del carácter de fin de línea al stash

2. 1. 4. 

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

* Calcula la longitud de las dos cadenas de entrada
* Asigna memoria para la nueva cadena, que es la suma de las longitudes de las dos cadenas de entrada más 1 para el carácter nulo de terminación
* Copia la primera cadena a la nueva cadena
* Copia la segunda cadena a la nueva cadena, comenzando donde terminó la primera cadena
* Devuelve la nueva cadena

Esta función se utiliza para concatenar dos cadenas. En get_next_line, se utiliza en extract_line para concatenar el buffer leído del archivo a la line.

3. Funciones principales

* Conceptos:

- stash: Es una cadena estática que se utiliza para almacenar los caracteres que se han leído per que aún no se han devuelto. En cada llamada a get_next_line, se lee una línea de stash antes de leer el archivo.
- eol_loc: Es un puntero a un entero que se utiliza para almacenar la ubicación del carácter de fin de línea ('\n') en line. Si no hay un carácter de fin de línea en line, eol_loc se establece en -1.
- line: Es la cadena que se va a devolver. Se inicializa a partir de stash y luego se leen y concatenan más caracteres de la entrada hasta que se encuentra un carácter de fin de línea o se llega del archivo 
- Buffer: Es la región de memoria que se utiliza para almacenar temporalmente los datos leídos del archivo antes de procesarlos. Cuando se llama a get_next_line, se lee un bloque de daatos del archivo al buffer, luego la función busca un carácter de fin de línea en el buffer, y si encuentra uno se extrae la línea del buffer y se prepara el buffer para la próxima lectura moviendo los caracteres después del carácter de fin de línea al inicio del buffer. 
	* El uso del buffer en get_next_line permite leer y procesar los datos en bloques en lugar de un carácter a la vez, lo que puede ser más eficiente, especialmente para archivos grandes. Además, el buffer permite a get_next_line manejar líneas que son más largas que el tamaño del buffer, ya que puede leer múltiples bloques de datos del archivo para una sola línea.

3. 1. 

char	*init_line(char *stash, int *eol_loc)
{
	size_t	len;
	char	*line;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, len);
	line[len] = '\0';
	if (len > 0 && line[len - 1] == '\n')
		*eol_loc = len - 1;
	return (line);
}

Esta función se utiliza para inicializar la line a partir del stash. Busca el primer carácter de fin de línea en el stash y copia hasta ese punto en la line.

* size_t len; char *line: Aquí se declaran las variables que se utilizarán en la función.
	* len se utilizará para almacenar la longitud de la línea que se está inicializando.
	* line será la línea que se devolverá.
* while (stash[len] && stash[len] != '\n') len++;: Este bucle se utiliza paa calcular la longitud de la linea hasta el primer carácter de nueva línea ('\n') o hasta el final de la cadena stash.
* len++; line = malloc(sizeof(char) * (len + 1));: Aquí se incrementa len en uno para tener en cuenta el carácter de nueva línea, y luego se asigna memoria para line con el tamaño de len más uno para el caracter nulo de terminación ('\0').
* ft_memcpy(line, stash, len);: Esta línea copia len caracteres de stash a line.
* line[len] = '\0';: Aquí se termina line con un carácter nulo
* if (len > 0 && line[len - 1] == '\n') *eol_loc = len - 1;: Si el último carácter de line es una carácter de nueva línea, se establece *eol_loc a len - 1, que es la ubicación del carácter de fin de línea en line
* return (line);: Finalmente, se devuelve line

3. 2. 

size_t	locate_eol(char *line)
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

* size_t i = 0;: Aquí se declara e inicializa la variable i, que se utilizará para iterar sobre la cadena.
* if (!line) return (-1);: Esta línea comprueba si line es NULL. Si es así, devuelve -1. Esto es una precaución para evitar errores si se lama a locale_eol con un argumento NULL.
* while (i < BUFFER_SIZE): Este bucle se utiliza para iterar sobre la cadena. Se detiene cuando i alcanza BUFFER_SIZE, lo que significa que ha llegado al final del buffer.
* if (line[i] == '\n' || line[i] == '\0') return (i + 1);: Dentro del bucle, esta línnea comprueba si el carácter actual es un carácter de fin de línea ('\n') o un carácter nulo ('\0'). Si es así, devuelve i + 1, que es la ubicación del carácter de fin de línea en la cadena o el final de la cadena si no se encontró un carácter de fin de línea-
* i++;: Esta línea incrementa i en cada iteración del bucle
* return (i);: Si el bucle termina sin encontrar un carácter de fin de línea o un carácter nulo, se devuelve i, que es igual a BUFFER_SIZE. Esto indica qque se ha llegado al final del buffer sin encontrar unn carácter de fin de línea.

3. 3. 

char	*extract_line(char *line, char *stash, int *eol_loc, int fd)
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
		line_size = locate_eol(buffer);
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

Esta función se utiliza para leer del archivo y extraer líneas del buffer de lectura. Trabaja en conjunto con las funciones locate_eol, ft_bzero, ft_strlcpy_gnl y ft_strjoin_gnl para implementar la funcionalidad de lectura línea por línea de get_next_line.

* char buffer[BUFFER_SIZE + 1]; ssize_t read_check; size_t line_size; 
	* buffer[BUFFER_SIZE + 1] es el buffer de lectura.
	* read_check se utilizará para almacenar el resultado de la llamada a read.
	* line_size se utilizará para almacenar la longitud de la línea que se está extrayendo del buffer.
* while (*eol_loc == -1): Este bucle se ejecuta mientras no se haya encontrado un carácter de fin de línea en la línea actual.
* ft_bzero(buffer, (BUFFER_SIZE + 1));: Aquí se lee del archivo al buffer. read_check se establece en el número de bytes leídos o -1 si se produce un error.
* if (read_check == -1): Este bloque de código se ejecuta si se produce un error al leer del archivo. Libera la memoria asignada a line, limpia stash y devuelve NULL.
* line_size = locate_eol(buffer);: Aquí se llama a locate_eol para encontrar la ubicación del carácter de fin de línea en el buffer.
* ft_strlcpy_gnl(stash, &buffer[line_size], (BUFFER_SIZE + 1));: Esta línea copia el resto del buffer después del carácter de fin de línea al stash.
* buffer[line_size] = '\0';: Aquí se termina el buffer con un carácter nulo en la ubicación del carácter de fin de línea.
* line = ft_strjoin_gnl(line, buffer, eol_loc);: Esta línea concatena el buffer aa la línea actual.
* if (read_check == 0): Este bloque de código se ejecuta si se ha llegado al final del archivo. Limpia stash y sale del buche.
* return (line);: Finalmente, se devuelve line.

3. 4. 

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

get_next_line utiliza las funciones init_line, ft_strlcpy_gnl y extract_line para implementar la funcionalidad de lectura línea por línea. Init_line se utiliza para inicializar line con los caracteres de stash, ft_strlcpy_gnl se utiliza para mover los caracteres en stash, y extract_line se utiliza para leer más caracteres del archivo y añadirlos a line.

* static char stash[BUFFER_SIZE + 1]; char *line; int eol_loc;:
	* stash[BUFFER_SIZE + 1];: Es un buffer estático que se utiliza paara almacenar los caracteres que se han leído pero que aún no se han devuelto.
	* line;: Es un puntero a la línea que se está construyendo
	* eol_loc;: Es la ubicación del carácter de fin de línea en stash.
* if (fd < 0 || BUFFER_SIZE <= 0) return NULL;: Esta línea comprueba si el descriptor de archivo es válido y si el tamaño del buffer es mayor que cero. si alguna de estas condiciones no se cumple, devuelve NULL.
* eol_loc = -1; Se inicializa a -1, lo que indica que aún no se ha encontrado un carácter de fin de línea.
* line = init_line(stash, &eol_loc);: Aquí se llama a init_line para inicializar line con los caracteres de stash hasta el primer carácter de línea
* if (!line) return (NULL);: Esta línea comprueba si init_line devolvió NULL, lo que indicaría un error. Si es así, devuelve NULL.
* ft_strlcpy_gnl(stash, &stash[eol_loc + 1], BUFFER_SIZE + 1);: Esta línea mueve los caracteres en stash después del carácter de fin de línea al inicio de stash.
* line = extract_line(line, stash, &eol_loc, fd);: Aquí se llama a extract_line para leer más caracteres del archivo y añadirlos a line hassta que se encuentre un carácter de fin de línea.
* if (!line || line [0] == '\0'): Este bloque de código se ejecuta si extract_line devolvió NULL o una línea vacía. En ambos casos, libera la memoria asignada a line y devuelve NULL.
return (line);: Finalmente, se devuelve line.
