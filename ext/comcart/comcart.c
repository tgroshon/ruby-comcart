#include <ruby.h>

VALUE Comcart = Qnil;

// Declare a couple of functions. The first is initialization code that runs
// when this file is loaded, and the second is the actual business logic we're
// implementing.
void Init_comcart();
VALUE method_comcart_process(VALUE self, VALUE path);

// Initial setup function, takes no arguments and returns nothing. Some API
// notes:
//
// * rb_define_module() creates and returns a top-level module by name
//
// * rb_define_module_under() takes a module and a name, and creates a new
//   module within the given one
//
// * rb_define_singleton_method() take a module, the method name, a reference to
//   a C function, and the method's arity, and exposes the C function as a
//   single method on the given module
//
void Init_comcart() {
  Comcart = rb_define_module("Comcart");
  rb_define_singleton_method(Comcart, "process", method_comcart_process, 1);
}

VALUE method_comcart_process(VALUE self, VALUE path) {
  return Qnil;
}
