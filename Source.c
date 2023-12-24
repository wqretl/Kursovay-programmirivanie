#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_TAGS 5
#define MAX_NAME_LENGTH 100
#define MAX_DATE_LENGTH 20
#define MAX_LOCATION_LENGTH 100
#define MAX_CATEGORY_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    float date[MAX_DATE_LENGTH];
    char location[MAX_LOCATION_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int tags[MAX_TAGS][MAX_NAME_LENGTH];
    float fileSize;
} Photo;

int addPhoto(Photo* database, int size);
int searchByTag(Photo* database, int size, char searchTag[]);
void sortByDate(Photo* database, int size);
int saveDataToFile(Photo* database, int size);
int printDataFromFile(Photo* database, int size);
int searchByName(Photo* database, int size, char* searchName);
int main() {
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    Photo database[100];
    int* ptr_database;
    ptr_database = &database;
    int size = 0;
    int choice;
    do {
        printf("����� ���������� � ���������!\n");
        printf("_______________________________________________________________________________________________________________________\n");
        printf("����\n");
        printf("�������� ��������\n");
        printf("1 �������� ����� ����������\n");
        printf("2 ����� ���������� �� ����\n");
        printf("3 ���������� �� ���� ������\n");
        printf("4 ��������� ������\n");
        printf("5 ��������� ������\n");
        printf("6 ����� ���������� �� ��������\n");
        printf("7 �����\n");
        printf("_______________________________________________________________________________________________________________________\n");
        scanf("%d", &choice);
        char searchTag[MAX_NAME_LENGTH];
        char searchName[100];
        switch (choice)
        {
        case 1:
            addPhoto(database, size);
            size++;

            break;
        case 2:

            printf("������� ��� ��� ������: ");
            scanf("%s", searchTag);
            searchByTag(database, size, searchTag);
            break;
        case 3:
            sortByDate(database, size);
            printf("���� ������ ������������� �� ���� ������\n");
            break;
        case 4:
        {
            saveDataToFile(database, size);
            break;
        }
        case 5:
        {
            printDataFromFile(database, size);
            break;
        }
        case 6:

            printf("������� �������� ���������� ��� ������: ");
            scanf("%s", searchName);
            searchByName(database, size, searchName);

            break;

        case 7:
            printf("����� �� ���������  ");
            return 0;
            break;
        default:
            break;
        }
    } while (choice != 7);
    return 0;
}
int  addPhoto(Photo* database, int size) {
    printf("������� �������� ����������: ");
    scanf("%s", database[size].name);
    printf("������� ���� ������ (����-��-��): ");
    scanf("%s", database[size].date);
    printf("������� ����� ������: ");
    scanf("%s", database[size].location);
    printf("������� ���������: ");
    scanf("%s", database[size].category);
    printf("������� ���� (�� 5 ����, ������ ����� ������): ");
    for (int i = 0; i < MAX_TAGS; i++) {
        scanf("%s", database[size].tags[i]);
    }
    printf("������� ������ �����: ");
    scanf("%f", &database[size].fileSize);
    return  1;

}

int searchByTag(Photo* database, int size, char searchTags[MAX_TAGS][MAX_NAME_LENGTH]) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        int tagMatchCount = 0;
        for (int j = 0; j < MAX_TAGS; j++) {
            for (int k = 0; k < MAX_TAGS; k++) {
                if (strlen(searchTags[k]) > 0 && strcmp(database[i].tags[j], searchTags[k]) == 0) {
                    tagMatchCount++;
                    break;
                }
            }
        }
        if (tagMatchCount > 0) {
            printf("������� ���������� �� �����:\n");
            printf("��������: %s\n", database[i].name);
            printf("���� ������: %s\n", database[i].date);
            printf("����� ������: %s\n", database[i].location);
            printf("���������: %s\n", database[i].category);
            printf("����: ");
            for (int k = 0; k < MAX_TAGS; k++) {
                if (strlen(database[i].tags[k]) > 0) {
                    printf("%s ", database[i].tags[k]);
                }
            }
            printf("\n");
            printf("������ �����: %.2f\n", database[i].fileSize);
            found = 1;
        }
    }
    if (!found) {
        printf("���������� �� ����� �� �������\n");
    }
    return found;
}

void sortByDate(Photo* database, int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            int year1, month1, day1;
            int year2, month2, day2;
            sscanf(database[j].date, "%d-%d-%d", &year1, &month1, &day1);
            sscanf(database[j + 1].date, "%d-%d-%d", &year2, &month2, &day2);
            if (year1 > year2 || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2)) {
                // ����� ����������
                Photo temp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = temp;
            }
        }
    }
}
int saveDataToFile(Photo* database, int size)
{
    FILE* file = fopen("photo_database.txt", "a");
    if (file == NULL) {
        printf("������ �������� �����");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "��������: %s\n", database[i].name);
        fprintf(file, "���� ������: %s\n", database[i].date);
        fprintf(file, "����� ������: %s\n", database[i].location);
        fprintf(file, "���������: %s\n", database[i].category);
        fprintf(file, "����:\n");
        for (int j = 0; j < MAX_TAGS; j++) {
            if (strlen(database[i].tags[j]) > 0) {
                fprintf(file, "%s ", database[i].tags[j]);
            }
        }
        fprintf(file, "\n");
        fprintf(file, "������ �����: %f\n", database[i].fileSize);
        fprintf(file, "_______________________________________________________________________________________________________________________\n");
    }
    fclose(file);
    printf("������ ��������� � ���� photo_database.txt\n");
    return 1;
}

int printDataFromFile()
{
    FILE* file = fopen("photo_database.txt", "r");
    if (file == NULL) {
        printf("������ �������� �����");
        return;
    }
    char buffer[1000];
    while (fgets(buffer, 1000, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
    return 1;
}
int searchByName(Photo* database, int size, char* searchName) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(database[i].name, searchName) == 0) {
            printf("������� ���������� �� ��������:\n");
            printf("��������: %s\n", database[i].name);
            printf("���� ������: %s\n", database[i].date);
            printf("����� ������: %s\n", database[i].location);
            printf("���������: %s\n", database[i].category);
            printf("����: ");
            for (int k = 0; k < MAX_TAGS; k++) {
                if (strlen(database[i].tags[k]) > 0) {
                    printf("%s ", database[i].tags[k]);
                }
            }
            printf("\n");
            printf("������ �����: %.2f\n", database[i].fileSize);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("���������� � ����� ������ �� �������\n");
    }

}


