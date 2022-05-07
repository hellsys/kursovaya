#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    maxlen = 128,
    sep = ';'

};

struct name {
    char *name;
    struct car *next; /* Pointer to the next structure*/
    struct car *prev; /* Pointer to the previous structure*/
};

struct car {
    char *manufacture; /* Производитель */
    struct name *name; /* Модель */
    int gears; /* количество передач */
    int power; /* максимальная мощность при 5000 об/мин, л.с. */
    float fuel_consumption; /* расход топлива, литры */
    float weight; /* вес, тонны */
    int year; /* год выпуска */
    int count; /* порядковый номер */
};

struct car_Head {
    int cnt;
    struct car *first;
    struct car *last;
};

typedef struct car cars;
typedef struct car_Head head;

head *make_head();

void delete_selected(head *my_head, cars *node_to_delete);

cars *struct_fill(char **s2);

void clear_string_array(char **str, int n);

char **simple_split(const char *str, unsigned length, char sep);

cars *create_node(char *s1);

void add_first(head *my_head, cars *new_node);

void insert_after(head *my_head, cars *new_node, cars *current_node);

void select_by_gears(head *my_head);

void select_by_manufacturer(head *my_head);

void select_by_model(head *my_head);

void select_by_power(head *my_head);

void select_by_fuel(head *my_head);

void select_by_weight(head *my_head);

void select_by_year(head *my_head);

cars *select_by_number(head *my_head);

void print_header();

void struct_out(struct car *str0);

void found_struct_out(struct car *str0);

void print_PS();

void list_out_first(head *head_point);

void list_out_last(head *head_point);

int str_check(char *str);

head *create_list();

void free_list(head *dlist);

int comp_manuf_and_model(const void *ptr1, const void *ptr2);

int comp_gears(const void *ptr1, const void *ptr2);

int comp_power(const void *ptr1, const void *ptr2);

int comp_fuel(const void *ptr1, const void *ptr2);

int comp_weight(const void *ptr1, const void *ptr2);

int comp_year(const void *ptr1, const void *ptr2);

void adding_elements(head *head_point);

void edit_elements(head *head_point);

void search_elements(head *head);

void delete_element(head *head);

void sort_elements(head *head);

void clear_memory(head *head_point);

void output(head *head_point);

int main() {
    head *head_point = NULL;
    int flag;

    puts("Enter the information according to the format:\nMANUFACTURE;MODEL;NUMBER OF GEARS;MAXIMUM POWER;"
         "FUEL CONSUMPTION;WEIGHT(TONS);YEAR OF PRODUCTION\n");
    puts("Enter empty string when you're done");

    head_point = create_list();
    if (head_point != NULL) {
        do {
            if (head_point->first == NULL) {
                flag = -1;
                puts("There are no elements in the list! You can either add cards or output current list to check that it's empty!\n1 - add the information\n2 - output current list");
                while (flag != 1) {
                    scanf("%d", &flag);
                    switch (flag) {
                        case 1:
                            adding_elements(head_point);
                        case 2:
                            output(head_point);
                        default:
                            puts("Option selection error, select the correct option from the list!");
                    }
                }
            }
            puts("\nMenu:\n0: Help\n"
                 "1: Adding cards about the objects of the subject area\n"
                 "2: Editing cards\n"
                 "3: Deleting cards\n"
                 "4: Card file output\n"
                 "5: Search for cards by parameter\n"
                 "6: Sorting the card file by parameter\n"
                 "7: Exit\n"
                 "8: Clear screen\n");

            scanf("%d", &flag);

            switch (flag) {
                case 1:
                    adding_elements(head_point);
                    break;
                case 2:
                    edit_elements(head_point);
                    break;
                case 3:
                    delete_element(head_point);
                    break;
                case 4:
                    output(head_point);
                    break;
                case 5:
                    search_elements(head_point);
                    break;
                case 6:
                    sort_elements(head_point);
                case 7:
                    break;
                case 8:
                    system("cls");
                    break;
                default:
                    puts("Option selection error, select the correct option from the list!");
            }
        } while (flag != 7);

        free_list(head_point);
        clear_memory(head_point);
    }
    else puts("Restart the program and enter data in correct way!");
    getchar();
    return 0;
}

head *make_head() {
    head *ph = NULL;

    ph = (head *) malloc(sizeof(head));
    if (ph) {
        ph->cnt = 0;
        ph->first = NULL;
        ph->last = NULL;
    }
    return ph;
}

void delete_selected(head *my_head, cars *node_to_delete) {
    cars *q, *q1;

    q = my_head->first;
    q1 = my_head->last;
    if (q == q1) {

    } else if (node_to_delete == q) {
        my_head->first = node_to_delete->name->next;
        node_to_delete->name->next->name->prev = NULL;
        node_to_delete->name->next = NULL;

    } else {
        while (q != NULL) {
            if (q->name->next == node_to_delete) {
                if (node_to_delete == q1) {
                    my_head->last = q;
                    q->name->next = NULL;
                    node_to_delete->name->prev = NULL;
                    node_to_delete->name->next = NULL;
                    q = q->name->next;

                } else {
                    q->name->next = node_to_delete->name->next;
                    node_to_delete->name->next->name->prev = q;
                    node_to_delete->name->prev = NULL;
                    node_to_delete->name->next = NULL;

                    q = q->name->next;
                }
            } else q = q->name->next;
        }
    }

    node_to_delete->name = NULL;
    free(node_to_delete->name);
    node_to_delete = NULL;
    free(node_to_delete);

    if (my_head->first == my_head->last) {
        my_head->first = NULL;
        my_head->last = NULL;
        free(my_head->first);
        free(my_head->last);
    }

}

cars *struct_fill(char **s2) {
    cars *str0 = NULL;
    str0 = (cars *) malloc(sizeof(cars));
    str0->name = (struct name *) malloc(sizeof(struct name));
    if (str0->name != NULL) {
        str0->manufacture = s2[0];
        str0->name->name = s2[1];
        str0->gears = atoi(s2[2]);
        str0->power = atoi(s2[3]);
        str0->fuel_consumption = atof(s2[4]);
        str0->weight = atof(s2[5]);
        str0->year = atoi(s2[6]);
    }
    return str0;
}

void clear_string_array(char **str, int n) {
    int i;

    for (i = 0; i < n; i++) {
        free(str[i]);
        str[i] = NULL;
    }
    free(str);
    str = NULL;
}

char **simple_split(const char *str, unsigned length, char sep) {
    char **str_array = NULL;
    int i, j, k, m;
    int key, count;
    for (j = 0, m = 0; j < length; j++) {
        if (str[j] == sep) m++;
    }

    key = 0;
    str_array = (char **) malloc((m + 1) * sizeof(char *));
    if (str_array != NULL) {
        for (i = 0, count = 0; i <= m; i++, count++) {
            str_array[i] = (char *) malloc(length * sizeof(char));
            if (str_array[i] != NULL) key = 1;
            else {
                key = 0;
                i = m;
            }
        }
        if (key) {
            k = 0;
            m = 0;
            for (j = 0; j < length; j++) {
                if (str[j] != sep) str_array[m][j - k] = str[j];
                else {
                    str_array[m][j - k] = '\0';
                    k = j + 1;
                    m++;
                }
            }
        } else {
            clear_string_array(str_array, count);
        }
    }
    return str_array;
}

cars *create_node(char *s1) /* node initialization */
{
    unsigned s1_len;
    char **s2;
    s1_len = strlen(s1);

    cars *new_node = NULL; /* pointer to new node */
    char *word;

    new_node = (cars *) malloc(sizeof(cars));
    word = (char *) malloc((s1_len + 1) * sizeof(char));
    if (new_node && word) {
        s1_len = strlen(s1);
        if (s1[s1_len - 1] != '\0') {
            s1[s1_len - 1] = '\0';
        }
        s1_len = strlen(s1);

        s2 = simple_split(s1, s1_len, sep);
        if (s2 != NULL) {
            new_node = struct_fill(s2);
        } else puts("Memory error!");

        new_node->name->next = NULL;           /* next node is absent */
        new_node->name->prev = NULL;
    }
    return new_node;  /* return of node address */
}

void add_first(head *my_head, cars *new_node) {
    if (my_head && new_node) {
        my_head->first = new_node;
        my_head->last = new_node;
        my_head->cnt++;
    }
}

void insert_after(head *my_head, cars *new_node, cars *current_node) {
    int n;
    if (my_head && new_node && current_node) {
        n = my_head->cnt + 1;
        if (current_node->name->next == NULL) {
            current_node->name->next = new_node;
            new_node->name->prev = current_node;
            my_head->last = new_node;
        } else {
            new_node->name->next = current_node->name->next;
            current_node->name->next->name->prev = new_node;
            current_node->name->next = new_node;
            new_node->name->prev = current_node;
        }
        my_head->cnt = n;
    }
}

void select_by_gears(head *my_head) {
    int found_count;
    cars *q;
    int n;
    scanf("%d", &n);
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->gears == n) {
                found_struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("Nothing found");
}

void select_by_manufacturer(head *my_head) {
    int found_count;
    char str[maxlen];
    getchar();
    fgets(str, maxlen, stdin);
    str[strlen(str) - 1] = '\0';
    cars *q;
    q = my_head->first;
    found_count = 0;
    while (q != NULL) {
        if (stricmp(q->manufacture, str) == 0) {
            found_struct_out(q);
            found_count++;
        }
        q = q->name->next;
    }
    if (found_count == 0) puts("Nothing found");
}

void select_by_model(head *my_head) {
    int found_count;
    char str[maxlen];
    getchar();
    fgets(str, maxlen, stdin);
    str[strlen(str) - 1] = '\0';
    cars *q;
    q = my_head->first;
    found_count = 0;
    while (q != NULL) {
        if (stricmp(q->name->name, str) == 0) {
            found_struct_out(q);
            found_count++;
        }
        q = q->name->next;
    }
    if (found_count == 0) puts("Nothing found");
}

void select_by_power(head *my_head) {
    int found_count;
    cars *q;
    int n;
    scanf("%d", &n);
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->power == n) {
                found_struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("Nothing found");
}

void select_by_fuel(head *my_head) {
    int found_count;
    cars *q;
    float n;
    scanf("%f", &n);
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->fuel_consumption == n) {
                found_struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("Nothing found");
}

void select_by_weight(head *my_head) {
    int found_count;
    cars *q;
    float n;
    scanf("%f", &n);
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->weight == n) {
                found_struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("Nothing found");
}

void select_by_year(head *my_head) {
    int found_count;
    cars *q;
    int n;
    scanf("%d", &n);
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->year == n) {
                found_struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("Nothing found");
}

cars *select_by_number(head *my_head) {
    cars *q;
    int n;
    scanf("%d", &n);
    q = my_head->first;
    if ((n <= my_head->cnt)) {
        while (q != NULL && q->count != n) {
            q = q->name->next;
        }
    } else q = NULL;
    return q;
}

void print_header() {
    printf("|%5s |%12s |%12s |%3s |%5s |%5s |%5s |%5s |\n", "Num", "Manufacturer", "Model",
           "1*", "2*", "3*", "4*", "5*");
    puts("|------|-------------|-------------|----|------|------|------|------|");
}

void struct_out(struct car *str0) {
    printf("|%5d |%12s |%12s |%3d |%5d |%5.2f |%5.2f |%5d |\n",
           str0->count, str0->manufacture, str0->name->name, str0->gears, str0->power, str0->fuel_consumption,
           str0->weight, str0->year);
}

void found_struct_out(struct car *str0) {
    printf("|%12s |%12s |%3d |%5d |%5.2f |%5.2f |%5d |\n",
           str0->manufacture, str0->name->name, str0->gears, str0->power, str0->fuel_consumption,
           str0->weight, str0->year);
}

void print_PS() {
    puts("P.S.:\n1* - Number of gears\n2* - Max power\n3* - Fuel consumption\n4* - Weight (tons)\n5* - Length\n6* - Year of production");
}

void list_out_first(head *head_point) {
    cars *current_car_node;

    current_car_node = head_point->first;

    while (current_car_node != NULL) {
        struct_out(current_car_node);
        current_car_node = current_car_node->name->next;
    }
}

void list_out_last(head *head_point) {
    cars *current_car_node;

    current_car_node = head_point->last;

    while (current_car_node != NULL) {
        struct_out(current_car_node);
        current_car_node = current_car_node->name->prev;
    }
}

head *create_list() {
    int i = 2;
    head *head_point = NULL;
    char temp_str[maxlen];
    char insert_str[maxlen];
    cars *current_car_node = NULL;
    cars *new_car_node;

    head_point = make_head();

    if (str_check(fgets(temp_str, maxlen, stdin)) == 1) {
        current_car_node = create_node(temp_str);
        add_first(head_point, current_car_node);

        current_car_node->count = 1;

        while (strcmp((fgets(insert_str, maxlen, stdin)), "\n") != 0) {
            if (str_check(insert_str) == 1) {
                new_car_node = create_node(insert_str);
                new_car_node->count = i;
                i++;
                insert_after(head_point, new_car_node, current_car_node);
                current_car_node = current_car_node->name->next;
            } else {
                puts("Input error!(This element won't be added in the list. Continue entering data according to the example)");
            }
        }
    } else {
        puts("Input error!");
        head_point = NULL;
    }
    return head_point;
}

void free_list(head *dlist) {
    cars *curr = dlist->first;

    while (curr) {
        free(curr->name->name);
        curr->name->name = NULL;

        free(curr->manufacture);
        curr->manufacture = NULL;

        curr = curr->name->next;

    }
}

int comp_manuf_and_model(const void *ptr1, const void *ptr2) {
    int cmp1, cmp2;
    int res;
    cars *p1 = (cars *) ptr1;
    cars *p2 = (cars *) ptr2;

    cmp1 = stricmp(p1->manufacture, p2->manufacture);
    if (cmp1) res = cmp1;
    else {
        cmp2 = stricmp(p1->name->name, p2->name->name);
        res = cmp2;
    }

    return res;
}

int comp_gears(const void *ptr1, const void *ptr2) {
    int res;
    cars *p1 = (cars *) ptr1;
    cars *p2 = (cars *) ptr2;

    res = p1->gears - p2->gears;

    return res;
}

int comp_power(const void *ptr1, const void *ptr2) {
    int res;
    cars *p1 = (cars *) ptr1;
    cars *p2 = (cars *) ptr2;

    res = p1->power - p2->power;

    return res;
}

int comp_fuel(const void *ptr1, const void *ptr2) {
    float res;
    cars *p1 = (cars *) ptr1;
    cars *p2 = (cars *) ptr2;

    res = p2->fuel_consumption - p1->fuel_consumption;
    return res > 0 ? 1 : -1;
}

int comp_weight(const void *ptr1, const void *ptr2) {
    float res;
    cars *p1 = (cars *) ptr1;
    cars *p2 = (cars *) ptr2;

    res = p2->weight - p1->weight;
    return res > 0 ? 1 : -1;
}

int comp_year(const void *ptr1, const void *ptr2) {
    int res;
    cars *p1 = (cars *) ptr1;
    cars *p2 = (cars *) ptr2;

    res = p1->year - p2->year;

    return res;
}

void adding_elements(head *head_point) {
    char insert_str[maxlen];
    cars *current_car_node = NULL;
    cars *new_car_node;

    fflush(stdin);

    puts("Enter the information according to the format:\nMANUFACTURE;MODEL;NUMBER OF GEARS;MAXIMUM POWER;"
         "FUEL CONSUMPTION;WEIGHT(TONS);YEAR OF PRODUCTION\n");
    puts("Enter empty string when you're done");

    while (strcmp((fgets(insert_str, maxlen, stdin)), "\n") != 0) {
        new_car_node = create_node(insert_str);
        insert_after(head_point, new_car_node, current_car_node);
        current_car_node = current_car_node->name->next;
    }

}

void edit_elements(head *head_point) {
    int i;
    int num;
    int change_flag;
    cars *curr_node = head_point->first;
    puts("Here is your current list:\n");
    list_out_first(head_point);
    puts("Enter the number of the element which you would like to edit (or enter 0 to exit):");
    scanf("%d", &num);

    if (num != 0) {
        while (num > head_point->cnt) {
            printf("There is no element with number %d in the list!\n Reenter the number", num);
            scanf("%d", &num);
        }
        for (i = 1; i < num; i++) {
            curr_node = curr_node->name->next;
        }
        puts("Which field would you like to change?\n1 - manufacturer\n2 - model\n3 - number of gears\n4 - max power\n"
             "5 - fuel consumption\n6 - weight\n7 - year of production\n0 - exit");
        scanf("%d", &change_flag);

        switch (change_flag) {
            case 0:
                break;
            case 1:
                puts("Enter new manufacturer: ");
                fgets(curr_node->manufacture, maxlen, stdin);
                break;
            case 2:
                puts("Enter new model: ");
                fgets(curr_node->name->name, maxlen, stdin);
                break;
            case 3:
                puts("Enter new number of gears: ");
                scanf("%d", &curr_node->gears);
                break;
            case 4:
                puts("Enter new max power: ");
                scanf("%d", &curr_node->power);
                break;
            case 5:
                puts("Enter new fuel consumption: ");
                scanf("%f", &curr_node->fuel_consumption);
                break;
            case 6:
                puts("Enter new weight: ");
                scanf("%f", &curr_node->weight);
                break;
            case 7:
                puts("Enter new year of production: ");
                scanf("%d", &curr_node->year);
                break;
            default:
                puts("Option selection error, select the correct option from the list!");
        }

    }
}

void search_elements(head *head) {
    int search_flag;
    puts("By which parameter do you want to find the element?\n1 - manufacturer\n2 - model\n3 - number of gears\n4 - max power\n"
         "5 - fuel consumption\n6 - weight\n7 - year of production\n0 - exit");
    scanf("%d", &search_flag);

    switch (search_flag) {
        case 1:
            puts("Enter manufacturer to find");
            select_by_manufacturer(head);
            break;
        case 2:
            puts("Enter model to find");
            select_by_model(head);
            break;
        case 3:
            puts("Enter number of gears to find");
            select_by_gears(head);
            break;
        case 4:
            puts("Enter max power to find");
            select_by_power(head);
            break;
        case 5:
            puts("Enter fuel consumption to find");
            select_by_fuel(head);
            break;
        case 6:
            puts("Enter weight to find");
            select_by_weight(head);
            break;
        case 7:
            puts("Enter year of production to find");
            select_by_year(head);
            break;
        default:
            puts("Option selection error, select the correct option from the list!");
    }
}

void delete_element(head *head) {
    int i;
    cars *found_element = NULL;
    cars *curr_elem = NULL;
    puts("Enter number of the element to delete:");
    found_element = select_by_number(head);
    if (found_element != NULL) {
        delete_selected(head, found_element);
        puts("Selected item has been successfully deleted");
        head->cnt = head->cnt - 1;
        curr_elem = head->first;
        for (i = 01; i <= head->cnt; i++) {
            curr_elem->count = i;
            curr_elem = curr_elem->name->next;
        }
    } else puts("Deleting error! Enter correct number of the element");

}

void sort_elements(head *head) {
    cars *curr_node = NULL;
    cars *cars_array = NULL;
    int i;
    int sort_flag;
    curr_node = head->first;

    cars_array = (cars *) malloc((head->cnt) * (sizeof(cars)));

    for (i = 0; i < head->cnt; i++) {
        cars_array[i] = *curr_node;
        curr_node = curr_node->name->next;
    }

    puts("By what parameter do you want to sort the list?\n1 - manufacturer and model\n3 - number of gears\n4 - max power\n"
         "5 - fuel consumption\n6 - weight\n7 - year of production\n0 - exit");

    scanf("%d", &sort_flag);
    switch (sort_flag) {
        case 0:
            break;
        case 1:
            qsort(cars_array, head->cnt, sizeof(cars), comp_manuf_and_model);
            break;
        case 2:
            qsort(cars_array, head->cnt, sizeof(cars), comp_gears);
            break;
        case 3:
            qsort(cars_array, head->cnt, sizeof(cars), comp_power);
            break;
        case 4:
            qsort(cars_array, head->cnt, sizeof(cars), comp_fuel);
            break;
        case 5:
            qsort(cars_array, head->cnt, sizeof(cars), comp_weight);
            break;
        case 6:
            qsort(cars_array, head->cnt, sizeof(cars), comp_year);
            break;
        default:
            puts("Option selection error, select the correct option from the list!");
    }
    head->first = &cars_array[0];
    curr_node = head->first;
    cars_array[0].count = 1;
    for (i = 1; i <= head->cnt; i++) {
        cars_array[i].count = i + 1;
        curr_node->name->next = &cars_array[i];
        if (i == head->cnt) curr_node->name->next = NULL;
        curr_node = curr_node->name->next;
    }
    free(cars_array);
    cars_array = NULL;
}

void output(head *head_point) {
    int out_flag;
    puts("\n");
    if (head_point->first != NULL) {
        puts("Would you like to print list from the first or from the last element?\n1 - from the first\n2 - from the last\n0 - exit");
        scanf("%d", &out_flag);
        switch (out_flag) {
            case 0:
                break;
            case 1:
                print_header();
                list_out_first(head_point);
                break;
            case 2:
                print_header();
                list_out_last(head_point);
                break;
            default:
                puts("Option selection error, select the correct option from the list!");
        }
        print_PS();
    } else {
        print_header();
        print_PS();
    }
}

void clear_memory(head *head_point) {
    cars *temp_node;
    cars *curr_node;
    curr_node = head_point->first;

    while (curr_node != NULL) {
        temp_node = curr_node->name->next;
        delete_selected(head_point, curr_node);
        curr_node = temp_node;
    }
    head_point->first = NULL;
    head_point->last = NULL;
    head_point = NULL;
    free(head_point);
}

int str_check(char *str) {
    char **str_array;
    int key = 1;
    int i, j;
    char sep;
    int count;
    count = 0;
    sep = ';';

    for (i = 0; i < strlen(str); i++) {
        if (str[i] == sep) count++;
    }

    if (count < 6 || count > 7) key = 0;
    else {
        str_array = simple_split(str, strlen(str), sep);
        for (i = 2; i < 6; i++) {
            for (j = 0; j < strlen(str_array[i]); j++) {
                if (str_array[i][j] < 47 || str_array[i][j] > 58) {
                    if (str_array[i][j] == 46 || str_array[i][j] == 44) key = 1;
                    else key = 0;
                }
            }
        }
    }

    return key;
}