# Kung-Fu Chess

A real-time chess engine built with C++17.

---

## Architecture

The project follows these design principles:

- **Single Responsibility Principle** — each class has one clear responsibility.
- **Separation of Concerns** — rendering, game logic, input, and rules are fully separated.
- **Strategy Pattern** — each piece movement rule is implemented as a separate class inheriting from `MoveRule`.
- **Service Layer** — `GameEngine` orchestrates the application flow.
- **Validation Service** — `RuleEngine` validates all legal moves.
- **Adapter Pattern** — `BoardMapper` converts pixel coordinates into board positions.
- **DTO / Read-only View Model** — `GameSnapshot` and `CellSnapshot` provide immutable data for rendering.
- **Builder Pattern** — `BoardBuilder` constructs a `Board` from a string input.

---

## Project Structure

```text
Chess/
├── src/
│   ├── Constants.hpp               # Global constants
│   │
│   ├── model/
│   │   ├── Piece.hpp / .cpp
│   │   └── Board.hpp / .cpp        # grid: vector<vector<unique_ptr<Piece>>>
│   │
│   ├── movement/
│   │   ├── MoveRule.hpp
│   │   ├── RookRule.hpp / .cpp
│   │   ├── BishopRule.hpp / .cpp
│   │   ├── QueenRule.hpp / .cpp
│   │   ├── KnightRule.hpp / .cpp
│   │   ├── KingRule.hpp / .cpp
│   │   └── PawnRule.hpp / .cpp
│   │
│   ├── rule_engine/
│   │   ├── RuleResult.hpp
│   │   └── RuleEngine.hpp / .cpp
│   │
│   ├── arbiter/
│   │   ├── Motion.hpp
│   │   └── RealTimeArbiter.hpp
│   │
│   ├── controllerClick/
│   │   ├── CellPos.hpp
│   │   ├── ClickResult.hpp
│   │   ├── BoardMapper.hpp / .cpp
│   │   └── controllerClick.hpp / .cpp
│   │
│   ├── game_engine/
│   │   └── GameEngine.hpp / .cpp
│   │
│   ├── renderer/
│   │   ├── GameSnapshot.hpp
│   │   └── Renderer.hpp
│   │
│   └── text_io/
│       ├── PieceFactory.hpp / .cpp
│       ├── BoardBuilder.hpp / .cpp  # builds Board from string
│       ├── BoardParser.hpp / .cpp   # wrapper over BoardBuilder
│       └── BoardPrinter.hpp / .cpp
│
└── tests/
    ├── text_test_runner/
    │   ├── CommandType.hpp
    │   └── TextTestRunner.hpp / .cpp
    ├── test_new.cpp
    └── main.cpp
```

---

## Build & Run

### Compile main

```bash
g++ -std=c++17 -I src \
  main.cpp \
  tests/text_test_runner/TextTestRunner.cpp \
  src/game_engine/GameEngine.cpp \
  src/arbiter/RealTimeArbiter.cpp \
  src/model/Board.cpp \
  src/model/Piece.cpp \
  src/rule_engine/RuleEngine.cpp \
  src/controllerClick/controllerClick.cpp \
  src/controllerClick/BoardMapper.cpp \
  src/text_io/BoardParser.cpp \
  src/text_io/BoardBuilder.cpp \
  src/text_io/BoardPrinter.cpp \
  src/text_io/PieceFactory.cpp \
  src/movement/RookRule.cpp \
  src/movement/BishopRule.cpp \
  src/movement/QueenRule.cpp \
  src/movement/KnightRule.cpp \
  src/movement/KingRule.cpp \
  src/movement/PawnRule.cpp \
  -o chess && ./chess
```

### Run

```bash
./chess_gui.exe board.txt
```

### Run Compile tests
```bash
g++ -std=c++17 -I src \
    tests/test_new.cpp \
    tests/text_test_runner/TextTestRunner.cpp \
    src/game_engine/GameEngine.cpp \
    src/arbiter/RealTimeArbiter.cpp \
    src/model/Board.cpp \
    src/model/Piece.cpp \
    src/rule_engine/RuleEngine.cpp \
    src/controllerClick/controllerClick.cpp \
    src/controllerClick/BoardMapper.cpp \
    src/text_io/BoardParser.cpp \
    src/text_io/BoardBuilder.cpp \
    src/text_io/BoardPrinter.cpp \
    src/text_io/PieceFactory.cpp \
    src/movement/RookRule.cpp \
    src/movement/BishopRule.cpp \
    src/movement/QueenRule.cpp \
    src/movement/KnightRule.cpp \
    src/movement/KingRule.cpp \
    src/movement/PawnRule.cpp \
    -o chess_test && ./chess_test
```

---

## Input Format

```text
Board:
wR wN wB wQ wK wB wN wR
wP wP wP wP wP wP wP wP
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
bP bP bP bP bP bP bP bP
bR bN bB bQ bK bB bN bR

Commands:
click 50 50
click 50 150
wait 1000
print board
```

---

## Commands

| Command | Description |
|----------|-------------|
| `click X Y` | Click at pixel position `(X, Y)` |
| `jump X Y` | Make the selected piece jump for 1000 ms |
| `wait MS` | Advance the game clock by `MS` milliseconds |
| `print board` | Print the current board |

---

## Jump Mechanic

A jump makes a piece **airborne** for **1000 ms** (`JUMP_DURATION`).

While airborne, the piece remains on its square and can capture any opposing piece that reaches that square during the jump interval.

Rules:

- A moving piece cannot jump.
- A piece that is already jumping cannot jump again.
- A moving piece that reaches the square of a jumping enemy is captured.
- Clicking the currently selected square again triggers a jump (if allowed).

---

## Piece Tokens

| Token | Piece |
|--------|-------|
| `wK` / `bK` | White / Black King |
| `wQ` / `bQ` | White / Black Queen |
| `wR` / `bR` | White / Black Rook |
| `wB` / `bB` | White / Black Bishop |
| `wN` / `bN` | White / Black Knight |
| `wP` / `bP` | White / Black Pawn |

---

# עברית

מנוע שחמט בזמן אמת הכתוב ב־C++17.

---

## ארכיטקטורה

הפרויקט מבוסס על העקרונות הבאים:

- **Single Responsibility Principle** – לכל מחלקה אחריות אחת בלבד.
- **Separation of Concerns** – הפרדה מלאה בין לוגיקת המשחק, הקלט, החוקים והרינדור.
- **Strategy Pattern** – חוקי התנועה של כל כלי ממומשים במחלקה נפרדת היורשת מ־`MoveRule`.
- **Service Layer** – המחלקה `GameEngine` מרכזת ומנהלת את זרימת המשחק.
- **Validation Service** – המחלקה `RuleEngine` אחראית על בדיקת חוקיות המהלכים.
- **Adapter Pattern** – המחלקה `BoardMapper` ממירה קואורדינטות פיקסלים למיקומים על הלוח.
- **DTO / Read-only View Model** – המחלקות `GameSnapshot` ו־`CellSnapshot` מספקות נתונים לקריאה בלבד עבור שכבת התצוגה.

---

## מבנה הפרויקט, הידור והרצה

מבנה התיקיות, הידור והרצה מתואר למעלה בגרסה האנגלית.

---

## פורמט הקלט

תחילה מופיע הלוח (8×8), ולאחריו רשימת הפקודות לביצוע.

דוגמה מופיעה בגרסה האנגלית.

---

## הפקודות

| פקודה | הסבר |
|--------|------|
| `click X Y` | לחיצה על מיקום הפיקסלים `(X,Y)` |
| `jump X Y` | ביצוע קפיצה של הכלי הנבחר למשך 1000 אלפיות שנייה |
| `wait MS` | קידום שעון המשחק במספר אלפיות השנייה המבוקש |
| `print board` | הדפסת מצב הלוח הנוכחי |

---

## מנגנון הקפיצה

בעת קפיצה הכלי נמצא במצב **Airborne** למשך **1000ms**.

במהלך זמן זה:

- הכלי נשאר באותו תא.
- ניתן לבצע קפיצה רק אם הכלי אינו בתנועה.
- לא ניתן להתחיל קפיצה נוספת כאשר הכלי כבר קופץ.
- כלי שמגיע לתא של כלי קופץ במהלך חלון הזמן נתפס.
- לחיצה נוספת על אותו תא מפעילה קפיצה כאשר הדבר חוקי.

---

## סימוני הכלים

| סימון | כלי |
|--------|-----|
| `wK` / `bK` | מלך לבן / שחור |
| `wQ` / `bQ` | מלכה לבנה / שחורה |
| `wR` / `bR` | צריח לבן / שחור |
| `wB` / `bB` | רץ לבן / שחור |
| `wN` / `bN` | פרש לבן / שחור |
| `wP` / `bP` | רגלי לבן / שחור |