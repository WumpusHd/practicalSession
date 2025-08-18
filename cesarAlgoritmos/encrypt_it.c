#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int rotacion = atoi(argv[1]); // Se convierte el primer argumento a entero
    char *frase = argv[2];
    int longitud = strlen(frase);

    //Acá se supone que la rotación se hará en base a las 26
    //letras de nuestro abecedario en español
    rotacion = rotacion % 26;
    if (rotacion < 0) rotacion += 26;

    // Acá se aplica el cifrado César
    for (int i = 0; i < longitud; i++) {
        if (isupper(frase[i])) {
            // Rotar letras mayúsculas
            frase[i] = ((frase[i] - 'A' + rotacion) % 26) + 'A';
        } else if (islower(frase[i])) {
            // Rotar letras minúsculas
            frase[i] = ((frase[i] - 'a' + rotacion) % 26) + 'a';
        }
    }

    printf("%s\n", frase);
    return 0;
}
