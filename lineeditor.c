#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LENGTH 256

char document[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

// Function declarations
void insertLine();
void deleteLine();
void displayDocument();
void saveFile();
void loadFile();
void searchText();
void findAndReplace();
void showStatistics();
void clearInputBuffer();

int main()
{
    int choice;

    printf("=====================================\n");
    printf("       SIMPLE LINE EDITOR IN C       \n");
    printf("=====================================\n");

    do
    {
        printf("\n----------- MENU -----------\n");
        printf("1. Insert a line\n");
        printf("2. Delete a line\n");
        printf("3. Display document\n");
        printf("4. Save document to file\n");
        printf("5. Load document from file\n");
        printf("6. Search text\n");
        printf("7. Find and replace\n");
        printf("8. Line count / Word count\n");
        printf("9. Exit\n");
        printf("----------------------------\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
            case 1:
                insertLine();
                break;

            case 2:
                deleteLine();
                break;

            case 3:
                displayDocument();
                break;

            case 4:
                saveFile();
                break;

            case 5:
                loadFile();
                break;

            case 6:
                searchText();
                break;

            case 7:
                findAndReplace();
                break;

            case 8:
                showStatistics();
                break;

            case 9:
                printf("\nExiting Line Editor...\n");
                break;

            default:
                printf("Invalid choice! Please enter 1-9.\n");
        }

    } while (choice != 9);

    return 0;
}


// ---------------------------------------------------
// Clear input buffer
// ---------------------------------------------------

void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Clear remaining characters
    }
}


// ---------------------------------------------------
// Insert a line
// ---------------------------------------------------

void insertLine()
{
    int lineNumber;
    int i;
    char text[MAX_LENGTH];

    if (lineCount >= MAX_LINES)
    {
        printf("Document is full!\n");
        return;
    }

    printf("Enter line number (1 to %d): ", lineCount + 1);

    if (scanf("%d", &lineNumber) != 1)
    {
        printf("Invalid line number!\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (lineNumber < 1 || lineNumber > lineCount + 1)
    {
        printf("Invalid line number!\n");
        return;
    }

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);

    // Remove newline added by fgets
    text[strcspn(text, "\n")] = '\0';

    // Shift existing lines downward
    for (i = lineCount; i >= lineNumber; i--)
    {
        strcpy(document[i], document[i - 1]);
    }

    strcpy(document[lineNumber - 1], text);

    lineCount++;

    printf("Line inserted successfully!\n");
}


// ---------------------------------------------------
// Delete a line
// ---------------------------------------------------

void deleteLine()
{
    int lineNumber;
    int i;

    if (lineCount == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("Enter line number to delete: ");

    if (scanf("%d", &lineNumber) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (lineNumber < 1 || lineNumber > lineCount)
    {
        printf("Invalid line number!\n");
        return;
    }

    // Shift lines upward
    for (i = lineNumber - 1; i < lineCount - 1; i++)
    {
        strcpy(document[i], document[i + 1]);
    }

    lineCount--;

    printf("Line %d deleted successfully!\n", lineNumber);
}


// ---------------------------------------------------
// Display document
// ---------------------------------------------------

void displayDocument()
{
    int i;

    if (lineCount == 0)
    {
        printf("\nDocument is empty!\n");
        return;
    }

    printf("\n========== DOCUMENT ==========\n");

    for (i = 0; i < lineCount; i++)
    {
        printf("%d: %s\n", i + 1, document[i]);
    }

    printf("==============================\n");
}


// ---------------------------------------------------
// Save document to file
// ---------------------------------------------------

void saveFile()
{
    FILE *file;
    char filename[100];
    int i;

    printf("Enter filename (example: document.txt): ");
    fgets(filename, sizeof(filename), stdin);

    filename[strcspn(filename, "\n")] = '\0';

    file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < lineCount; i++)
    {
        fprintf(file, "%s\n", document[i]);
    }

    fclose(file);

    printf("Document saved successfully to %s\n", filename);
}


// ---------------------------------------------------
// Load document from file
// ---------------------------------------------------

void loadFile()
{
    FILE *file;
    char filename[100];

    printf("Enter filename to load: ");
    fgets(filename, sizeof(filename), stdin);

    filename[strcspn(filename, "\n")] = '\0';

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("File not found or could not be opened!\n");
        return;
    }

    lineCount = 0;

    while (lineCount < MAX_LINES &&
           fgets(document[lineCount], MAX_LENGTH, file) != NULL)
    {
        // Remove newline character
        document[lineCount]
            [strcspn(document[lineCount], "\n")] = '\0';

        lineCount++;
    }

    fclose(file);

    printf("File loaded successfully!\n");
    printf("%d line(s) loaded.\n", lineCount);
}


// ---------------------------------------------------
// Search text
// ---------------------------------------------------

void searchText()
{
    char search[MAX_LENGTH];
    int i;
    int found = 0;

    if (lineCount == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("Enter word or phrase to search: ");
    fgets(search, MAX_LENGTH, stdin);

    search[strcspn(search, "\n")] = '\0';

    printf("\nSearch results:\n");

    for (i = 0; i < lineCount; i++)
    {
        if (strstr(document[i], search) != NULL)
        {
            printf("Found on line %d: %s\n",
                   i + 1, document[i]);

            found = 1;
        }
    }

    if (!found)
    {
        printf("Text not found in the document.\n");
    }
}


// ---------------------------------------------------
// Find and Replace
// ---------------------------------------------------

void findAndReplace()
{
    char find[MAX_LENGTH];
    char replace[MAX_LENGTH];
    char newLine[MAX_LENGTH];

    char *position;

    int lineNumber;
    int beforeLength;

    if (lineCount == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("Enter line number: ");

    if (scanf("%d", &lineNumber) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (lineNumber < 1 || lineNumber > lineCount)
    {
        printf("Invalid line number!\n");
        return;
    }

    printf("Enter text to find: ");
    fgets(find, MAX_LENGTH, stdin);
    find[strcspn(find, "\n")] = '\0';

    printf("Enter replacement text: ");
    fgets(replace, MAX_LENGTH, stdin);
    replace[strcspn(replace, "\n")] = '\0';

    position = strstr(document[lineNumber - 1], find);

    if (position == NULL)
    {
        printf("Text not found on line %d.\n", lineNumber);
        return;
    }

    beforeLength = position - document[lineNumber - 1];

    // Copy text before searched word
    strncpy(newLine,
            document[lineNumber - 1],
            beforeLength);

    newLine[beforeLength] = '\0';

    // Add replacement text
    strcat(newLine, replace);

    // Add remaining text
    strcat(newLine, position + strlen(find));

    strcpy(document[lineNumber - 1], newLine);

    printf("Text replaced successfully!\n");
}


// ---------------------------------------------------
// Line count and Word count
// ---------------------------------------------------

void showStatistics()
{
    int words = 0;
    int i;
    int j;
    int inWord;

    for (i = 0; i < lineCount; i++)
    {
        inWord = 0;

        for (j = 0; document[i][j] != '\0'; j++)
        {
            if (document[i][j] != ' ' &&
                document[i][j] != '\t')
            {
                if (!inWord)
                {
                    words++;
                    inWord = 1;
                }
            }
            else
            {
                inWord = 0;
            }
        }
    }

    printf("\n======= DOCUMENT STATISTICS =======\n");
    printf("Total lines : %d\n", lineCount);
    printf("Total words : %d\n", words);
    printf("===================================\n");
}