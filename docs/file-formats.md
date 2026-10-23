# Formatos de archivos de DinoRegistry

## 1. dinosaurs.txt

Archivo de texto plano. Cada línea representa un dinosaurio
con ocho campos separados por el carácter `|`.

Orden de los campos:

1. Código único.
2. Nombre.
3. Período geológico.
4. Dieta.
5. Longitud en metros.
6. Peso en toneladas.
7. Antigüedad en millones de años.
8. Lugar de descubrimiento.

Ejemplo válido:

DIN-001|Tyrannosaurus Rex|Cretacico|Carnivoro|12.0|8.0|68.0|Montana, USA
DIN-002|Triceratops|Cretacico|Herbivoro|9.0|6.0|66.0|Dakota del Sur, USA

Los valores numéricos deben poder convertirse a números.
No se debe usar `|` dentro de un campo. Los códigos deben ser
únicos. Las líneas vacías se ignoran; las líneas inválidas
se omiten y generan un aviso.

## 2. excavation.txt

Archivo de texto plano que contiene el mapa de excavación.
Cada línea se muestra tal como aparece en el archivo. Puede
incluir zonas, coordenadas, encabezados y observaciones.

Ejemplo válido:

MAPA DE EXCAVACION - SITIO A
----------------------------
Zona A: 12.5 N, 74.2 W - excavacion principal
Zona B: 12.6 N, 74.3 W - restos pendientes

## 3. report.txt

Archivo de salida generado por DinoRegistry. Contiene el
número total de dinosaurios y, para cada registro, el código,
nombre, período, dieta, longitud, peso, antigüedad y lugar
de descubrimiento.

No es necesario editarlo manualmente. Se regenera al guardar
desde el menú o al salir del programa.

## Ubicación de los archivos

Los nombres `dinosaurs.txt`, `excavation.txt` y `report.txt`
son rutas relativas al directorio desde el que se ejecuta
DinoRegistry. Ejecuta el programa desde la raíz del proyecto
para mantenerlos en el mismo lugar.
