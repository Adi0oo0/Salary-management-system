
// IMPORTS ----------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ------------------------------------------------------------------------------------------

// PROTOTYPES -------------------------------------------------------------------------------

int input_0(void);
void administrator(void);
void add_employee(void);
void remove_employee(void);
void display_all_employees(void);
void update_employee(void);



// ------------------------------------------------------------------------------------------

// GVs --------------------------------------------------------------------------------------

char *employees[100];
long employee_salary[100];
long allowance[100];


// ------------------------------------------------------------------------------------------

// MAIN -------------------------------------------------------------------------------------
int main(){
    while (1) {
        
    int option = input_0();
    if (option == 1) {
        printf("=================================================================================================================\n");
        administrator();
    } else if (option == 2) {
        printf("Calculate Salary selected.\n");
    } else if (option == 3) {
        printf("Help selected.\n");
    } else if (option == 4) {
        printf("Exit selected.\n");
        return 0;
    } else {
        printf("Invalid option selected.\n");
    }

}

}
// ------------------------------------------------------------------------------------------

// FUNCTIONS --------------------------------------------------------------------------------

int input_0(void){
    printf("Select an integer option among: \n");
    printf("1. Administrator\t2. Calculate Salary\t3. Help\t\t4. Exit\n--> ");
    int option;
    scanf("%d", &option);
    getchar();
    if (option < 1 || option > 4) {
        printf("\n\n!Invalid option selected. Please try again.\n");
        return input_0();
    }
    return option;
}

void administrator(void){
    while (1) {
        printf("\nAdministrator Menu:\n");
        printf("Select an integer option among: \n");
        printf("1. Add Employee\t2. Remove Employee\t3. Update Employee\t4. All Employees\t 5. Back\n--> ");
        int option;
        scanf("%d", &option);
        getchar();
        switch (option) {
            case 1:
                add_employee();
                break;
            case 2:
                remove_employee();
                break;
            case 3:
                update_employee();
                break;
            case 4:
                display_all_employees();
                break;
            case 5:
                printf("=================================================================================================================\n");
                return; // Return to main menu
            default:
                printf("Invalid option selected.\n");
        }
        printf("=================================================================================================================\n");
    }
}

void add_employee(void){
    char name[100];
    long salary;
    printf("Enter employee name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character from name
    printf("Enter employee salary: ");
    scanf("%ld", &salary);
    getchar();

    // Add employee to the list
    for (int i = 0; i < 100; i++) {
        if (employees[i] == NULL) {
            employees[i] = strdup(name); // Allocate memory and copy name
            employee_salary[i] = salary;
            allowance[i] = 0; // Initialize allowance to 0
            printf("Employee %s added with salary %ld.\n", name, salary);
            return;
        }
    }
    printf("Employee list is full. Cannot add more employees.\n");
}

void remove_employee(void){
    char name[100];
    printf("Enter employee name to remove: ");
    fgets(name, sizeof(name), stdin);

    // Remove employee from the list
    for (int i = 0; i < 100; i++) {
        if (employees[i] != NULL && strcmp(employees[i], name) == 0) {
            free(employees[i]); // Free allocated memory
            employees[i] = NULL;
            employee_salary[i] = 0;
            allowance[i] = 0;
            printf("Employee %s removed.\n", name);
            return;
        }
    }
    printf("Employee %s not found.\n", name);
}

void display_all_employees(void){
    printf("All Employees:\n");
    for (int i = 0; i < 100; i++) {
        if (employees[i] != NULL) {
            printf("\nName: %s  \t  Salary: %ld  \t  Allowance: %ld\n", employees[i], employee_salary[i], allowance[i]);
        }
    }
}

void update_employee(void){
    char name[100];
    printf("Enter employee name to update: ");
    fgets(name, sizeof(name), stdin);

    // Update employee salary
    for (int i = 0; i < 100; i++) {
        if (employees[i] != NULL && strcmp(employees[i], name) == 0) {
            long new_salary;
            printf("Enter new salary for %s: ", name);
            scanf("%ld", &new_salary);
            getchar();
            employee_salary[i] = new_salary;
            printf("Enter new allowance for %s:        current: %ld", name, allowance[i]);
            scanf("%ld", &allowance[i]);
            getchar();
            printf("Employee %s salary updated to %ld and allowance updated to %ld.\n", name, new_salary, allowance[i]);
            return;
        }
    }
    printf("Employee %s not found.\n", name);
}


// ------------------------------------------------------------------------------------------