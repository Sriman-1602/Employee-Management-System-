#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee 
{
    int id;
    char name[50];
    float salary;
};

void add_employee(FILE *fp);
void display_employee(FILE *fp, int id);
void display_all_employees(FILE *fp);
void search_employee(FILE *fp, int id);
void edit_employee(FILE *fp, int id);
void delete_employee(FILE *fp, int id);

int main() 
{
    int choice;

    while (1) 
	{
        printf("\nEmployee Management System\n");
        printf("--------------------------\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Search Employee\n");
        printf("5. Edit Employee\n");
        printf("6. Delete Employee\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                add_employee(fopen("employees.dat", "ab"));
                break;
            case 2: 
			{
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);
                display_employee(fopen("employees.dat", "rb"), id);
                break;
            }
            case 3:
                display_all_employees(fopen("employees.dat", "rb"));
                break;
            case 4: 
			{
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);
                search_employee(fopen("employees.dat", "rb"), id);
                break;
            }
            case 5: 
			{
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);
                edit_employee(fopen("employees.dat", "rb+"), id);
                break;
            }
            case 6: 
			{
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);
                delete_employee(fopen("employees.dat", "rb+"), id);
                break;
            }
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

void add_employee(FILE *fp) 
{
    int id;
    char name[50];
    float salary;

    printf("Enter employee ID: ");
    scanf("%d", &id);

    
    struct Employee employee;
    while (fread(&employee, sizeof(struct Employee), 1, fp)) 
	{
        if (employee.id == id) 
		{
            printf("Employee with ID %d already exists.\n", id);
            fclose(fp);
            return;
        }
    }
    rewind(fp);

    printf("Enter employee name: ");
    scanf("%s", name);

    printf("Enter employee salary: ");
    scanf("%f", &salary);

    struct Employee new_employee = {id, "", 0.0};
    strcpy(new_employee.name, name);
    new_employee.salary = salary;

    fwrite(&new_employee, sizeof(struct Employee), 1, fp);

    fclose(fp);

    printf("Employee added successfully.\n");
}

void display_employee(FILE *fp, int id) 
{
    struct Employee employee;
    while (fread(&employee, sizeof(struct Employee), 1, fp)) 
	{
        if (employee.id == id) 
		{
            printf("ID: %d\n", employee.id);
            printf("Name: %s\n", employee.name);
            printf("Salary: %f\n", employee.salary);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("Employee not found.\n");
}

void display_all_employees(FILE *fp) 
{
    struct Employee employee;
    while (fread(&employee, sizeof(struct Employee), 1, fp)) 
	{
        printf("ID: %d\n", employee.id);
        printf("Name: %s\n", employee.name);
        printf("Salary: %f\n", employee.salary);
        printf("--------------------\n");
    }
    fclose(fp);
}

void search_employee(FILE *fp, int id) 
{
    struct Employee employee;
    while (fread(&employee, sizeof(struct Employee), 1, fp)) 
	{
        if (employee.id == id) 
		{
            printf("Employee found:\n");
            printf("ID: %d\n", employee.id);
            printf("Name: %s\n", employee.name);
            printf("Salary: %f\n", employee.salary);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("Employee not found.\n");
}

void edit_employee(FILE *fp, int id) 
{
    struct Employee employee;
    while (fread(&employee, sizeof(struct Employee), 1, fp)) 
	{
        if (employee.id == id) 
		{
            printf("Enter new employee name: ");
            scanf("%s", employee.name);
            printf("Enter new employee salary: ");
            scanf("%f", &employee.salary);
            fseek(fp,-sizeof(struct Employee), SEEK_CUR);
            fwrite(&employee, sizeof(struct Employee), 1, fp);
            fclose(fp);
            printf("Employee updated successfully.\n");
            return;
        }
    }
    fclose(fp);
    printf("Employee not found.\n");
}

void delete_employee(FILE *fp, int id) 
{
    struct Employee employee;
    FILE *temp = fopen("temp.dat", "wb");
    while (fread(&employee, sizeof(struct Employee), 1, fp)) 
	{
        if (employee.id != id) 
		{
            fwrite(&employee, sizeof(struct Employee), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("employees.dat");
    rename("temp.dat", "employees.dat");
    printf("Employee deleted successfully.\n");
}
