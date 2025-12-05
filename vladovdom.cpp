#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Author {
private:
    string name;
    int birthYear;

public:
    Author(string n = "Unknown", int by = 1900) : name(n), birthYear(by) {}

    string getName() const { return name; }
    int getBirthYear() const { return birthYear; }

    void setBirthYear(int by) {
        if (by >= 1850 && by <= 2025)
            birthYear = by;
        else
            cout << "Invalid birth year\n";
    }

    string to_string() const {
        return name + " (" + std::to_string(birthYear) + ")";
    }
};

class Book {
private:
    string title;
    Author author;
    int year;
    double price;
    string isbn;

    void validate() {
        if (year < 1000 || year > 2025) year = 1900;
        if (price < 0) price = 0;
    }

public:
    static int totalBooks;

    Book() : title("Unknown"), author(), year(1900), price(0), isbn("N/A") { ++totalBooks; }
    Book(const string& t, const Author& a, int y, double p, const string& i)
        : title(t), author(a), year(y), price(p), isbn(i) {
        validate();
        ++totalBooks;
    }

    Book(const Book& other) = default;
    Book(Book&& other) noexcept = default;
    Book& operator=(const Book& other) = default;
    Book& operator=(Book&& other) noexcept = default;
    ~Book() { --totalBooks; }

    string getTitle() const { return title; }
    Author getAuthor() const { return author; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    string getISBN() const { return isbn; }

    void setYear(int y) { if (y >= 1000 && y <= 2025) year = y; }
    void setPrice(double p) { if (p >= 0) price = p; }

    string to_string() const {
        return "Title: " + title + "\n  Author: " + author.to_string() +
               "\n  Year: " + std::to_string(year) +
               "\n  Price: $" + std::to_string(price) +
               "\n  ISBN: " + isbn;
    }

    static int getTotalBooks() { return totalBooks; }
};

int Book::totalBooks = 0;

class Member {
private:
    string name;
    string memberId;
    int yearJoined;

public:
    Member(string n = "Unknown", string id = "N/A", int yj = 2000)
        : name(n), memberId(id), yearJoined(yj) {}

    string getName() const { return name; }
    string getMemberId() const { return memberId; }
    int getYearJoined() const { return yearJoined; }

    void setMemberId(const string& id) {
        if (!id.empty()) memberId = id;
        else cout << "Invalid memberId\n";
    }

    string to_string() const {
        return "Member: " + name + " (ID: " + memberId + "), joined " + std::to_string(yearJoined);
    }
};

class Loan {
private:
    string isbn;
    string memberId;
    string startDate;
    string dueDate;
    bool returned;

public:
    Loan(const string& i, const string& m, const string& s, const string& d)
        : isbn(i), memberId(m), startDate(s), dueDate(d), returned(false) {
        if (dueDate < startDate) {
            cout << "Due date cannot be before start date. Setting dueDate = startDate.\n";
            dueDate = startDate;
        }
    }

    void markReturned() { returned = true; }

    bool isOverdue(const string& today) const {
        return !returned && today > dueDate;
    }

    bool isReturned() const { return returned; }

    string getISBN() const { return isbn; }
    string getMemberId() const { return memberId; }

    string to_string() const {
        return "Loan: ISBN " + isbn + ", Member " + memberId +
               ", Start: " + startDate + ", Due: " + dueDate +
               ", Status: " + (returned ? "Returned" : "Not returned");
    }
};

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Loan> loans;

public:
    void addBook(const Book& b) { books.push_back(b); }
    void addMember(const Member& m) { members.push_back(m); }

    bool hasBook(const string& isbn) const {
        return any_of(books.begin(), books.end(), [&](const Book& b) { return b.getISBN() == isbn; });
    }

    bool isBookAvailable(const string& isbn) const {
        for (const auto& loan : loans) {
            if (loan.getISBN() == isbn && !loan.isReturned()) return false;
        }
        return hasBook(isbn);
    }

    bool loanBook(const string& isbn, const string& memberId, const string& start, const string& due) {
        if (!hasBook(isbn)) {
            cout << "Book with ISBN " << isbn << " not found.\n";
            return false;
        }
        if (!isBookAvailable(isbn)) {
            cout << "Book with ISBN " << isbn << " is currently loaned out.\n";
            return false;
        }
        loans.emplace_back(isbn, memberId, start, due);
        cout << "Loan created for ISBN " << isbn << " to member " << memberId << ".\n";
        return true;
    }

    bool returnBook(const string& isbn, const string& memberId) {
        for (auto& loan : loans) {
            if (loan.getISBN() == isbn && loan.getMemberId() == memberId && !loan.isReturned()) {
                loan.markReturned();
                cout << "Book with ISBN " << isbn << " returned by member " << memberId << ".\n";
                return true;
            }
        }
        cout << "No active loan found for ISBN " << isbn << " and member " << memberId << ".\n";
        return false;
    }

    vector<Book> findByAuthor(const string& authorName) const {
        vector<Book> result;
        for (const auto& book : books) {
            if (book.getAuthor().getName().find(authorName) != string::npos)
                result.push_back(book);
        }
        return result;
    }

    string to_string() const {
        int activeLoans = 0;
        for (const auto& loan : loans)
            if (!loan.isReturned()) ++activeLoans;

        string result = "=== Library Report ===\n";
        result += "Total books: " + std::to_string(books.size()) + "\n";
        result += "Total members: " + std::to_string(members.size()) + "\n";
        result += "Active loans: " + std::to_string(activeLoans) + "\n";
        result += "----------------------\nBooks List:\n";

        for (const auto& book : books) {
            result += book.to_string() + "\n";
            result += "  Availability: " + string(isBookAvailable(book.getISBN()) ? "Available" : "Loaned out") + "\n\n";
        }

        return result;
    }
};

int main() {
    Library lib;
    Author a{"Ivan Vazov", 1850};
    Book b1{"Pod igoto", a, 1894, 25.50, "ISBN-001"};
    Book b2{"Nema zemya", a, 1900, 18.90, "ISBN-002"};

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addMember(Member{"Petar Petrov", "M001", 2023});

    cout << lib.to_string() << "\n";

    lib.loanBook("ISBN-001", "M001", "2025-11-03", "2025-11-17");

    cout << "\nAvailability check:\n";
    cout << "ISBN-001: " << (lib.isBookAvailable("ISBN-001") ? "Available" : "Loaned out") << "\n";
    lib.returnBook("ISBN-001", "M001");
    cout << "ISBN-001: " << (lib.isBookAvailable("ISBN-001") ? "Available" : "Loaned out") << "\n";

    cout << "\nBooks by Vazov:\n";
    for (const auto& bk : lib.findByAuthor("Vazov")) {
        cout << bk.to_string() << "\n";
    }
}


