// Harvard CS50x - Week 4 - Problem Set 4 
// Recover: https://cs50.harvard.edu/x/psets/4/recover/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
uint8_t JPEG_SIGNATURE_3[] = {0xff, 0xd8, 0xff};

bool check_jpg(uint8_t block[]);

int main(int argc, char *argv[])
{
    // User input check
    if (argc != 2)
    {
        printf("Usage: ./recover [forensic image name]\n");

        return 1;
    }

    // File opening check
    FILE *recovery_file = fopen(argv[1], "r");

    if (recovery_file == NULL)
    {
        printf("Could not open %s\n", argv[1]);

        return 1;
    }

    // Images recovery
    int image_counter = 0;

    char file_name[9]; // File name as 000.jpg, 001.jpg ...

    uint8_t buffer[BLOCK_SIZE];

    FILE *current_file; // Outside pointer of opened file

    while (fread(buffer, 1, BLOCK_SIZE, recovery_file) == BLOCK_SIZE) // Files can only
                                                                      // be written in blocks
                                                                      // of 512 bytes
    {
        if (check_jpg(buffer) == true)
        {
            if (image_counter == 0) // First JPG found
            {
                sprintf(file_name, "%03i.jpg", image_counter);

                current_file = fopen(file_name, "w");

                fwrite(buffer, BLOCK_SIZE, 1, current_file);

                image_counter++;
            }
            else // New JPG found (not first)
            {
                fclose(current_file);

                sprintf(file_name, "%03i.jpg", image_counter);

                current_file = fopen(file_name, "w");

                fwrite(buffer, BLOCK_SIZE, 1, current_file);

                image_counter++;
            }
        }
        else if (image_counter != 0) // Continuity of opened jpg
        {
            fwrite(buffer, BLOCK_SIZE, 1, current_file);
        }
    }

    if (image_counter != 0)   // Guard against a not jpg file
        fclose(current_file); // Close last .jpg file

    fclose(recovery_file);
}

bool check_jpg(uint8_t block[])
{
    // Check first 3 numbers as signature
    for (int i = 0; i < 3; i++)
    {
        if (block[i] != JPEG_SIGNATURE_3[i])
            return false;
    }

    // Check fourth number as signature (inside the range of values)
    if (block[3] >= 0xe0 && block[3] <= 0xef)
        return true;

    return false;
}
