#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "contacts.dat"

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

void addContact() {
    Contact c;
    FILE *fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name: ");
    getchar(); // to consume leftover newline
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0; // remove newline

    printf("Enter phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;

    printf("Enter email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    fwrite(&c, sizeof(Contact), 1, fp);
    fclose(fp);
    printf("Contact added successfully.\n");
}

void viewContacts() {
    Contact c;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n--- All Contacts ---\n");

    while (fread(&c, sizeof(Contact), 1, fp)) {
        printf("\nName: %s\nPhone: %s\nEmail: %s\n", c.name, c.phone, c.email);
    }

    fclose(fp);
}

void searchContact() {
    char searchName[50];
    Contact c;
    int found = 0;

    printf("Enter name to search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.name, searchName) == 0) {
            printf("\n--- Contact Found ---\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\n", c.name, c.phone, c.email);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Contact not found.\n");
    }
}

void deleteContact() {
    char deleteName[50];
    Contact c;
    int found = 0;

    printf("Enter name to delete: ");
    getchar();
    fgets(deleteName, sizeof(deleteName), stdin);
    deleteName[strcspn(deleteName, "\n")] = 0;

    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.name, deleteName) != 0) {
            fwrite(&c, sizeof(Contact), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n====== Contact Management System ======\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
