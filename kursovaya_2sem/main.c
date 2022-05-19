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

/*Function makes head of the list */
head *make_head();

/*Function deletes selected element from the list */
void delete_selected(head *my_head, cars *node_to_delete);

/*Function fills the structure from the information from the string*/
cars *struct_fill(char **s2);

/*Function clears allocated memory from the structure*/
void clear_string_array(char **str, int n);

/*Function splits information from the string by the separator*/
char **simple_split(const char *str, unsigned length, char sep);

/*Function creates node of the list*/
cars *create_node(char *s1);

/*Function adds first element of the list*/
void add_first(head *my_head, cars *new_node);

/*Function inserts element of the list after the selected element*/
void insert_after(head *my_head, cars *new_node, cars *current_node);

/*Function searches element by gears*/
void select_by_gears(head *my_head);

/*Function searches element by manufacturer*/
void select_by_manufacturer(head *my_head);

/*Function searches element by model*/
void select_by_model(head *my_head);

/*Function searches element by power*/
void select_by_power(head *my_head);

/*Function searches element by fuel*/
void select_by_fuel(head *my_head);

/*Function searches element by weight*/
void select_by_weight(head *my_head);

/*Function searches element by year of production*/
void select_by_year(head *my_head);

/*Function searches element by number*/
cars *select_by_number(head *my_head);

/*Function prints header*/
void print_header();

/*Function outs selected structure*/
void struct_out(struct car *current_car_node);

///*Function outs selected structure (differs from the previous one by a slightly different output format)*/
//void found_struct_out(struct car *str0);

/*Function prints P.S.*/
void print_PS();

/*Function outs the list from the first element*/
void list_out_first(head *head_point);

/*Function outs the list from the last element*/
void list_out_last(head *head_point);

/*Function checks if the information in the string fits the format correctly*/
int str_check(char *str);

/*Function creates the list*/
head *create_list();

/*Function frees memory from the list*/
void free_list(head *dlist);

/*Function compares 2 structures by manufacturer and model*/
int comp_manuf_and_model(const void *ptr1, const void *ptr2);

/*Function compares 2 structures by number of gears*/
int comp_gears(const void *ptr1, const void *ptr2);

/*Function compares 2 structures by max power*/
int comp_power(const void *ptr1, const void *ptr2);

/*Function compares 2 structures by fuel consumption*/
int comp_fuel(const void *ptr1, const void *ptr2);

/*Function compares 2 structures by weight*/
int comp_weight(const void *ptr1, const void *ptr2);

/*Function compares 2 structures by year of production*/
int comp_year(const void *ptr1, const void *ptr2);

/*Function adds elements to the list*/
void adding_elements(head *head_point);

/*Function edit elements in the list*/
void edit_elements(head *head_point);

/*Function searches elements in the list by the parameter*/
void search_elements(head *head);

/*Function deletes selected element from the list*/
void delete_element(head *head);

/*Function sorts elements by the parameter*/
void sort_elements(head *head);

/*Function frees memory that was used by the program during the work*/
void clear_memory(head *head_point);

/*Function outputs the list*/
void output(head *head_point);

void file_output(head *head_point);

int main() {
    head *head_point = NULL;
    int flag;

    puts("Enter the information according to the format:\nMANUFACTURE;MODEL;NUMBER OF GEARS;MAXIMUM POWER;"
         "FUEL CONSUMPTION;WEIGHT(TONS);YEAR OF PRODUCTION\n");
    puts("Enter empty string when you're done");

    head_point = create_list();
    do {
        /*If there are no elements in the list user will have to add elements*/
        if (head_point->first == NULL) {
            flag = -1;
            puts("There are no elements in the list! You can either add cards or output current list to check that it's empty!\n1 - add the information\n2 - output current list");
            while (flag != 1) {
                scanf("%d", &flag);
                switch (flag) {
                    case 1:
                        adding_elements(head_point);
                        break;
                    case 2:
                        output(head_point);
                        break;
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

        /*Program operation options. The program will run until the user exits*/
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
                file_output(head_point);
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
    /*Deleting an element means that the previous element now points to the next one, and the next
     * one points to the previous one. Extreme cases are also considered,
     * such as the last or first element of a list or a list consisting of a single element*/
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
    /*Each field of the structure is filled in from the corresponding element
     * of a two-dimensional array of strings.*/
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
//    str[length-1] = '\0';
//    length = length - 1;
    /*Counting the number of delimiters in a row to allocate the appropriate
     * amount of memory for a two-dimensional array*/
    for (j = 0, m = 0; j < length; j++) {
        if (str[j] == sep) m++;
    }

    key = 0;
    str_array = (char **) malloc((m + 1) * sizeof(char *));
    if (str_array != NULL) {
        for (i = 0, count = 0; i <= m; i++, count++) {
            /*Memory allocation for each row*/
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
            /*Fragmentary input into a two-dimensional array from a string.
             * The character is entered into the array if it is not equal to the separator*/
            for (j = 0; j < length; j++) {
                if (str[j] != sep) str_array[m][j - k] = str[j];
                else {
                    str_array[m][j - k] = '\0';
                    k = j + 1;
                    m++;
                }
            }
            str_array[m][j - k] = '\0';
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
//        if (s1[s1_len - 1] != '\0') {
//            s1[s1_len - 1] = '\0';
//        }
//        s1_len = strlen(s1);

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
    /*Inserting an item into the list means that the previous item now points to the one being inserted, and the one
     * being inserted points to the one that the previous one previously pointed to*/
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

/*All the following search functions are passed through all the elements of the list and when finding the one in
 * which the specified parameter matches the search parameter, the element is output. (The program provides only the
 * output of the found elements, so a new list is not created, since there is no point in this)*/

void select_by_gears(head *my_head) {
    int found_count;
    cars *q;
    int n;
    scanf("%d", &n);
    print_header();
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->gears == n) {
                struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("\nNothing found");
    else print_PS();

}

void select_by_manufacturer(head *my_head) {
    int found_count;
    char str[maxlen];
    getchar();
    fgets(str, maxlen, stdin);
    print_header();
    str[strlen(str) - 1] = '\0';
    cars *q;
    q = my_head->first;
    found_count = 0;
    while (q != NULL) {
        if (stricmp(q->manufacture, str) == 0) {
            struct_out(q);
            found_count++;
        }
        q = q->name->next;
    }
    if (found_count == 0) puts("\nNothing found");
    else print_PS();
}

void select_by_model(head *my_head) {
    int found_count;
    char str[maxlen];
    getchar();
    fgets(str, maxlen, stdin);
    print_header();
    str[strlen(str) - 1] = '\0';
    cars *q;
    q = my_head->first;
    found_count = 0;
    while (q != NULL) {
        if (stricmp(q->name->name, str) == 0) {
            struct_out(q);
            found_count++;
        }
        q = q->name->next;
    }
    if (found_count == 0) puts("\nNothing found");
    else print_PS();
}

void select_by_power(head *my_head) {
    int found_count;
    cars *q;
    int n;
    scanf("%d", &n);
    print_PS();
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->power == n) {
                struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("\nNothing found");
    else print_PS();

}

void select_by_fuel(head *my_head) {
    int found_count;
    cars *q;
    float n;
    scanf("%f", &n);
    print_header();
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->fuel_consumption == n) {
                struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("\nNothing found");
    else print_PS();
}

void select_by_weight(head *my_head) {
    int found_count;
    cars *q;
    float n;
    scanf("%f", &n);
    print_header();
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->weight == n) {
                struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("\nNothing found");
    else print_PS();

}

void select_by_year(head *my_head) {
    int found_count;
    cars *q;
    int n;
    scanf("%d", &n);
    print_header();
    q = my_head->first;
    found_count = 0;
    if ((n > 0)) {
        while (q != NULL) {
            if (q->year == n) {
                struct_out(q);
                found_count++;
            }
            q = q->name->next;
        }
    } else q = NULL;
    if (found_count == 0) puts("\nNothing found");
    else print_PS();

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

void struct_out(struct car *current_car_node) {
    printf("|%5d |%12s |%12s |%3d |%5d |%5.2f |%5.2f |%5d |\n",
           current_car_node->count, current_car_node->manufacture, current_car_node->name->name, current_car_node->gears,
           current_car_node->power, current_car_node->fuel_consumption,
           current_car_node->weight, current_car_node->year);
}

//void found_struct_out(struct car *str0) {
//    printf("|%12s |%12s |%3d |%5d |%5.2f |%5.2f |%5d |\n",
//           str0->manufacture, str0->name->name, str0->gears, str0->power, str0->fuel_consumption,
//           str0->weight, str0->year);
//}

void print_PS() {
    puts("P.S.:\n1* - Number of gears\n2* - Max power\n3* - Fuel consumption\n4* - Weight (tons)\n5* - Year of production");
}

/*The list is displayed element by element starting from the first*/
void list_out_first(head *head_point) {
    cars *current_car_node;

    current_car_node = head_point->first;

    while (current_car_node != NULL) {
        struct_out(current_car_node);
        current_car_node = current_car_node->name->next;
    }
}

/*The list is displayed element by element starting from the last*/
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

    /*Comparing the first line with the input format and, in case of a match, creating the first element of the list,
     * otherwise an error message is displayed and a cycle is started that ends only if the string
     * is entered correctly*/
    if (str_check(fgets(temp_str, maxlen, stdin)) == 1) {
        current_car_node = create_node(temp_str);
        add_first(head_point, current_car_node);

        current_car_node->count = 1;
    } else {
        puts("Input error. Enter data in the correct way please.");
        while (str_check(fgets(temp_str, maxlen, stdin)) != 1) {
            puts("Input error. Enter data in the correct way please.");
        }
        current_car_node = create_node(temp_str);
        add_first(head_point, current_car_node);

        current_car_node->count = 1;
    }
    /*The lines are entered cyclically, each line is checked for the correctness of the input and, in case of a match,
     *a list node is formed from the line and inserted after the last element at the moment.
     * The loop ends its work if an empty string is entered*/
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

/*Each of the comparators listed below returns a positive number if the first of the compared elements is greater
 * than the second and vice versa otherwise. This is necessary to use the qsort function*/
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

/*The lines are entered cyclically, each line is checked for the correctness of the input and, in case of a match,
*a list node is formed from the line and inserted after the last element at the moment.
* The loop ends its work if an empty string is entered*/
void adding_elements(head *head_point) {
    char insert_str[maxlen];
    cars *current_car_node = NULL;
    cars *new_car_node;
    int num;

    num = head_point->cnt + 1;
    current_car_node = head_point->last;

    fflush(stdin);

    puts("Enter the information according to the format:\nMANUFACTURE;MODEL;NUMBER OF GEARS;MAXIMUM POWER;"
         "FUEL CONSUMPTION;WEIGHT(TONS);YEAR OF PRODUCTION\n");
    puts("Enter empty string when you're done");

    while (strcmp((fgets(insert_str, maxlen, stdin)), "\n") != 0) {
        new_car_node = create_node(insert_str);
        new_car_node->count = num;
        insert_after(head_point, new_car_node, current_car_node);
        current_car_node = current_car_node->name->next;
        num++;
    }

}

void edit_elements(head *head_point) {
    int i;
    int num;
    int change_flag;
    cars *curr_node = head_point->first;
    puts("Here is your current list:\n");
    list_out_first(head_point);
    /*For the program to work, the user must enter the serial number of the item in the list*/
    puts("Enter the number of the element which you would like to edit (or enter 0 to exit):");
    scanf("%d", &num);

    if (num != 0) {
        /*If such an item is not in the list, an error message is displayed and you are prompted to
         * enter the number again*/
        while (num > head_point->cnt) {
            printf("There is no element with number %d in the list!\n Reenter the number", num);
            scanf("%d", &num);
        }
        /*Traversing the entire list until the entered item number is found*/
        for (i = 1; i < num; i++) {
            curr_node = curr_node->name->next;
        }
        /*The user selects from the suggested list which field of the element needs to be edited,
         * then enters the new contents of the field*/
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

/*The user selects from the list by which parameter the search will be performed, then outputs
 * the desired content and with the help of the function corresponding to each field, the search is performed*/
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
    /*Entering a number to delete and searching for an item with the corresponding number*/
    puts("Enter number of the element to delete:");
    found_element = select_by_number(head);
    if (found_element != NULL) {
        /*Deleting an item using the corresponding function, reducing the total number of list items*/
        delete_selected(head, found_element);
        puts("Selected item has been successfully deleted");
        head->cnt = head->cnt - 1;
        curr_elem = head->first;
        /*Renumbering list items*/
        for (i = 1; i <= head->cnt; i++) {
            curr_elem->count = i;
            curr_elem = curr_elem->name->next;
        }
    } else puts("Deleting error! Enter correct number of the element");

}

void sort_elements(head *head) {
    cars *curr_node = NULL;
    cars *cars_array = NULL;
    cars *cars_temp = NULL;
    int i;
    int sort_flag;
    curr_node = head->first;

    /*Allocation of memory for an array of structures*/
    cars_array = (cars *) malloc((head->cnt) * (sizeof(cars)));

    /*Adding list items to an array*/
    for (i = 0; i < head->cnt; i++) {
        cars_array[i] = *curr_node;
        curr_node = curr_node->name->next;
    }

    /*Selecting a parameter for sorting*/
    puts("By what parameter do you want to sort the list?\n1 - manufacturer and model\n2 - number of gears\n3 - max power\n"
         "4 - fuel consumption\n5 - weight\n6 - year of production\n0 - exit");

    scanf("%d", &sort_flag);

    /*Using the qsort function to sort an array using the comparator corresponding to each field*/
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
    /*Reassigning pointers based on a sorted array*/
    head->first = &cars_array[0];
    curr_node = head->first;
    curr_node->name->prev = NULL;
    cars_array[0].count = 1;
    for (i = 1; i <= head->cnt; i++) {
        printf("%d", i);

        cars_array[i].count = i + 1;
        curr_node->name->next = &cars_array[i];
        if (i != head->cnt) {
            cars_temp = curr_node;
            curr_node->name->next->name->prev = cars_temp;
        }
        if (i == head->cnt) {
            head->last = curr_node;
            curr_node->name->next = NULL;
            curr_node->name->prev = cars_temp;
        }
        curr_node = curr_node->name->next;
    }

}

void output(head *head_point) {
    int out_flag;
    puts("\n");
    if (head_point->first != NULL) {
        /*Selecting the output option (from the first element or from the last)*/
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

    /*Memory cleaning is carried out by deleting each element of the list piecemeal*/
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
    int flag = 0;
    count = 0;
    sep = ';';

    str[strlen(str)-1] = '\0';

    /*Counting the number of delimiters in a line*/
    for (i = 0; i < strlen(str) - 1; i++) {
        if (str[i] == sep) count++;
    }

    /*If the number of delimiters is not equal to 6 (that is how many delimiters the string satisfying the
     * conditions contains), the string is no longer satisfying the condition*/
    if (count != 6) key = 0;
    else {
        /*Splitting a string into elements of a two-dimensional array of strings for
         * subsequent analysis of each proposed element*/
        str_array = simple_split(str, strlen(str), sep);
        /*Comparisons of ASCII codes of elements of a two-dimensional array starting from the second with ASCII codes
         * corresponding to digits, since anything can be written in the first two (the manufacturer and the
         * model are strings)*/
        for (i = 2; i < 7; i++) {

            for (j = 0;(j < strlen(str_array[i])); j++) {
                if (str_array[i][j] < 47 || str_array[i][j] > 58) {
                    /*Also, the correct elements will be a dot and a comma for the 5th and 6th elements of a two-dimensional array, since fractional values are stored in these fields*/
                    if ((i == 4 || i == 5) && (str_array[i][j] == 46 || str_array[i][j] == 44)) key = 1;
                    else flag = 1;
                }
            }
        }
    }

    if (flag) key = 0;

    return key;
}

void file_output(head *head_point){
    FILE  *df = fopen("C:\\Users\\sasha\\CLionProjects\\kursovaya\\kursovaya_2sem\\out.csv", "w");

    if (df){
        cars *current_car_node;

        current_car_node = head_point->first;

        while (current_car_node != NULL) {
            fprintf(df,"%d;%s;%s;%d;%d; %.2f; %.2f;%d\n",
                   current_car_node->count, current_car_node->manufacture, current_car_node->name->name, current_car_node->gears,
                   current_car_node->power, current_car_node->fuel_consumption,
                   current_car_node->weight, current_car_node->year);
            current_car_node = current_car_node->name->next;
        }
    }
    fclose(df);
}
