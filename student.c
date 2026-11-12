#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define TABLE_SIZE 47

typedef struct {
    int id;
    char name[40];
    char department[10];
    int marks;
} Student;

typedef struct BSTNode {
    Student data;
    struct BSTNode *left, *right;
} BSTNode;

typedef struct AVLNode {
    Student data;
    struct AVLNode *left, *right;
    int height;
} AVLNode;

typedef struct {
    int occupied;
    Student data;
} HashSlot;

Student students[MAX_STUDENTS] = {
    {4101,"Aadhav","CSE",87},
    {4102,"Bhavya","ECE",92},
    {4103,"Chirag","IT",78},
    {4104,"Dharani","EEE",95},
    {4105,"Ebrahim","AIML",84},
    {4106,"Gautham","CSE",90},
    {4107,"Hema","ECE",81},
    {4108,"Irfan","IT",96},
    {4109,"Jothi","EEE",88},
    {4110,"Kavin","AIML",79},
    {4111,"Mohana","CSE",93},
    {4112,"Niranjan","ECE",85},
    {4113,"Oviya","IT",91},
    {4114,"Pradeep","EEE",76},
    {4115,"Raghav","AIML",98},
    {4116,"Sahana","CSE",82},
    {4117,"Tharika","ECE",89},
    {4118,"Umesh","IT",94},
    {4119,"Varsha","EEE",80},
    {4120,"Yazhini","AIML",97},
    {4121,"Zubin","CSE",86},
    {4122,"Akilan","ECE",90},
    {4123,"Banu","IT",83},
    {4124,"Chandrika","EEE",92},
    {4125,"Dinesh","AIML",77},
    {4126,"Elakkiya","CSE",95},
    {4127,"Farooq","ECE",88},
    {4128,"Gokila","IT",84},
    {4129,"Harish","EEE",91},
    {4130,"Iniya","AIML",89}
};
int studentCount = 30;
BSTNode *bstRoot = NULL;
AVLNode *avlRoot = NULL;
HashSlot hashTable[TABLE_SIZE];
int totalCollisions = 0;

void printStudent(Student s) {
    printf("ID: %d | Name: %-12s | Department: %-3s | Marks: %d\n",
           s.id, s.name, s.department, s.marks);
}

/* ---------------- Binary Search Tree ---------------- */
BSTNode *bstInsert(BSTNode *root, Student s) {
    if (!root) {
        BSTNode *n = (BSTNode *)malloc(sizeof(BSTNode));
        if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
        n->data = s; n->left = n->right = NULL;
        return n;
    }
    if (s.id < root->data.id) root->left = bstInsert(root->left, s);
    else if (s.id > root->data.id) root->right = bstInsert(root->right, s);
    return root;
}

BSTNode *bstSearch(BSTNode *root, int id, int *comparisons) {
    while (root) {
        (*comparisons)++;
        if (id == root->data.id) return root;
        root = (id < root->data.id) ? root->left : root->right;
    }
    return NULL;
}

int bstHeight(BSTNode *root) {
    if (!root) return 0;
    int l = bstHeight(root->left), r = bstHeight(root->right);
    return 1 + (l > r ? l : r);
}
void bstInorder(BSTNode *r) {
    if (r) { bstInorder(r->left); printStudent(r->data); bstInorder(r->right); }
}
void bstPreorder(BSTNode *r) {
    if (r) { printStudent(r->data); bstPreorder(r->left); bstPreorder(r->right); }
}
void bstPostorder(BSTNode *r) {
    if (r) { bstPostorder(r->left); bstPostorder(r->right); printStudent(r->data); }
}

/* ---------------- AVL Tree ---------------- */
int maxInt(int a, int b) { return a > b ? a : b; }
int avlHeight(AVLNode *n) { return n ? n->height : 0; }
AVLNode *newAVLNode(Student s) {
    AVLNode *n = (AVLNode *)malloc(sizeof(AVLNode));
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->data = s; n->left = n->right = NULL; n->height = 1;
    return n;
}
AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->left, *t = x->right;
    x->right = y; y->left = t;
    y->height = 1 + maxInt(avlHeight(y->left), avlHeight(y->right));
    x->height = 1 + maxInt(avlHeight(x->left), avlHeight(x->right));
    return x;
}
AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->right, *t = y->left;
    y->left = x; x->right = t;
    x->height = 1 + maxInt(avlHeight(x->left), avlHeight(x->right));
    y->height = 1 + maxInt(avlHeight(y->left), avlHeight(y->right));
    return y;
}
int balanceFactor(AVLNode *n) {
    return n ? avlHeight(n->left) - avlHeight(n->right) : 0;
}
AVLNode *avlInsert(AVLNode *root, Student s) {
    if (!root) return newAVLNode(s);
    if (s.id < root->data.id) root->left = avlInsert(root->left, s);
    else if (s.id > root->data.id) root->right = avlInsert(root->right, s);
    else return root;

    root->height = 1 + maxInt(avlHeight(root->left), avlHeight(root->right));
    int b = balanceFactor(root);

    if (b > 1 && s.id < root->left->data.id) return rotateRight(root); /* LL */
    if (b < -1 && s.id > root->right->data.id) return rotateLeft(root); /* RR */
    if (b > 1 && s.id > root->left->data.id) { /* LR */
        root->left = rotateLeft(root->left); return rotateRight(root);
    }
    if (b < -1 && s.id < root->right->data.id) { /* RL */
        root->right = rotateRight(root->right); return rotateLeft(root);
    }
    return root;
}
AVLNode *avlSearch(AVLNode *root, int id, int *comparisons) {
    while (root) {
        (*comparisons)++;
        if (id == root->data.id) return root;
        root = (id < root->data.id) ? root->left : root->right;
    }
    return NULL;
}
void avlInorder(AVLNode *r) {
    if (r) { avlInorder(r->left); printStudent(r->data); avlInorder(r->right); }
}
void avlPreorder(AVLNode *r) {
    if (r) { printStudent(r->data); avlPreorder(r->left); avlPreorder(r->right); }
}
void avlPostorder(AVLNode *r) {
    if (r) { avlPostorder(r->left); avlPostorder(r->right); printStudent(r->data); }
}

/* ---------------- Hashing with Linear Probing ---------------- */
int hashFunction(int id) { return id % 10; }

void hashInsert(Student s) {
    int index = hashFunction(s.id), checked = 0;
    while (hashTable[index].occupied && checked < TABLE_SIZE) {
        totalCollisions++;
        index = (index + 1) % TABLE_SIZE;
        checked++;
    }
    if (checked == TABLE_SIZE) {
        printf("Hash table is full; cannot insert ID %d.\n", s.id);
        return;
    }
    hashTable[index].occupied = 1;
    hashTable[index].data = s;
}

int hashSearch(int id, int *probes) {
    int index = hashFunction(id), checked = 0;
    *probes = 0;
    while (checked < TABLE_SIZE && hashTable[index].occupied) {
        (*probes)++;
        if (hashTable[index].data.id == id) return index;
        index = (index + 1) % TABLE_SIZE;
        checked++;
    }
    if (checked < TABLE_SIZE) (*probes)++; /* count the first empty slot */
    return -1;
}

void displayHashTable(void) {
    int i;
    printf("\nHASH TABLE (occupied slots)\n");
    for (i = 0; i < TABLE_SIZE; i++)
        if (hashTable[i].occupied)
            printf("Index %2d -> ID %d (%s)\n", i,
                   hashTable[i].data.id, hashTable[i].data.name);
}

void buildStructures(void) {
    int i;
    memset(hashTable, 0, sizeof(hashTable));
    totalCollisions = 0;
    for (i = 0; i < studentCount; i++) {
        bstRoot = bstInsert(bstRoot, students[i]);
        avlRoot = avlInsert(avlRoot, students[i]);
        hashInsert(students[i]);
    }
}

void searchMenu(void) {
    int id, comparisons = 0, probes = 0, choice, index;
    printf("Enter Student ID to search: ");
    if (scanf("%d", &id) != 1) { puts("Invalid input."); return; }
    printf("1. BST  2. AVL  3. Hash Table\nChoose structure: ");
    if (scanf("%d", &choice) != 1) { puts("Invalid input."); return; }

    if (choice == 1) {
        BSTNode *found = bstSearch(bstRoot, id, &comparisons);
        if (found) printStudent(found->data); else puts("Student not found.");
        printf("BST key comparisons: %d\n", comparisons);
    } else if (choice == 2) {
        AVLNode *found = avlSearch(avlRoot, id, &comparisons);
        if (found) printStudent(found->data); else puts("Student not found.");
        printf("AVL key comparisons: %d\n", comparisons);
    } else if (choice == 3) {
        index = hashSearch(id, &probes);
        if (index >= 0) printStudent(hashTable[index].data);
        else puts("Student not found.");
        printf("Hash table probes: %d\n", probes);
    } else puts("Invalid choice.");
}

void runExperiment(void) {
    int c1 = 0, c2 = 0, p1 = 0, p2 = 0;
    int successID = 4115, missingID = 4199;
    bstSearch(bstRoot, successID, &c1);
    bstSearch(bstRoot, missingID, &c2);
    avlSearch(avlRoot, successID, &p1);
    avlSearch(avlRoot, missingID, &p2);
    int hp1 = 0, hp2 = 0;
    hashSearch(successID, &hp1);
    hashSearch(missingID, &hp2);

    printf("\n========== PERFORMANCE EXPERIMENT ==========\n");
    printf("Dataset size: %d students\n", studentCount);
    printf("BST height: %d | successful comparisons: %d | unsuccessful: %d\n",
           bstHeight(bstRoot), c1, c2);
    printf("AVL height: %d | successful comparisons: %d | unsuccessful: %d\n",
           avlHeight(avlRoot), p1, p2);
    printf("Hash table size: %d | insertion collisions: %d\n",
           TABLE_SIZE, totalCollisions);
    printf("Hash successful search probes (ID %d): %d\n", successID, hp1);
    printf("Hash unsuccessful search probes (ID %d): %d\n", missingID, hp2);
    puts("============================================");
}

void addStudent(void) {
    Student s;
    if (studentCount >= MAX_STUDENTS) { puts("Student storage is full."); return; }
    printf("Enter ID: ");
    if (scanf("%d", &s.id) != 1) { puts("Invalid input."); return; }
    for (int i = 0; i < studentCount; i++)
        if (students[i].id == s.id) { puts("That ID already exists."); return; }
    printf("Enter name (one word): ");
    if (scanf("%39s", s.name) != 1) { puts("Invalid input."); return; }
    printf("Enter department (CSE/ECE/IT/EEE): ");
    if (scanf("%9s", s.department) != 1) { puts("Invalid input."); return; }
    printf("Enter marks: ");
    if (scanf("%d", &s.marks) != 1) { puts("Invalid input."); return; }

    students[studentCount++] = s;
    bstRoot = bstInsert(bstRoot, s);
    avlRoot = avlInsert(avlRoot, s);
    hashInsert(s);
    puts("Student inserted into all three data structures.");
}

void displayStudents(void) {
    printf("\n%-8s %-15s %-12s %s\n", "ID", "NAME", "DEPARTMENT", "MARKS");
    for (int i = 0; i < studentCount; i++)
        printf("%-8d %-15s %-12s %d\n", students[i].id,
               students[i].name, students[i].department, students[i].marks);
}

int main(void) {
    int choice;
    buildStructures();
    do {
        printf("\n===== STUDENT RECORD MANAGEMENT =====\n");
        printf("1. Search using BST\n");
        printf("2. Search using AVL Tree\n");
        printf("3. Search using Hashing\n");
        printf("4. Display BST traversals\n");
        printf("5. Display AVL traversals\n");
        printf("6. Display Hash Table\n");
        printf("7. Insert a new student\n");
        printf("8. Run performance experiment\n");
        printf("9. Display all student records\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            puts("Invalid input. Exiting."); break;
        }
        switch (choice) {
            case 1: case 2: case 3: searchMenu(); break;
            case 4:
                puts("\nBST INORDER:"); bstInorder(bstRoot);
                puts("\nBST PREORDER:"); bstPreorder(bstRoot);
                puts("\nBST POSTORDER:"); bstPostorder(bstRoot);
                break;
            case 5:
                puts("\nAVL INORDER:"); avlInorder(avlRoot);
                puts("\nAVL PREORDER:"); avlPreorder(avlRoot);
                puts("\nAVL POSTORDER:"); avlPostorder(avlRoot);
                break;
            case 6: displayHashTable(); break;
            case 7: addStudent(); break;
            case 8: runExperiment(); break;
            case 9: displayStudents(); break;
            case 0: puts("Exiting program."); break;
            default: puts("Invalid choice.");
        }
    } while (choice != 0);
    return 0;
}
