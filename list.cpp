#include <iostream>
#include <vector>
#include <random>
using namespace std;

bool rnd(float p){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1); 
    double randomNumber = dis(gen);	
    return (randomNumber < p);}

template <typename T>
class OneNode {
public:
    OneNode* right;
    OneNode* down;
    T val;
    
    
OneNode () : right(nullptr), down(nullptr){}
};


template <typename T>
class Skiplist {
public:

std::vector<OneNode<T>> list;
int height;
    
Skiplist() : list {}, height(0) {}
    
template <typename Iterator>
Skiplist(Iterator begin, Iterator end) : list{}, height(0) {
for (auto it = begin; it != end; ++it) {insert(*it);}}
                        
Skiplist(std::vector<OneNode<T>> li) : list(li), height(1) {}
     
           
bool find(const T& value) {
     int idx = list.size() - 1;
     OneNode<T>* current = &list[idx];
     for (int i = idx; i >= 0; i--) {
        while (current->right && current->right->val < value) {
            current = current->right;  
        }
        if (current->right && current->right->val == value) {
            return true; 
        }
        if (current->val == value){
        return true;}
        
        if (current->down) {
            current = current->down;  
        } else {
            break; 
        }
    }
    return false;}
     
     
void print() {
    
    int maxLevel = list.size(); 
        
    for (int level = maxLevel - 1; level >= 0; level--) {
    OneNode<T>* current = &(list[level]);
    cout << "Level " << level << ": ";
    while (current->right) {
    if(current->val)
    cout << current->val << " -> ";
    current = current->right;}
    cout << current->val << endl;}
    cout << endl;}
    		    		
OneNode<T>* insert_on_level (int level, const T& value) {

OneNode<T>* current = &(list[level]);
while (current->right && current->right->val < value) {
current = current->right;}

if (current->right == nullptr && current->val < value) {
OneNode<T>* neW = new OneNode<T>;
neW -> val = value;
current->right= neW;
neW -> right = nullptr;
return neW;}

if (current->right == nullptr && current->val > value) {
OneNode<T>* neW = new OneNode<T>;
neW -> val = value;
neW->right= current;
list[level] = *neW;
return neW;}

else {
OneNode<T>* neW = new OneNode<T>;
neW -> val = value;
OneNode<T>* current_right = current->right;
current->right =neW;
neW -> right = current_right;
return neW;
}
}    		

void insert(const T& value) {
     
if(!find(value)){ 
         
int counter = 0;
while(rnd(0.5)  && (list.size() > counter) ){counter++;}

if(counter != list.size()){
    
vector<OneNode<T>*> list_of_new; 
     
for (int i = counter; i>=0; i--){

OneNode<T>* Level_new = insert_on_level(i, value);

list_of_new.push_back(Level_new);
}

for (int i = counter; i>0; i--){
list_of_new[counter-i]->down = list_of_new[counter-i+1];

}
}

else{

OneNode<T>* neW_node = new OneNode<T>;
neW_node->val = value;
list.push_back((*neW_node));
vector<OneNode<T>*> list_of_new; 
list_of_new.push_back(neW_node);
     
for (int i = counter-1; i>=0; i--){

OneNode<T>* Level_new = insert_on_level(i, value);

list_of_new.push_back(Level_new);
}

for (int i = counter; i>0; i--){

list_of_new[counter-i]->down = list_of_new[counter-i+1];

}

}

}}


void delete_on_level (int level, const T& value){

OneNode<T>* current = &(list[level]);

if (current->val == value){

if(current->right == nullptr){
delete current;
}

else if(current->right != nullptr && current->right){

(list[level]) = *(current->right);

}}

else if(current->right->right && current->right->val == value){
auto A = current;
auto B = current->right;
auto C = current->right->right;

A->right = C;
delete B;
}

else if(current->right->right == nullptr && current->right->val == value){
delete current->right;

}

else{

while(current->right && current->right->val < value){
current = current->right;}

if(current && current->right && current->right->right ){

auto A = current;
auto B = current->right;
auto C = current->right->right;

A->right = C;
delete B;
}

else if(current && current->right ){
auto A = current;
auto B = current->right;

A->right = nullptr;
delete B;}

else if(current){
delete current;}

}}



int find_on_the_top_level (const T& value){

int idx = list.size() - 1;
OneNode<T>* current = &list[idx];
for (int i =idx; i>=0; i--){

cout << current->val << endl;
while (current->right && current->right->val < value){
current = current->right;
cout << "right" << endl;
cout << current->val << endl;}
if (current->right && current->right->val == value) {
return idx;}
if (current->val == value){
return idx;}
else if(current->down){
current = current->down;
cout<<"down" << endl;}
cout << current->val << endl;
}}


void remove (const T& value){
if(find(value)){
int idx = find_on_the_top_level(value);
for (int i = idx; i>=0; i--){
delete_on_level(i, value);
}}}

  
};

int main() {
 
Skiplist<int> s;
  
s.insert(1);
s.insert(2);
s.insert(4);
s.insert(3);
s.insert(5);

s.print();

s.delete_on_level(0,1);

s.print();

s.delete_on_level(0,2);

s.print();

cout << s.find_on_the_top_level(5)  <<endl;

return 0;
}

