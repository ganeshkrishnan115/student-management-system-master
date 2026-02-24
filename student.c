#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Student struct Stud

/* ===== STRUCT ===== */

struct Stud
{
    char name[100];
    char dept[50];
    int roll;
    float sgpa[12];
    float cgpa;
};

/* ===== FUNCTION DECLARATIONS ===== */

void add(FILE *fp);
void modify(FILE *fp);
void display(FILE *fp);
void individual(FILE *fp);
FILE *delete_student(FILE *fp);
void clear_input_buffer();

/* ===== MAIN FUNCTION ===== */

int main()
{
    FILE *fp;
    int option;

    fp = fopen("db.txt", "rb+");

    if (fp == NULL)
    {
        fp = fopen("db.txt", "wb+");
        if (fp == NULL)
        {
            printf("Error opening file.\n");
            return 0;
        }
    }

    while (1)
    {
        printf("\n==============================\n");
        printf(" Student Management System\n");
        printf("==============================\n");

        printf("\n1. Add Student");
        printf("\n2. Modify Student");
        printf("\n3. Show All Students");
        printf("\n4. Individual View");
        printf("\n5. Delete Student");
        printf("\n6. Exit");

        printf("\n\nEnter option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1: add(fp); break;
            case 2: modify(fp); break;
            case 3: display(fp); break;
            case 4: individual(fp); break;
            case 5: fp = delete_student(fp); break;
            case 6: fclose(fp); return 0;
            default: printf("Invalid option\n");
        }
    }
}

/* ===== ADD STUDENT ===== */

void add(FILE *fp)
{
    Student s;
    int i;
    float total;
    char another = 'y';

    fseek(fp, 0, SEEK_END);

    while (another == 'y' || another == 'Y')
    {
        clear_input_buffer();

        printf("\nEnter Name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = 0;

        printf("Enter Department: ");
        fgets(s.dept, sizeof(s.dept), stdin);
        s.dept[strcspn(s.dept, "\n")] = 0;

        printf("Enter Roll: ");
        scanf("%d", &s.roll);

        printf("Enter SGPA for 12 semesters:\n");

        total = 0;
        for (i = 0; i < 12; i++)
        {
            scanf("%f", &s.sgpa[i]);
            total += s.sgpa[i];
        }

        s.cgpa = total / 12.0;

        fwrite(&s, sizeof(s), 1, fp);

        printf("Add another student? (y/n): ");
        clear_input_buffer();
        scanf("%c", &another);
    }
}

/* ===== MODIFY STUDENT ===== */

void modify(FILE *fp)
{
    Student s;
    int roll, found = 0, i;
    float total;

    printf("\nEnter Roll to Modify: ");
    scanf("%d", &roll);

    rewind(fp);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (s.roll == roll)
        {
            found = 1;
            fseek(fp, -sizeof(s), SEEK_CUR);

            clear_input_buffer();

            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter New Department: ");
            fgets(s.dept, sizeof(s.dept), stdin);
            s.dept[strcspn(s.dept, "\n")] = 0;

            printf("Enter New Roll: ");
            scanf("%d", &s.roll);

            printf("Enter SGPA for 12 semesters:\n");

            total = 0;
            for (i = 0; i < 12; i++)
            {
                scanf("%f", &s.sgpa[i]);
                total += s.sgpa[i];
            }

            s.cgpa = total / 12.0;

            fwrite(&s, sizeof(s), 1, fp);
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");
}

/* ===== DISPLAY ALL ===== */

void display(FILE *fp)
{
    Student s;
    int i;

    rewind(fp);

    printf("\nAll Students:\n");

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("\nName: %s", s.name);
        printf("\nDepartment: %s", s.dept);
        printf("\nRoll: %d", s.roll);

        printf("\nSGPA: ");
        for (i = 0; i < 12; i++)
            printf("%.2f ", s.sgpa[i]);

        printf("\nCGPA: %.2f", s.cgpa);
        printf("\n---------------------------\n");
    }
}

/* ===== INDIVIDUAL VIEW ===== */

void individual(FILE *fp)
{
    Student s;
    int roll, found = 0, i;

    printf("\nEnter Roll: ");
    scanf("%d", &roll);

    rewind(fp);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (s.roll == roll)
        {
            found = 1;

            printf("\nName: %s", s.name);
            printf("\nDepartment: %s", s.dept);
            printf("\nRoll: %d", s.roll);

            printf("\nSGPA: ");
            for (i = 0; i < 12; i++)
                printf("%.2f ", s.sgpa[i]);

            printf("\nCGPA: %.2f\n", s.cgpa);
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");
}

/* ===== DELETE STUDENT ===== */

FILE *delete_student(FILE *fp)
{
    Student s;
    FILE *temp;
    int roll, found = 0;

    temp = fopen("temp.txt", "wb");

    printf("\nEnter Roll to Delete: ");
    scanf("%d", &roll);

    rewind(fp);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (s.roll == roll)
        {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("db.txt");
    rename("temp.txt", "db.txt");

    fp = fopen("db.txt", "rb+");

    if (!found)
        printf("Record not found.\n");
    else
        printf("Record deleted successfully.\n");

    return fp;
}

/* ===== CLEAR BUFFER ===== */

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}