//-----------------------------------------------------------------------------
// List.cpp
// ishaplan
// pa6
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    prev = nullptr;
    next = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
List::List(){
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos = 0;
    len = 0;
}

// Copy Constructor.
List::List(const List& L) {
    // Initialize member variables
    frontDummy = new Node(-1);  
    backDummy = new Node(-1);  
    beforeCursor = frontDummy; 
    afterCursor = backDummy;     
    pos = 0;
    len = 0;
    if(L.length() > 0){
        Node* N = L.frontDummy->next;
        while (N != L.backDummy) {
            insertBefore(N->data);
            N = N->next;
        }
    }
}



// Destructor
List::~List(){
    this->clear();
    delete frontDummy;
    delete backDummy;

}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return (len);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(this->len > 0){
        return this->frontDummy->next->data;
    }
    else{
        throw std::length_error("List: front(): empty list");
        return -1;
    }
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(this->len > 0){
        return this->backDummy->prev->data;
    }
    else{
        throw std::length_error("List: back(): empty list");
        return -1;
    }
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    if( 0 <= this->pos && this->pos <= this->len){
        return this->pos;
    }
    else{
        throw std::range_error("List: position(): off list");
        return -1;
    }
    
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(this->pos < this->len){
        return this->afterCursor->data;
    }
    else{
        throw std::range_error("List: peekNext(): cursor at back");
        return -1;
    }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(this->pos > 0){
        return this->beforeCursor->data;
    }
    else{
        throw std::range_error("List: peekPrev(): cursor at front"); 
        return -1;
    }
}


// Manipulation procedures ----------------------------------------------------
// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){ //idk
    if(this->len > 0){
        this->moveBack();
        while(this->len > 0){
            this->eraseBefore();
        }
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    this->pos = 0;
    this->afterCursor = this->frontDummy->next;
    this->beforeCursor = this->frontDummy;

    //make sure that, at some point, you initialize beforecursor next to be after cursor and vice versa with prev1
    this->beforeCursor->next = this->afterCursor;
    this->afterCursor->prev = this->beforeCursor;
}

// moveBack()
// Moves cursor to position length() in this List.
//some notes:
//make sure that, at some point, you initialize beforecursor next to be after cursor and vice versa with prev1
void List::moveBack() {
    this->pos = this->len;
    this->beforeCursor = this->backDummy->prev;
    this->afterCursor = this->backDummy;

    //make sure that, at some point, you initialize beforecursor next to be after cursor and vice versa with prev1  
    this->beforeCursor->next = this->afterCursor;
    this->afterCursor->prev = this->beforeCursor;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(this->pos < this->len){
        this->pos++;
        //Node *temp = this->beforeCursor;
        this->beforeCursor = this->beforeCursor->next;
        this->afterCursor = this->afterCursor->next;
        return beforeCursor->data;
    }
    else{
        throw std::range_error("List: moveNext(): cursor at back");    
        return -1;
    }
}
// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(this->pos > 0){
        this->pos--;
        this->beforeCursor = this->beforeCursor->prev;
        //Node* temp = this->afterCursor;
        this->afterCursor = this->afterCursor->prev;
        return afterCursor->data;
    }
    else{
      throw std::range_error("List: movePrev(): cursor at front");  
      return -1;
    }
}

void List::insertAfter(ListElement x) {
    Node *newN = new Node(x);  
    //std::cout << "position:" << position() << std::endl;
    if(len == 0){
        afterCursor = newN;
        afterCursor->next = backDummy;
        backDummy->prev = afterCursor;
        beforeCursor = frontDummy;
        afterCursor->prev = frontDummy;
        beforeCursor->next = afterCursor;
        len++;
    }
    else{
        newN->next = this->afterCursor;     
        this->afterCursor->prev = newN;      
        newN->prev = this->beforeCursor;     
        this->beforeCursor->next = newN;     
        afterCursor = newN;
        this->len++;
    }
    
}


void List::insertBefore(ListElement x) {
    Node *newN = new Node(x);  
    //std::cout << "position:" << position() << std::endl;
    beforeCursor->next = newN;  
    newN->prev = beforeCursor;  
    //newN->next = beforeCursor;
    afterCursor->prev = newN;
    newN->next = afterCursor;
    beforeCursor = newN;
    

    this->len++;                     
    this->pos++;                     
}


// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(this->pos < this->len){
        this->afterCursor->data = x;
    }
    else{
      throw std::range_error("List: setAfter(): cursor at back");  
    }
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(this->pos > 0){
        this->beforeCursor->data = x;
    }
    else{
      throw std::range_error("List: setBefore(): cursor at front"); 
    }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(len > 0){
        if(this->pos == this->len-1){
            this->len--;
            Node *temp = this->afterCursor;
            this->beforeCursor->next = this->backDummy;
            this->backDummy->prev = this->beforeCursor;
            this->afterCursor = this->backDummy;
            delete temp;
        }
        else if(this->pos < this->len){
            this->len--;
            Node* temp = this->afterCursor;
            this->afterCursor = this->afterCursor->next;
            this->beforeCursor->next = this->afterCursor;
            this->afterCursor->prev = this->beforeCursor;
            delete temp;
        }
        else{
            throw std::range_error("List: eraseAfter(): cursor at back");  
        }
    }
    
}

void List::eraseBefore() {
    if (len > 0) {
        if (this->pos == 1) {
            this->len--;
            this->pos--;
            Node *temp = this->beforeCursor;
            this->afterCursor->prev = this->frontDummy;
            this->frontDummy->next = this->afterCursor;
            this->beforeCursor = this->frontDummy;
            delete temp;
        } else if (this->pos > 0) {
            this->len--;
            this->pos--;
            Node* temp = this->beforeCursor;
            this->beforeCursor = this->beforeCursor->prev;
            this->afterCursor->prev = this->beforeCursor;
            this->beforeCursor->next = this->afterCursor;

            // Update next pointer of the node before the deleted node
            if (this->beforeCursor->prev != nullptr) {
                this->beforeCursor->prev->next = this->beforeCursor;
            }

            delete temp;
        } else {
            throw std::range_error("List: eraseBefore(): cursor at front");  
        }
    }
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of Queue consisting of a space separated 
// list of data values.
// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(this->pos < this->len){
        if(x == this->afterCursor->data){
            this->moveNext();
            return this->pos;
        }
        this->moveNext();
    }
    this->moveBack();
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while (pos > 0) {
        /*ListElement L = movePrev();
        std::cout << "mvoeprev " << L  << " x: " << x << std::endl;
        std::cout << "pos " << pos  <<  std::endl;*/
        if(pos !=0 && beforeCursor != backDummy){
            if (movePrev() == x ) {
                return pos;
            }
        }
        //movePrev();
    }
    moveFront(); // If x is not found, place the cursor at position 0.
    return -1;
}

void List::cleanup() {
    if (len > 0) {

        Node* searcher = frontDummy->next;
        Node* nodefound = nullptr;
        int spos = 0;
        int npos = 0;

        while (npos < len) {
            int value = searcher->data; // Moved inside the while loop to get the value of the current node

            while (searcher != backDummy) {
                if (value == searcher->data) {
                    if (nodefound == nullptr) { // Don't erase, just mark the node
                        nodefound = searcher;
                        npos = spos;
                    } else if(spos != 0) { // Erase the node
                        len--; // Decrease the length of the list
                        if(pos > spos){
                            pos--;
                        }
                        // Update the pointers to remove the node from the list
                        searcher->prev->next = searcher->next;
                        searcher->next->prev = searcher->prev;

                        // Save the next node before deleting the current one
                        Node* temp = searcher->next;

                        // Delete the node
                        if(searcher != backDummy)
                            delete searcher;

                        // Move to the next node
                        searcher = temp;

                        continue; // Continue to the next iteration without incrementing spos
                    }
                    else{
                        return;
                    }
                }

                // Move to the next node
                searcher = searcher->next;
                spos++;
            }

            // Move to the next node found after duplicates
            if (nodefound != nullptr) {
                searcher = nodefound->next;
                npos++;
            }

            nodefound = nullptr;
            spos = npos;
        }
        
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List copy(*this);  
    List Lcopy(L);    

    copy.moveBack();
    Lcopy.moveFront();

    while (Lcopy.position() < Lcopy.length()) {
        ListElement element = Lcopy.peekNext();  
        copy.insertBefore(element);              
        //copy.moveNext();                         
        Lcopy.moveNext();                        
    }
    copy.moveFront();
    //std::cout << "copy" << copy << std::endl;
    return copy;    
}


// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string s = "(";

    if(length() > 0){
        Node *current = frontDummy->next; 

        while (current != backDummy) {
            //std::cout << "print " << current->data;
            if(current->next == backDummy){
                s += std::to_string(current->data);
            }
            else{
                s += std::to_string(current->data) + ", ";
            }
            current = current->next;
        }
    }    //std::cout << std::endl;
    s += ")";

    return s;
}


// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    if (len != R.len) {
        return false;
    }
    else if(len == 0 && R.len == 0){
        return true;
    }
    else {
        List thisCopy(*this);
        List rCopy(R);

        thisCopy.moveFront();
        rCopy.moveFront();

        while (thisCopy.position() < thisCopy.length() && rCopy.position() < rCopy.length()) {
            if (thisCopy.peekNext() != rCopy.peekNext()) {
                return false;
            }

            thisCopy.moveNext();
            rCopy.moveNext();
        }
        
        return true; // If no differences found, lists are equal
    }
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) { // not self assignment
        // Clear the current content of this list
        clear();

        // Make a copy of L
        List temp(L);

        //std::cout << "here is the assignment operator at work" << *this << std::endl;
        std::swap(this->pos, temp.pos);
        std::swap(this->frontDummy, temp.frontDummy);
        std::swap(this->backDummy, temp.backDummy);
        std::swap(this->len, temp.len);
        std::swap(this->afterCursor, temp.afterCursor);
        std::swap(this->beforeCursor, temp.beforeCursor);
        // Delete the nodes in this list
        temp.clear();

        // Return this with the new data installed
        return *this;
    }
    
    // Return this without any modifications
    return *this;
}
