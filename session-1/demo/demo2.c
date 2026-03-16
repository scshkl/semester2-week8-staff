#include <stdio.h>

typedef struct student{
    char name[100];
    int student_id_number;
    char school[100];
    char degree_subject[100];

} Student;

int main(void){
    int age = 6;
    int *p_age = &age;

    printf("age:%d, *p_age: %d\n\n", age, *p_age);

    Student aStudent = {
        .name = "ali",
        .student_id_number = 123456,
        .school = "Computer Science",
        .degree_subject = "Computer Science"
    };

    Student *pStudent = &aStudent;
    printf("Name: %s\n", pStudent->name);
    //printf("Name: %s\n\n", (*pStudent).name);

    return 0;
}