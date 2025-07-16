# MiniDB 🗂️

A lightweight in-memory SQL-like **relational database engine** built using **C++**.

> This project mimics core DBMS functionalities such as table creation, data insertion, querying, deletion, and updates—all from a terminal-based interface.

---

## ✨ Features

- 🧠 SQL-like query parsing (custom parser)
- 🏗️ `CREATE TABLE` with typed columns (`INT`, `STRING`)
- ➕ `INSERT INTO` with strict type validation
- 🔍 `SELECT` all or with `WHERE` clause
- ✏️ `UPDATE` with conditional logic
- ❌ `DELETE` rows by condition
- 📦 Modular code design using **OOP principles**
- 🧪 Robust CLI and error feedback

---

## 📁 Folder Structure

```
MiniDB/
├── include/       # Header files
│   ├── db.hpp
│   └── table.hpp
├── src/           # Implementation files
│   ├── main.cpp
│   ├── db.cpp
│   ├── table.cpp
│   └── parser.cpp
├── Makefile       # For Linux/macOS builds (optional)
├── minidb.exe     # Windows binary (after compilation)
└── README.md
```

---

## 🧪 Example Queries

```sql
CREATE TABLE students (name STRING, age INT);
INSERT INTO students VALUES ("Sayan", 21);
INSERT INTO students VALUES ("Rohit", 20);
SELECT * FROM students;
SELECT * FROM students WHERE name = "Sayan";
UPDATE students SET age = 22 WHERE name = "Sayan";
DELETE FROM students WHERE age = 20;
```

---

## 🚀 How to Run

### 🛠️ Compile (Linux/macOS)
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o minidb
./minidb
```

### ⚙️ Compile (Windows - MinGW)
```bash
g++ -std=c++17 -Iinclude src/main.cpp src/parser.cpp src/db.cpp src/table.cpp -o minidb
minidb.exe
```

---

## 📌 Roadmap

- [x] Basic SQL command support
- [x] Type-safe columns
- [x] CLI interface
- [ ] Persistence with file I/O
- [ ] Indexing for faster lookup
- [ ] JOIN operations and relational algebra

---

## 🤝 Contributions
Pull requests and suggestions are welcome! If you'd like to collaborate, feel free to fork or raise an issue.

---

## 📄 License
MIT License © 2025 [Your Name]

---

> Made with ❤️ for DBMS learning, C++ practice, and system-level understanding.

---

## 🔗 GitHub
[👉 Click here to visit the repository](https://github.com/your-username/MiniDB)

> _Replace the URL with your actual repo link_