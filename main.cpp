#include "network.h"

int main(){
    FILE *f = fopen("network_structure.dat","rb");
    if(f == NULL){
        printf("\nNo es posible abrir el archivo!");
        return -1;
    }
    struct data *v;
    int x;
    x = llenar(v,f);
    fclose(f);
    delete []v;
    return 0;
}
