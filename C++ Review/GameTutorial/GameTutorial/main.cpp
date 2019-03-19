//
//  main.cpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/12/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
using namespace std;

void tutorial1();
void tutorial2();
void tutorial3();
void tutorial4();
void tutorial5();
void tutorial6();
void tutorial7();
void tutorial8();
void tutorial9();
void tutorial10(int);
void tutorial11();
void tutorial12();
void tutorial13();
void tutorial14();
void tutorial15();
void tutorial16();
void tutorial17();
void tutorial18();
void tutorial19();
void tutorial20();
void tutorial21();
void tutorial22();
void tutorial23();
void tutorial24();
void tutorial25();
void tutorial26();
void tutorial27();
void tutorial28();
void tutorial29();
void tutorial30();
void tutorial31();
void tutorial32();
void tutorial33();
void tutorial34();
void tutorial35();
void tutorial36();
void tutorial37();
void tutorial38();
void tutorial39();
void tutorial40();

void gameChallenge1();
void gameChallenge2();
void gameChallenge3();
void gameChallenge4();

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swapRef(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

class Circle {
    
};

class Picture {
public:
    Picture() {
        
    }
    
    Picture(const Picture& other) {
        m_circles[0] = other.m_circles[0];
        std::cout << m_circles[50] << std::endl;
    }
    
private:
    Circle* m_circles[100];
    Circle* c;
};


class Actor {
public:
    Actor(string nm, string r) : m_name(nm), m_role(r) {}
    string name() const {
        return m_name;
    }
    string role() const {
        return m_role;
    }
private:
    string m_name;
    string m_role;
};

class Cast {
public:
    Cast(int lim) : m_size(0), m_maxCastSize(lim) {
        m_cast = new Actor*[lim];
    }
    // copy constructor
    Cast(const Cast& other) {
        m_size = other.m_size;
        m_maxCastSize = other.m_maxCastSize;
        m_cast = new Actor*[m_maxCastSize];
        for (int i = 0; i < m_size; i++) {
            Actor *actor = other.m_cast[i];
            m_cast[i] = new Actor(actor->name(), actor->role());
        }
    }
    
    // assignment operator
    Cast& operator=(const Cast& other) {
        if (this == &other) return *this;
        
        for (int i = 0; i < m_size; i++) {
            delete m_cast[i];
        }
        
        delete[] m_cast;
        
        m_size = other.m_size;
        m_maxCastSize = other.m_maxCastSize;
        m_cast = new Actor*[m_maxCastSize];
        
        for (int i = 0; i < m_size; i++) {
            Actor *actor = other.m_cast[i];
            m_cast[i] = new Actor(actor->name(), actor->role());
        }
        
        
        return *this;
    }
    
    // destructor
    ~Cast() {
        for (int i = 0; i < m_size; i++) {
            delete m_cast[i];
        }
        
        delete[] m_cast;
    }
    
    void hire(string nm, string r) {
        if (m_size < m_maxCastSize) {
            m_cast[m_size++] = new Actor(nm, r);
        }
    }
    
private:
    Actor **m_cast;
    int m_size;
    int m_maxCastSize;
};

class Shape {
public:
    virtual float getArea() = 0;
    virtual float getCircum() = 0;
};

class Rectangle : public Shape {
public:
    virtual float getArea() {
        return 100;
    }
};

int main() {
    
    Shape s;
    Rectangle r;
    
    
    Picture p1;
    Picture *p2 = new Picture(p1);
    
    Cast *cast = new Cast(500);
    cast->hire("fasd", "fa");
    delete cast;
    
    //tutorial1();
    //tutorial2();
    //tutorial3();
    //tutorial4();
    //tutorial5();
    //tutorial6();
    //tutorial7();
    //tutorial8();
    //gameChallenge1();
    //tutorial9();
    //tutorial10(10);
    
    /*
    for (int i = 0; i < 2; i++) {
        tutorial11();
    }
     */
    
    //tutorial12();
    //tutorial13();
    //tutorial14();
    //tutorial15();
    //tutorial16();
    //gameChallenge2();
    //tutorial17();
    //tutorial18();
    //tutorial19();
    //tutorial20();
    //tutorial21();
    //tutorial22();
    //tutorial23();
    //gameChallenge3();
    //tutorial24();
    //tutorial25();
    //tutorial26();
    //tutorial27();
    //tutorial28();
    //tutorial29();
    //tutorial30();
    //tutorial31();
    //tutorial32();
    //tutorial33();
    //tutorial34();
    //tutorial35();
    //tutorial36();
    //tutorial37();
    //tutorial38();
    //tutorial39();
    //tutorial40();
    int a = 3;
    int b = 4;
    
    //swap(&a, &b);
//    swapRef(a, b);
//    cout << a << b << endl;
    
//
//    while (int i < 100) {
//        cout << i << endl;
//    }
    
    return 0;
}



// Tutorial 1: Hello World
void tutorial1() {
    cout << "Hello World!" << endl;
}

// Tutorial 2: Variables
void tutorial2() {
    int kittens = 100;
    float fKittens = 100.8f;
    double dKitttens = 100.8;
    cout << "You have " << kittens << " kittens." << endl;
    cout << "You have " << fKittens << " fKittens." << endl;
    cout << "You have " << dKitttens << " dKitttens." << endl;
    
    float playerDamage = 100.0f;
    float zombieHealth = 200.0f;
    zombieHealth = zombieHealth - playerDamage;
    cout << "Zombine Health: " << zombieHealth << endl;
}

// Tutorial 3: Chars And Strings
void tutorial3() {
    char dog = '$';
    cout << dog << endl;
    
    string playerName = "Ben";
    cout << "Your name is " << playerName << endl;
    cout << "Your name is " << playerName.length() << " letters long\n";
    
    playerName = "Fred";
    cout << "Your name is " << playerName << endl;
}

// Tutorial 4: Standard Input And If Statements
void tutorial4() {
    string playerName;
    int age;
    
    cout << "What is your name sir knight?\n";
    cin >> playerName;
    
    cout << "Hello Sir " << playerName << "\n";
    cout << "How old are you?\n";
    cin >> age;
    
    cout << "you are " << age << " years old.\n";
    
    if (age >= 100) {
        cout << "You are way too old man\n";
    }
}

// Tutorial 5: if/else
void tutorial5() {
    string playerName;
    int age;
    
    cout << "What is your name sir knight?\n";
    cin >> playerName;
    
    cout << "How old are you?\n";
    cin >> age;
    
    if (age <= 3) {
        cout << "You are lying\n";
    } else if (age < 12) {
        cout << "You are too young to play!\n";
    } else if (age > 90) {
        cout << "You are too old to play!\n";
    } else {
        cout << "You are old enough to play\n";
    }
}

// Tutorial 6: Loops
void tutorial6() {
    int counter = 0;
    while (counter < 10) {
        counter++;
        cout << "ha";
    }
    
    for (int counter = 0; counter < 10; counter++) {
        cout << "ha " << counter << endl;
    }
    
    counter = 0;
    do {
        counter++;
        cout << "ha " << counter << endl;
    } while (counter < 10);
}

// Tutorial 7: Comments, Bools And Loop Recap
void tutorial7() {
    /*
     Comments
     */
    
    for (int i = 0; i < 100; i += 2) {
        cout << i << endl;
    }
    
    bool isGameOver = false;
    
    while (!isGameOver) {
        // do stuff
        isGameOver = true;
    }
}

// Tutorial 8: Random Number Generator
void tutorial8() {
    // mt19937 is a type
    mt19937 randomGenerator(time(0));
    uniform_int_distribution<int> diceRoll(1, 6);
    
    cout << "I am rolling a " << diceRoll(randomGenerator) << endl;
    
    uniform_real_distribution<float> attacRoll(0.0f, 1.0f);
    cout << "I am attacking snake!" << endl;
    
    float attack = attacRoll(randomGenerator);
    cout << "attack: " << attack << endl;
    if (attack < 0.3f) {
        cout << "I hit the snake! Yay!\n";
    } else {
        cout << "I missed the snake oh noooo!\n";
    }
    
}

// Game Challenge 1: 1D Combat Simulator
void gameChallenge1() {
    int numHumans;
    int numSkeletons;
    
    int originalNumHumans;
    int originalNumSkeletons;
    
    int humanHealth = 50;
    int skeletonHealth = 10;
    
    int currentHumanHealth;
    int currentSkeletonHealth;
    
    mt19937 randomGenerator(time(0));
    uniform_int_distribution<int> humanAttack(3, 10);
    uniform_int_distribution<int> skeletonAttack(1, 3);
    
    cout << "*** Skeleton vs Humans ***" << endl;
    
    cout << "Input the number of humans: ";
    cin >> originalNumHumans;
    
    cout << "Input the number of skeletons: ";
    cin >> originalNumSkeletons;
    
    cout << "Beginning combat!" << endl;
    
    numHumans = originalNumHumans;
    numSkeletons = originalNumSkeletons;
    
    cout << "<Combat Noises>" << endl;
    
    currentHumanHealth = humanHealth;
    currentSkeletonHealth = skeletonHealth;
    while (numHumans > 0 && numSkeletons > 0) {
        
        currentSkeletonHealth -= humanAttack(randomGenerator);
        currentHumanHealth -= skeletonAttack(randomGenerator);
        
        if (currentHumanHealth <= 0) {
            numHumans--;
            currentHumanHealth = humanHealth;
        }
        
        if (currentSkeletonHealth <= 0) {
            numSkeletons--;
            currentSkeletonHealth = skeletonHealth;
        }
    }
    
    cout << "Combat ended!" << endl;
    
    if (numHumans > 0) {
        cout << "Humans Win!" << endl;
        cout << "There are " << numHumans << " humans left." << endl;
        cout << originalNumHumans - numHumans << " humans and " << originalNumSkeletons << " skeletons lost their lives." << endl;
    } else if (numSkeletons > 0) {
        cout << "Skeletons Win!" << endl;
        cout << "There are " << numSkeletons << " skeletons left." << endl;
        cout << originalNumHumans << " humans and " << originalNumSkeletons - numSkeletons << " skeletons lost their lives." << endl;
    } else {
        cout << "Draw!" << endl;
        cout << "No one is left." << endl;
        cout << originalNumHumans << " humans and " << originalNumSkeletons << " skeletons lost their lives." << endl;
    }
    
}

// Tutorial 9: Functions
int getNumHumans();
int getNumSkeletons();

void tutorial9() {
    int originalNumHumans;
    int originalNumSkeletons;
    
    originalNumHumans = getNumHumans();
    originalNumSkeletons = getNumSkeletons();
}

int getNumHumans() {
    int originalNumHumans;
    cout << "Input the number of humans: ";
    cin >> originalNumHumans;
    return originalNumHumans;
}

int getNumSkeletons() {
    int originalNumSkeletons;
    cout << "Input the number of skeletons: ";
    cin >> originalNumSkeletons;
    return originalNumSkeletons;
}

// Tutorial 10: Parameters and Forward declarations
void tutorial10(int num) {
    cout << "argument: " << num << endl;
}

// Tutorial 11: Static Variables and Pass by Preference
void passByValue(int num);
void passByReference(int& num);

void tutorial11() {
    // this randomGenerator never disappear until the program ends
    static mt19937 randomGenerator(time(0));
    
    static int i = 5;
    i += 1;
    cout << "i: " << i << endl;
    
    int num = 5;
    cout << "num: " << num << endl;
    passByValue(num);
    cout << "num++ (passByValue): " << num << endl;
    passByReference(num);
    cout << "num++ (passByReference): " << num << endl;
}

void passByValue(int num) {
    num++;
}

void passByReference(int &num) {
    num++;
}

// Tutorial 12: Arrays for Item Shop
void tutorial12() {
    const int numItems = 5;
    string shopItemNames[numItems] = {"Boots", "Sword", "Helmet", "Kitten", "Axe"};
    
    cout << "*** Welcome to the item shop! ***\n";
    for (int i = 0; i < numItems; i++) {
        cout << shopItemNames[i] << endl;
    }
    cout << "*************\n\n";
    cout << "What would you like to buy?\n";
    
}

// Tutorial 13: Finished Shop And Global Const
const int numItems = 5;
const string shopItemNames[numItems] = { "Boots", "Sword", "Helmet", "Kitten", "Axe" };
// const makes sure playerInventory doesn't change
void printInventory(const int playerInventory[numItems]);
void printShop();
// array argument is by default pass by reference
bool buyItems(int playerInventory[numItems]);

void tutorial13() {
    
    bool isDone = false;
    int playerInventory[numItems] = { 0, 0, 0, 0, 0 };
    cout << "*** Welcome to the item shop! ***\n";
    
    while (!isDone) {
        printShop();
        printInventory(playerInventory);
        isDone = !buyItems(playerInventory);
        
    }
    
    
}

void printInventory(const int playerInventory[numItems]) {
    cout << "Your inventory is: \n";
    for (int i = 0; i < numItems; i++) {
        if (playerInventory[i] > 0) {
            cout << playerInventory[i] << " x " << shopItemNames[i] << endl;
        }
    }
}

void printShop() {
    cout << "ItemShop: \n";
    for (int i = 0; i < numItems; i++) {
        cout << i + 1 << "." << shopItemNames[i] << endl;
    }
    cout << "*************\n\n";
    cout << "What would you like to buy?\n";
}

bool buyItems(int playerInventory[numItems]) {
    int input;
    cout << "What would you like to buy? Enter -1 to quit. Enter (" << 1 << "-" << numItems << "): ";
    cin >> input;
    
    if (input == -1) {
        return false;
    }
    
    if (input <= 0 || input > numItems) {
        cout << "That was a bad input!\n";
        return true;
    }
    
    playerInventory[input - 1]++;
    return true;
}

// Tutorial 14: Classes, Objects, Access Specifiers
class Monster14 {
public:
    void growl() {
        cout << "Growl!!!\n";
    }
    
    // setter
    void setName(string name) {
        _name = name;
    }
    
    // getter
    string getName() {
        return _name;
    }
    
private:
    string _name;
};

void tutorial14() {
    Monster14 monster1;
    monster1.setName("Geroge");
    
    cout << monster1.getName() << endl;
    monster1.growl();
}

// Tutorial 15: Checkerboard with 2D Array and Modulus
class CheckerBoard {
public:
    void initBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    board[i][j] = '_';
                } else {
                    board[i][j] = '*';
                }
            }
        }
    }
    
    void printBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
private:
    char board[8][8];
};

void tutorial15() {
    CheckerBoard checkBoard;
    checkBoard.initBoard();
    checkBoard.printBoard();
}

// Tutorial 16: Separate Files and Constructors
#include "Monster.hpp"
void tutorial16() {
    Monster monster1("Fred");
    Monster monster2("George");
    
    monster1.printName();
    monster2.printName();
    
    Monster monsters[100];
    monsters[0].printName();
    
}

// Game Challenge 2: Tic Tac Toe
#include "TicTacToe.hpp"

void gameChallenge2() {
    TicTacToe ttt;
    ttt.start();
}

// Tutorial 17: Vectors
void tutorial17() {
    vector<string> itemNames;
    itemNames.push_back("Gloves");
    itemNames.push_back("Hats");
    itemNames.push_back("Axes");
    itemNames.push_back("Rocks");
    
    itemNames[1] = itemNames.back();
    itemNames.pop_back();
    
    for (int i = 0; i < itemNames.size(); i++) {
        cout << itemNames[i] << endl;
    }

}

// Tutorial 18: Lists
void tutorial18() {
    list<string> shopItemNames;
    
    shopItemNames.push_back("Gloves");
    shopItemNames.push_front("Axe");
    shopItemNames.push_back("Kittens");
    shopItemNames.push_back("Swords");
    shopItemNames.push_back("Cars");
    shopItemNames.push_back("Kittens");
    
    list<string>::iterator it;
    for (list<string>::iterator it = shopItemNames.begin(); it != shopItemNames.end(); it++) {
        cout << *it << endl;
    }
    
    cout << "\n";
    shopItemNames.remove("Kittens");
    
    for (list<string>::iterator it = shopItemNames.begin(); it != shopItemNames.end(); it++) {
        cout << *it << endl;
    }
    
    cout << "\n";
    shopItemNames.push_back("Kittens");
    shopItemNames.push_back("Swords");
    shopItemNames.push_back("Cars");
    shopItemNames.push_back("Kittens");
    
    for (list<string>::iterator it = shopItemNames.begin(); it != shopItemNames.end(); it++) {
        if (*it == "Kittens") {
            it = shopItemNames.erase(it);
            break;
        }
    }
    
}

// Tutorial 19: File IO and advanced input
// If you are using xcode, you need to set custom working directory.
// https://stackoverflow.com/questions/16779149/c-program-in-xcode-not-outputting-simple-text-file-using-outfile
void clearInput();

void tutorial19() {
    ofstream outputFile;
    ifstream inputFile;
    
    /*
    outputFile.open("myFile.txt");
    if (outputFile.fail()) {
        perror("myFile.txt");
        return;
    }
    cout << "hello\n";
    outputFile << "Hello World!\n";
    outputFile.close();
     */
    
    string input;
    
    inputFile.open("myFile.txt");
    
    while (getline(inputFile, input)) {
        cout << input << endl;
    }
    
    while (true) {
        int a;
        if (!(cin >> a)) {
            clearInput();
            continue;
        }
        
        cout << a;
    
    }
    
}

void clearInput() {
    cout << "That is bad!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
}

// Tutorial 20: printf, C-Strings, and Documentation
void tutorial20() {
    printf("Hello World\n");
    int a = 5000;
    float c = 0.54574754f;
    printf("Hello: %10d %.2f\n", a, c);
    
    // C++ String
    string myName = "Jun";
    
    // C String
    char myString[] = "Jun";
    char myStr[] = {'J', 'u', 'n', '\0'};
    
    printf("%s\n", myName.c_str());
    printf("%s\n", myString);
    printf("%s\n", myStr);
    //  .
    // ...
    //.....
    char dot = '.';
    char dot3[] = "...";
    char dot5[] = ".....";
    printf("%3c\n", dot);
    printf("%4s\n", dot3);
    printf("%s\n", dot5);
}

// Tutorial 21: Basic Binary
void tutorial21() {
    
}

// Tutorial 22: Type Casting, integer division, variable concepts
void tutorial22() {
    float f;
    double d;
    
    int i;
    char c = 90;
    unsigned int ui;
    
    cout << c << endl;
    cout << (int)c << endl;
    
    int a = 5;
    int b = 6;
    
    cout << (float)a / b << endl;
    
}

// Tutorial 23: Switch Statement
void tutorial23() {
    char moveSpot = 'S';
    
    if (moveSpot == '.') {
        printf("You can move!\n");
    } else if (moveSpot == '#') {
        printf("You can't move there\n");
    } else if (moveSpot == 'S') {
        printf("Battle Time!\n");
    }
    
    switch (moveSpot) {
        case '.':
            printf("You can move!\n");
            break;
        case '#':
            printf("You can't move there\n");
            break;
        case 'S':
            printf("Battle Time!\n");
            break;
        default:
            break;
    }
    
}

// Game Challenge 3: ASCII Roguelike
void gameChallenge3() {
    // skipped
}

// Tutorial 24: sizeof and bufferes
void tutorial24() {
    
    cout << "int: " << sizeof(int) << endl;
    cout << "int: " << sizeof(char) << endl;
    cout << "int: " << sizeof(double) << endl;
    cout << "int: " << sizeof(float) << endl;
    
    int myBuffer[10000];
    cout << "myBuffer: " << sizeof(myBuffer) << endl;
    
    const int BUFFER_SIZE = 100;
    char myB[BUFFER_SIZE];
    
    memset(myB, 'A', sizeof(char) * BUFFER_SIZE);
    
    for (int i = 0; i < BUFFER_SIZE; i++) {
        cout << myB[i] << endl;
    }
}

// Tutorial 25: Pointers basics
void tutorial25() {
    int a = 5;
    
    int *myPointer = nullptr;
    
    myPointer = &a;
    
    cout << *myPointer << endl;
    cout << &a << endl;
}

// Tutorial 26: Stack vs Heap Memory
void tutorial26() {
    // This is going to crash because it exceeds the capacity of the stack.
    // Instead, we should use heap memory with the keyword 'new'.
    int a[100000000000];
}

// Tutorial 27: new, delete, and delete[]
void tutorial27() {
    int *a = new int[100000000000];
    
    delete[] a;
    a = nullptr;
    
    
    int *b = new int;
    delete b;
    b = nullptr;
    
}

// Tutorial 28: Dialogue Tree with pointers
void tutorial28() {
    // skipped
}

// Tutorial 29: smart pointer
void tutorial29() {
    // skipped
}

// Tutorial 30: Dynamic Arrays, destructors
void tutorial30() {
    int input;
    cin >> input;
    
    int *myArray = new int[input];
    
    delete[] myArray;
}

class Zombie {
public:
    Zombie() {
        _items = new int[100];
    }
    ~Zombie() {
        delete[] _items;
    }
    
private:
    int *_items;
};

// Game Challenge 4: 2D Combat Simulator
void gameChallenge4() {
    // skipped
}

// Tutorial 31: Inheritance AND
// Tutorial 32: Polymorphism and the vrtual keyword
class Monster31 {
public:
    Monster31() {
        _name = "NONAME";
    }
    
    Monster31(string name) {
        _name = name;
    }
    
    virtual void update() {
        cout << "empty update\n";
    }
    
    virtual void attack() {
        cout << _name << " is attacking!\n";
    }
    
    void move() {
        cout << _name << " is moving!\n";
    }
    
protected:
    string _name;
private:
    
};

class Spider : public Monster31 {
public:
    Spider(string name) {
        _name = name;
    }
    
    void climb() {
        cout << _name << " is jumping!\n";
    }
    
    void update() {
        move();
        attack();
        climb();
    }
    
    void attack() {
        cout << _name << " is biting with its fangs\n";
    }
    
private:
    
};

class Goblin : public Monster31 {
public:
    Goblin(string name) {
        _name = name;
    }
    
    void update() {
        move();
        attack();
    }
    
private:
    
};

void tutorial31() {
    
    Spider spider("Bob");
    
    spider.attack();
    spider.move();
    spider.climb();
}


void tutorial32() {
    list<Monster31*> monsters;
    
    Spider spider("Bob");
    Goblin goblin("Gob");
    
    monsters.push_back(&spider);
    monsters.push_back(&goblin);
    
    bool isDone = false;
    while (!isDone) {
        for (list<Monster31*>::iterator mit = monsters.begin(); mit != monsters.end(); mit++) {
            (*mit)->update();
        }
        
        int a;
        cin >> a;
        
    }
}

// Tutorial 33: Pointer pitfalls and coding style
void tutorial33() {
}

// Tutorial 34: Pure virtual functions and abstract classes
class Enemy34 {
public:
    virtual void attack() = 0;
};

class Scorpion : public Enemy34 {
public:
    Scorpion() {
        
    }
};

void tutorial34() {
    
}

// Tutorial 35: Default Parameters and structs
void printError(string s, bool printToFile = true) {
    cout << printToFile << endl;
}

struct Block {
    int blockID;
    int textureID;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void tutorial35() {
    printError("");
    printError("", false);
    
    Block block1; // struct variables are all public by default
    Block block2 = {}; // set all zeros
    
    cout << block1.blockID << endl;
    
}

// Tutorial 36: Scope
void tutorial36() {
    
}

// Tutorial 37: Static member functions and variables
class IOManager {
public:
    static int appendToFile(string filename) {
        ofstream file(filename, ios_base::app);
        if (file.fail()) {
            return 1;
        }
        
        return 0;
    }
private:
    
};

void tutorial37() {
    IOManager::appendToFile("myFile.txt");
}

// Tutorial 38: Game States, enums, enum classes
enum class GameState { MAIN_MENU, EXIT, PLAYING, OPTIONS };
//enum GameStates { MAIN_MENU, EXIT, PLAYING, OPTIONS };
//const int MAIN_MENU = 0;
//const int EXIT = 1;
//const int PLAYING = 2;
//const int OPTIONS = 3;

void tutorial38() {
    GameState gameState = GameState::OPTIONS;
}

// Tutorial 39: Recursion
int factorial(int n) {
    if (n < 0) return 0;
    
    if (n == 0) return 1;
    
    return n * factorial(n - 1);
}

void tutorial39() {
    cout << factorial(3) << endl;
}

// Tutorial 40: AI for Tic Tac Toe
void tutorial40() {
    // skipped
}
