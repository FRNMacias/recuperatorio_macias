#include "network.h"

struct data *resize(struct data *v,int tam){//incrementa la estructura unicamente de a uno.
    struct data *aux;
    aux = new struct data[tam+1];
    for(int i=0; i<tam; i++){
        aux[i]=v[i];
    }
    delete []v;
    return aux;
}
uint16_t *resize_16(uint16_t *v,int tam){//incrementa la estructura unicamente de a uno.
    uint16_t *aux;
    aux = new uint16_t[tam+1];
    for(int i=0; i<tam; i++){
        aux[i]=v[i];
    }
    delete []v;
    return aux;
}
void busquedad(struct data *v,int pos,uint16_t ID){
    uint16_t *sec;
    int band=0,c=0,band2=0;
    uint16_t aux;
    while(band==0){
        if(band2==0){
            aux = (ID-1);
            band2++;
        }
        else{
            aux = (v[(aux)].ID_upper)-1;
        }
        sec = resize_16(sec,c);
        if(v[(aux)].ID_upper != 1023){
            sec[c]=v[(ID-1)].ID_upper;
        }
        else{
            band==1;
        }
        c++;
    }
    printf("\nSECUENCIA:\n");
    for(int i=(c-1); i >= 0; i=i-1){
        printf("ID %u",sec[i]);
        printf("\t->");
    }
    printf("ID %u",ID);
}
int llenar(struct data *v, FILE *f){
    uint16_t aux, aux1;
    int b,x=0,pos=0;
    int CPU=0, t=0,presion=0,caudal=0,nivel=0, motor=0,valvula=0, conc=0;
    fseek(f,0,SEEK_END);
    b = ftell(f);
    rewind(f);
    while(x<b){
        printf("\n------------------------------");
        v = resize(v,pos);
        fread(&aux,sizeof(uint16_t),1,f);
        v[pos].ID = aux >> 6;
        printf("\n[%u]",v[pos].ID);
        aux1 = aux << 10; 
        v[pos].lower = aux1 >> 10;
        fread(&aux,sizeof(uint16_t),1,f);
        v[pos].type_NH = aux >> 12;
        aux1 = aux << 4; 
        v[pos].info = aux1 >> 8;
        aux1 = aux << 12; 
        v[pos].type_NL = aux1 >> 15;
        fread(&aux,sizeof(uint16_t),1,f);
        aux1= aux << 3;
        v[pos].ID_upper = aux1 >> 6;
        if(v[pos].type_NH == 0 && v[pos].type_NL == 0){//CPU
            CPU++;
            printf("\nCPU");
            printf("\nCantidad de dispositivos inferiores %u", v[pos].lower);
            printf("\nIDs de dispositivos inferiores:");
            v[pos].IDs = new uint16_t[v[pos].lower];
            for(int i=0; i<v[pos].lower; i++){
                fread(&aux,sizeof(uint16_t),1,f);
                aux1 = aux << 6;
                v[pos].IDs[i] = aux1 >> 6;
                printf("\nID%d: %u",i,v[pos].IDs[i]);
            }
        }
        if(v[pos].type_NH == 1 && v[pos].type_NL == 1){//concentrador
            conc++;
            printf("\nCONCENTRADOR");
            printf("\nCantidad de dispositivos inferiores %u", v[pos].lower);
            printf("\nIDs de los dispositicos inferiores:");
            v[pos].IDs = new uint16_t[v[pos].lower];
            for(int i=0; i<v[pos].lower; i++){
                fread(&aux,sizeof(uint16_t),1,f);
                aux1 = aux << 6;
                v[pos].IDs[i] = aux1 >> 6;
                printf("\nID%d: %u",i,v[pos].IDs[i]);
            } 
        }
        if(v[pos].type_NH == 0 && v[pos].type_NL == 1){//sensor
            aux = v[pos].info << 10;
            v[pos].info = aux >> 14;
            if(v[pos].info == 0){
                printf("\nSENSOR DE CAUDAL");
                caudal++;
            }
            if(v[pos].info == 1){
                printf("\nSENSOR DE TEMPERATURA");
                t++;
            }
            if(v[pos].info == 2){
                printf("\nSENSOR DE PRESION");
                presion++;
            }
            if(v[pos].info == 3){
                printf("\nSENSOR DE NIVEL");
                nivel++;
            }
        }
        if(v[pos].type_NH == 1 && v[pos].type_NL == 0){//actuador
            aux = v[pos].info << 13;
            v[pos].info = aux >> 15;
            if(v[pos].info == 0){
                printf("\nACTUADOR, ELECTRO VALVULA");
                valvula++;
            }
            if(v[pos].info == 1){
                printf("\nACTUADOR, MOTOR");
                motor++;
            }
        }
        if(v[pos].ID_upper == 1023){
            printf("\nNo contiene disp. superiores.");
        }
        else{
            printf("\nID dispositivo sup: %u",v[pos].ID_upper);
        }
        pos++;
        x = ftell(f);
    }
    printf("\nCantidad de dispositivos de cada tipo:\n");
    printf("\nCPU: %d",CPU);
    printf("\nCONCENTRADOR: %d",conc);
    printf("\nSENSOR DE CAUDAL: %d",caudal);
    printf("\nSENSOR DE TMPERATURA: %d",t);
    printf("\nSENSOR DE PRESION: %d",presion);
    printf("\nSENSOR DE NIVEL: %d",nivel);
    printf("\nMOTOR: %d",motor);
    printf("\nELECTRO VALVULA: %d",valvula);
    FILE *c = fopen("network_structure.txt","wb");
    if(c==NULL){
        printf("\nNo es posible abrir el archivo para escritura");
    }
    imprimir(c,pos,v);
    fclose(c);
    uint16_t ID_busq;
    int band;
    do{
        band=0;
        printf("\nIngrese ID: ");
        scanf("%u",&ID_busq);
        if(ID_busq < 1 || ID_busq >10){
            band==1;
        }
    }while(band==1);
    busquedad(v,pos,ID_busq);
    /*uint16_t *sec;
    int w=0,band2=0;
    band=0;
    while(band==0){
        if(band2==0){
            aux = (ID_busq-1);
            band2++;
        }
        else{
            aux = (v[(aux)].ID_upper)-1;
        }
        sec = resize_16(sec,w);
        if(v[(aux)].ID_upper != 1023){
            sec[w]=v[(ID_busq-1)].ID_upper;
        }
        else{
            band==1;
        }
        w++;
    }
    printf("\nSECUENCIA:\n");
    for(int g=(w-1); g >= 0; g=g-1){
        printf("ID %u",sec[g]);
        printf("\t->");
    }
    printf("ID %u",ID_busq);*/
    return pos;
}
void imprimir(FILE *c, int x,struct data *v){
    for(int i=0; i<x; i++){
        fprintf(c,"\n------------------------------------------");
        fprintf(c,"\n[%u]",v[i].ID);
        if(v[i].type_NH == 0 && v[i].type_NL == 0){
            fprintf(c,"\nCPU");
            fprintf(c,"\nCantidad de dispositivos inferiores:");
            fprintf(c,"\nIDs de dispositivos inferiores:");
            for(int k=0; k<(v[i].lower); k++){
                fprintf(c,"\nID%d: %u",k,v[i].IDs[k]);
            }
        }
        if(v[i].type_NH == 1 && v[i].type_NL == 1){
            fprintf(c,"\nCONCENTRADOR");
            fprintf(c,"\nCantidad de dispositivos inferiores:");
            fprintf(c,"\nIDs de dispositivos inferiores:");
            for(int k=0; k<(v[i].lower); k++){
                fprintf(c,"\nID%d: %u",k,v[i].IDs[k]);
            }
        }
        if(v[i].type_NH == 0 && v[i].type_NL == 1){
            if(v[i].info == 0){
                fprintf(c,"\nSENSOR DE CAUDAL");
            }
            if(v[i].info == 1){
                fprintf(c,"\nSENSOR DE TEMPERATURA");
            }
            if(v[i].info == 2){
                fprintf(c,"\nSENSOR DE PRESION");
            }
            if(v[i].info == 3){
                fprintf(c,"\nSENSOR DE NIVEL");
            }
        }
        if(v[i].type_NH == 1 && v[i].type_NL == 0){
            if(v[i].info == 0){
                fprintf(c,"\nACTUADOR, ELECTRO VALVULA");
            }
            if(v[i].info == 1){
                fprintf(c,"\nACTUADOR, MOTOR");
            }
        }
    } 
}
