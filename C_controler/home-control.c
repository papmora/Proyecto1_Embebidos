#include "home-control.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* NAMES[9] = {"LED_CUARTO_A", "LED_CUARTO_B", "LED_SALA", "LED_COMEDOR", "LED_COCINA", 
"PUERTA_DELANTERA", "PUERTA_TRASERA", "PUERTA_CUARTO_A", "PUERTA_CUARTO_B"};

int GPIOs[9] = {LED_CUARTO_A, LED_CUARTO_B, LED_SALA, LED_COMEDOR, LED_COCINA,
  PUERTA_DELANTERA, PUERTA_TRASERA, PUERTA_CUARTO_A, PUERTA_CUARTO_B};


/* //////////// Control de LEDs /////////////////////////////////*/

/**
 * Enciende un LED especifico
 * @param id  id del LED
 * @return retorna 0 si se enciende correctamente, -1 en caso de error
 */
int led_on(int id_led) {
  write_GPIO(GPIOs[id_led],1);
  printf("Led %s encendido\n", NAMES[id_led]);
  return 0;
}

/**
 * Apaga un LED especifico
 * @param id id del LED
 * @return retorna 0 si se enciende correctamente, -1 en caso de error
 */
int led_off (int id_led){
  write_GPIO (GPIOs[id_led],0);
  printf("Led %s apagado\n", NAMES[id_led]);
  return 0;
}


/* //////////// Control de puertas /////////////////////////////////*/

/**
 * Cambia el estado de una puerta especifica
 * @param id de la puerta
 * @return estado de la puerta. 0 si esta abierta y 1 si esta cerrada
 */
int state_door (int id_door){
  int val = read_GPIO (GPIOs[id_door]);
  if(val==1) printf("Puerta %s se encuentra cerrada\n", NAMES[id_door]);
  else printf("Puerta %s se encuentra abierta\n", NAMES[id_door]);
  return val;
}


/* ////////// Control de Pines (GPIO) ///////////////////////////////// */

/**
 * Reserva los todos los GPIO a usar
 * @return retorna 0 si se reservan correctamente, -1 en caso de error
 */
int reserve_all () {
  for (int i=0; i<5; i++) {
    reserve_GPIO (GPIOs[i], OUT); //Pins para output
  }
  for (int i=5; i<9; i++) {
    reserve_GPIO (GPIOs[i], IN); //Pins para input
  }
  return 0;
}

/**
 * Libera todos los pines GPIO a usar
 * @return retorna 0 si se liberan correctamente, -1 en caso de error
 */
int free_all () {
  for (int i=0; i<9; i++) { 
    free_GPIO (GPIOs[i]);
  }
  return 0;
}

/**
 * Reserva y define los pines como input o output
 * @param pin puerto a reservar y configurar
 * @param mode 0 para usar como input, 1 como output 
 * @return 0 si se configura correctamente, -1 en caso de error
 */
int reserve_GPIO (int pin, int mode) {
  int fd;
  char buf[MAXBUF];
  //Abrir el archivo para exportar el GPIO
  fd = open("/sys/class/gpio/export", O_WRONLY);
  if(fd==-1){
    printf("Error 01: al abrir el archivo export para el pin %d\n", pin);
    return -1;
  }

  //Escribir numero de pin en el archivo export para reservar el GPIO
  sprintf(buf, "%d", pin);
  if(write(fd, buf, strlen(buf)) == -1){
    printf("Error 02: al reservar el pin %d\n", pin);
    close(fd);
    return -1;
  }

  close(fd);

  // Define la direccion del GPIO creado
  sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
  fd = open(buf, O_WRONLY);
  if(fd == -1){
    printf("Error 03: al abrir el archivo para definir la direccion del pin %d\n", pin);
    return -1;
  }
 
  if (mode == OUT) { // Direccion output
    if(write(fd, "out", 3) == -1){
      printf("Error 04: al definir el pin %d como output\n", pin);
      close(fd);
      return -1;
    }
  }
  else { // Direccion input
    if(write(fd, "in", 2) == -1){
      printf("Error 05: al definir el pin %d como input\n", pin);
      close(fd);
      return -1;
    }
  }

  close(fd);
  printf("Led %s reservado exitosamente", NAMES[pin]);
  return 0; //Reserva exitosa
}


/**
 * Lee el valor digital de un pin especifico
 * @param pin GPIO a leer
 * @return 0 para LOW, 1 para HIGH, -1 en casod e error
 */
int read_GPIO(int pin) {
  char value;
  int fd;
  char buf[MAXBUF];

  //Abrir archivo para lectura
  sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
  fd = open(buf, O_RDONLY);
  if(fd==-1){
    printf("Error 06: al abrir el archivo para leer el pin %d\n", pin);
    return -1;
  }

  //Leer el pin
  if(read(fd, &value, 1) == -1){
    printf("Error 07: al leer el pin %d\n", pin);
    return -1;
  }

  close(fd);
  return (value == 49 ? 1 : 0);
}

/**
 * Escribe un valor digital para un pin especifico
 * @param pin GPIO a escribir
 * @param value valor: 1 para HIGH, 0 para LOW
 * @return 0 si se escribe correctamente, -1 en caso de error
 */
int write_GPIO (int pin, int value) {
  int fd;
  char buf[MAXBUF];

  //Abrir el archivo
  sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
  fd = open(buf, O_WRONLY);
  if(fd==-1){
    printf("Error 08: al abrir el archivo para escribir en el pin %d\n", pin);
    return -1;
  }

  if (value) { // GPIO high
    if(write(fd, "1", 1) == -1){
      printf("Error 09: al escribir 1 en el pin %d\n", pin);  
      close(fd);
      return -1;
    }
  }
  else { // GPIO low
    if(write(fd, "0", 1) == -1){
      printf("Error 10: al escribir 0 en el pin %d\n", pin); 
      close(fd);
      return -1; 
    }
  }

  close(fd);
  return 0;
}

/**
 * Libera el GPIO
 * @param pin GPIO a liberar
 * @return 0 si se libera, -1 en caso de error
 */
int free_GPIO(int pin) {
  int fd;
  char buf[MAXBUF];

  //Revisar si se encuentra reservado
  sprintf(buf, "/sys/class/gpio/gpio%d\n", pin);
  fd = open(buf, O_WRONLY);
  if(fd==-1){
    printf("El pin %d ya se encuentra libre\n", pin);
    close(fd);
    return -1;
  }

  //Abrir el archivo
  fd = open("/sys/class/gpio/unexport", O_WRONLY);
  if(fd==-1){
    printf("Error 11: al abrir el archivo para liberar el pin %d\n", pin);
    return -1;
  }

  //Liberar el pin
  sprintf(buf, "%d", pin);
  if(write(fd, buf, strlen(buf)) == -1){
    printf("Error 12: al liberar el pin %d\n", pin);
    close(fd);
    return -1;
  }

  close(fd);
  return 0;
}

int start_camera() {
    // Configurar la cámara
    printf("Cámara inicializada con éxito.\n");
    return 0;
}

int capture_image(const char *outputFile) {
    // Ejecutar fswebcam para capturar una imagen
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "fswebcam -r %dx%d --jpeg 85 -D 1 -q %s", 
             IMG_WIDTH, IMG_HEIGHT, OUTPUT_FILE);
    
    int result = system(cmd);

    if (result != 0) {
        perror("Error al capturar la imagen");
        return -1;
    }

    printf("Imagen capturada con éxito.\n");
    return 0;
}


