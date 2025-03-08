
# CS 4308 Project 1 – Lexical Analyzer in C

This project implements a lexical analyzer in C that tokenizes an input file 
into identifiers, keywords, numeric literals, string literals, operators, 
and punctuation (From a subset of Python and Java). A trie data structure is used for 
efficient keyword lookup. The analyzer supports token sets based on both Python and Java rules.
It handles Python and Java interchangeably, there is no distinction between code that is python or java yet.

---

## Overview

This project demonstrates:
- **Lexical Analysis:** Scanning input files and breaking them down into tokens.
- **Trie-Based Keyword Lookup:** Efficient insertion, search, and deletion for keywords.
- **Token Classification:** Identifying tokens based on rules for identifiers, keywords, literals, operators, and punctuation.
- **Modular Code Structure:** Separation of functionality across multiple source and header files.

### Token sets include:
- **Keywords:**  
  - *Python:* `def`, `print`  
  - *Java:* `public`, `class`, `static`, `void`, `int`, `String`
- **Identifiers:**
    - **Start With:** `A-z`, `_`
    - **Can Contain:** `0–9`, `A-z`, `_`
    - **Ends With:** `Punctuation`, `Whitespace`
- **Literals:**  
  - *Python:* Numerical (integer, float) and string literals (enclosed in `'` or `"`).  
  - *Java:* Numeric literals include integers (only digits) and decimals (begin with a digit or a period and contain a single decimal point).
- **Operators:** `=`, `+`
- **Punctuation:**  
  - *Python:* `(`, `)`, `,`, `:`  
  - *Java:* `{`, `}`, `(`, `)`, `[`, `]`, `,`, `;`


## Project Structure

```
lexical_analyzer/
├── CMakeLists.txt                # build instructions
├── README.md
├── .gitignore
├── files/
│   └── test.txt
├── include/
│   ├── main.h                    # entry point, defines keywords, open file, call scanner
│   ├── scanner.h
│   ├── token.h
│   └── utils.h
└── src/
    ├── main.c                    
    ├── scanner.c                 # scans input, assigns tokens
    ├── token.c
    └── utils.c                   # trie implementation for keywords
```


---

## Installation

### Prerequisites

- **C Compiler:** GCC or Clang
- **CMake:** Version 3.10 or higher

### Build Instructions

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd lexical_analyzer
   ```

2. Create a build directory and run CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Run the executable:
    - Default mode uses `files/test.txt` as input:
      ```bash
      ./lexical_analyzer
      ```
    - Or provide a custom input file:
      ```bash
      ./lexical_analyzer your_file.txt
      ```

---

## Features

- **Lexical Analysis:**
    - Reads input from a text file, processes it line by line, and generates tokens based on specific character patterns.
    - TODO: 
      - Create functions for identifying chars instead of large if statements
      - Distinguish between Python and Java, highlight errors inline
 
- **Trie-Based Keyword Lookup:**
    - Implements a trie in `utils.c` for storing keywords, with efficient insertion and recursive deallocation.
  
- **Tokenization:**
    - The scanner in `scanner.c` processes the input to classify tokens, while `token.c` handles token initialization, assignment, and printing.

---