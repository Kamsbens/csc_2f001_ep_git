#include "ast.h"
#include <iostream>

int main() {
    frame_t* frame = new frame_t;
    node_t* integer = new integer_t { 3 };
    std::cout << integer->to_string() << " => "
              << integer->eval(frame)->to_string() << std::endl;

    list_t* list = new list_t;
    list->append(new integer_t { 1 });
    list->append(new integer_t { 2 });
    list->append(new integer_t { 3 });
    std::cout << list->to_string() << std::endl;

    node_t* add = new add_t;
    list_t* ast = new list_t;
    ast->append(add);
    ast->append(new list_t);
    ast->at(1)->as_list()->append(add);
    ast->at(1)->as_list()->append(new integer_t { 1 });
    ast->at(1)->as_list()->append(new integer_t { 2 });
    ast->append(new integer_t { 3 });
    std::cout << ast->to_string() << " => "
              << ast->eval(frame)->to_string() << std::endl;

    frame->set(new symbol_t { "a" }, new integer_t { 666 });
    frame->set(new symbol_t { "b" }, new integer_t { 21 });
    frame->set(new symbol_t { "a" }, new integer_t { 42 });
    std::cout << frame->to_string() << ": a="
              << frame->get(new symbol_t { "a" })->to_string() << std::endl;

    symbol_t* a = new symbol_t { "a" };
    frame->set(a, new integer_t { 37 });
    ast->at(1)->as_list()->set_at(1, a);
    std::cout << ast->to_string() << " => "
              << ast->eval(frame)->to_string() << std::endl;

    list_t* assignment = new list_t;
    assignment->append(new set_t);
    assignment->append(a);
    assignment->append(ast);
    std::cout << assignment->to_string() << " => "
              << assignment->eval(frame)->to_string() << std::endl;
    std::cout << "a=" << a->eval(frame)->to_string() << std::endl;

    return 0;
}
