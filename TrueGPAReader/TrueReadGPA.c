#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data{
    char term[20];
    char code[20];
    char name[20];
    double credit;
    double grade;
};

int main(){
    struct Data Subject[300];
    FILE *file = fopen("My GPAX Data.csv", "r");

    if (file == NULL) {
        perror("Error Occured");
        return 1;
    }

    char first[1], line[1024], * token, term[30];
    int index = 0, col = 0, count = 0;
    double each_grade = 0, each_credit = 0, math_grade = 0, math_credit = 0, eng_grade = 0, eng_credit = 0, sci_grade = 0, sci_credit = 0;
    double Total_Credit = 0, Total_Grade = 0;
    fgets(line, sizeof(line), file);
    token = strtok(line, ",");
    while(token != NULL){
            if (col != 0)
            token = strtok(NULL, ",");
            col++;
    }

    while(fgets(line, sizeof(line), file)){
        col = 0;
        token = strtok(line, ",");
        if(strstr(line,",,,,") != NULL)
            continue;
        while(token != NULL){
            if (strstr(token,"Grade") != NULL)
                strcpy(term, token);
            else
            {
                if(col == 0){
                    strcpy(Subject[index].term,term);
                    strcpy(Subject[index].code,token);
                }
                if(col == 1)
                    strcpy(Subject[index].name,token);
                if(col == 2)
                    Subject[index].credit = atof(token);
                if(col == 3)
                    Subject[index].grade = atof(token);
                col++;
            }
            token = strtok(NULL, ",");
        }
        index++;
    }

    FILE *cfPtr;

    if((cfPtr = fopen("New File.csv", "w")) == NULL)
        puts("File Could Not Be Opened");
    else{
        fprintf(cfPtr, "Semester         Grade  Math  Eng   Sci\n");
        printf("Semester         Grade  Math  Eng   Sci\n");

        strcpy(term, Subject[0].term);
        for (int i = 0; i <= index; i++){
            if(strcmp(term,Subject[i].term) != 0){
                Total_Grade += each_grade;
                Total_Credit += each_credit;
                math_grade = math_grade/ math_credit;
                eng_grade = eng_grade/ eng_credit;
                sci_grade = sci_grade/ sci_credit;
                each_grade = each_grade/ each_credit;
                fprintf(cfPtr, "%s, %.2lf, %.2lf, %.2lf, %.2lf\n", term, each_grade, math_grade, eng_grade, sci_grade);
                printf("%s, %.2lf, %.2lf, %.2lf, %.2lf\n", term, each_grade, math_grade, eng_grade, sci_grade);
                strcpy(term, Subject[i].term);
                math_grade = 0, math_credit = 0, eng_grade = 0, eng_credit = 0, sci_grade = 0, sci_credit = 0, each_credit = 0, each_grade = 0;
                count++;
            }

            each_credit += Subject[i].credit;
            each_grade += (Subject[i].credit * Subject[i].grade);
            
            if(strstr(Subject[i].code,"อ") != NULL){
                eng_credit += Subject[i].credit;
                eng_grade += (Subject[i].credit * Subject[i].grade);
            }

            if(strstr(Subject[i].code,"ค") != NULL || strstr(Subject[i].code,"SI") != NULL){
                math_credit += Subject[i].credit;
                math_grade += (Subject[i].credit * Subject[i].grade);
            }
            if(strstr(Subject[i].code,"ว") != NULL || strstr(Subject[i].code,"SI") != NULL){
                sci_credit += Subject[i].credit;
                sci_grade += (Subject[i].credit * Subject[i].grade);
            }
        }
        Total_Grade = Total_Grade/ Total_Credit;
        fprintf(cfPtr, "Average Grade For %d Semesters Is: %.3lf", count, Total_Grade);
        printf("Average Grade For %d Semesters Is: %.3lf", count, Total_Grade);
    }
    fclose(file);
    fclose(cfPtr);
    return 0;
}