#include <ruby.h>
#include <stdlib.h>

VALUE Comcart = Qnil;
VALUE cGeneral = Qnil;

void Init_comcart();
VALUE method_comcart_process(VALUE self, VALUE path);
VALUE method_new_general(VALUE self, VALUE x);
void gen_free(int* data);
VALUE gen_alloc(VALUE self);
VALUE gen_m_initialize(VALUE self, VALUE val);
VALUE gen_m_data(VALUE self);

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
  rb_define_singleton_method(Comcart, "c_process", method_comcart_process, 1);
  rb_define_singleton_method(Comcart, "make_gen", method_new_general, 1);

	cGeneral = rb_define_class_under(Comcart, "General", rb_cObject);
	rb_define_alloc_func(cGeneral, gen_alloc);
	rb_define_method(cGeneral, "initialize", gen_m_initialize, 1);
	rb_define_method(cGeneral, "data", gen_m_data, 0);
}

VALUE method_comcart_process(VALUE self, VALUE path) {
  return Qnil;
}

VALUE method_new_general(VALUE self, VALUE x) {
  VALUE argv[1] = { x };
  return rb_class_new_instance(1, argv, cGeneral);
}

void gen_free(int* data) {
	free(data);
}

VALUE gen_alloc(VALUE self) {
	/* allocate */
	int* data = malloc(sizeof(int));

	/* wrap */
	return Data_Wrap_Struct(self, NULL, gen_free, data);
}

VALUE gen_m_initialize(VALUE self, VALUE val) {
	int* data;
	/* unwrap */
	Data_Get_Struct(self, int, data);

	*data = NUM2INT(val);

	return self;
}

VALUE gen_m_data(VALUE self) {
	int* data;
	Data_Get_Struct(self, int, data);

	return INT2NUM(*data);
}
