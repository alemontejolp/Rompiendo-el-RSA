#FUENTE PARA PROBLEMA DE PROGRAMACIÓN.

¡NO! NO ES UN VERDADERO ALGORITMO PARA VULNERAR LA ENCRIPTACIÓN RSA
ESA COSA ES MUY SEGURA.

El nombre del problema es "Rompiendo el RSA".

El objetivo de este es puramente didáctico. Consiste en intentar
vulnerar el algoritmo RSA (cuando los valores de los números secretos
'p' y 'q' son pequeños) para comprender el funcionamiento de este algoritmo.

El código aquí alojado no está optimizado para manejar números
mayores a 64 bits.

El paradigma usado es: programación estructurada.

#Directorio ./management:

En este directorio está un manejador para generar casos de prueba,
generar llaves, encriptar, desencriptar, etc., con el fin de facilitar
la comprovación de los resultados de la solución ideada.

#Directorio ./solution:

Aquí se encuentra una propuesta de solución. Todo lo necesario está en un
mismo archivo.

#Directorio ./libs:

Está la librería usada para el manejador. En concreto es sólo la interfaz

#Directorio ./src:

Está la implementación de la librería.
