
======================
INPUT
======================

Procesando inputs:

1. Leemos la linea de comandos (readline), y vamos separando el input en nodos.
2. Al crear los nodos leemos y guardamos el tipo de comando (t_cmd: Literal, programa, argumentos...).
3. Creé un meta tipo que también guardamos en el nodo, (t_meta) para distinguir entre los comandos bin que estamos montando (ls, pwd, echo..), los externos (cualquier binario), las redirecciones (| o > <), etc. (esto tiene sentido mas adelante).

en este punto tenemos, por ejemplo:

[42-ms /minishell] ./push_swap 5 2 7 | ./checker 5 2

lista:
[./push_swap] -> [5] -> [2] -> [7] -> [|] -> [./checker] -> [5] -> [2]

la cosa es que inplementando los pipes, me di cuenta que sería un tema cuando enlacemos mas de un pipe. Despues de montarme varias opciones, me di cuenta que podía hacer funcionar los pipes de manera generica, pero corriendolos así:

[42-ms /minishell] | ./push_swap 5 2 7 ./checker 5 2

claro, al ir procesando normalmente la lista, el pipe puesto al principio permitía "iniciar" el proceso de crear un tubería antes de ejecutar los procesos que estaban involucrados. Entonces, esto ya parece un novela cutre y romántica, me acordé de los videos de la piscina. Pipes, > < >> << etc, lo que hacen es modificar el flujo de trabajo, así que me monté en la idea de transformar la lista en un flujo de trabajo que pudiesemos seguir paso a paso, una vez procesada inicialmente.

como verás los nodos tienen otras variables, por que la cosa es esta:

cargada la lista (paso 3)...

4. Modificamos la lista y la convertimos en un flujo de trabajo, se transforma de una lista simple, a una rama (un árbol binario, pero no estricto). Los nodos principales los ocupan únicamente procesos (bins, externos o redirecciones), y cada uno tiene, un lista de argumentos.. vamos que quedaría así:

 lista:
[./push_swap] -> [5] -> [2] -> [7] -> [|] -> [./checker] -> [5] -> [2]

Rama
[./push_swap] -> [|] -> [./checker]
|                       |
 -([5] -> [2] -> [7])    -([5] -> [2])

De este modo podemos ir procesando nodos, sin preocuparnos de los argumentos, ya que no estan en el medio, si no en cada rama.

5. Pero, por que siempre hay uno, el pipe vincula, modifica el comporamiento de los nodos adyacentes, que además pueden estar vinculados con otros pipes, así que: Despues de obtener el flujo, revisamos las redirecciones (esta hecho solo con pipe, pero la idea es hacerlo con todas) y escribimos estos vinculos en los nodos (vars in y out), despues de lo cual podemos eliminar el nodo que contiene el pipe como tal... con lo que quedaría:

[./push_swap] --------> [./checker]
|                       |
 -([5] -> [2] -> [7])    -([5] -> [2])

 donde cada nodo indica cual es su entrada y su salida, en caso de ser distinta a la stdin pues en lugar de ejecutar sencillamente, pues se ejecuta con un pipe al siguiente o al anterior, dependiedo.

 Bueno, después de toda esta chapa. Como tuve que toquetear mucho para hacer trabajar los pipes, ahor mismo el repo esta en modo embarrado. Si haces el make y pones comandos, ahora mismo te imprime la rama de como se va a interpretar. Espero terminar hoy de implementar los pipes en general, para que puedan ir encadenandose, y volver a la normalidad, pero procesando la rama en orden.

 Nos queda por implementar algunos buil ins (env, unset, export..), si quieres irle dando al tema, perfecto, en el peor de los casos con que arranquemos la semana con lo que tenemos pulido, seria genial.

 Por cierto, ya sabia yo. Como los build ins pueden estar entre pipes también, existe la posibilidad de que los necesitemos desde procesos hijos del propio mini. Por esa razón cada comando debería estar separado en dos partes, una que reciba el nodo desde el ./minishell normalmente y convierta los argumentos en *argv[], y otro que reciba *argv[] y lo ejecute. De ese modo podremos usar esas funciones "directamente" desde main. Creo que si intento explicarlo peor, no me sale, pero creo que esta chapa va larga.

 



=======

<dirent.h>

librería para trabajar con directorios. Estructura dirent:

struct dirent {
    ino_t          d_ino;       /* inode number */
    off_t          d_off;       /* offset to the next dirent */
    unsigned short d_reclen;    /* length of this record */
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types */
    char           d_name[256]; /* filename */
};


