Aquí está una descripción de cada función y el orden en que deberías construirlas:

1. _fill_line_buffer: Esta función lee del archivo identificado por fd hasta que encuentra un carácter de nueva línea (\n) o hasta que se ha leído todo el archivo. Concatena lo que lee en left_c. Deberías construir esta función después de ft_strchr porque la utiliza.

static char *_fill_line_buffer(int fd, char *left_c char *buffer);

Toma tres argumentos:
- Un descriptor de archivo fd
- Una cadena left_c que contiene cualquier dato que se haya leído pero que aún no se haya procesado
- Un buffer donde se almacenarán los datos leídos del archivo

    ssize_t b_read; 
    char    *tmp; 

- b_read almacena el número de bytes leídos del archivo
- tmp, se utilizará para manipular las cadenas

    b_read = 1;
    while (b_read > 0)

- b_read se inicializa a 1 y se inicia un bucle que continuará mientras b_Read sea mayor que 0. Esto significa que el bucle continuará hasta que se haya leído todo el archivo

        b_read = read(fd, buffer, BUFFER_SIZE);

Se lee del archivo fd en buffer, hasta un máximo de BUFFER_SIZE bytes. El número de bytes leídos se almacena en b_read

        if (b_read == -1)
    {
        free(left_c);
        return (0);
    }
- Si read devuelve -1, esto indica un error. En este caso, se libera left_c y se devuelve 0 para indicar el error.

else if (b_read == 0)
        break ;

Si read devuelve 0, esto indica que se ha llegado al final del archivo. En este caso, se sale del bucle.

    buffer[b_read] = '\0';

Se añade un carácter nulo al final de los datos que se acaban de leer para asegurar que buffer es una cadena válida

if (!left_c)
        left_c = ft_strdup("");

Si left_c es NULL, se inicializa a una cadena vacía

    tmp = left_c;
    left_c = ft_strjoin(tmp, buffer);
    free (tmp);
    tmp = NULL;

Se concatena buffer al final de left_c. Esto se hace utilizando una variable temporal tmp para evitar la pérdida de memoria.

 if (ft_strchr(buffer, '\n'))
        break;

Si se encuentra un carácter de nueva línea en buffer, se sale del bucle. Esto significa que se ha leído una línea completa del archivo

return (left_c)

Finalmente, se devuelve left_c, que contiene cualquier dato que se haya leído pero que aún no se haya procesado.

** La variable left_c es importante porque almacena los datos que se han leído del archivo pero que aún no se han procesado. "procesar" en get_next_line significa devolver una línea completa de texto al código que llamó a get_next_line. 

Cuando llamas a get_next_line varias veces, left_c permite que la función recuerde los datos que se leyeron en las llamadas anteriores pero que aún no se han devuelto. 

Esto es útil porque read puede leer más datos de los que puedes procesar en una sola llamada a get_next_line.
* Por ejemplo, si read lee dos líneas de texto pero sólo puedes devolver una línea por llamada a get_next_line, puedes almacenar la segunda línea en left_c y devolverla en la próxima llamada a get_next_line

Así mismo, left_c también es util para manejar el caso en que los datos que se leen del archivo no terminan con un carácter de nueva línea. En este caso, puedes almacenar los datos en left_c y devolverlos en la próxima llamada a get_next_line


2. _set_line: Esta función busca el final de la línea en line_buffer y toma una subcadena desde el final de la línea hasta el final de line_buffer. Esto se convierte en lo que queda de nuestra línea (left_c). Deberías construir esta función después de _fill_line_buffer porque se utiliza en la función principal get_next_line.

static char *_set_line(char *line_buffer);
{
    char    *left_c; // 1. Declara un puntero a char llamado left_c. Este será el búfer restante después de leer una línea.
    ssize_t     i; // 2. Declara una variable de tipo ssize_t llamada i. Esta será usada para iterar sobre line_buffer.

    i = 0; // 3. Inicializa i a 0. Esto es para empezar a iterar desde el principio de line_buffer.

    // 4. Este es un bucle while que continúa hasta que se encuentra un carácter de nueva línea ('\n') o un carácter nulo ('\0') en line_buffer.
    while(line_buffer[i] != '\n' && line_buffer[i] != '\0')
        i++; // 5. Incrementa i en cada iteración del bucle.

    // 6. Comprueba si el carácter en la posición i de line_buffer es un carácter nulo, o si el segundo carácter de line_buffer es un carácter nulo.
    // Si alguna de estas condiciones es verdadera, la función devuelve NULL.
    if (line_buffer[i] == 0 || line_buffer[1] == 0)
        return (NULL);

    // 7. Llama a la función ft_substr para crear una subcadena de line_buffer que comienza en la posición i + 1 y tiene una longitud de la longitud de line_buffer menos i.
    // Esta subcadena se asigna a left_c.
    left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);

    // 8. Comprueba si el primer carácter de left_c es un carácter nulo. Si es así, libera la memoria asignada a left_c y establece left_c a NULL.
    if (*left_c == 0)
    {
        free(left_c);
        left_c = NULL;
    }

    // 9. Establece el carácter en la posición i + 1 de line_buffer a un carácter nulo. Esto efectivamente termina la línea en line_buffer.
    line_buffer[i + 1] = 0;

    // 10. Devuelve left_c, que es la subcadena de line_buffer después de la línea leída.
    return (left_c);
}

3. get_next_line: Esta es la función principal que utiliza las otras tres funciones. Lee una línea del archivo identificado por fd y devuelve esa línea. Deberías construir esta función al final.

- fill_line_buffer

1. Inicializa una variable b_read a 1 para entrar en el bucle while.

2. Entra en un bucle while que continúa mientras b_read sea mayor que 0. Esto significa que continuará leyendo del archivo hasta que no haya más que leer.

3. Dentro del bucle, utiliza la función read para leer BUFFER_SIZE caracteres del archivo en el búfer. Almacena el número de caracteres leídos en b_read.

4. Comprueba si b_read es -1, lo que indicaría un error en la lectura del archivo. Si es así, libera left_c y devuelve NULL.

5. Si b_read es 0, significa que has llegado al final del archivo. En este caso, rompe el bucle.

6. Asegúrate de que el último carácter del búfer sea el carácter nulo (\0), para que el búfer sea una cadena válida en C.

7. Si left_c es NULL, significa que es la primera vez que pasas por el bucle. En este caso, duplica el contenido del búfer en left_c.

8. Si left_c no es NULL, significa que ya has leído algunos caracteres del archivo. En este caso, concatena el contenido del búfer a left_c.

9. Comprueba si el búfer contiene el carácter de nueva línea (\n). Si es así, rompe el bucle.

10. Al final de la función, devuelve left_c, que contiene todos los caracteres que has leído del archivo.