
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
void salary(char *name);
long deducted_salary(char *name);

// ------------------------------------------------------------------------------------------

// GVs --------------------------------------------------------------------------------------

char *employees[100];
long employee_salary[100];
long allowance[100];
char helpdesk[] = "Helpdesk:\n1. To add an employee, select 'Administrator' and then 'Add Employee'.\n2. To remove an employee, select 'Administrator' and then 'Remove Employee'.\n3. To update an employee's salary or allowance, select 'Administrator' and then 'Update Employee'.\n4. To view all employees, select 'Administrator' and then 'All Employees'.\n5. To calculate an employee's salary after deductions, select 'Calculate Salary' and enter the employee's name.\n6. To exit the program, select 'Exit'.\n\n";

// ------------------------------------------------------------------------------------------

// MAIN -------------------------------------------------------------------------------------
int main(){
    while (1) {
        
    int option = input_0();
    printf("=================================================================================================================\n\n");
    // Admin controls
    if (option == 1) {
        administrator();
    }
    // salary calculation
    else if (option == 2) {
        char name[100];
        printf("Enter employee name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline character from name
        salary(name);
        printf("\n=================================================================================================================\n");
    }
    // Helpdesk
    else if (option == 3) {
        printf("%s", helpdesk);
        printf("\n=================================================================================================================\n");

    } 
    // Exit
    else if (option == 4) {
        printf("Exit selected.\n\n");
        return 0;
    } else {
        printf("Invalid option selected.\n");
    }

}

}
// ------------------------------------------------------------------------------------------

// FUNCTIONS --------------------------------------------------------------------------------

void salary(char *name){
    long final_salary = deducted_salary(name);
    if (final_salary != -1) {
        printf("Final salary for %s after deductions: %ld\n", name, final_salary);
    }
}

long deducted_salary(char *name){
    int idx = -1;
    for (int i = 0; i < 100; i++) {
        if (employees[i] != NULL && strcmp(employees[i], name) == 0) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Employee not found.\n");
        return -1;
    }
    long salary = employee_salary[idx];
    long allowance_amount = allowance[idx];
    long total_deductions = 0;
    int per = 0;

    // Calculate deductions based on salary
    if (salary < 10000) {
        total_deductions = salary * 0.05; 
        per = 5;
    } else if (salary < 20000) {
        total_deductions = salary * 0.1; 
        per = 10;
    } else {
        total_deductions = salary * 0.15; 
        per = 15;
    }

    // Deduct allowance from total deductions
    total_deductions -= allowance_amount;
    printf("Deduction percentage: %d%%\n", per);

    return salary - total_deductions;
}

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
    printf("Administrator Menu:\n");
    while (1) {
        
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
                printf("\n=================================================================================================================\n");
                return; // Return to main menu
            default:
                printf("Invalid option selected.\n");
        }
        printf("\n=================================================================================================================\n");
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
    name[strcspn(name, "\n")] = 0; // Remove newline character from name

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
            printf("\nName: %s  \t  Salary: %ld  \t  Allowance: %ld  \t  Deduction percentage: %%%.1f  \t  Deducted Salary: %ld\n", employees[i], employee_salary[i], allowance[i], (1 - (float)deducted_salary(employees[i]) / employee_salary[i]) * 100, deducted_salary(employees[i]));
        }
    }
}

void update_employee(void){
    char name[100];
    printf("Enter employee name to update: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character from name

    // Update employee salary
    for (int i = 0; i < 100; i++) {
        if (employees[i] != NULL && strcmp(employees[i], name) == 0) {
            long new_salary;
            printf("Enter new salary for %s: ", name);
            scanf("%ld", &new_salary);
            getchar();
            employee_salary[i] = new_salary;
            printf("Enter new allowance for %s (current: %ld): ", name, allowance[i]);
            scanf("%ld", &allowance[i]);
            getchar();
            printf("Employee %s salary updated to %ld and allowance updated to %ld.\n", name, new_salary, allowance[i]);
            return;
        }
    }
    printf("Employee %s not found.\n", name);
}




// ------------------------------------------------------------------------------------------