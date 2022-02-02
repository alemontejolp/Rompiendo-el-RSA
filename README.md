# FUENTE PARA PROBLEMA DE PROGRAMACIÓN.

**¡NO! NO ES UN VERDADERO ALGORITMO PARA VULNERAR EL SISTEMA RSA,
ESA COSA ES MUY SEGURA.**

El nombre del problema es "Rompiendo el sistema RSA". Para leer el problema, ir aquí:
https://docs.google.com/document/d/1Qry6g86-jX9c6QpcuxeuyXiXgMV4YPPAH9FW4bR0hKg/edit?usp=sharing

Para poner aprueba tu solución, ir aquí:
https://omegaup.com/arena/problem/rompiendo-el-sistema-rsa#problems

El objetivo de este es puramente educativo. Consiste en intentar
vulnerar el algoritmo RSA (cuando los valores de los números secretos
'p' y 'q' son pequeños) para comprender el funcionamiento de este algoritmo.

El código aquí alojado no está optimizado para manejar números
mayores a 64 bits.

El paradigma usado es: programación estructurada.

## Directorio: ./manager

En este directorio está un manejador (CLI) para generar casos de prueba,
generar llaves, cifrar, descifrar, etc., con el fin de facilitar
la comprovación de los resultados de la solución ideada.

Para ver las opciones, usar el comando "rsa help" en el ejecutable del manejador.

Si está en un sistema oprativo tipo POSIX, puede compilar el manejador ejecutando
el script de BASH `./build.sh`. Recuerde primero darle los permisos de ejecucicón
con `chmod +x build.sh`

```bash
chmod +x build.sh
./build.sh
```

## Directorio: ./solution

Aquí se encuentra una propuesta de solución. Todo lo necesario está en un
mismo archivo. También hay 10 archivos '.in' que pueden ser usados como casos de prueba
para la solución, así como 10 archivos '.out', que son las respectivas salidas para cada archivo '.in'.

## Directorio: ./libs

Está la librería usada para el manejador. En concreto es el código del CLI y el código del
algoritmo.

## Directorio: ./src

Está la implementación de la librería.
