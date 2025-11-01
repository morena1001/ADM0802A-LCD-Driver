#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define PRIMITIVE_CAT(a, ...) (a ## __VA_ARGS__)
#define PIN_PAIR(x, y) #x#y
#define GET_PORT(x) (PRIMITIVE_CAT (GPIO, x))
#define GET_PIN(x) (PRIMITIVE_CAT (GPIO_PIN_, x))
#define GET_PORT_C(x) (PRIMITIVE_CAT (GPIO, x))
#define GPIOA "HELLO"
#define GPIO_PIN_1 "WORLD"
#define why(x)  (x)

char* PinPair (char port, uint8_t pin) {
	char* pair = malloc (sizeof (char) + sizeof (uint8_t));
    sprintf (pair, "%c%d", port, pin);
    return pair;
}

char* init (char* pair) {
    // printf (GET_PORT (pair[0]));

}

int main () {
    // printf (PinPair ('A', 1));
    // printf (PIN_PAIR (a, 1));
    // printf (GET_PORT(A));
    // printf (GET_PIN (1));

    char* apple = "A";
    char apple_2 = 'A';
    printf (GET_PORT_C (why(apple_2)));
    printf ("\n%c", why(apple));
}