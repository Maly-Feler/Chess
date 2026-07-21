# Kung-Fu Chess

מנוע שחמט בזמן אמת ב־C++17.

הפרויקט מחולק ל־Client ו־Server:

* Client אחראי על תקשורת, קלט משתמש ותצוגה.
* Server אחראי על ניהול מצב המשחק, חוקי המשחק ועדכון תנועות.

---

# מבנה הפרויקט

```
Chess/
│
├── client/
│   ├── main.cpp
│   ├── NetworkClient.cpp
│   └── NetworkClient.hpp
│
├── server/
│   ├── main.cpp
│   ├── GameLoop.cpp
│   ├── GameLoop.hpp
│   ├── PlayerSession.hpp
│   ├── WebSocketServer.cpp
│   └── WebSocketServer.hpp
│
├── src/
│   ├── model/
│   ├── movement/
│   ├── rule_engine/
│   ├── arbiter/
│   ├── game_engine/
│   ├── network/
│   ├── commands/
│   ├── text_io/
│   ├── config/
│   ├── renderer/
│   ├── controllerClick/
│   ├── audio/
│   └── vision/
│
└── CMakeLists.txt
```

---

# ארכיטקטורה

```
Client
 |
 | WebSocket
 |
Server
 |
GameLoop
 |
GameEngine
 |
+----------------+
| RuleEngine     |
| RealTimeArbiter|
+----------------+
 |
Board
 |
Piece
```

---

# שכבות

## Model

מכיל את מודל המשחק:

* Board
* Piece
* PieceFactory

אינו תלוי בממשק משתמש.

---

## Movement

מכיל חוקי תנועה:

* PawnRule
* RookRule
* BishopRule
* KnightRule
* QueenRule
* KingRule

מבוסס על Strategy Pattern.

---

## Rule Engine

אחראי על בדיקות חוקיות:

* בדיקת תנועה
* בדיקת גבולות
* בדיקת מסלולים
* בדיקת כלי מקור ויעד

---

## Arbiter

ניהול תנועות בזמן אמת:

* Motion
* MotionUpdater
* MotionAdvancer
* CollisionResolver
* RealTimeArbiter

---

## Game Engine

שכבת תיאום:

* ניהול מצב משחק
* יצירת Snapshot
* חיבור בין מנגנוני המשחק

---

## Network

תקשורת:

* Protocol
* Message
* Serializer
* WebSocketServer
* NetworkClient

---

## Renderer

אחראי להצגת המשחק:

* ImgRenderer
* SpriteAnimator
* AnimatorPool

---

# Design Patterns

## Strategy Pattern

```
MoveRule
 |
 +-- PawnRule
 +-- RookRule
 +-- BishopRule
 +-- KnightRule
 +-- QueenRule
 +-- KingRule
```

---

## Factory Pattern

```
PieceFactory
 |
 +-- Piece objects
```

---

## Builder Pattern

```
BoardBuilder
      |
      v
    Board
```

---

## DTO Pattern

העברת מידע לתצוגה:

```
Game State
    |
    v
GameSnapshot
    |
    v
Renderer
```

---

# הידור

דרישות:

* C++17
* CMake 3.16+
* OpenCV 4.5.1
* WebSocket++

---

# Build

```bash
cmake -S . -B build
cmake --build build --config Release
```

---

# הרצה

Client:

Windows:

```bash
build/Release/KungFuChessClient.exe
```

Server:

Windows:

```bash
build/Release/KungFuChessServer.exe
```

---

# אחריות מחלקות מרכזיות

| מחלקה           | אחריות            |
| --------------- | ----------------- |
| Board           | ניהול מצב הלוח    |
| Piece           | מודל כלי          |
| PieceFactory    | יצירת כלים        |
| RuleEngine      | בדיקת חוקיות      |
| RealTimeArbiter | ניהול תנועות      |
| GameEngine      | תיאום מערכת המשחק |
| Serializer      | המרת הודעות       |
| NetworkClient   | תקשורת Client     |
| WebSocketServer | תקשורת Server     |
| Renderer        | הצגת מצב המשחק    |

---

# פורמט לוח

דוגמה:

```
wR wN wB wQ wK wB wN wR
wP wP wP wP wP wP wP wP
. . . . . . . .
```

סימונים:

| סימון | כלי    |
| ----- | ------ |
| K     | King   |
| Q     | Queen  |
| R     | Rook   |
| B     | Bishop |
| N     | Knight |
| P     | Pawn   |

---

# מגבלות ידועות

| רכיב          | הערה                           |
| ------------- | ------------------------------ |
| GameEngine    | קיימות עדיין תלויות בין רכיבים |
| SpriteLoader  | חלק מהנתיבים מוגדרים בקוד      |
| Renderer      | קיימים קבועים כפולים           |
| MotionUpdater | קיימים חלקים שאינם בשימוש      |
