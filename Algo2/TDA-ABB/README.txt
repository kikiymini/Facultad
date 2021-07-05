Un Readme.txt donde explique el TDA implementado. Explique qué es una árbol, árbol binario y árbol binario
de búsqueda. Explique por qué es importante la distinción de cada uno de estos conceptos.

El arbol es un tipo de dato abstracto en en el que tenemos nodos vinculados entre ellos. Todo arbol posee un nodo raiz 
desde el que se ramifica a otros nodos segun el criterio del arbol con el que trabajamos.

El arbol binario tiene la principal regla de que todo nodo contiene un solo elemento y solo dos punteros a otros nodos, 
sus "hijos", uno a su izquierda y otro a su derecha.

El arbol binario de busqueda agrega sobre el anterior marcando reglas sobre el arbol. Segun el criterio de comparacion
del mismo, los hijos a la izquierda de un nodo tienen que ser si o si menores que el, y sobre su derecha iran todo nodo
con mayores elementos.

El trabajo practico consiste de funciones basicas de todo tda como crear o destruir el arbol, la insercion y el borrado
se aseguran que la operacion mantenga las reglas de un arbol binario de busqueda y los nodos queden enlazados entre si
correctamente. Los recorridos son en su mayoria recursivos ya que en este caso logran una visibilidad del codigo mucho mejor
que si fuera con un while, pero tienen la desventaja que cortar una funcion solo corta a si misma y no a toda la cadena de recursividad
por lo que es necesario agregar un argumento que evalue luego de cada llamado recursivo si este debe seguir iterando. 

La suposicion mas importante es que el arbol NO puede tener dos elementos iguales.