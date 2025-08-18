#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Uso: $0 <índice_rotación> <frase>"
    exit 1
fi

rot=$1
frase=$2

# Normalizar la rotación para que esté entre 0-25
rot=$((rot % 26))
if [ $rot -lt 0 ]; then
    rot=$((rot + 26))
fi

# Crear alfabetos rotados
mayusculas=$(echo {A..Z} | tr -d ' ')
minusculas=$(echo {a..z} | tr -d ' ')
rot_mayusculas=$(echo $mayusculas | cut -c $((rot+1))-26)${mayusculas:0:$rot}
rot_minusculas=$(echo $minusculas | cut -c $((rot+1))-26)${minusculas:0:$rot}

# Encriptar usando tr
echo "$frase" | tr "$mayusculas$minusculas" "$rot_mayusculas$rot_minusculas"