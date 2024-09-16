/*
Isabella Shapland // First and Last Name
ishaplan // UCSC UserID
2024 Winter CSE101 PA8 // Replace ID with assignment number
dictionary.cpp // FileName
The main file for the dictionary adt// Description
*/
// Class Constructors & Destructors ----------------------------------------
#include "Dictionary.h"
#include <sstream>
#define BLACK 0
#define RED 1

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr; //maybe they should be null ptrs
    left = nullptr;
    right = nullptr;
    color = RED;
}


// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    root->color = BLACK;
    current = nil;

    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    root->color = BLACK;
    current = nil;
    num_pairs = 0;
    //std::cout<< "here are the number of pairs: " << D.num_pairs << std::endl;
    if (D.root != D.nil) {
        preOrderCopy(D.root, D.nil);
    }
}

// Destructor
Dictionary::~Dictionary(){
    //find a way to delete all the nodes 
    postOrderDelete(root);
    delete nil;
}


// Access functions --------------------------------------------------------

// siNe()
// Returns the siNe of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
   return (search(root, k) != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    Node* N = search(root, k); 
    if(N != nil){ //come back to this
        return N->val;
    }
    else{
        throw std::logic_error("key 'blah' does not exist");
    }
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(hasCurrent()){
        return current->key;
    }
    else{
        throw std::logic_error("current undefined");
    }
    //todo: write the error messages
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent()){
        return current->val;
    }

    else{
        throw std::logic_error("current undefined");
    }
    //todo: write the error messages
}



// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}
// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        if(R->color == RED){
            s.append(R->key).append(" (RED)").append("\n");
        }
        else{
            s.append(R->key).append("\n");
        }
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    } else{
        return;
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        RB_insert(R);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        //remove(R->key);
        delete R; // Deallocate memory for the current node
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    //std::cout << "node that is being searched: " << R->to_String() << std::endl;
    if(R == nil || R->key == k){   
        return R;
    }
    else if(k < R->key){
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if(R != nil){
        current = R;
        while(current->left != nil){
            current = current->left;
        }
        return current;
    }
    return nil;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if(R != nil){
        current = R;
        while(current->right != nil){
            current = current->right;
        }
        return current;
    }
    return nil;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N == nil){
        return nil;
    }
    if(N->right != nil){
        return findMin(N->right);
    }
    Node* y = N->parent;
    while(y != nil && N == y->right){
        N = y;
        y = y->parent;
    }
    return y;
}


// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if(N == nil){
        return nil;
    }
    if(N->left != nil){
        return findMax(N->left);
    }
    Node* y = N->parent;
    while(y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    // set y
   Node* y = N->right; 
   // turn y's left subtree into N's right subtree
   N->right = y->left; 
   if(y->left != nil)     // not necessary if using sentinal nil node
        y->left->parent = N;
   
   // link y's parent to N
   y->parent = N->parent; 
   if(N->parent == nil)
        root = y;
   else if(N == N->parent->left)
        N->parent->left = y;
   else
        N->parent->right = y;
   
   // put N on y's left
   y->left = N; 
   N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    // set y
   Node* y = N->left; 
   
   // turn y's right subtree into x's left subtree
   N->left = y->right; 
   if(y->right != nil)  // not necessary if using sentinal nil node
      y->right->parent = N;
   
   // link y's parent to x
   y->parent = N->parent; 
   if(N->parent == nil)
        root = y;
   else if(N == N->parent->right)
        N->parent->right = y;
   else 
        N->parent->left = y;
   
   // put x on y's right
   y->right = N; 
   N->parent = y;
}
void Dictionary::RB_insert(Dictionary::Node* N){
    Node* y = nil;
    Node* x = root;
    while(x != nil){
        y = x;
        if(N->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    Node* newNode = new Node(N->key, N->val);
    if(y == nil){
        root = newNode;
    }
    else if(N->key < y->key){
        y->left = newNode;
    }
    else{
        y->right = newNode;
    }
}

// RB_Insert()
void Dictionary::BST_insert(Node* N){
    //if contains?
    Node* y = nil;
    Node* x = root;
    
    while(x != nil){
        y = x;
        if(N->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    N->parent = y;
    if(y == nil){
        root = N;
    }
    else if(N->key < y->key){
        y->left = N;
    }   
    else{
        y->right = N;
    }
    N->left = nil;
    N->right = nil;
    N->color = RED;
    RB_InsertFixUp(N);
}

void Dictionary::RB_InsertFixUp(Node* N){
   while(N->parent->color == RED){
      if (N->parent == N->parent->parent->left){
            Node* y = N->parent->parent->right;
            if(y->color == RED){
                N->parent->color = BLACK;              // case 1
                y->color = BLACK;                     // case 1
                N->parent->parent->color = RED;         // case 1
                N = N->parent->parent;   
            } 
            else {
                if(N == N->parent->right){
                    N = N->parent;                     // case 2
                    LeftRotate(N);                 // case 2
                }
                N->parent->color = BLACK;              // case 3
                N->parent->parent->color = RED;         // case 3
                RightRotate(N->parent->parent);  
                }
        } else {
            Node* y = N->parent->parent->left;
            if(y->color == RED){
                N->parent->color = BLACK;              // case 4
                y->color = BLACK;                     // case 4
                N->parent->parent->color = RED;         // case 4
                N = N->parent->parent;
            } else{
                if(N == N->parent->left){
                    N = N->parent;                     // case 5
                    RightRotate(N);
                }                   // case 5
                N->parent->color = BLACK;              // case 6
                N->parent->parent->color = RED;         // case 6
                LeftRotate(N->parent->parent); 
            } 
        }
    }     // case 6
   root->color = BLACK;
}
// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
   else if(u == u->parent->left){
        u->parent->left = v;
   } 
   else{
        u->parent->right = v;
   } 
   v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    while(N != root and N->color == BLACK){
        if(N == N->parent->left){
            Node* w = N->parent->right;
            if(w->color == RED){
                w->color = BLACK;                        // case 1
                N->parent->color = RED;                   // case 1
                LeftRotate(N->parent);                // case 1
                w = N->parent->right;                     // case 1
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;                          // case 2
                N = N->parent;                           // case 2
            }
            else{ 
                if(w->right->color == BLACK){
                    w->left->color = BLACK;                // case 3
                    w->color = RED;                       // case 3
                    RightRotate(w);                       // case 3
                    w = N->parent->right;                  // case 3
                }
                w->color = N->parent->color;               // case 4
                N->parent->color = BLACK;                 // case 4
                w->right->color = BLACK;                  // case 4
                LeftRotate(N->parent);                // case 4
                N = root;                             // case 4
            } 
        }else{
            Node* w = N->parent->left;
            if(w->color == RED){
                w->color = BLACK;                        // case 5
                N->parent->color = RED;                   // case 5
                RightRotate(N->parent);                  // case 5
                w = N->parent->left;                      // case 5
            }
            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;                          // case 6
                N = N->parent;                           // case 6
            }
            else{
                if(w->left->color == BLACK){
                    w->right->color = BLACK;               // case 7
                    w->color = RED;                       // case 7
                    LeftRotate(w);                    // case 7
                    w = N->parent->left;                   // case 7
                }
                w->color = N->parent->color;               // case 8
                N->parent->color = BLACK;                 // case 8
                w->left->color = BLACK;                   // case 8
                RightRotate(N->parent);               // case 8
                N = root;                             // case 8
                }  
            }
    }
    N->color = BLACK;
}


void Dictionary::RB_Delete(Node* N){
    Node* y = N;
    Node* x;
    int y_original_color = y->color;
    if(N->left == nil){
        x = N->right;
        RB_Transplant(N, N->right);
    }    
    else if(N->right == nil){
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else{
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == N){
            x->parent = y;
        } 
        else{
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;   
    }
    if(y_original_color == BLACK){
        RB_DeleteFixUp(x);
    }
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v)->
void Dictionary::setValue(keyType k, valType v){
    Node* curr = search(root, k);
    if(curr != nil){
        curr->val = v;
    }
    else{
        Node* newNode = new Node(k, v);
        newNode->parent = nil;
        newNode->left = nil;
        newNode->right = nil;
        BST_insert(newNode);
        /*
        Node* y = nil;
        Node* x = root;
        while(x != nil){
            y = x;
            if(k < x->key){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }
        Node* newNode = new Node(k, v);
        if(y == nil){
            root = newNode;
        }
        else if(k < y->key){
            y->left = newNode;
        }
        else{
            y->right = newNode;
        }
        
        */
        num_pairs++;
    }

}

void Dictionary::transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v!= nil){
        v->parent = u->parent;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    Node* curr = search(root, k);
    if(curr != nil){
        RB_Delete(curr);
        /*
        Node* N = search(root, k);
        if(N->left == nil){
            transplant(N, N->right);
        }
        else if(N->right == nil){
            transplant(N, N->left);
        }
        else{
            Node* y = findMin(N->right);
            if(y->parent != N){
                transplant(y, y->right);
                y->right = N->right;
                y->right->parent = y;
            }
            transplant(N, y);
            
            y->left = N->left;
            y->left->parent = y;

        }*/
        if(current == curr){
            current = nil;
        }
        else if (current->key < curr->key){
            current = current->parent;
        }
        
        delete curr;
        num_pairs--;
    }
    else{
        throw std::logic_error("key 'blah' does not exist");
    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(root != nil){
        current = findMin(root);
    }  
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(root != nil){
        current = findMax(root);
    }   
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(current != nil){
        if (current->right != nil) {
        current = findMin(current->right);
        } else {
            Node* parent = current->parent;
            while (parent != nil && current == parent->right) {
                current = parent;
                parent = parent->parent;
            }
            // If parent is nullptr, current is at the last pair
            if (parent == nil) {
                current = nil;
            } else {
                // Otherwise, move to the next pair
                current = parent;
            }
        }
    } else{
        throw std::logic_error("current undefined");
    }
    

}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(current != nil){
        if (current->left != nil) {
        current = findMax(current->left);
        } else {
            Node* parent = current->parent;
            while (parent != nil && current == parent->left) {
                current = parent;
                parent = parent->parent;
            }
            // If parent is nullptr, current is at the first pair
            if (parent == nil) {
                current = nil;
            } else {
                // Otherwise, move to the previous pair
                current = parent;
            }
        }
    }
    else{
        throw std::logic_error("current undefined");
    }
    
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary-> Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. The key order is 
   // given by a pre-order tree walk. The keys stored in black Nodes will appear in
   // the returned string as "key\n", and the keys stored in red Nodes will appear 
   // as "key (RED)\n".  The output of this function is demonstrated in 
   // /Examples/pa8/DictionaryClient-out.
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    if(num_pairs != D.num_pairs){
        return false;
    }
    if(to_string() == D.to_string() || pre_string() == D.pre_string()){
        return true;
    }
    return false;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this != &D){
        clear();
        preOrderCopy(D.root, D.nil); //might not include findmax
        //idk if this is actually gonna work tbh try nil if not
        num_pairs = D.num_pairs;
    }
    return *this;
}
