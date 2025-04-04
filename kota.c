#include "kota.h"
#include <string.h>

void createKota(kota *k, char *kt) {
    strcpy((*k).kt, kt);
    (*k).p = NULL;
}
