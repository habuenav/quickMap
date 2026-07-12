#### **[[ENGLISH]](#spanish)**

# quickMap

`quickMap` es una librería de Arduino ultra rápida diseñada para reemplazar la función nativa `map()`. Al precalcular la pendiente y el desfase de la ecuación de la recta durante la inicialización, **elimina por completo las costosas operaciones de división en tiempo de ejecución**, convirtiendo el mapeo en una simple multiplicación y suma en línea (`inline`).

Es ideal para aplicaciones con restricciones de tiempo crítico, como procesamiento de audio, síntesis digital de señales (DSP) y la lectura de sensores de alta velocidad (como sensores de soplo o potenciómetros).

## Características

- Código optimizado para obtener lecturas rápidas sin divisiones en tiempo de ejecución.
- Soporte nativo para trabajar con precisión de punto flotante de 32 bits (`float`).
- Soporta de forma nativa rangos invertidos de manera automática (ej. de 0..1023 a 255..0).
- Restricción automática (*constrain*) integrada para limitar los valores estrictamente dentro de los rangos definidos.

## Requisitos

- **Placa**: Compatible con cualquier arquitectura (ESP32, AVR, STM32, RP2040, etc.).
- **IDE de Arduino**: Recomendado 1.8.10 o superior.

## Instalación

1. Descarga el archivo ZIP de la librería desde [GitHub](https://github.com/habuenav/quickMap).
2. En el IDE de Arduino, ve a **Programa** > **Incluir Librería** > **Añadir biblioteca .ZIP...**.
3. Selecciona el archivo ZIP descargado para instalar la librería.
4. Puedes instalarlo directamente desde el Administrador de bibliotecas del IDE de Arduino; solo tienes que buscar quickMap.

O también puedes extraer el archivo ZIP en tu directorio de librerías de Arduino (`libraries/`).

### Código de ejemplo
```
#include <quickMap.h>

quickMap miMapeo;

void setup() {
  Serial.begin(115200);
  // Inicializa: rango de entrada (0.0 a 1023.0), rango de salida (0.0 a 127.0 para MIDI)
  miMapeo.init(0.0f, 1023.0f, 0.0f, 127.0f);
}

void loop() {
  float lecturaRaw = analogRead(34); // Ejemplo de pin analógico
  
  // Mapeo ultra rápido con límites automáticos
  float resultado = miMapeo.map(lecturaRaw); 
  
  Serial.println(resultado);
  delay(10); // Ciclo rápido de prueba
}
```
## API

### Constructor

**`quickMap()`**: Inicializa la clase con valores por defecto (Rango de entrada de 0.0 a 1.0, rango de salida de 0.0 a 1.0).

### Métodos

* **`bool init(float in_min, float in_max, float out_min, float out_max)`**: Configura los límites y precalcula los factores matemáticos. Devuelve `false` si el rango de entrada es cero para evitar errores matemáticos.
* **`inline float map(const float value)`**: Realiza el mapeo matemático de manera ultra rápida. Aplica automáticamente restricciones de límite (*constrain*) en base a los valores cargados en el método `init()`.

### Notas

* La optimización principal se basa en el álgebra lineal; al calcular la base y el factor en el `setup()`, el microcontrolador no sufre realizando divisiones pesadas en cada iteración del `loop()`.
* Está optimizada para trabajar de forma nativa con flotantes de 32 bits (`float`), asegurando que arquitecturas como el ESP32 aprovechen al máximo su unidad de punto flotante por hardware.
* Si inviertes los rangos en el `init()` (ej. `in_min` mayor que `in_max`), la librería adaptará automáticamente los límites de restricción interna para que la salida siga comportándose correctamente sin romperse.

## Ejemplos

En la carpeta `examples/` del repositorio encontrarás códigos de prueba adicionales para verificar su implementación.

## Contribuciones

Las contribuciones son bienvenidas. Si encuentras un problema o tienes una sugerencia, por favor abre un issue o envía un pull request en el repositorio de GitHub.


#### **[[SPANISH]](#english)**

# quickMap

`quickMap` is an ultra-fast Arduino library designed to replace the native `map()` function. By precalculating the slope and offset of the linear equation during initialization, it **completely eliminates costly division operations at runtime**, turning the mapping process into a simple inline multiplication and addition.

It is ideal for performance-critical applications with strict time constraints, such as audio processing, digital signal processing (DSP), and high-speed sensor reading (like breath sensors or potentiometers).

## Characteristics

- Optimized code for fast readings with zero runtime divisions.
- Native support for working with 32-bit floating-point precision (`float`).
- Natively and automatically supports reverse mappings (e.g., mapping from 0..1023 to 255..0).
- Built-in automatic boundary constraints (*constrain*) to strictly clamp output values within defined bounds.

## Requirements

- **Board**: Compatible with any architecture (ESP32, AVR, STM32, RP2040, etc.).
- **Arduino IDE**: Recommended 1.8.10 or higher.

## Installation

1. Download the library ZIP file from [GitHub](https://github.com/habuenav/quickMap).
2. In the Arduino IDE, go to **Sketch** > **Include Library** > **Add .ZIP Library...**.
3. Select the downloaded ZIP file to install the library.
4. You can install it directly from the Arduino IDE Library Manager—just search for quickMap.

Alternatively, you can extract the ZIP file directly into your Arduino libraries directory (`libraries/`).

## API

### Builder

**`quickMap()`**: Initializes the class with default values (Input range from 0.0 to 1.0, output range from 0.0 to 1.0).

## Methods

* **`bool init(float in_min, float in_max, float out_min, float out_max)`**: Configures boundaries and precalculates mathematical factors. Returns `false` if the input range is zero to prevent mathematical errors.
* **`inline float map(const float value)`**: Performs ultra-fast mathematical mapping. Automatically applies boundary constraints based on the values loaded during `init()`.

### NOTES

* The main optimization relies on linear algebra; by calculating the base and factor inside `setup()`, the microcontroller avoids performing heavy division tasks on every `loop()` iteration.
* It is fine-tuned to work natively with 32-bit floating-point numbers (`float`), ensuring architectures like the ESP32 fully exploit their hardware floating-point unit (FPU).
* If you invert the ranges in `init()` (e.g., making `in_min` greater than `in_max`), the library will automatically adapt its internal bounding logic so that clamping continues to work perfectly without clipping or failing.

## Examples

Inside the `examples/` directory of the repository, you will find additional test codes to verify its implementation.

## Contributions

Contributions are welcome. If you find an issue or have a suggestion, please open an issue or send a pull request in the GitHub repository.
