#include "ast.h"
#include <cstdlib>
#include <iostream>

void error(std::string str) {
    std::cout << "Error: " << str << std::endl;
    exit(1);
}

node_t* node_t::eval(frame_t*) {
    return this;
}

node_t* node_t::apply(list_t*, frame_t*) {
    error("this node cannot be applied");
}

std::string node_t::to_string() {
    return "???";
}

list_t* node_t::as_list() {
    error("this node is not a list");
}

uintptr_t node_t::int_value() {
    error("this node is not an integer");
}

bool node_t::is(std::string) {
    return false;
}

integer_t::integer_t(uintptr_t value) : value { value } { }

std::string integer_t::to_string() {
    return std::to_string(value);
}

uintptr_t integer_t::int_value() {
    return value;
}

list_t::list_t() : elements { nullptr }, nb_elements { 0 }, capacity { 0 } { }

list_t* list_t::as_list() {
    return this;
}

size_t list_t::size() {
    return nb_elements;
}

node_t* list_t::at(size_t i) {
    if (i >= nb_elements)
        error("index out of bounds");
    return elements[i];
}

void list_t::set_at(size_t i, node_t* value) {
    if (i >= nb_elements)
        error("index out of bounds");
    elements[i] = value;
}

void list_t::append(node_t* value) {
    if (nb_elements == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        node_t** new_elements = new node_t*[new_capacity];
        for (size_t i = 0; i < nb_elements; i++)
            new_elements[i] = elements[i];
        elements = new_elements;
        capacity = new_capacity;
    }
    elements[nb_elements] = value;
    nb_elements++;
}

std::string list_t::to_string() {
    std::string result = "(";
    for (size_t i = 0; i < nb_elements; i++) {
        if (i != 0)
            result += " ";
        result += elements[i]->to_string();
    }
    return result + ")";
}

node_t* list_t::eval(frame_t* frame) {
    if (size() == 0)
        error("cannot evaluate an empty list");
    return at(0)->eval(frame)->apply(this, frame);
}

keyword_t::keyword_t(std::string id) : id { id } { }

std::string keyword_t::to_string() {
    return "<" + id + ">";
}

add_t::add_t() : keyword_t { "+" } { }

node_t* add_t::apply(list_t* list, frame_t* frame) {
    uintptr_t result = 0;
    for (size_t i = 1; i < list->size(); i++)
        result += list->at(i)->eval(frame)->int_value();
    return new integer_t { result };
}

symbol_t::symbol_t(std::string id) : id { id } { }

bool symbol_t::is(std::string id) {
    return this->id == id;
}

std::string symbol_t::to_string() {
    return id;
}

node_t* symbol_t::eval(frame_t* frame) {
    if (frame == nullptr)
        error("cannot evaluate a symbol without a frame");
    return frame->get(this);
}

void frame_t::set(node_t* sym, node_t* value) {
    if (!sym->is(sym->to_string()))
        error("variable name must be a symbol");
    for (size_t i = 0; i < size(); i++) {
        list_t* binding = at(i)->as_list();
        if (sym->is(binding->at(0)->to_string())) {
            binding->set_at(1, value);
            return;
        }
    }
    list_t* binding = new list_t;
    binding->append(sym);
    binding->append(value);
    append(binding);
}

node_t* frame_t::get(node_t* sym) {
    for (size_t i = 0; i < size(); i++) {
        list_t* binding = at(i)->as_list();
        if (sym->is(binding->at(0)->to_string()))
            return binding->at(1);
    }
    error("undefined symbol: " + sym->to_string());
}

set_t::set_t() : keyword_t { "set!" } { }

node_t* set_t::apply(list_t* list, frame_t* frame) {
    if (list->size() != 3)
        error("set! expects a symbol and a value");
    if (frame == nullptr)
        error("set! requires a frame");
    node_t* sym = list->at(1);
    if (!sym->is(sym->to_string()))
        error("set! expects a symbol as its first argument");
    node_t* value = list->at(2)->eval(frame);
    frame->set(sym, value);
    return value;
}
