#include "election.h"

int main() {
    while (1) {
        printf("\n\n=============================");
        printf("\n    MINI VOTING SYSTEM");
        printf("\n=============================");
        printf("\n  1. Student Panel");
        printf("\n  2. Admin Panel");
        printf("\n  3. Exit");
        printf("\n  Option: ");

        char input;
        scanf(" %c", &input);

        switch (input) {
            case '1': studentPanel(); break;
            case '2': adminPanel();   break;
            case '3': return 0;
            default:
                printf("\n  Invalid option!");
                getch();
        }
    }
    return 0;
}
