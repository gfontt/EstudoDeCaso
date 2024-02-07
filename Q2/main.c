#include <stdlib.h>
#include <stdio.h>
#include "decode.h"

int main(){

    char *fileContent = readFile();
    if(fileContent == NULL){
        printf("Ocorreu um erro na leitura do arquivo!");
    }

    char *decoded_message = base64(fileContent);
    printf("A mensagem decodificada é %s\n", decoded_message);

    char *encoded_message = reverse(decoded_message);
    printf("A mensagem recodificada é %s\n", encoded_message);
    
    return 0;
}