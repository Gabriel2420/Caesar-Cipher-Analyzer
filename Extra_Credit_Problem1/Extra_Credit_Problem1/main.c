#define _CRT_SECURE_NO_WARNINGS
#include "CaesarCipherCracker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_text_from_keyboard(char* text, int max_length)
{
    printf("Enter text: ");
    fgets(text, max_length, stdin);
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n')
        text[len - 1] = '\0';
}

void read_text_from_file(const char* filename, char* text, int max_length)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        return;
    }

    size_t total_read = 0;
    while (fgets(text + total_read, max_length - total_read, file) != NULL && total_read < max_length - 1)
    {
        total_read += strlen(text + total_read);
    }
    text[total_read] = '\0';
    fclose(file);
}

void encrypt_with_specific_shift(const char* text, int shift, char* encrypted_text)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            encrypted_text[i] = 'a' + (text[i] - 'a' + shift) % 26;
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            encrypted_text[i] = 'A' + (text[i] - 'A' + shift) % 26;
        }
        else
        {
            encrypted_text[i] = text[i];
        }
    }
    encrypted_text[i] = '\0';
}

void decrypt_with_specific_shift(const char* text, int shift, char* decrypted_text)
{
    encrypt_with_specific_shift(text, 26 - shift, decrypted_text);
}

void display_computed_distribution(const double distribution[ALPHABET_SIZE])
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        printf("%c: %.2f\n", 'a' + i, distribution[i]);
    }
}

int main()
{
    char text[1000] = "";
    char encrypted_text[1000] = "";
    char decrypted_text[1000] = "";
    int shift;

    while (1)
    {
        printf("\n--- Caesar Cipher Cracker ---\n");
        printf("1. Read text from keyboard\n");
        printf("2. Read text from file\n");
        printf("3. Encrypt text\n");
        printf("4. Decrypt text with known shift\n");
        printf("5. Break encryption (find shift)\n");
        printf("6. Compute letter frequency distribution\n");
        printf("7. Exit\n");
        printf("Choose an option: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        while ((getchar()) != '\n');

        switch (choice)
        {
        case 1:
            read_text_from_keyboard(text, 1000);
            printf("Text: %s\n", text);
            break;

        case 2:
            printf("Enter filename: ");
            char filename[100];
            scanf("%99s", filename);
            while ((getchar()) != '\n');
            read_text_from_file(filename, text, 1000);
            printf("Read text: %s\n", text);
            break;

        case 3:
            printf("Enter shift value: ");
            scanf("%d", &shift);
            while ((getchar()) != '\n');
            memset(encrypted_text, 0, sizeof(encrypted_text));
            encrypt_with_specific_shift(text, shift, encrypted_text);
            printf("Encrypted Text: %s\n", encrypted_text);
            break;

        case 4:
            if (encrypted_text[0] == '\0') {
                printf("Error: No encrypted text available. Please encrypt a message first.\n");
                break;
            }
            printf("Enter shift value for decryption: ");
            scanf("%d", &shift);
            while ((getchar()) != '\n');
            memset(decrypted_text, 0, sizeof(decrypted_text));
            decrypt_with_specific_shift(encrypted_text, shift, decrypted_text);
            printf("Decrypted Text: %s\n", decrypted_text);
            break;

        case 5:
            if (encrypted_text[0] == '\0') {
                printf("Error: No encrypted text available. Please encrypt a message first.\n");
                break;
            }
            int top_shifts[TOP_N];
            double top_distances[TOP_N];
            break_caesar_cipher(encrypted_text, top_shifts, top_distances, euclidean_distance);
            printf("Most likely shift: %d\n", top_shifts[0]);
            decrypt_with_specific_shift(encrypted_text, top_shifts[0], decrypted_text);
            printf("Decrypted Text: %s\n", decrypted_text);
            break;
        case 6:
        {
            printf("Distribution of which text you want to find?\n");
            printf("1. Text\n");
            printf("2. Encrypted Text\n");
            printf("3. Decrypted Text\n");
            printf("Choose an option: ");
            int choice;
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');
                continue;
            }
            while ((getchar()) != '\n');
            switch (choice)
            {
            case 1:
            {
                double distribution[ALPHABET_SIZE];
                compute_histogram(text, distribution);
                display_computed_distribution(distribution);
                break;
            }
            case 2:
            {
                if (encrypted_text[0] == '\0') {
                    printf("Error: No encrypted text available. Please encrypt a message first.\n");
                    break;
                }
                double distribution[ALPHABET_SIZE];
                compute_histogram(encrypted_text, distribution);
                display_computed_distribution(distribution);
                break;
            }
            case 3:
            {
                if (decrypted_text[0] == '\0') {
                    printf("Error: No decrypted text available. Please decrypt a message first.\n");
                    break;
                }
                double distribution[ALPHABET_SIZE];
                compute_histogram(decrypted_text, distribution);
                display_computed_distribution(distribution);
                break;
            }
            default:
                printf("Invalid choice. Try again.\n");
            }
            break;
        }
        case 7:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
