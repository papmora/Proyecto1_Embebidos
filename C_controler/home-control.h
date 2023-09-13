#ifndef HOME_CONTROL_H
#define HOME_CONTROL_H

#define LED_CUARTO_A 16
#define LED_CUARTO_B 17
#define LED_SALA 18
#define LED_COMEDOR 19
#define LED_COCINA 20
#define PUERTA_DELANTERA 21
#define PUERTA_TRASERA 22
#define PUERTA_CUARTO_A 23
#define PUERTA_CUARTO_B 24

#define IN 0
#define OUT 1

#define MAXBUF 1024
#define DELIM "="

#define VIDEO_DEVICE "/dev/video0"  // Ruta al dispositivo de video
#define OUTPUT_FILE "captured_image.jpg" //Imagen generada
#define BUFFER_SIZE 1024
#define IMG_WIDTH 640
#define IMG_HEIGHT 480


int led_on (int);
int led_off (int);
int state_door (int);

int reserve_all ();
int free_all ();

int reserve_GPIO (int, int);
int write_GPIO (int, int);
int read_GPIO (int);
int free_GPIO (int);

int start_camera();
int capture_image();


#endif
