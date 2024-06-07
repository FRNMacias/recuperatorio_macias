#pragma once
#include <stdint.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>
struct data{
    uint16_t ID,lower,type_NH,type_NL;
    uint16_t *IDs,ID_upper,info;
};
struct data *resize(struct data *v,int tam);
int llenar(struct data *v, FILE *f);
void imprimir(FILE *c, int x, struct data *v);
void busquedad(struct data *v,int pos,uint32_t ID);
