#include <iostream>
#include <string>
#include <cctype>

int main(int argc, char *argv[]) {
    int rot = std::stoi(argv[1]); // Convertir el índice de rotación a entero
    std::string frase = argv[2];

    // Normalizar la rotación para que esté entre 0-25
    rot = rot % 26;
    if (rot < 0) rot += 26;

    // Encriptar la frase
    for (char &c : frase) {
        if (std::isupper(c)) {
            c = ((c - 'A' + rot) % 26) + 'A';
        } else if (std::islower(c)) {
            c = ((c - 'a' + rot) % 26) + 'a';
        }
    }

    std::cout << frase << std::endl;
    return 0;
}