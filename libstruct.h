#ifndef LIBSTRUCT_H
#define LIBSTRUCT_H

#include <stdlib.h>

// Struct definitions
typedef struct Book {
    char *title;         // Dynamic array for the book's title
    char *author;        // Dynamic array for the book's author
    int year;            // Year the book was published
    int isAvailable;     // 1 if available, 0 if checked out
} Book;

typedef struct Library {
    Book **library;      // Dynamic array of Book pointers (max size 100)
    int count;           // Current number of books in the library
} Library;

// Function prototypes
void addBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void removeBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void printLibrary(Library *library);
Book* findBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void checkoutBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void returnBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);

#endif // LIBSTRUCT_H