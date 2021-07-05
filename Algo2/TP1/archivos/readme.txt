Funcionalidad del programa:
El trabajo realizado consiste en la creacion de herramientas capaces de permitirle
al usuario acceder a informacion respecto a salones que almacenan entrenadores
con sus respectivas victorias y Pokemones en su poder. Sera posible obtener los 
entrenadores que cumplan con una cuota minima de victorias solicitadas, asi como tambien
agregar nuevos al salon para posteriormente almacenarlos en un nuevo archivo.

----------------------------------------------------------------------------------------

Heap:
El heap es un tipo de memoria dinamica que, como su nombre indica, puede
variar su tamaño durante la ejecucion del programa, asi mismo, los datos 
reservados en ellos solo permaneceran en ella durante el tiempo de ejecucion.
Para poder acceder a ella es necesario hacer uso de punteros los cuales
tendran su memoria asignada con la funcion malloc() o realloc(), una vez 
que dejamos de hacer uso de estas variables debemos liberarlas con free().
Aqui almacenaremos la memoria que ocupe mucho espacio, o bien, la que deseamos
almacenar mas alla del tiempo de ejecucion de la funcion encargada de crearla.

----------------------------------------------------------------------------------------

Stack:
El stack es un bloque de memoria fija cuyo tamaño no varia a lo largo de 
la ejecucion de nuestro programa, es en este sector el lugar donde se almacenan
las variables creadas por una funcion hasta que la misma finaliza. En ella 
tambien habitan los punteros a la memoria dinamica (heap). Si bien el uso 
de memoria en el heap es de mayor facilidad gracias a que la misma se libera 
sola, puede resultar se un problema para programas que requiere de mucha 
memoria, ya que podria no ser suficiente el espacio disponible en el stack 
provocando un "overflow", provocando que nuestro programa se finalice abruptamente
causando la perdida con los datos que estabamos trabajando.

----------------------------------------------------------------------------------------

Malloc:
Es la funcion encargada de asignarle memoria del heap a un puntero, la manera de
utilizarla es:

void* ptr = malloc(tamanio); 

el llamado resultara en que el puntero ptr este dirigido a un bloque de memoria de
"tamanio" bytes.

----------------------------------------------------------------------------------------

Realloc:
Nos permite redimensionar la memoria del heap, agrandando o achicando el bloque de
memoria al que apuntere el puntero pasado como argumento, si este es NULL, la funcion
actuara como malloc.

ptr = realloc(ptr, tamanio*2)

La linea anterior resultara que el puntero anterior de tamaño "tamanio" pase a ser el
doble. Algo importante de realloc es que al ejecutarse no pierde el contenido que
almacenaba previamente.

----------------------------------------------------------------------------------------

Free:
Asi como asignamos memoria en el heap con malloc, debemos liberarla una vez que 
ya no hacemos uso de ella, para evitar llenar nuestra memoria con datos que ya no
tienen relevancia alguna, para ello utilizaremos free de la siguiente manera:

free(ptr);

lo que provocara que el bloque de memoria al que apuntaba "ptr" sea liberado y ya no 
ocupe espacio en nuestra memoria.

----------------------------------------------------------------------------------------

