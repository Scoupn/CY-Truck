#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autre.h"


// Fonction utilitaire pour retourner le maximum entre deux entiers
int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

// Fonction utilitaire pour retourner le minimum entre deux entiers
int min(int a, int b) {
  if (a >= b) {
    return b;
  }
  return a;
}

// Fonction utilitaire pour retourner le minimum entre trois entiers
int min2(int a, int b, int c) {
  return min(min(a, b), c);
}

// Fonction utilitaire pour retourner le maximum entre trois entiers
int max2(int a, int b, int c) {
  return max(max(a, b), c);
}
