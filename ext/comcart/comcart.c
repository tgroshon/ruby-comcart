/**
  * Docs:
  * - https://silverhammermba.github.io/emberb/
  * - https://blog.jcoglan.com/2012/07/29/your-first-ruby-native-extension-c/
  * - http://blog.x-aeon.com/2012/12/13/the-ruby-c-api-basics/
  * - https://github.com/steveklabnik/rust_example
  */
#include <ruby.h>
#include <stdlib.h>

VALUE Comcart = Qnil;
VALUE cGeneral = Qnil;
struct general_data {
	VALUE x;
  VALUE str;
};

void Init_comcart();
VALUE method_comcart_process(VALUE self, VALUE path);
VALUE method_new_general(VALUE self, VALUE x, VALUE s);
VALUE gen_alloc(VALUE self);
VALUE gen_m_initialize(VALUE self, VALUE val, VALUE str);
VALUE gen_m_data(VALUE self);
void gen_mark(struct general_data* data);

void Init_comcart() {
  Comcart = rb_define_module("Comcart");
  rb_define_singleton_method(Comcart, "c_process", method_comcart_process, 1);
  rb_define_singleton_method(Comcart, "make_gen", method_new_general, 2);

	cGeneral = rb_define_class_under(Comcart, "General", rb_cObject);
	rb_define_alloc_func(cGeneral, gen_alloc);
	rb_define_method(cGeneral, "initialize", gen_m_initialize, 2);
	rb_define_method(cGeneral, "data", gen_m_data, 0);
}

VALUE method_comcart_process(VALUE self, VALUE path) {
  return Qnil;
}

VALUE method_new_general(VALUE self, VALUE x, VALUE s) {
  VALUE argv[2] = { x, s };
  return rb_class_new_instance(2, argv, cGeneral);
}

VALUE gen_alloc(VALUE self) {
	struct general_data* data;
	return Data_Make_Struct(self, struct general_data, gen_mark, RUBY_DEFAULT_FREE, data);
}

VALUE gen_m_initialize(VALUE self, VALUE val, VALUE str) {
	struct general_data* data;
	Data_Get_Struct(self, struct general_data, data);

	data->x = val;
	data->str = str;

	return self;
}

VALUE gen_m_data(VALUE self) {
	struct general_data* data;
	Data_Get_Struct(self, struct general_data, data);

	return data->str;
}

void gen_mark(struct general_data* data) {
	rb_gc_mark(data->x);
	rb_gc_mark(data->str);
}
