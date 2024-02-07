#include "decode.h"

#define FILE_TO_READ        "message.txt"
#define BUFFER_SIZE         100
#define BASE64_NUM_CHARS    64

char decode_buffer[BUFFER_SIZE];
char encode_buffer[BUFFER_SIZE];

static const char * base64_table =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

int _get_index_from_table(char c);

char* readFile(){
    FILE *fp;
    char content[BUFFER_SIZE] = {0};
    fp = fopen(FILE_TO_READ, "rb");
    fread(&content, sizeof(char), BUFFER_SIZE, fp);
    fclose(fp);
    return content;
}

/**
 * @param [in] - encoded message
 * @return - decoded message
*/
char* base64(char* encoded_message){
    int i = 0, j = 0;
    unsigned char input_buffer[4], output_buffer[3];

    while (encoded_message[i] != '\0') {
        for (int k = 0; k < 4; k++) {
            if (encoded_message[i] != '=') {
                input_buffer[k] = _get_index_from_table(encoded_message[i++]);
            } else {
                input_buffer[k] = 0;
                i++;
            }
        }

        output_buffer[0] = (input_buffer[0] << 2) + ((input_buffer[1] & 0x30) >> 4);
        output_buffer[1] = ((input_buffer[1] & 0x0F) << 4) + ((input_buffer[2] & 0x3C) >> 2);
        output_buffer[2] = ((input_buffer[2] & 0x03) << 6) + input_buffer[3];

        for (int k = 0; k < 3; k++) {
            if (encoded_message[i - 1] != '=') {
                decode_buffer[j++] = output_buffer[k];
            } else {
                break;
            }
        }
    }

    decode_buffer[j] = '\0';
    return decode_buffer;
}

/**
 * @param [in] - decoded message
 * @return - encoded message
*/
char* reverse(char* decoded_message){
    int i = 0, j = 0;
    unsigned char input_buffer[3], output_buffer[4];

    while (decoded_message[i] != '\0') {
        int input_length = 0;

        for (int k = 0; k < 3; k++) {
            if (decoded_message[i] != '\0') {
                input_buffer[k] = decoded_message[i++];
                input_length++;
            } else {
                input_buffer[k] = 0;
            }
        }

        output_buffer[0] = (input_buffer[0] & 0xFC) >> 2;
        output_buffer[1] = ((input_buffer[0] & 0x03) << 4) + ((input_buffer[1] & 0xF0) >> 4);
        output_buffer[2] = ((input_buffer[1] & 0x0F) << 2) + ((input_buffer[2] & 0xC0) >> 6);
        output_buffer[3] = input_buffer[2] & 0x3F;

        for (int k = 0; k < 4; k++) {
            if (k <= input_length) {
                encode_buffer[j++] = base64_table[output_buffer[k]];
            } else {
                encode_buffer[j++] = '=';
            }
        }
    }

    encode_buffer[j] = '\0';
    return encode_buffer;
}

int _get_index_from_table(char c) {
    for (int i = 0; i < BASE64_NUM_CHARS; i++) {
        if (base64_table[i] == c) {
            return i;
        }
    }
    return -1;
}