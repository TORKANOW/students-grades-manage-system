#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define MAX_USERS 100

typedef struct {
    int id;
    char password[20];
} User;

typedef struct {
    char name[50];
    int id;
    int CH_grade;
    int EN_grade;
    int MA_grade;
} Student;

User teachers[MAX_USERS];
Student studentInfo[MAX_USERS];

int teacher_count = 0;
int student_count = 0;
int studentInfo_count = 0;

void inputstudentmessage();
void menu();
void regmenu_1();
void regmenu_3();
void logmenu_2_teacher();
void logmenu_2_student();
void menu_2_teacher();
void menu_2_student();
void showstudentsmessage();
void changepasswords();
void register_user(User users[], int *count, const char *user_type);
int login_user(User users[], int count, const char *user_type);
void display_student_info();
void delete_student_info();
void sort_student_info();
void change_password(User users[], int count, const char *user_type);
void save_data();
void load_data();
void statistics();

void inputstudentmessage() {
    int num_students;

    printf("输入学生人数: ");
    scanf("%d", &num_students);
    getchar(); 

    for (int i = 0; i < num_students; i++) {
        Student student;

        printf("学生%d姓名: ", i + 1);
        scanf("%s", student.name);

        printf("学生%d学号: ", i + 1);
        scanf("%d", &student.id);

        printf("学生%d 成绩(语 英 数): ", i + 1);
        scanf("%d %d %d", &student.CH_grade, &student.EN_grade, &student.MA_grade);
        getchar(); 

        studentInfo[studentInfo_count++] = student;

        printf("学生信息已记录: 姓名: %s, 学号: %d, 语文: %d, 英语: %d, 数学: %d\n",
               student.name, student.id, student.CH_grade, student.EN_grade, student.MA_grade);
    }
}

void menu() {
    printf("————————————————————————————————————————————————————————————————\n");
    printf("                       学生成绩管理系统                         \n");
    printf("————————————————————————————————————————————————————————————————\n");
    printf("          1.教师登录                      2.教师注册             \n");
    printf("                         0.退出系统            \n");
    printf("————————————————————————————————————————————————————————————————\n");
}

void regmenu_1() {
    register_user(teachers, &teacher_count, "教师");
}

void logmenu_2_teacher() {
    if (login_user(teachers, teacher_count, "教师")) {
        int choice;
        do {
            menu_2_teacher();
            scanf("%d", &choice);
            switch (choice) {
                case 0:
                    printf("退出教师菜单。\n");
                    break;
                case 1:
                    inputstudentmessage();
                    break;
                case 2:
                    showstudentsmessage();
                    break;
                case 3:
                    delete_student_info();
                    break;
                case 4:
                    sort_student_info();
                    break;
                case 5:
                    save_data();
                    break;
                case 6:
                    load_data();
                    break;
                case 7:
                    statistics();
                    break;
                default:
                    printf("无效选项，请重新输入。\n");
                    break;
            }
        } while (choice != 0);
    }
}

void menu_2_teacher() {
    printf("————————————————————————————————————————————————————————————————\n");
    printf("                       学生成绩管理系统                         \n");
    printf("————————————————————————————————————————————————————————————————\n");
    printf("          1.录入学生信息                      2.显示学生信息            \n");
    printf("          3.删除学生信息                      4.排序学生成绩            \n");
    printf("          5.保存数据到文件                    6.从文件加载数据          \n");
    printf("          7.统计学生成绩信息                  0.退出系统                \n");
    printf("————————————————————————————————————————————————————————————————\n");
}

void showstudentsmessage() {
    printf("显示所有学生信息:\n");
    for (int i = 0; i < studentInfo_count; i++) {
        printf("姓名: %s, 学号: %d, 语文: %d, 英语: %d, 数学: %d\n",
               studentInfo[i].name, studentInfo[i].id,
               studentInfo[i].CH_grade, studentInfo[i].EN_grade, studentInfo[i].MA_grade);
    }
    return ;
}

void delete_student_info() {
    int id;
    printf("输入学生学号删除该学生成绩信息: ");
    scanf("%d", &id);

    for (int i = 0; i < studentInfo_count; i++) {
        if (studentInfo[i].id == id) {
            for (int j = i; j < studentInfo_count - 1; j++) {
                studentInfo[j] = studentInfo[j + 1];
            }
            studentInfo_count--;
            printf("该学生成绩信息已清除！\n");
            return;
        }
    }
    printf("未找到该学生\n");
    return;
}

void sort_student_info() {
    int choice;
    printf("按那种方式排序:\n");
    printf("1. 按语文成绩从高到低排序\n");
    printf("2. 按英语成绩从高到低排序\n");
    printf("3. 按数学成绩从高到低排序\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
           
            for (int i = 0; i < studentInfo_count - 1; i++) {
                for (int j = 0; j < studentInfo_count - i - 1; j++) {
                    if (studentInfo[j].CH_grade < studentInfo[j + 1].CH_grade) {
                        Student temp = studentInfo[j];
                        studentInfo[j] = studentInfo[j + 1];
                        studentInfo[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            
            for (int i = 0; i < studentInfo_count - 1; i++) {
                for (int j = 0; j < studentInfo_count - i - 1; j++) {
                    if (studentInfo[j].EN_grade < studentInfo[j + 1].EN_grade) {
                        Student temp = studentInfo[j];
                        studentInfo[j] = studentInfo[j + 1];
                        studentInfo[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            
            for (int i = 0; i < studentInfo_count - 1; i++) {
                for (int j = 0; j < studentInfo_count - i - 1; j++) {
                    if (studentInfo[j].MA_grade < studentInfo[j + 1].MA_grade) {
                        Student temp = studentInfo[j];
                        studentInfo[j] = studentInfo[j + 1];
                        studentInfo[j + 1] = temp;
                    }
                }
            }
            break;
        default:
            printf("Invalid option.\n");
            break;
    }

    
    showstudentsmessage();
    return;
}

void save_data() {
    FILE *fp = fopen("student_info.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败。\n");
        return;
    }

    for (int i = 0; i < studentInfo_count; i++) {
        fprintf(fp, "%s %d %d %d %d\n",
                studentInfo[i].name, studentInfo[i].id,
                studentInfo[i].CH_grade, studentInfo[i].EN_grade, studentInfo[i].MA_grade);
    }

    fclose(fp);
    printf("数据保存成功。\n");
    return;
}

void load_data() {
    FILE *fp = fopen("student_info.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败。\n");
        return;
    }

    studentInfo_count = 0;
    while (fscanf(fp, "%s %d %d %d %d\n",
                  studentInfo[studentInfo_count].name, &studentInfo[studentInfo_count].id,
                  &studentInfo[studentInfo_count].CH_grade, &studentInfo[studentInfo_count].EN_grade,
                  &studentInfo[studentInfo_count].MA_grade) != EOF) {
        studentInfo_count++;
    }

    fclose(fp);
    printf("数据加载成功。\n");
    return;
}

void statistics() {
    int total_CH = 0, total_EN = 0, total_MA = 0;
    float avg_CH, avg_EN, avg_MA;

    for (int i = 0; i < studentInfo_count; i++) {
        total_CH += studentInfo[i].CH_grade;
        total_EN += studentInfo[i].EN_grade;
        total_MA += studentInfo[i].MA_grade;
    }

    avg_CH = (float)total_CH / studentInfo_count;
    avg_EN = (float)total_EN / studentInfo_count;
    avg_MA = (float)total_MA / studentInfo_count;

    printf("学生成绩统计:\n");
    printf("语文平均分: %.2f, 英语平均分: %.2f, 数学平均分: %.2f\n", avg_CH, avg_EN, avg_MA);
    return;
}

void register_user(User users[], int *count, const char *user_type) {
    User user;

    printf("输入 %s 工号: ", user_type);
    scanf("%d", &user.id);
    getchar(); 

    printf("输入 %s 密码: ", user_type);
    fgets(user.password, sizeof(user.password), stdin);
    strtok(user.password, "\n");

    users[(*count)++] = user;
    printf("%s注册成功。\n", user_type);
    return;
}

int login_user(User users[], int count, const char *user_type) {
    int id;
    char password[20];
    printf("输入 %s 工号: ", user_type);
    scanf("%d", &id);
    getchar(); 

    printf("输入 %s 密码: ", user_type);
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n");

    for (int i = 0; i < count; i++) {
        if (users[i].id == id && strcmp(users[i].password, password) == 0) {
            printf("%s登录成功。\n", user_type);
            return 1;
        }
    }
    printf("教师工号或密码错误。\n");
    return 0;
}

int main() {
    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("退出系统。\n");
                return 0;
            case 1:
                logmenu_2_teacher();
                break;
            case 2:
                regmenu_1();
                break;
            default:
                printf("无效选项，请重新输入。\n");
                break;
        }
    }

    return 0;
}
