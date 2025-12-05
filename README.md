# Мини "Библиотечна система"

## Описание
Това е малка библиотечна система на C++ с обектно-ориентиран дизайн.  
Системата включва класове за управление на автори, книги, читатели и заеми, както и основен клас Library, който обединява всички функционалности.

### Класове

- **Author**
  - Представя автор на книга.
  -  `name` (име), `birthYear` (година на раждане).
  - Методи: `to_string()`, getters/setters с валидации.

- **Book**
  - Представя книга.
  -  `title`, `author` (обект Author), `year`, `price`, `isbn`.
  - Статичен член: `totalBooks` – брой на живите инстанции.
  - Методи: `to_string()`, getters/setters с валидации, static `getTotalBooks()`.
  - Rule of 5: copy/move конструктори и оператори, деструктор.

- **Member**
  - Представя читател.
  -  `name`, `memberId`, `yearJoined`.
  - Методи: `to_string()`, getters/setters с валидации.

- **Loan**
  - Представя заем на книга от читател.
  -  `isbn`, `memberId`, `startDate`, `dueDate`, `returned`.
  - Методи: `markReturned()`, `isOverdue()`, `to_string()`.

- **Library**
  - Управлява книгите, читателите и заемите.
  -  `books`, `members`, `loans`.
  - Методи: `addBook()`, `addMember()`, `hasBook()`, `isBookAvailable()`, `loanBook()`, `returnBook()`, `findByAuthor()`, `to_string()` за подробен отчет.

## Компилиране
За компилиране на проекта (един файл `main.cpp`) използвайте следната команда:

```bash
g++ -std=gnu++17 -Wall -Wextra -O2 -o library main.cpp
```
или ползвайте компилатор като CodeBlocks

## Примерен изход

```
=== Library Report ===
Total books: 2
Total members: 1
Active loans: 0
----------------------
Books List:
Title: Pod igoto
  Author: Ivan Vazov (1850)
  Year: 1894
  Price: $25.500000
  ISBN: ISBN-001
  Availability: Available

Title: Nema zemya
  Author: Ivan Vazov (1850)
  Year: 1900
  Price: $18.900000
  ISBN: ISBN-002
  Availability: Available


Loan created for ISBN ISBN-001 to member M001.

Availability check:
ISBN-001: Loaned out
Book with ISBN ISBN-001 returned by member M001.
ISBN-001: Available

Books by Vazov:
Title: Pod igoto
  Author: Ivan Vazov (1850)
  Year: 1894
  Price: $25.500000
  ISBN: ISBN-001
Title: Nema zemya
  Author: Ivan Vazov (1850)
  Year: 1900
  Price: $18.900000
  ISBN: ISBN-002
```
