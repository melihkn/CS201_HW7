#include "Book.h"
#include <iostream>


Book::Book() {
	title = "";
	author = "";
	publicationYear = 0;
}

Book::Book(const string& myTitle, const string& myAuthor, int year) {
	title = myTitle;
	author = myAuthor;
	publicationYear = year;
}

string Book::getTitle() const {

	return title;
}

string Book::getAuthor() const {
	return author;
}

int Book::getPublicationYear() const {
	return publicationYear;
}

void Book::setTitle(const string& book_title) {
	title = book_title;
}

void Book::setAuthor(const string& book_author) {
	author = book_author;
}

void Book::setPublicationYear(int book_publicationYear) {
	publicationYear = book_publicationYear;
}

string Book::getAuthorLastName() const {
	string surname = author.substr(author.rfind(' ') + 1);
	return surname;
}

void Book::display() const {

	cout << getTitle() << ", " << getAuthor() << ", " << getPublicationYear() << endl;
}