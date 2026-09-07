#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

char lines[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

void displayDocument()
{
    if (lineCount == 0)
    {
        printf("\n[Document is empty]\n");
        return;
    }

    printf("\n--------- DOCUMENT ---------\n");

    for (int i = 0; i < lineCount; i++)
    {
        printf("%d | %s\n", i + 1, lines[i]);
    }

    printf("----------------------------\n");
}

void insertLine()
{
    int lineNumber;
    char text[MAX_LENGTH];

    printf("Enter line number: ");
    scanf("%d", &lineNumber);
    getchar();

    if (lineNumber < 1 || lineNumber > lineCount + 1)
    {
        printf("[ERROR] Invalid line number.\n");
        return;
    }

    if (lineCount >= MAX_LINES)
    {
        printf("[ERROR] Document is full.\n");
        return;
    }

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);

    text[strcspn(text, "\n")] = '\0';

    for (int i = lineCount; i >= lineNumber; i--)
    {
        strcpy(lines[i], lines[i - 1]);
    }

    strcpy(lines[lineNumber - 1], text);
    lineCount++;

    printf("[SUCCESS] Line inserted.\n");
}

void deleteLine()
{
    int lineNumber;

    if (lineCount == 0)
    {
        printf("\n[ERROR] Document is empty.\n");
        return;
    }

    printf("Enter line number to delete: ");
    scanf("%d", &lineNumber);
    getchar();

    if (lineNumber < 1 || lineNumber > lineCount)
    {
        printf("[ERROR] Invalid line number.\n");
        return;
    }

    for (int i = lineNumber - 1; i < lineCount - 1; i++)
    {
        strcpy(lines[i], lines[i + 1]);
    }

    lineCount--;

    printf("[SUCCESS] Line deleted.\n");
}

void saveFile()
{
    char filename[100];
    FILE *file;

    printf("Enter file name: ");
    scanf("%99s", filename);

    file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("[ERROR] Could not save file.\n");
        return;
    }

    for (int i = 0; i < lineCount; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);

    printf("[SUCCESS] File saved.\n");
}

void loadFile()
{
    char filename[100];
    FILE *file;

    printf("Enter file name: ");
    scanf("%99s", filename);

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("[ERROR] Could not open file.\n");
        return;
    }

    lineCount = 0;

    while (lineCount < MAX_LINES &&
           fgets(lines[lineCount], MAX_LENGTH, file) != NULL)
    {
        lines[lineCount][strcspn(lines[lineCount], "\n")] = '\0';
        lineCount++;
    }

    fclose(file);

    printf("[SUCCESS] File loaded.\n");
}

void searchText()
{
    char search[MAX_LENGTH];
    int found = 0;

    printf("Enter word or phrase to search: ");
    fgets(search, MAX_LENGTH, stdin);

    search[strcspn(search, "\n")] = '\0';

    if (strlen(search) == 0)
    {
        printf("[ERROR] Search text cannot be empty.\n");
        return;
    }

    for (int i = 0; i < lineCount; i++)
    {
        if (strstr(lines[i], search) != NULL)
        {
            printf("Found in line %d: %s\n", i + 1, lines[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("[NOT FOUND] The text was not found.\n");
    }
}

void showHelp()
{
    printf("\n========== HELP ==========\n");

    printf("1. Insert Line\n");
    printf("   Add a new line at a given position.\n\n");

    printf("2. Delete Line\n");
    printf("   Delete a line using its line number.\n\n");

    printf("3. Display Document\n");
    printf("   Show all lines with line numbers.\n\n");

    printf("4. Save File\n");
    printf("   Save the document to a text file.\n\n");

    printf("5. Load File\n");
    printf("   Load a text file into the editor.\n\n");

    printf("6. Search\n");
    printf("   Find a word or phrase in the document.\n\n");

    printf("7. Help\n");
    printf("   Show this help information.\n\n");

    printf("8. Exit\n");
    printf("   Close the line editor.\n");

    printf("==========================\n");
}

int main()
{
    int choice;

    printf("=================================\n");
    printf("        SIMPLE LINE EDITOR       \n");
    printf("=================================\n");

    while (1)
    {
        printf("\n1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Display Document\n");
        printf("4. Save File\n");
        printf("5. Load File\n");
        printf("6. Search\n");
        printf("7. Help\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

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
                showHelp();
                break;

            case 8:
                printf("\nExiting Line Editor...\n");
                return 0;

            default:
                printf("\n[ERROR] Invalid choice.\n");
        }
    }

    return 0;
}