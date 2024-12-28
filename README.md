# library-management 
Library Management System
Overview
This program, Library Management System, provides functionality to manage a digital library. It allows for adding, removing, checking out, and returning books. The program reads commands from a file and processes them to manage the library's inventory. Each book in the library has the following attributes:

Title
Author
Year of publication
Availability status (available or checked out)

Features
Add Books: Add new books to the library, ensuring no duplicates are entered.
Remove Books: Remove books from the library by title, author, and year.
Checkout Books: Mark books as checked out if available.
Return Books: Mark books as returned and available for future checkout.
View Library: Display all books currently in the library, along with their availability status.

Input and Output
Input: A file containing commands to manage the library. Supported commands include:

add: Add a book to the library.
remove: Remove a book from the library.
checkout: Checkout a book.
return: Return a book.
print: Display all books in the library.
Output: Command-line messages indicating the results of operations, such as successful additions, removals, or errors (e.g., "Book not found" or "Library is full").

How It Works
File Processing: The program reads commands and book details from the input file.
Dynamic Memory Allocation: Memory is dynamically allocated for each book's details to manage the library efficiently.
Book Management: Functions process the commands and update the library accordingly:
addBook(): Adds a book to the library.
removeBook(): Removes a book from the library.
checkoutBook(): Checks out a book.
returnBook(): Returns a checked-out book.
printLibrary(): Displays all books in the library.