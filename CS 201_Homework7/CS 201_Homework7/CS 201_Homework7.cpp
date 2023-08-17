#include <iostream>
#include <string>
#include "Book.h"
#include "strutils.h"
#include <vector>

// in sucourse predefined books vector creates an error, bu in compiler it works, inquire it
// check binary search whether ascending surname order is mandatory or not

using namespace std;


//function to take user input to determine which function will be called, returns operation number
int operationSelect() {
	int operation;
	cout << "Library System Menu:" << endl << "1. Add books" << endl << "2. Search for an author" << endl \
		<< "3. Search for by book title" << endl << "4. Display books" << endl << "5. Quit" << endl << "Enter your choice: ";
	cin >> operation;
	return operation;
}

//a function to determine whether book1's position is smaller than book2's or not
bool compareBooks(const Book& book1, const Book& book2) {
	string surname1 = LowerString(book1.getAuthorLastName()); //surnames are converted to lowercase because 
	string surname2 = LowerString(book2.getAuthorLastName()); //hw tells us these sortings are case-insensitive
	if (surname1 != surname2)//If surnames are not equal return smaller or bigger
		return surname1 < surname2;

	return LowerString(book1.getTitle()) < LowerString(book2.getTitle()); // if surnames are equal checks titles of books (rule of this hw)
}

//function to sort a vector full of Book structure, used method is insertion sort
void insertionSortLibrary(vector<Book>& books) {
	int size = books.size();
	int i, loc;

	for (i = 1; i < size; i++) {
		Book temp = books[i];
		loc = i;

		while (loc > 0 && compareBooks(temp, books[loc - 1])) {

			books[loc] = books[loc - 1];
			loc--;

		}

		books[loc] = temp;
	}
}

//inesrtion a book to a sorted vector full of books
void insertBook(vector<Book>& books, const Book& book) {
	int count = books.size();
	books.push_back(book);

	int loc = count;

	while (loc > 0 && compareBooks(book, books[loc - 1])) {

		books[loc] = books[loc - 1];
		loc--;

	}

	books[loc] = book;
}

//function to display vector
void displayLibrary(const vector<Book>& books) {
	int i, size = books.size();

	cout << "Sorted books by author's last name: " << endl;

	for (i = 0; i < size; i++) {
		cout << i + 1 << ". ";
		books[i].display();
	}
	cout << endl;
}

//function to add a new book to vector full of books
void includeBook(vector<Book>& books) {
	Book book;
	string title, author;
	int year;
	cout << "Enter the new book details: " << endl;
	// take inputs of book that you want to add to library, assume that all of them are in appropriate format
	cout << "Enter book's title: ";
	getline(cin >> ws, title);
	book.setTitle(title);


	cout << "Enter book's author: ";
	getline(cin >> ws, author);
	book.setAuthor(author);



	cout << "Enter book's publication year: ";
	cin >> year;
	book.setPublicationYear(year);

	insertBook(books, book);// insertBook function called, we assume that vector is sorted because in the beginning of main vector sorted with insertionSortLibrary func
}


//function to find books written by author that is given by user, use binary search by surname as case-insensitive, if same use title's of books
vector<Book> binarySearch(const vector<Book>& books, const string& author, vector<int>& positions, const string& surname, int& low, int& middle, int& high) {
	vector<Book> searchedList; // a new vector to return books belong to given author
	int size = books.size();

	while (low <= high) { //low and high represent thresholds
		middle = (high + low) / 2;
		string middleSurname = books[middle].getAuthorLastName();
		if (LowerString(middleSurname) == LowerString(surname)) {
			low = middle + 1; // change low and high because if we don't while loop executes after and after
			high = middle - 1;

			int idx = middle;
			while (true) { // a loop to go to first idx whose surname equals to given surname
				if (LowerString(surname) == LowerString(books[idx].getAuthorLastName())) {
					idx--;
				}
				else {
					break; //break loop when surname changes
				}

			}

			idx++; //increase idx +1 because after last occurence of surname idx decreased and now it belongs to a book which we don't look for

			while (LowerString(surname) == LowerString(books[idx].getAuthorLastName())) { //check surnames and names after that
				if (LowerString(author) == LowerString(books[idx].getAuthor())) {
					positions.push_back(idx + 1); //list to fill positions of books
					searchedList.push_back(books[idx]);
				}
				idx++;
			}
		}
		else if (LowerString(middleSurname) < LowerString(surname)) { //means that given surname is bigger than surname in the middle, that means search bigger half
			low = middle + 1; //new low becomes middle+- 1
			middle = (high + low) / 2;
		}
		else { //means that given surname is lower than surname in the middle, that means search lower half
			high = middle - 1; //new high becomes middle - 1
			middle = (high + low) / 2;
		}
	}
	return searchedList;
}

//function to search author by given surname, used binarysearch function inside and created parameters which needed, also displayed books
void searchAuthor(const vector<Book>& books, const string& author) { //binary search
	string surname = author.substr(author.rfind(' ') + 1);

	vector<int> positions; //give with ampersand char to func
	vector<Book> searchedList;//return

	int low = 1, middle, high = books.size() - 1;
	middle = high / low;


	searchedList = binarySearch(books, author, positions, surname, low, middle, high);

	int i, searchedSize = searchedList.size();

	if (searchedSize == 0) { //if empty error mesage
		cout << "No books were found." << endl;
	}
	else { //display books with given format

		cout << "Books by " << surname << ":" << endl;

		for (i = 0; i < searchedSize; i++) {
			Book book = searchedList[i];
			cout << "Title: " << book.getTitle() << ", Publication Year: " << book.getPublicationYear() << ", Position: " << positions[i] << endl;
		}
	}


}

// function to search a book with given title as case-insensitive, used linear search
void searchTitle(const vector<Book>& books, const string& title) { //linear search
	int i, size = books.size();

	cout << "Books matching the title " << "\"" << title << "\":" << endl;

	bool check = false;

	for (i = 0; i < size; i++) {
		if (LowerString(books[i].getTitle()) == LowerString(title)) {
			cout << "Title: " << books[i].getTitle() << ", Author: " << books[i].getAuthor() <<
				", Publication Year: " << books[i].getPublicationYear() << ", Position: " << i + 1 << endl;
			check = true;
		}
	}

	if (!check)
		cout << "No books were found." << endl;
}

//function to fill vector with initial books, created as an solution to homework upload system's error
void fillBooks(vector<Book>& books) {
	Book b1("The Great Gatsby", "F Scott Fitzgerald", 1925);
	Book b2("Moby Dick", "Herman Melville", 1851);
	Book b3("To Kill a Mockingbird", "Harper Lee", 1960);
	Book b4("Pride and Prejudice", "Jane Austen", 1813);
	Book b5("Burmese Days", "George Orwell", 1934);
	Book b6("Brave New World", "Aldous Huxley", 1932);
	Book b7("Animal Farm", "George Orwell", 1945);
	books.push_back(b1);
	books.push_back(b2);
	books.push_back(b3);
	books.push_back(b4);
	books.push_back(b5);
	books.push_back(b6);
	books.push_back(b7);

}

int main() {
	int operation;
	vector<Book> books;
	fillBooks(books);

	insertionSortLibrary(books); // list is sorted beforehand, so don't need to sort in every step

	do {
		operation = operationSelect();

		if (operation == 1) {
			includeBook(books);
		}
		else if (operation == 2) {
			string author;
			cout << "Enter the author of the book you want to search for: ";
			getline(cin >> ws, author);
			searchAuthor(books, author);
		}
		else if (operation == 3) {
			string title;
			cout << "Enter the title of the book you want to search for: ";
			getline(cin >> ws, title);
			searchTitle(books, title);
		}
		else if (operation == 4) {
			displayLibrary(books);
		}
		else if (operation == 5) {
			cout << "Goodbye!" << endl;
		}
		else {
			cout << "Invalid choice, please try again." << endl; // loop executes unless operation = 5, if operation not in range throw an error mesage
		}

	} while (operation != 5);

	return 1;
}
