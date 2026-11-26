# Formatos de archivos de DinoRegistry

## 1. `dinosaurs.txt` (entrada y persistencia)

Archivo de texto plano. Cada línea no vacía representa un dinosaurio con ocho
campos separados por `|`, en este orden:

1. Código.
2. Nombre.
3. Período geológico.
4. Dieta.
5. Longitud en metros (`double`).
6. Peso en toneladas (`double`).
7. Antigüedad en millones de años (`double`).
8. Lugar de descubrimiento.

Ejemplo:

```text
DIN-001|Tyrannosaurus Rex|Cretacico|Carnivoro|12|8|68|Montana, USA
DIN-002|Triceratops|Cretacico|Herbivoro|9|6|66|Dakota del Sur, USA
```

No se debe incluir `|` dentro de un campo. Los campos numéricos deben poder
convertirse con `std::stod`. El cargador exige código y nombre no vacíos y la
función de gestión impide códigos duplicados (comparación sin distinguir
mayúsculas/minúsculas). Las líneas vacías se ignoran; las inválidas o duplicadas
se omiten y generan avisos. El archivo se reescribe al guardar la colección.

## 2. `excavation.txt` (matriz de excavación)

En esta versión, el archivo que consume `loadExcavationMap` NO es texto libre:
contiene primero dos enteros positivos (filas y columnas), seguidos por
exactamente `filas * columnas` enteros no negativos. Se permiten espacios y
saltos de línea entre números. No se permite contenido adicional después de
la última celda.

Ejemplo de 3 filas por 3 columnas:

```text
3 3
1 2 3
4 5 6
7 8 9
```

El archivo de ejemplo incluido contiene una matriz de 8 x 8. La función
`readExcavationMap` solo imprime el contenido textual del archivo; el análisis
matemático usa `loadExcavationMap`, que interpreta la matriz numérica. Por eso,
la descripción anterior del archivo como texto libre fue corregida para
coincidir con el formato que realmente valida el módulo de mapas.

## 3. `report.txt` (salida generada)

Archivo de texto generado por `generateReport` al guardar/salir. No es un
archivo de entrada ni debe editarse manualmente. Contiene un título, el total
de registros y una ficha por dinosaurio. Los campos numéricos se escriben con
dos decimales.

Ejemplo de estructura:

```text
REPORTE DE DINOSAURIOS
======================

Total de dinosaurios: 1

Codigo: DIN-001
Nombre: Tyrannosaurus Rex
Periodo: Cretacico
Dieta: Carnivoro
Longitud: 12.00 metros
Peso: 8.00 toneladas
Antiguedad: 68.00 millones de anos
Lugar de descubrimiento: Montana, USA
```

Cuando la colección está vacía, el reporte indica `Total de dinosaurios: 0` y
`La coleccion esta vacia.`

## Ubicación

Los nombres de archivo se resuelven respecto al directorio de trabajo actual.
Ejecutar DinoRegistry desde la raíz del repositorio para que encuentre los
archivos de ejemplo y cree `report.txt` allí.
