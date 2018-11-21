# VE280

<img src="https://ws1.sinaimg.cn/large/006tNbRwly1fwg7hovo4gj30ky0ektck.jpg" width="200" align=left />

## About Honor Code

If there is same questions or labs in the future, it is the responsibility of JI students not to copy or modify these codes, or TeX files because it is against the Honor Code. The owner of this repository dosen't take any commitment for other's faults.

According to the student handbook (2015 version),

> It is a violation of the Honor Code for students to submit, as their own, work that is not the result of their own labor and thoughts. This applies, in particular, to ideas, expressions or work obtained from other students as well as from books, the internet, and other sources. The failure to properly credit ideas, expressions or work from others is considered plagiarism.

---

## Mid 1 Review

# 03

* Header guard to prevent multiple definitions! 

To compile multiple source files, use command 

* g++ -Wall -o program src1.cpp src2.cpp src3.cpp 

# 04

lvalue and rvalue 

* lvalue: An expression which may appear as either the left-hand 

or right-hand side of an assignment 

* rvalue: An expression which may appear on the right- but not left-hand side of an assignment 

Array is passed by reference. 

* int sum(int a[], unsigned int size) ;

Function Call Mechanisms 

* Two mechanisms: 
* Call-by- Value
* Call-by-Reference 

# 08

Enum

-   You can define an enumeration type as follows: `enum Suit_t {CLUBS, DIAMONDS, HEARTS, SPADES};`
-   To define variables of this type you say: `enum Suit_t suit`; 
-   You can initialize them as:
   `enum Suit_t suit = DIAMONDS`; 
-  Once you have such an enum type defined, you can *use it as an argument*, just like anything else. 
-  Enums are passed by-value, and can be assigned. 

```c++
bool isRed(enum Suit_t s) { 
    switch (s) {
        case DIAMONDS:
        case HEARTS:
        return true;
             break;
        case CLUBS:
        case SPADES: return false;
             break;
        default:
             assert(0);
             break;
     }
}
```

f you write

 ```C++
enum Suit_t {CLUBS, DIAMONDS, HEARTS, SPADES};
 ```

then numerically 

```
     CLUBS = 0, DIAMONDS = 1,
     HEARTS = 2, SPADES = 3
```

Using this fact, it will sometimes make life easier 

```c++
enum Suit_t s = CLUBS;
const string suitname[] = {“clubs”, 
“diamonds”, “hearts”, “spades”};
cout << “suit s is ” << suitname[s];
```

# 11

###Five Steps in Testing 

* To test some piece of code (either a component or a whole piece): 

1. Understand the specification 

2. Identify the required behaviors 

3. Write specific tests 

4. Know the answers in advance 

5. Include stress tests 

   UIWKI

> Write specific tests 
>
> * There are three classes of test cases that make sense: 
>   * **Simple inputs**
>   * **Boundary conditions**
>   * **Nonsense** 
> * Simple cases are those that are “normal” for the problem at hand. 
> * “Boundary” cases are at the edges of what is expected, or formed to exploit some detail of implementation. 
> * “Nonsense” cases are those that are clearly unexpected. 

### Using Assert Function 

`include <cassert>`

```c++
int smaller = min(a, b); assert(smaller <= a && smaller <= b);
```

*Note that things to be asserted might be expensive！*

If it is, you can disable it, by compiling with the **NDEBUG** preprocessor variable. 

####There are two ways to do this:

1. Define it before` including <cassert>`: 

```c++
#define NDEBUG // disable assert() 
#include <cassert> 
assert(very_expensive_func());
```

2. Specify it on the command line of the compiler: g++ -DNDEBUG ... 

# 12 Exception 

We want a means of recognizing and handling unusual conditions in the program at runtime 

## three general strategies for determining legitimate output for illegitimate input: 

1. “It’s my problem!” 

   * Try to “fix” things and continue execution by “enforcing” legitimate inputs from illegitimate ones by 
   * either *<u>modifying the inputs</u>* 
   * or *<u>returning default outputs</u>* that make sense in the context 

2. “I Give up!”

   *  Use something like assert(). 

   *  assert(condition) terminates the program if condition is not true. 

3. “It’s your problem!” 

   ​	    ^ The caller of the function 

## Exception Handling 

```c++
void foo() {
	try { Block [if(n < 0) throw n;] }
	catch (Type var) { Handler } 
}
```

![image-20180627153506249](/var/folders/34/b48wfdt532q05zmvgtwd86kh0000gn/T/abnerworks.Typora/image-20180627153506249.png)

# 13 Abstract Data Types 

##Struct Types 

```c++
struct Grades { 
    char name[9]; 
    int midterm; 
    int final;
};
```

##结构体的初始化

将各成员的初值，按顺序地放在一对大括号{}中，并用逗号分隔，一一对应赋值。比如初始化Student结构体变量stu

```c++
 struct Student {
     char *name;
     int age;
 };
 struct Student stu = {"MJ", 27}
```

只能在定义变量的同时进行初始化赋值，初始化赋值和变量的定义不能分开，下面的做法是错误的：

```c++
struct Student stu;
stu = {"MJ", 27};
```







## Abstract Data Types 

###Abstract data types provide the following two advantages: 

1. **<u>*Information hiding*</u>**: we don't need to know the details of how the object is represented, nor do we need to know how the operations on those objects are implemented. 
2. **<u>*Encapsulation 封装*</u>**: the objects and their operations are defined in the same place; the ADT combines both data and operation in one entity. 

* ADTs are local 
* ADTs are substitutable: 

```c++
class anInt {
// OVERVIEW: Omitted for space int v;
public:
int get_value();
void
// EFFECTS: returns the current value set_value(int newValue);
// MODIFIES: this
// EFFECTS: sets the current value // equal to arg
};
```

###The definitions of member functions are usually put in the .cpp file;  You should include .h in the .cpp now! 

```c++
int anInt::get_value() { 
    return v;
}
void anInt::set_value(int newValue) {
	v = newValue;
}
```

### Usage in main()

```c++
void add_one(anInt i) {
    i.set_value(i.get_value()+1);
}
int main() {
    anInt foo;
    foo.set_value(0);
    add_one(foo);
    cout << foo.get_value() << endl; return 0;
}
```

初始化句式：

```c++
Class_T::Class_T(): anInt(0), aDouble(1.2),aString(“Yes”)
{
}
```

### Const Member Functions 

####Const Member Functions 只能被const使用

```c++
Implement: size()
    
int IntSet::size() const {
return numElts; 
}

A const object can only call its const member functions!
    
const IntSet is; 
cout << is.size(); ✅
is.insert(2);❎
```

####Const Member Functions 中的函数只能是 const

```c++
对于：void A::g() const { f(); }
void A::f() {...} ✅
void A::f() const {...} ❎
```

![image-20180627161528904](/var/folders/34/b48wfdt532q05zmvgtwd86kh0000gn/T/abnerworks.Typora/image-20180627161528904.png)

