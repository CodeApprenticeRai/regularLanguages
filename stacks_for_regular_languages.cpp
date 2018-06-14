//
// Created by tareg on 5/30/2018.
//

#include <cstring>

#include <vector>
#include <iostream>

#include "stacks_for_regular_languages.h"
#include <stdexcept>


// As per the last section in the c++ documentation on templates http://www.cplusplus.com/doc/oldtutorial/templates/
// template specification and implementation must be found in the file that it is being instantiated from.

// I would've rathered to be more organized but the above constraint kinda requires me to keep everything in the same file.

// Template specification
template <typename T>
class stack_p1 {

    // I was going to use a linked list implementation,
    // but that seemed like more work so I'm doing a vector
    // based one first.
    // Maybe I'll do it later.

private:

    // For vector implementation
    std::vector<T> nodes;

    // For Linked Lists Implementation
    struct StackNode{
        T data;
        StackNode *prev;
    };

    StackNode stackBase = {.data = NULL, .prev=NULL};
    StackNode* top = &stackBase;

public:
//    stack_p1( const stack_p1 &obj);

    bool isEmpty();

    T pop();

    void push(T item);

    T peek();
};

// Template Implementation

// Linked List Based Stack Implementation
//    template <class T>  stack_p1<T>::stack_p1(){
//        top = { .data = NULL, .prev = NULL };
//    }
//
//template <class T> bool stack_p1<T>::isEmpty(){
//        return top->data == stackBase.data;
//    }
//
//template <class T> T stack_p1<T>::pop(){
//        StackNode* being_popped = this->top;
//        this->top = being_popped->prev;
//        return being_popped->data;
//    };
//
//template <class T> void stack_p1<T>::push(T item){
//        if (this->isEmpty()){
//            StackNode *new_node;
//            new_node->data = item;
//            new_node->prev = this->top;
//            this->top = new_node;
//            return;
//        }
//    }
//
//template <class T> T stack_p1<T>::peek(){
//       return this->top->data;
//    }

// Linked List Tests
//StackNode2<char*> stackBase = {.data = NULL, .prev=NULL};
//StackNode2<char*>* top = &stackBase;
//
//
//std::cout << (stackBase.data == NULL) << " " << (top->data == stackBase.data);
//
//StackNode2<char*>* newNode;
//std::cout << "here \n";
//
//newNode->data = "hello";
//std::cout << "here \n";
//
//newNode->prev = top;
//std::cout << "here \n";
//
//top = newNode;
//std::cout << "here \n";
//
//
//std::cout << (stackBase.data == NULL);
//std::cout << " " << (top->data == stackBase.data);




// Vector-based Stack Implementation
//
//  If I have to choose which one to be graded on I choose this one.


template <class T> bool stack_p1<T>::isEmpty(){
    return nodes.empty();
};

template <class T> T stack_p1<T>::pop(){
    if (!nodes.empty()){
        T returnValue = nodes.back();
        nodes.pop_back();
        return returnValue;
    }
    else {
        throw std::out_of_range("The stack is empty.\nThere is nothing to return");
    }
}

template <class T> void stack_p1<T>::push(T item){
    nodes.push_back(item);
    return;
}

template <class T> T stack_p1<T>::peek(){
    if (!nodes.empty()){
        return nodes.back();
    }
    else {
        throw std::out_of_range("The stack is empty.\nThere is nothing to return");
    }
}




// Regular Language Checkers


bool stacks_for_regular_languages::L1(char* inputString){
    stack_p1<char> stack;
    int n = std::strlen(inputString);

    for ( int i = 0; i < n; i++){
        char c = inputString[i];

        if ( stack.isEmpty() ){
            stack.push( c );
            continue;
        }
        if (  stack.peek() == c ){
            stack.push( c );
        }
        else {
            stack.pop();
        }
    }

    return stack.isEmpty();
}

bool stacks_for_regular_languages::L2(char* inputString) {
    if (inputString == ""){
        return false;
    }

    stack_p1<char> stack;
    int i = 0;
    int n = std::strlen(inputString);

    bool b_flag = false;

    while (i < n) {
//        char c = *(inputString+i);
        char c = inputString[i];
//        std::cout << "i:" << i << "\n";

        if (b_flag){

            if ( (c != 'B') or (stack.isEmpty()) ) {
                return false;
            }
            stack.pop();
        }
        else if (c == 'A') {
            stack.push(c);
        }
        else if (c == 'B') {
            b_flag = true;
            // if B is the first character, return false i.e. if the stack i empty here return false
            if (stack.isEmpty()){
                return false;
            }
            else{
                stack.pop();
            }
        }
        else {
            // if an invalid character is passed, return false
            return false;
        }
        i++;
    }
    return stack.isEmpty();
}



/*
L3 Alg:
 Do L2 but at every step push to a copy stack
    if 'A' reached stop pushing to copy stack

    for remainder of method inverse compare chars popped from ocpy stack and string.
    if popped_char != inputString[i]: return false;
    else:
    return true

*/


// helper function
stack_p1<char> *stackFromString(const char* checkString){
    stack_p1<char> *stack = new stack_p1<char>;
    int n = strlen(checkString);
    for (int i = 0; i < n; i++){
        stack->push(checkString[i]);
    }
    return stack;
}

std::string* stringFromStack(stack_p1<char>* stack, bool reversed){
    std::string *returnString = new std::string();

    while(!stack->isEmpty()){
        returnString->push_back( stack->peek() ) ;
        stack->pop();
    }

//    std::string *returnStringReversed = new std::string();
//    if (reversed){
//        for (int i = strlen(returnString->c_str())-1; i > -1;i-- ){
//            returnStringReversed->push_back(returnString[i]);
//        }
//        return returnStringReversed;
//    }

    return returnString;
}

char flip(char c){
    if (c == 'A'){
        return 'B';
    }
    if (c == 'B'){
        return 'A';
    }
}

bool stacks_for_regular_languages::L3(char * inputString) {
    if (inputString == "") {
        return false;
    }

    // Since using a stack is actually the more expensive option, I'm assuming we don't really care about complexity
    stack_p1<char> stack;
    stack_p1<char> copyStack;

    int i = 0;
    int n = std::strlen(inputString);

    std::cout << n << " " << inputString << ": "; // test code

    bool b_flag = false;
    bool ab_flag = false;

    while ((!ab_flag) and (i < n)) {
        char c = inputString[i];
        std::cout << c << i; // test code
        if (b_flag) {
            if (c == 'A') {
                ab_flag = true;
                continue;
            }
            else if ((c != 'B') or ( stack.isEmpty() ) ) {
                return false;
            }
            else if (c == 'B'){
                stack.pop();
                copyStack.push(c);
            }

        } else if (c == 'A') {
            stack.push(c);
            copyStack.push(c);
        } else if (c == 'B') {
            b_flag = true;
            // if B is the first character, return false i.e. if the stack i empty here return false
            if (stack.isEmpty()) {
                return false;
            } else {
                stack.pop();
                copyStack.push(c);
            }
        } else {
            // if an invalid character is passed, return false
            return false;
        }
        if (!ab_flag){
            i++;
        }
    }
    if ( (!stack.isEmpty()) and (!(i < n)) ) {
        return false;
    }

    std::cout << " ";
//    std::cout << "vv " << i << " vv";
    std::string* checkString = new std::string(); // stringFromStack(copyStack, false)

    while(!copyStack.isEmpty()){
        checkString->push_back( copyStack.peek() );
        copyStack.pop();
    }

//    std::cout << "\n" << "*" <<checkString << "*";
    // eat some more memory


    while (i < n){
        stack_p1<char> *copyStack2 = stackFromString(checkString->c_str());
        while(!copyStack2->isEmpty()){
            char c = inputString[i];
            std::cout << " *" << c << copyStack2->peek() << i ;
            if (copyStack2->peek() != c){
                return false;
            }
            else if (copyStack2->peek() == c){
                copyStack2->pop();
                i++;
            }
        }
    }
    return true;
}


bool stacks_for_regular_languages::L4(char * inputString){
    if (inputString == "") {
        return false;
    }

    // Since using a stack is actually the more expensive option, I'm assuming we don't really care about complexity
    stack_p1<char> stack;
    stack_p1<char> copyStack;

    int i = 0;
    int n = std::strlen(inputString);

    std::cout << n << " " << inputString << ": "; // test code

    bool b_flag = false;
    bool ab_flag = false;

    while ((!ab_flag) and (i < n)) {
        char c = inputString[i];
        std::cout << c << i; // test code
        if (b_flag) {
            if (c == 'A') {
                ab_flag = true;
                continue;
            }
            else if ((c != 'B')){
                return false;
            }
            else if (c == 'B'){
                // if 'B' is the first character the evaluation will perhaps be incorrect
                stack.push(c);
                copyStack.push(c);
            }
        } else if (c == 'A') {
            stack.push(c);
            copyStack.push(c);
        } else if (c == 'B') {
            b_flag = true;
            // if B is the first character, return false i.e. if the stack i empty here return false
            stack.push(c);
            copyStack.push(c);
        }
        else {
            // if an invalid character is passed, return false
            return false;
        }
        if (!ab_flag){
            i++;
        }
    }
//    if ( (!stack.isEmpty()) and (!(i < n)) ) {
//        return false;
//    }

    std::cout << " ";
//    std::cout << "vv " << i << " vv";
    std::string* checkString = new std::string(); // stringFromStack(copyStack, false)

    while(!copyStack.isEmpty()){
        checkString->push_back( copyStack.peek() );
        copyStack.pop();
    }

//    std::cout << "\n" << "*" <<checkString << "*";
    // eat some more memory


    while (i < n){
        stack_p1<char> *copyStack2 = stackFromString(checkString->c_str());
        while(!copyStack2->isEmpty()){
            char c = inputString[i];
            std::cout << " *" << c << copyStack2->peek() << i ;
            if (copyStack2->peek() != c){
                return false;
            }
            else if (copyStack2->peek() == c){
                copyStack2->pop();
                i++;
            }
        }
    }
    return true;
}


// Test Functions


struct testObj {
    char* testString;
    bool L1_output;
    bool L2_output;
    bool L3_output;
    bool L4_output;
};

// push a string to the stack pop it until stack is empty.
void test_stack( char* string){
//    stack_p1<int> ints;
    stack_p1<char> chars;
//    std::vector<char*> in_chars;

//    char *a  = "juicy";


//    in_chars.push_back();
//    in_chars.push_back(b);

    for (int i = 0; i < strlen(string); i++){
//        std::cout << in_chars.at(i % 2) << "\n";
//        chars.push( in_chars.at(i % 2)  );

        std::cout << string[i];
        chars.push(string[i]);

    }

    while (!chars.isEmpty()){
        std::cout << chars.peek();
        chars.pop();
    }
}

void test_L1 ( std::vector<char*> testStrings ){

    for (int i = 0; i < testStrings.size(); i++){
        std::cout << stacks_for_regular_languages::L1(testStrings.at(i)) << "\n";
    }
    return;
}

void test_L2 ( std::vector<char*> testStrings  ){


    for (int i = 0; i < testStrings.size(); i++){
        std::cout << stacks_for_regular_languages::L2(testStrings.at(i)) << " \n";
    }
    return;
}

void test_L3 ( std::vector<char*> testStrings  ){


    for (int i = 0; i < testStrings.size(); i++){
        std::cout << " " << stacks_for_regular_languages::L3(testStrings.at(i)) << "\n";
    }
    return;
}

void test_L4 ( std::vector<char*> testStrings  ){


    for (int i = 0; i < testStrings.size(); i++){
        std::cout << " " << stacks_for_regular_languages::L4(testStrings.at(i)) << "\n";
    }
    return;
}


template <class T>
struct StackNode2{
    T data;
    StackNode2 *prev;
};



int main() {
    std::vector<char*> testStrings1 =  { "ABBA", "ABABB", "BABAAB", "ABC", "BBAAA", "BBBAAA", "AAABABBB" };
    std::vector<char*> testStrings0 = { "AAABBB", "AB", "", "AABBB", "AAABB", "ABAB", "BBAA", "BBBAA", "AAB", "ABCBA", "ABBBA", "ABBA", "ABAABBAAABBB", "AA", "AABBBAABBB", "AABB" };
    std::vector<char*> testStrings2 = { "AAABBBAAABBBAAABBB", "AB","ABABAB", "ABABBAB", "AABBBAABBB"};
    std::vector<char*> testStringsL4 = { "AAABBBAAABBBAAABBB", "AAABAAAB","ABBABBABB", "ABABBAB", "AABBBAABBB"};
//  test_L1( testStrings1 );
//    test_L2( testStrings0 );
//    test_L3( testStrings2 );
    test_L4( testStringsL4 );


    return 0;
}


// TODO:

//      L
//    - The L1 algorithm works well and my vector stack implementation
//        also works.
//        - Confirm that I can use this implementation with professor.
//    - Linked List Implementation doesn't work, and I don't much to make it work . If I have time I'll play around with it.
//
//    - Write L2, L3, L4
//      - L2: seems to work well. Only thing left to do is to test on professor's test cases.
//      - L3:  I have the algorithm for it, but it kinda counts??  I'll have to double check this one with the profs L2_with_for_loop and copy_sequence, if first_sequence_over check for i=prev_i; i < strlen(); i+= sequence_length+1]
//      - L4: a mixture of l2 and L3. while A, copy, if B flag, if flag and "A" break, compare sequence through remainder of string

//     Shouldn't be  more than two more blocks away from completion.




// OTHER TESTS

// TESTS for String-Stack Stack-String Converters
//char* checkString = "helloWorld";
//
//for (int i = 0; i < strlen(checkString); i++){
//std::cout << checkString[i];
//}
//std::cout << "\n";
//
//stack_p1<char>* s1 = stackFromString(checkString);
////    while ( !(s1->isEmpty()) ) {
////        std::cout << s1->peek();
////        s1->pop();
////    }
////    std::cout << "\n";
//
//const char* str2 = stringFromStack(s1, false)->c_str();
//
//for (int i = 0; i < strlen(str2); i++){
//std::cout << str2[i];
//}
//    std::cout << str2;
