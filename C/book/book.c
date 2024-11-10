#include <stdio.h>

typedef struct {
    char title[100];
    char author[100];
    int pages;
} book_t;

int main(void) {
    book_t book;

    printf("Title: ");
    fgets(book.title, sizeof(book.title), stdin);

    printf("Author: ");
    fgets(book.author, sizeof(book.author), stdin);

    printf("Pages: ");
    scanf("%d", &book.pages);

    printf("\nBook Title: %sAuthor: %sPages: %d\n", book.title, book.author, book.pages);
}