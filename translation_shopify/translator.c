#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Braille representations for alphabet letters, capital indicator, numbers, and space
const char* braille_alphabet[] = {
    "O.....", "O.O...", "OO....", "OO.O..", "O..O..", "OOO...", "OOOO..", "O.OO..", ".OO...", ".OOO..", // a-j
    "O...O.", "O.O.O.", "OO..O.", "OO.OO.", "O..OO.", "OOO.O.", "OOOOO.", "O.OOO.", ".OO.O.", ".OOOO.", // k-t
    "O...OO", "O.O.OO", "OO..OO", "OO.OOO", "O..OOO", "OOO.OO"                                         // u-z
};
const char* braille_numbers[] = {
    ".O.OOO", "O.....", "O.O...", "OO....", "OO.O..", "O..O..", "OOO...", "OOOO..", "O.OO..", ".OO..."  // 1-9, 0
};
const char* braille_space = "......";
const char* braille_capital = ".....O";
const char* braille_number = ".O.OOO";

// Function to determine if the input is Braille (returns true if Braille)
bool is_braille(const char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != 'O' && input[i] != '.' && input[i] != ' ') {
            return false; // Non-braille characters found, so it's English
        }
    }
    return true; // Only Braille characters found
}

// Function to convert English to Braille
void english_to_braille(const char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {
            printf("%s", braille_space);
        }
        else if (input[i] >= 'A' && input[i] <= 'Z') {
            printf("%s", braille_capital); // Capital indicator
            printf("%s", braille_alphabet[input[i] - 'A']);
        }
        else if (input[i] >= 'a' && input[i] <= 'z') {
            printf("%s", braille_alphabet[input[i] - 'a']);
        }
        else if (input[i] >= '0' && input[i] <= '9') {
            printf("%s", braille_number); // Number indicator
            printf("%s", braille_numbers[input[i] - '0']);
        }
        printf(" ");
    }
    printf("\n");
}

// Function to convert Braille to English
void braille_to_english(const char* input) {
    char buffer[7] = { 0 }; // Temporary storage for each 6-dot braille character
    bool is_capital = false, is_number = false;
    int len = strlen(input);

    for (int i = 0, j = 0; i < len; i++) {
        if (input[i] == ' ') continue; // Skip spaces in Braille
        buffer[j++] = input[i];

        // Once we've read 6 characters, it's a full Braille symbol
        if (j == 6) {
            buffer[j] = '\0'; // Null-terminate the buffer

            // Check for special symbols (capital and number indicators)
            if (strcmp(buffer, braille_capital) == 0) {
                is_capital = true;
            }
            else if (strcmp(buffer, braille_number) == 0) {
                is_number = true;
            }
            else if (strcmp(buffer, braille_space) == 0) {
                printf(" "); // Output a space
            }
            else {
                // Decode letters and numbers
                if (is_number) {
                    for (int n = 0; n < 10; n++) {
                        if (strcmp(buffer, braille_numbers[n]) == 0) {
                            printf("%d", n);
                            break;
                        }
                    }
                    is_number = false;
                }
                else {
                    for (int l = 0; l < 26; l++) {
                        if (strcmp(buffer, braille_alphabet[l]) == 0) {
                            if (is_capital) {
                                printf("%c", 'A' + l);
                                is_capital = false;
                            }
                            else {
                                printf("%c", 'a' + l);
                            }
                            break;
                        }
                    }
                }
            }
            j = 0; // Reset buffer index for next Braille symbol
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string to translate>\n", argv[0]);
        return 1;
    }

    // Determine if the input is Braille or English
    const char* input = argv[1];
    if (is_braille(input)) {
        braille_to_english(input);
    }
    else {
        english_to_braille(input);
    }

    return 0;
}
