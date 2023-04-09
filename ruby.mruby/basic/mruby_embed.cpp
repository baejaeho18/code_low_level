#include <sstream>
#include <fstream>
#include <iostream>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/proc.h>
#include <mruby/class.h>
#include <mruby/data.h>

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
namespace {

  auto t_init(mrb_state* mrb, mrb_value self) -> mrb_value 
  {
    auto arr = mrb_ary_new(mrb);
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@arr"), arr);

    return self;
  }

  auto t_add(mrb_state* mrb, mrb_value self) -> mrb_value 
  {
    auto arr = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@arr"));
    mrb_value obj;
    mrb_get_args(mrb, "o", &obj);
    mrb_funcall(mrb, arr, "push", 1, obj);

    return arr;
  }

  //static struct RClass* cTest;
  auto init_by_test(mrb_state* mrb) -> RClass* 
  {
    auto cTest = mrb_define_class(mrb, "MyTest", mrb->object_class);

    mrb_define_method(mrb, cTest, "initialize", t_init, MRB_ARGS_NONE());
    mrb_define_method(mrb, cTest, "add"       , t_add , MRB_ARGS_REQ(1));

    return cTest;
  }

} 

int main()
{
  using namespace std;

  // cout << "Executing Ruby code from C++!\n";

  ifstream ifs("mytest.rb");
  if (!ifs.is_open())
  {
    cout << "Can't find the file";
    exit(EXIT_FAILURE);
  }

  stringstream buffer; 
  buffer << ifs.rdbuf();
  auto code = buffer.str();
  // cout << code;

  auto mrb = mrb_open();

  init_by_test(mrb);

  auto c = mrbc_context_new(mrb);
  auto p = mrb_parse_string(mrb, code.c_str(), c);
  auto proc = mrb_generate_code(mrb, p);
  mrb_context_run(mrb, proc, mrb_top_self(mrb), 0);
  if (mrb->exc) // exception?
    mrb_p(mrb, mrb_obj_value(mrb->exc));

  mrb_close(mrb);

  return 0;
}
