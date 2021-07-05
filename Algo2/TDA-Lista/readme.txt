Una lista es un tipo de dato abstracto en el que contamos con una serie elementos, cada uno almacenado en su propio nodo, los cuales 
estan conectados entre si. El nodo ademas de almacenar un elemento, almacena la o las direcciones a otros nodos, La manera de los cuales
los nodos estes conectados varia segun el tipo de lista que utilicemos, los cuales pueden ser:

- Lista simplemente enlazada:
Consta de nodos enlazados que contienen el elemento y la direccion del nodo siguiente, haciendo que el recorrido iterativo de la lista
sea unidireccional. Sabemos cuando hemos llegado al final de la lista ya que en su ultimo nodo, el puntero que apunta al siguiente nodo
apunta al nulo.

- Lista doblemente enlazada:
Analoga a lista simple, con la diferencia en que cada nodo almacena ademas de su siguiente, guarda la direccion de su anterior, lo que 
permite el movimiento bidireccional de la lista a costa de que el dato abstracto ocupara mayor espacio en memoria. El final esta marcado
de igual manera que la lista simple, y el inicio con el puntero a nodo anterior nulo.

- Lista circular:
Este tipo de lista se destaca por no tener un final marcado por un puntero al nulo, ya que el ultimo nodo apunta al nodo inicial. Esto 
puede ser bueno para funciones en las que debemos acceder varias veces a cada elemento de la lista, pero si no se plantean bien las
condiciones de corte corremos el riesgo de causar un loop infinito.

Para implementar la solucion primero se necesitan plantear casos posibles en los que sabemos que el programa fallara e implementarlos 
como pruebas, empezando por las operaciones mas simple de la lista, insertar. Luego implementar las funciones de iterador para saber 
que se estan insertando en orden y para luego poder borrar el ultimo elemento de la lista obteniendo el anteultimo nodo con el iterador. 
Una vez terminadas esas funciones implementamos insertar y borrar de posicion. Finalmente con todas las funciones anteriores creadas y
testeadas, podemos utilizarlas para las funciones de cola y pila.

