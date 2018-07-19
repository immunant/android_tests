#include <cstdio>

namespace {

struct Class {
  Class() {
    printf("Constructing a Class\n");
  }

  virtual ~Class() { }

  void foo();

  void callVirt();

  virtual void virtFunc();
};

struct Child : public Class {
  Child() {
    printf("Constructing a Child\n");
  }

  ~Child() {
    printf("Destructing a Child\n");
  }

  void bar();

  virtual void virtFunc();
};

void Class::foo() {
  printf("In Class::foo\n");
}

void Class::callVirt() {
  virtFunc();
  printf("In Class::callVirt\n");
}

void Class::virtFunc() {
  printf("In Class::virtFunc\n");
}


void Child::bar() {
  printf("In Child::bar\n");
}

void Child::virtFunc() {
  printf("In Child::virtFunc\n");
}

static Child static_child;

};

__attribute__ ((noinline))
static void helper(int x) {
  Class *c_ptr;
  if (x == 0) {
    c_ptr = new Class;
  } else {
    c_ptr = new Child;
  }
  c_ptr->virtFunc();
}

extern "C"
void init_library(int) {
  Class c;
  Child child;
  Class *c_ptr = &c;

  c_ptr->foo();
  c_ptr->virtFunc();
  c_ptr->callVirt();

  c_ptr = &child;
  c_ptr->foo();
  c_ptr->virtFunc();
  c_ptr->callVirt();

  helper(0);
  helper(1);
}
