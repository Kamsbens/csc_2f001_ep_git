#ifndef AST_H
#define AST_H

#include <cstddef>
#include <cstdint>
#include <string>

struct list_t;
struct frame_t;

void error(std::string str) __attribute__((noreturn));

struct node_t {
    virtual node_t* eval(frame_t* frame);
    virtual node_t* apply(list_t* list, frame_t* frame);
    virtual std::string to_string();
    virtual list_t* as_list();
    virtual uintptr_t int_value();
    virtual bool is(std::string id);
};

struct integer_t : node_t {
    uintptr_t value;

    integer_t(uintptr_t value);
    std::string to_string() override;
    uintptr_t int_value() override;
};

struct list_t : node_t {
    node_t** elements;
    size_t nb_elements;
    size_t capacity;

    list_t();
    list_t* as_list() override;
    size_t size();
    node_t* at(size_t i);
    void set_at(size_t i, node_t* value);
    void append(node_t* value);
    std::string to_string() override;
    node_t* eval(frame_t* frame) override;
};

struct keyword_t : node_t {
    std::string id;

    keyword_t(std::string id);
    std::string to_string() override;
};

struct add_t : keyword_t {
    add_t();
    node_t* apply(list_t* list, frame_t* frame) override;
};

struct symbol_t : node_t {
    std::string id;

    symbol_t(std::string id);
    bool is(std::string id) override;
    std::string to_string() override;
    node_t* eval(frame_t* frame) override;
};

struct frame_t : list_t {
    void set(node_t* sym, node_t* value);
    node_t* get(node_t* sym);
};

struct set_t : keyword_t {
    set_t();
    node_t* apply(list_t* list, frame_t* frame) override;
};

#endif
