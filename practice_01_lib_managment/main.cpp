#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Prints a separator line to the standard output.
 *
 * Used to visually separate item information in the console.
 */
void printLine()
{
    cout << "\n______________________________\n";
}

/**
 * @brief Abstract base class representing a generic library item.
 *
 * Holds the common attributes shared by all items in the library,
 * such as books, DVDs, and any future item types.
 *
 * This class is abstract because displayDetails() is pure virtual;
 * therefore, no instances of LibraryItem can be created directly.
 */
class LibraryItem
{
    private:
        string id;          /**< Unique identifier of the item. */
        string title;       /**< Title of the item. */
        bool isBorrowed;    /**< Borrow status: true if the item is currently borrowed. */

    public:
        /**
         * @brief Constructs a LibraryItem with the given id and title.
         * @param ID    Unique identifier of the item.
         * @param TITLE Title of the item.
         *
         * Initializes isBorrowed to false by default.
         */
        LibraryItem(string ID, string TITLE)
        {
            id = ID;
            title = TITLE;
            isBorrowed = false;
        }

        /**
         * @brief Displays detailed information about the item.
         *
         * Pure virtual function; every derived class must provide
         * its own implementation.
         */
        virtual void displayDetails() = 0;

        /**
         * @brief Marks the item as borrowed.
         */
        void borrowItem();

        /**
         * @brief Marks the item as returned (not borrowed).
         */
        void returnItem();

        /**
         * @brief Gets the item's unique identifier.
         * @return The item id as a string.
         */
        string getId() const { return id; };

        /**
         * @brief Gets the item's title.
         * @return The item title as a string.
         */
        string getTitle() const { return title; };

        /**
         * @brief Gets the current borrow status of the item.
         * @return true if the item is borrowed, false otherwise.
         */
        bool getBorrowed() const { return isBorrowed; };

        /**
         * @brief Virtual destructor.
         *
         * Ensures that the derived class destructor is called
         * when deleting through a base class pointer.
         */
        virtual ~LibraryItem() {};
};

/**
 * @brief Marks the item as borrowed.
 */
void LibraryItem::borrowItem()
{
    isBorrowed = true;
}

/**
 * @brief Marks the item as returned.
 */
void LibraryItem::returnItem()
{
    isBorrowed = false;
}

/**
 * @brief Represents a book in the library.
 *
 * Extends LibraryItem with book-specific attributes
 * such as author and number of pages.
 */
class Book : public LibraryItem
{
    private:
        string author;   /**< Name of the book's author. */
        int pages;       /**< Total number of pages. */

    public:
        /**
         * @brief Constructs a Book with the given attributes.
         * @param ID     Unique identifier.
         * @param TITLE  Title of the book.
         * @param AUTHOR Name of the author.
         * @param PAGES  Number of pages.
         */
        Book(string ID, string TITLE, string AUTHOR, int PAGES)
            : LibraryItem(ID, TITLE)
        {
            author = AUTHOR;
            pages = PAGES;
        }

        /**
         * @brief Displays detailed information about the book.
         */
        void displayDetails() override;
};

/**
 * @brief Implementation of Book::displayDetails.
 */
void Book::displayDetails()
{
    printLine();
    cout << "ID : " << getId() << endl
         << "TITLE : " << getTitle() << endl
         << "AUTHOR : " << author << endl
         << "PAGES : " << pages << endl
         << "IS BORROWED : " << getBorrowed() << endl;
    printLine();
}

/**
 * @brief Represents a DVD in the library.
 *
 * Extends LibraryItem with DVD-specific attributes
 * such as director and duration.
 */
class DVD : public LibraryItem
{
    private:
        string director;   /**< Name of the DVD's director. */
        string duration;   /**< Duration of the DVD (e.g., "148 min"). */

    public:
        /**
         * @brief Constructs a DVD with the given attributes.
         * @param ID       Unique identifier.
         * @param TITLE    Title of the DVD.
         * @param DIRECTOR Name of the director.
         * @param DURATION Duration of the DVD.
         */
        DVD(string ID, string TITLE, string DIRECTOR, string DURATION)
            : LibraryItem(ID, TITLE)
        {
            director = DIRECTOR;
            duration = DURATION;
        }

        /**
         * @brief Displays detailed information about the DVD.
         */
        void displayDetails() override;
};

/**
 * @brief Implementation of DVD::displayDetails.
 */
void DVD::displayDetails()
{
    printLine();
    cout << "ID : " << getId() << endl
         << "TITLE : " << getTitle() << endl
         << "DIRECTOR : " << director << endl
         << "DURATION : " << duration << endl
         << "IS BORROWED : " << getBorrowed() << endl;
    printLine();
}

/**
 * @brief Manages a collection of library items.
 *
 * Stores items as base class pointers, allowing polymorphic
 * behavior. Owns the items and is responsible for freeing
 * their memory in its destructor.
 */
class Library
{
    private:
        vector<LibraryItem*> items;   /**< Collection of library items. */

    public:
        /**
         * @brief Adds an item to the library.
         * @param item Pointer to the item to add.
         *
         * Ownership of the item is transferred to the Library,
         * which will delete it in its destructor.
         */
        void addItem(LibraryItem* item);

        /**
         * @brief Displays details of all items in the library.
         *
         * Uses polymorphism to call the appropriate
         * displayDetails() implementation for each item.
         */
        void showAll();

        /**
         * @brief Finds an item by id and marks it as borrowed.
         * @param id The identifier of the item to borrow.
         *
         * Prints "Borrowed!" if found, otherwise prints "Not found".
         */
        void findAndBorrow(string id);

        /**
         * @brief Finds an item by id and marks it as returned.
         * @param id The identifier of the item to return.
         *
         * Prints "Returned!" if found, otherwise prints "Not found".
         */
        void findAndReturn(string id);

        /**
         * @brief Destructor.
         *
         * Frees all dynamically allocated items in the collection.
         */
        ~Library()
        {
            for (auto item : items) delete item;
        }
};

/**
 * @brief Implementation of Library::addItem.
 */
void Library::addItem(LibraryItem* item)
{
    items.push_back(item);
}

/**
 * @brief Implementation of Library::showAll.
 */
void Library::showAll()
{
    for (auto item : items) item->displayDetails();
}

/**
 * @brief Implementation of Library::findAndBorrow.
 */
void Library::findAndBorrow(string id)
{
    for (auto item : items)
    {
        if (item->getId() == id)
        {
            item->borrowItem();
            cout << "Borrowed!" << endl;
            return;
        }
    }
    cout << "Not found" << endl;
}

/**
 * @brief Implementation of Library::findAndReturn.
 */
void Library::findAndReturn(string id)
{
    for (auto item : items)
    {
        if (item->getId() == id)
        {
            item->returnItem();
            cout << "Returned!" << endl;
            return;
        }
    }
    cout << "Not found" << endl;
}

/**
 * @brief Entry point of the program.
 *
 * Demonstrates the library system by:
 *  - creating books and DVDs,
 *  - displaying all items,
 *  - borrowing items by id,
 *  - returning items by id,
 *  - handling a not-found case,
 *  - displaying the final state.
 *
 * Memory is automatically released when the Library object
 * goes out of scope at the end of main.
 */
int main()
{
    Library lib;

    lib.addItem(new Book("B1", "Math", "Ali Rezaei", 250));
    lib.addItem(new Book("B2", "Physics", "Sara Ahmadi", 180));
    lib.addItem(new DVD("D1", "Titanic", "James Cameron", "120 min"));
    lib.addItem(new DVD("D2", "Avatar", "James Cameron", "160 min"));

    cout << "--- All Items ---" << endl;
    lib.showAll();

    lib.findAndBorrow("B1");
    lib.findAndBorrow("D1");
    lib.findAndBorrow("X9");

    cout << "\n--- After Borrowing ---" << endl;
    lib.showAll();

    lib.findAndReturn("B1");

    cout << "\n--- After Returning ---" << endl;
    lib.showAll();

    return 0;
}