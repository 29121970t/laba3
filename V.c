typedef struct List {
    List* next;
    List* prev;
    int data;
} List;

void View(List* t) {
    while (t->prev) {
        t = t->prev;
    }
    while (t->next) {
        printf("%d", t->data);
        t = t->next;
    }
    while (t->prev) {
        printf("%d", t->data);
        t = t->prev;
    }

}