#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Union for possible fields
union FormField {
    char name[50];
    int age;
    char email[50];
    float marks;
    char mobile[20];   // +countrycode + 10 digits
};

// Struct combines union + a tag
struct StudentForm {
    int fieldType;          // 1=Name, 2=Age, 3=Email, 4=Marks, 5=Mobile
    union FormField field;  // one active field at a time
};

// Function to display form data
void displayForm(struct StudentForm s) {
    printf("\n===== Current Field Data =====\n");
    switch(s.fieldType) {
        case 1: printf("Name   : %s\n", s.field.name); break;
        case 2: printf("Age    : %d\n", s.field.age); break;
        case 3: printf("Email  : %s\n", s.field.email); break;
        case 4: printf("Marks  : %.2f\n", s.field.marks); break;
        case 5: printf("Mobile : %s\n", s.field.mobile); break;
        default: printf("No data entered yet!\n");
    }
}

// Function to validate mobile number (+CC XXXXXXXXXX)
int validateMobile(const char *mobile) {
    int len = strlen(mobile);

    // Must start with '+'
    if (mobile[0] != '+') return 0;

    // Find where digits start after country code
    int i = 1;
    while (isdigit(mobile[i])) i++;  // skip country code digits

    // Remaining must be exactly 10 digits
    int remaining = len - i;
    if (remaining != 10) return 0;

    // Check last 10 are digits
    for (int j = i; j < len; j++) {
        if (!isdigit(mobile[j])) return 0;
    }

    return 1; // valid
}

int main() {
    struct StudentForm student;
    student.fieldType = 0; // nothing yet
    int choice;

    do {
        printf("\n===== Student Form Menu (Struct + Union) =====\n");
        printf("1. Enter Name\n");
        printf("2. Enter Age\n");
        printf("3. Enter Email\n");
        printf("4. Enter Marks\n");
        printf("5. Enter Mobile Number (+CountryCodeXXXXXXXXXX)\n");
        printf("6. Display Current Field\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter Name: ");
                scanf(" %[^\n]", student.field.name);
                student.fieldType = 1;
                break;

            case 2:
                printf("Enter Age: ");
                scanf("%d", &student.field.age);
                student.fieldType = 2;
                break;

            case 3:
                printf("Enter Email: ");
                scanf(" %[^\n]", student.field.email);
                student.fieldType = 3;
                break;

            case 4:
                printf("Enter Marks: ");
                scanf("%f", &student.field.marks);
                student.fieldType = 4;
                break;

            case 5: {
                char temp[20];
                printf("Enter Mobile (with country code, e.g. +911234567890): ");
                scanf(" %[^\n]", temp);
                if (validateMobile(temp)) {
                    strcpy(student.field.mobile, temp);
                    student.fieldType = 5;
                } else {
                    printf("❌ Invalid mobile number! Must be +CCXXXXXXXXXX (10 digits after country code).\n");
                }
                break;
            }

            case 6:
                displayForm(student);
                break;

            case 0:
                printf("Exiting... Thank you!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);

    return 0;
}
