#include <stdio.h>
#include <string.h>


int main(){

    int N;
    scanf("%d", &N);
    Company comp[N];
    int i;
    for(i=0; i<N; i++){
        read_company(&comp[i]);
    }
    char department[100];
    fgets(department, sizeof(department), stdin);
    cleanString(department);

    printEmployeesBelowAverageSalary(comp, N);
    printHighestSalaryEmployee(comp, N, department);

    return 0;
}

void read_company(Company *comp){
    scanf("%s %d", comp->name, &comp->number_of_employees);
    int i;
    for(i=0; i<comp->number_of_employees; i++){
        scanf("%s %s %s %d\n", comp->emp[i].name, comp->emp[i].EMBG, comp->emp[i].department, &comp->emp[i].salary);
    }
}
void printEmployeesBelowAverageSalary(Company *comp, int numCompanies){
    printf("Employees with salaries below the average:\n");
    int i, j;
    for(i=0; i<numCompanies; i++){
        int AverageSalary=0;
        for(j=0; j<comp[i].number_of_employees; j++){
            AverageSalary += comp[i].emp[j].salary;
        }
        AverageSalary = AverageSalary/comp[i].number_of_employees;
        for(j=0; j<comp[i].number_of_employees; j++){
            if(AverageSalary > comp[i].emp[j].salary){
                printf("%s %s %s %d\n", comp[i].emp[j].name, comp[i].emp[j].EMBG, comp[i].emp[j].department, comp[i].emp[j].salary);
            }
        }
    }
}

void printHighestSalaryEmployee(Company *comp, int numCompanies, char *department){
    printf("Employees with highest salaries for given department:\n");
    int i, j, temp;
    for(i=0; i<numCompanies; i++){
        int max=0, maxIndex=0, flag=0;
        for(j=0; j<comp[i].number_of_employees; j++){
            if(!(strcmp(comp[i].emp[j].department, department))){
                flag=1;
                if(max < comp[i].emp[j].salary){
                    max = comp[i].emp[j].salary;
                    maxIndex = j;
                    temp = maxIndex;
                }
            }
        }
        if(flag == 1){
            printf("%s %s %s %d\n", comp[i].emp[maxIndex].name, comp[i].emp[maxIndex].EMBG, comp[i].emp[maxIndex].department, comp[i].emp[maxIndex].salary);
        }
        else if(flag == 0 && i!=0){
            printf("%s %s %s %d\n", comp[i-1].emp[temp].name, comp[i-1].emp[temp].EMBG, comp[i-1].emp[temp].department, comp[i-1].emp[temp].salary);
        }
    }
}

void cleanString(char *department){
    department[strlen(department)-1] = '\0';
}