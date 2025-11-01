#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#define PRIMITIVE_CAT(a, ...) (a ## __VA_ARGS__)
#define PIN_PAIR(x, y) #x#y
#define PORT(x) (PRIMITIVE_CAT (GPIO, x))
#define PIN(x) (PRIMITIVE_CAT (GPIO_PIN_, x))
#define GPIOA "HELLO"
#define GPIO_PIN_1 "WORLD"

char* get_port (char* port) {
    switch (toupper (*port)) {
        #ifdef GPIOA    
            case 'A':   return PORT(A); 
        #endif

        #ifdef GPIOB    
            case 'B':   return PORT(B); 
        #endif

        #ifdef GPIOC    
            case 'C':   return PORT(C); 
        #endif

        #ifdef GPIOD    
            case 'D':   return PORT(D); 
        #endif
        
        #ifdef GPIOE    
            case 'E':   return PORT(E); 
        #endif

        #ifdef GPIOF    
            case 'F':   return PORT(F); 
        #endif

        #ifdef GPIOG    
            case 'G':   return PORT(G); 
        #endif

        #ifdef GPIOH    
            case 'H':   return PORT(H); 
        #endif

        #ifdef GPIOI    
            case 'I':   return PORT(I); 
        #endif

        #ifdef GPIOJ    
            case 'J':   return PORT(J); 
        #endif

        #ifdef GPIOK    
            case 'K':   return PORT(K); 
        #endif

        #ifdef GPIOL    
            case 'L':   return PORT(L); 
        #endif

        #ifdef GPIOM    
            case 'M':   return PORT(M); 
        #endif

        #ifdef GPION    
            case 'N':   return PORT(N); 
        #endif

        #ifdef GPIOO    
            case 'O':   return PORT(O); 
        #endif

        #ifdef GPIOP    
            case 'P':   return PORT(P); 
        #endif

        default:    return "WHYYYYYY";
    }
}

char* get_pin (char* pin) {
    switch (atoi (pin)) {
        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        #ifdef GPIO_PIN_1
            case 1:     return PIN(1);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(2);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(3);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(4);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(5);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(6);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(7);
        #endif
        
        #ifdef GPIO_PIN_0
            case 0:     return PIN(8);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif
        
        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        #ifdef GPIO_PIN_0
            case 0:     return PIN(0);
        #endif

        default:       return PIN (1);
    }
}

void init (char* pair) {
    char* pin = malloc (2 * sizeof (char));
    strncpy (pin, pair + 1, 2);

    printf (get_port (pair));
    printf (get_pin (pin));
    // printf ("%s %d", pair, atoi(pin));
    // printf ("%c %s", pair[0], pair.substr);

}

int main () {
    init (PIN_PAIR (a, 1));
    // printf (PinPair ('A', 1));
    // printf (PIN_PAIR (a, 1));
    // printf (GET_PORT(A));
    // printf (GET_PIN (1));

    // char* apple = "A";
    // char apple_2 = 'A';
    // printf (GET_PORT_C (why(apple_2)));
    // printf ("\n%c", why(apple));
}