#include "ClientApp.h"



int main() {
    ThisClient thisClient("localhost");

    while (true) {
        char input[6];
        scanf("%s", input);
        if (strcmp(input, "exit") == 0)
            break;

        if (strcmp(input, "test") == 0) {

            thisClient.Test();
        }

    }
    return 0;
}