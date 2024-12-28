//********************************************************
// program-libstruct.c
// Author: Jalil Fountain
// UCFID: 5390348
// Date: 11/18/24
// Class: COP 3223, Professor Parra
// Purpose: This program will create a library management system that allows for adding, removing, checking out, and returning books
// Input: file
// Output: (to the command line) displays file contents
//********************************************************
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libstruct.h"
//********************************************************** */
// void addBook
//
// Purpose:  expect the the details of a book (title, author, year) from the file and adds it to the library.
// Output: no output unless the library is full or the book is already in the library
//*********************************************************** */
void addBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear) {
    // Check if the library is full
    if (library->count >= 100) {
        printf("The library is full. Cannot add more books.\n");
        return;
    }
    // Check if the book already exists in the library
    for (int i = 0; i < library->count; i++) {
        // Compare title, author, and year for each book in the library
        if (strcmp(library->library[i]->title, bookTitle) == 0 &&
            strcmp(library->library[i]->author, bookAuthor) == 0 &&
            library->library[i]->year == bookYear) {
           
            printf("Book with title %s, author %s, and year %d is already in the library.\n",
                   bookTitle, bookAuthor, bookYear);
            return;
        }
    }
    // Dynamically allocate memory for a new Book
    Book *newBook = malloc(sizeof(Book));
    newBook->title = malloc(1024 * sizeof(char));
    newBook->author = malloc(1024 * sizeof(char));
    // Copy the provided title and author into the newly allocated memory
    strcpy(newBook->title, bookTitle);
    strcpy(newBook->author, bookAuthor);
    // Set the year and availability of the book 
    newBook->year = bookYear;
    newBook->isAvailable = 1;
    // Add the new book to the library array and increment the book count
    library->library[library->count] = newBook;
    library->count++;


    // Print message for adding the book
    printf("Book with title %s, author %s, and year %d added to the library.\n",
           bookTitle, bookAuthor, bookYear);
}
//********************************************************** */
// void removeBook
//
// Purpose:  searches for a book by its title and removes it from the library.
// Output: removed book
//*********************************************************** */
void removeBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear) {
    // Loop through the library to find the book that matches the given details
    for (int i = 0; i < library->count; i++) {
        if (library->library[i] != NULL && strcmp(library->library[i]->title, bookTitle) == 0 && strcmp(library->library[i]->author, bookAuthor) == 0 && library->library[i]->year == bookYear) {
            // Free the memory allocated for the book's title and author
            free(library->library[i]->title);
            free(library->library[i]->author);
            free(library->library[i]);  // Free the memory for the book itself
            // Shift all the books after the removed one to fill the gap (kept getting seg faults when trying to set the empty spot to NULL and couldnt figure out why so I went with the shifting method and will accept point deductions )
            for (int j = i; j < library->count - 1; j++) {
                library->library[j] = library->library[j + 1];
            }
            // Set the last position in the array to NULL and decrement the book count
            library->library[library->count - 1] = NULL;
            library->count--;
            // Print message for removal
            printf("Book with title %s, author %s, and year %d has been removed from the library.\n",
                   bookTitle, bookAuthor, bookYear);
            return;
        }
    }
    // Print error message if the book is not found
    printf("Book not found\n");
}
//********************************************************** */
// void printLibrary
//
// Purpose:  prints the details (title, author, year, availability) of all the books in the library.
// Output: details of all books in library
//*********************************************************** */
void printLibrary(Library *library) {
    // Loop through all the books and print their details
    for (int i = 0; i < library->count; i++) {
        if (library->library[i] != NULL) {
            // Print the availability status of each book
            if (library->library[i]->isAvailable) {
                printf("Book with title %s, author %s, and year %d is in the library and isn't checked out.\n",
                       library->library[i]->title,
                       library->library[i]->author,
                       library->library[i]->year);
            } else {
                printf("Book with title %s, author %s, and year %d is in the library and is checked out.\n",
                       library->library[i]->title,
                       library->library[i]->author,
                       library->library[i]->year);
            }
        }
    }
}
//********************************************************** */
// Book* findBook
//
// Purpose:  searches for a book by its title and returns a pointer to the matching Book struct if found. 
// Output: no output
//*********************************************************** */
Book* findBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear) {
    // Iterate through all books in the library
    for (int i = 0; i < library->count; i++) {
        // Check if the current book matches the search criteria
        if (library->library[i] != NULL && strcmp(library->library[i]->title, bookTitle) == 0 && strcmp(library->library[i]->author, bookAuthor) == 0 && library->library[i]->year == bookYear) {
            // If found, output the message
            printf("Book with title %s, author %s, and year %d is found!\n", 
                   library->library[i]->title, 
                   library->library[i]->author, 
                   library->library[i]->year);

            // Return the pointer to the book
            return library->library[i];
        }
    }

    // If no match is found, return NULL 
    return NULL;
}
//********************************************************** */
// void checkoutBook
//
// Purpose: changes the isAvailable field of the specified book to 0 (indicatingit is checked out).
// Output: book checked out, already checked out, or book not found
//*********************************************************** */
void checkoutBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear) {
    // Find the book in the library
    Book *book = findBook(library, bookTitle, bookAuthor, bookYear);

    // Check if the book was found
    if (book != NULL) {
        // If the book is available, mark it as checked out
        if (book->isAvailable == 1) {
            book->isAvailable = 0;
            printf("Book with title %s, author %s, and year %d is checked out.\n", bookTitle, bookAuthor, bookYear);
        } 
        // If the book is already checked out
        else {
            printf("Book with title %s, author %s, and year %d is already checked out.\n", bookTitle, bookAuthor, bookYear);
        }
    } 
    // If the book was not found
    else {
        printf("Book not found\n");
    }
}
//********************************************************** */
// void returnBook
//
// Purpose:  changes the isAvailable field of the specified book to 1 (indicating it is available again).
// Output: book returned, not checked out, or book not found
//*********************************************************** */
void returnBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear) {
    // Find the book in the library
    Book *book = findBook(library, bookTitle, bookAuthor, bookYear);
    // If the book is found
    if (book != NULL) {
        // If the book was checked out, mark it as available
        if (book->isAvailable == 0) {
            book->isAvailable = 1;
            printf("Book with title %s, author %s, and year %d is returned.\n", bookTitle, bookAuthor, bookYear);
        } 
        // If the book is already available
        else {
            printf("Book with title %s, author %s, and year %d is not checked out.\n", bookTitle, bookAuthor, bookYear);
        }
    } 
    // If the book was not found
    else {
        printf("Book not found\n");
    }
}
//********************************************************** */
// void processFile
//
// Purpose: process file's information and calls respective function 
// Output: file information
//*********************************************************** */
void processFile(const char *filename, Library *library) {
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Variables for reading command and book details
    char command[10]; //max command characters
    char bookTitle[1024]; //max book title characters 
    char bookAuthor[1024]; //max book author characters
    int bookYear; //year

    // Read the commands from the file
   while (fscanf(file, "%s", command) != EOF) {
    // Add a new book to the library
    if (strcmp(command, "add") == 0) {
        fscanf(file, " %1023[^,], %1023[^,], %d", bookTitle, bookAuthor, &bookYear);
        addBook(library, bookTitle, bookAuthor, bookYear);
    } 
    // Remove a book from the library
    else if (strcmp(command, "remove") == 0) {
        fscanf(file, " %1023[^,], %1023[^,], %d", bookTitle, bookAuthor, &bookYear);
        removeBook(library, bookTitle, bookAuthor, bookYear);
    } 
    // Print the library
    else if (strcmp(command, "print") == 0) {
        printLibrary(library);  // No need to read bookTitle, bookAuthor, and bookYear for print
    }
    // Check out a book
    else if (strcmp(command, "checkout") == 0) {
        fscanf(file, " %1023[^,], %1023[^,], %d", bookTitle, bookAuthor, &bookYear);
        checkoutBook(library, bookTitle, bookAuthor, bookYear);
    } 
    // Return a book to the library
    else if (strcmp(command, "return") == 0) {
        fscanf(file, " %1023[^,], %1023[^,], %d", bookTitle, bookAuthor, &bookYear);
        returnBook(library, bookTitle, bookAuthor, bookYear);
    } 
}

    // Close the file after processing
    fclose(file);
}
int main(int argc, char **argv) {
    // Dynamically allocate memory for the library array of Book pointers
    Library library;
    library.library = malloc(100 * sizeof(Book*));
    library.count = 0;  // Initialize the count of books to 0

    // Process the input file to update the library
    processFile(argv[1], &library);

    // Clean up dynamically allocated memory for books in the library
    for (int i = 0; i < library.count; i++) {
        if (library.library[i] != NULL) {
            free(library.library[i]->title);  // Free dynamically allocated title memory
            free(library.library[i]->author); // Free dynamically allocated author memory
            free(library.library[i]);          // Free the memory allocated for the book
        }
    }

    // Free the memory allocated for the library array
    free(library.library);

    return 0;  
}