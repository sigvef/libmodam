#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "MOD.h"

int main(){

    FILE*fp = fopen("res/class05.mod", "r");

    fseek(fp, 0L, SEEK_END);
    long n_bytes = ftell(fp);

    int8_t *buffer = (int8_t*) malloc(sizeof(int8_t)*n_bytes);

    fseek(fp, 0L, SEEK_SET);
    
    fread(buffer, sizeof(int8_t), n_bytes, fp);

    fclose(fp);

    MOD* mod = MOD_load(buffer);

    return 0;
}
