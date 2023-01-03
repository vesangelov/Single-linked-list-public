#include <iostream>
#include <memory>

template<typename T>
struct Node {
    T value_;
    bool head= false;
    std::shared_ptr<Node<T>> next;

    Node() : head(true), value_() {}
    explicit Node(T value) : head(false), value_(value) {}

    std::shared_ptr<Node<T>> push(T value){
        next = std::make_shared<Node<T>>(value);

        return next;
    }
};

template<typename T>
struct List{
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;

    List(){
        head = std::make_shared<Node<T>>();
        tail = head;
    }

    void add_node(T value){
        tail->push(value);
        tail = tail->next;
    }

    void print(){
        auto current = head;

        while(current != nullptr){
            std::cout << current->value_ << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void reverse(){
        auto current = head;
        std::shared_ptr<Node<T>> next, prev;

        while(current != nullptr){
            next = current->next;

            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    std::shared_ptr<Node<T>> create_node(T value){
        return std::make_shared<Node<T>>(value);
    }

    void insert_after(T after_value, T value){
        auto current = head;

        while(current != nullptr){
            if(current->value_ == after_value){
                auto temp_next = current->next;
                auto node = create_node(value);
                current->next = node;
                node->next = temp_next;
                break;
            }

            current = current->next;
        }
    }

    void insert_before(T before_value, T value){
        auto current = head;
        std::shared_ptr<Node<T>> prev;

        while(current != nullptr){
            if(current->value_ == before_value){
                auto node = create_node(value);
                node->next = current;
                prev->next = node;
                break; //should be deleted
            }

            prev = current;
            current = current->next;
        }
    }
};

int main() {

    List<int> list;

    for (int i = 1; i <= 10; ++i) {
        list.add_node(i);
    }

    list.print();
    list.reverse();
    list.print();
    list.reverse();

    list.insert_after(1, 2);
    list.print();
    list.insert_before(9, 20);

    list.print();

    return 0;
}
