#include <stdlib.h>
#include <stdio.h>

/* Include the mruby header */
#include <mruby.h>
#include <mruby/proc.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/compile.h>
#include <mruby/string.h>

static void test_free(mrb_state* mrb, void* p);
struct RClass* TestClass;

static const struct mrb_data_type test_type = {
  "TestClass", test_free
};

static void test_free(mrb_state* mrb, void* p)
{
  auto value = (int*)p;
  free(value);

  printf("test_free is called\n");
}

mrb_value test_init(mrb_state* mrb, mrb_value exec)
{
  printf("Test.initialize is called\n");
  return mrb_nil_value();
}

mrb_value test_run(mrb_state* mrb, mrb_value exec)
{
  for (int i=0; i<10; i++)
    printf("Test is running: %d\n", i);

  return mrb_fixnum_value(10);
}

void init_TestClass(mrb_state* mrb)
{
  TestClass = mrb_define_class(mrb, "Test", mrb->object_class);
  MRB_SET_INSTANCE_TT(TestClass, MRB_TT_CLASS);
  mrb_define_method(mrb, TestClass, "initialize", test_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, TestClass, "run", test_run, MRB_ARGS_NONE()); }

static void
p(mrb_state *mrb, mrb_value obj, int prompt)
{
  mrb_value val;

  val = mrb_funcall(mrb, obj, "inspect", 0); 
  if (prompt) {
    if (!mrb->exc) {
      fputs(" => ", stdout);
    }   
    else {
      val = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0); 
    }   
  }
  if (!mrb_string_p(val)) {
    val = mrb_obj_as_string(mrb, obj);
  }
  fwrite(RSTRING_PTR(val), RSTRING_LEN(val), 1, stdout);
  putc('\n', stdout);
}

int main()
{
  mrb_state *mrb = mrb_open();
  init_TestClass(mrb);

  char code[] = "$t = Test.new; res = $t.run; p res";
  printf("Executing Ruby code from C!\n");

  auto c = mrbc_context_new(mrb);
  auto p = mrb_parse_string(mrb, code, c);
  auto n = mrb_generate_code(mrb, p);

  // mrb_run(mrb, n, mrb_top_self(mrb));
  unsigned stack_keep = 0;
  auto result = mrb_vm_run(mrb,
                n,
                mrb_top_self(mrb),
                stack_keep);

  if (mrb->exc) // have exception
  {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
    mrb->exc = 0;
  }
  else
  {
    if (!mrb_respond_to(mrb, result, mrb_intern_lit(mrb, "inspect")))
      result = mrb_any_to_s(mrb, result);
    
    mrb_p(mrb, result);
  }

  mrbc_context_free(mrb, c);
  mrb_close(mrb);

  return 0;
}
