# DSA  Assignment 1 

Name:Sara Fawad  
CMS ID:509615 

##  Deliverables
The following `.cpp` files are included in this submission:
- `Polynomial.cpp` (Implementation of abstract Polynomial ADT)
- `TextEditor.cpp` (Cursor-based Text Editor Simulation)
- `UNO.cpp` (Simplified UNO Card Game Simulation)

## Approach

### Task 1 — Polynomial ADT  
Implemented using a **linked list** to represent polynomial terms in descending order of exponent.  
- Converted the provided header file into an **abstract class** with pure virtual functions.  
- Created a derived class (`LinkedListPolynomial`) to implement insertion, addition, multiplication, and differentiation.  
- Used dynamic memory allocation and cleanup to manage nodes properly.

### Task 2 — Text Editor Simulation  
Simulated a text editor with a **movable cursor** using a linked list.  
- Implemented `insertChar()`, `deleteChar()`, `moveLeft()`, and `moveRight()` to mimic Notepad-like behavior.  
- `getTextWithCursor()` returns the full text with `|` showing the cursor position.  
- Focused on efficient cursor movement and edge case handling (cursor at start/end).

### Task 3 — UNO Game Simulation  
Designed a simplified 2–4 player **UNO** simulation using OOP and vectors.  
- Implemented color/value matching, direction handling, and action cards (Skip, Reverse, Draw Two).  
- Used `<random>` with a fixed seed (1234) for reproducible shuffling.  
- Each turn updates the state string showing direction, top card, and player hand counts.

## Github link : https://github.com/sarafaw/Dsa__assignment1

## Challenges Faced:

-Initially, the code wasn’t compiling because the .h and .cpp files were not in the same folder,
 so Visual Studio couldn’t link them correctly.
-I also faced errors like “Cannot open include file: No such file or directory”, which I resolved by 
 correctly adding all source files to the project.
-Another common issue was “Unable to start program”, which happened because the executable hadn’t been built yet.
 I fixed it by rebuilding the solution.

**Task 1 — Polynomial ADT**

-The provided header file didn’t work directly with implementation, so I converted it into an
 abstract class and used inheritance to implement functionality.
-Faced logic issues while inserting terms in descending order and combining like terms.
-Debugging the linked list memory management was tricky 
— I had to carefully delete nodes to prevent memory leaks.

**Task 2 — Text Editor**

-The biggest challenge was correctly tracking the cursor position after insertions and deletions.
-Managing edge cases like deleting at position 0 or moving the cursor beyond text boundaries required careful logic.
-Also ensuring the display showed the cursor (|) at the right spot after every operation was initially confusing.

**Task 3 — UNO Simulation**

-Designing the game logic to handle Skip, Reverse, and Draw Two cards properly was challenging.
-Implementing turn direction (Clockwise vs Counter-clockwise) and player skipping logic took time to get right.
-Ensuring deterministic output using a fixed random seed (1234) for shuffling helped in debugging and matching the expected output.

