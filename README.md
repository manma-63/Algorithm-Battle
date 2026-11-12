# Algorithm Battle – Which Data Structure Wins?

## Project overview

This C project implements a Student Record Management System and compares three data structures using the same set of student records:

- **Binary Search Tree (BST):** stores records according to Student ID.
- **AVL Tree:** a self-balancing binary search tree that uses rotations to maintain height.
- **Hash Table with Linear Probing:** maps Student IDs to table slots and resolves collisions by checking subsequent slots.

Each record contains a Student ID, student name, department, and marks.

## Dataset

The program starts with **30 records**, with IDs **4101–4130**. All records are inserted into the BST, AVL Tree, and hash table in ascending ID order.

| Student ID | Name | Department | Marks |
|---:|---|---|---:|
| 4101 | Aadhav | CSE | 87 |
| 4102 | Bhavya | ECE | 92 |
| 4103 | Chirag | IT | 78 |
| 4104 | Dharani | EEE | 95 |
| 4105 | Ebrahim | AIML | 84 |
| 4106 | Gautham | CSE | 90 |
| 4107 | Hema | ECE | 81 |
| 4108 | Irfan | IT | 96 |
| 4109 | Jothi | EEE | 88 |
| 4110 | Kavin | AIML | 79 |
| 4111 | Mohana | CSE | 93 |
| 4112 | Niranjan | ECE | 85 |
| 4113 | Oviya | IT | 91 |
| 4114 | Pradeep | EEE | 76 |
| 4115 | Raghav | AIML | 98 |
| 4116 | Sahana | CSE | 82 |
| 4117 | Tharika | ECE | 89 |
| 4118 | Umesh | IT | 94 |
| 4119 | Varsha | EEE | 80 |
| 4120 | Yazhini | AIML | 97 |
| 4121 | Zubin | CSE | 86 |
| 4122 | Akilan | ECE | 90 |
| 4123 | Banu | IT | 83 |
| 4124 | Chandrika | EEE | 92 |
| 4125 | Dinesh | AIML | 77 |
| 4126 | Elakkiya | CSE | 95 |
| 4127 | Farooq | ECE | 88 |
| 4128 | Gokila | IT | 84 |
| 4129 | Harish | EEE | 91 |
| 4130 | Iniya | AIML | 89 |

## Data structure configuration

| Parameter | Value |
|---|---|
| Initial records | 30 |
| Student ID range | 4101–4130 |
| Maximum student capacity | 100 |
| Hash table size | 47 slots |
| Hash function | `h(id) = id % 10` |
| Collision handling | Linear Probing |
| Successful search key | 4115 |
| Unsuccessful search key | 4199 |

## Program features

| Menu option | Operation |
|---:|---|
| 1 | Search using BST |
| 2 | Search using AVL Tree |
| 3 | Search using Hashing |
| 4 | Display BST inorder, preorder, and postorder traversals |
| 5 | Display AVL inorder, preorder, and postorder traversals |
| 6 | Display the hash table |
| 7 | Insert a new student record |
| 8 | Run the performance experiment |
| 9 | Display all student records |
| 0 | Exit |

## Compile and run

GCC is required.

**Linux / macOS:**

```bash
gcc -std=c99 -Wall -Wextra student.c -o student
./student
```

**Windows (GCC / MinGW):**

```bash
gcc -std=c99 -Wall -Wextra student.c -o student.exe
student.exe
```

## Verified performance results

The following figures were obtained by compiling and running this `student.c` file, then selecting menu option **8** with the initial 30 records:

| Measurement | BST | AVL Tree | Hash Table |
|---|---:|---:|---:|
| Height (nodes) | 30 | 5 | Not applicable |
| Successful search (4115) | 15 comparisons | 5 comparisons | 10 probes |
| Unsuccessful search (4199) | 30 comparisons | 5 comparisons | 22 probes |
| Insertion collisions | Not applicable | Not applicable | 300 |

The ascending insertion order creates a right-skewed ordinary BST. The AVL Tree maintains a balanced structure. The hash-table result reflects the selected hash function and linear-probing strategy.

## Screenshots

The `Screenshots/` folder contains terminal-style captures of actual output from the compiled program:

1. Initial student dataset
2. Successful searches in BST, AVL Tree, and hash table
3. Unsuccessful searches in BST, AVL Tree, and hash table
4. BST and AVL traversals
5. Hash-table display
6. Insertion of an additional test student (ID 4131)
7. Performance comparison

The insertion screenshot uses the test record `4131, ManojTest, CSE, 75`. This record is added during that separate test run; the baseline performance table above is measured before the extra insertion.

## Repository structure

```text
Manoj_M_DSA_Submission/
├── student.c
├── README.md
├── Manoj_M_RA2511042050008.docx
└── Screenshots/
    ├── 01_student_dataset.png
    ├── 02_bst_successful_search.png
    ├── 03_avl_successful_search.png
    ├── 04_hash_successful_search.png
    ├── 05_bst_unsuccessful_search.png
    ├── 06_avl_unsuccessful_search.png
    ├── 07_hash_unsuccessful_search.png
    ├── 08_bst_traversals.png
    ├── 09_avl_traversals.png
    ├── 10_hash_table.png
    ├── 11_insert_student_4131.png
    └── 12_performance_comparison.png
```

## Repository reference

GitHub repository: https://github.com/manma-63/Algorithm-Battle.git

The files in this submission are a separate local version with the 4101–4130 dataset. Upload these files to the repository if you want the online repository to reflect this version.
