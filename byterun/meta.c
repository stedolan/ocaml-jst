/* Primitives for the toplevel */

#include "alloc.h"
#include "fix_code.h"
#include "interp.h"
#include "major_gc.h"
#include "memory.h"
#include "minor_gc.h"
#include "misc.h"
#include "mlvalues.h"
#include "prims.h"

value get_global_data(unit)     /* ML */
     value unit;
{
  return global_data;
}

value execute_bytecode(prog, len) /* ML */
     value prog, len;
{
#if defined(BIG_ENDIAN)
  fixup_endianness((code_t) prog, (asize_t) Long_val(len));
#endif
  return interprete((code_t) prog, (asize_t) Long_val(len));
}

value realloc_global(size)      /* ML */
     value size;
{
  mlsize_t requested_size, actual_size, i;
  value new_global_data;

  requested_size = Long_val(size);
  actual_size = Wosize_val(global_data);
  if (requested_size >= actual_size) {
    requested_size = (requested_size + 0x100) & 0xFFFFFF00;
    new_global_data = alloc_shr(requested_size, 0);
    for (i = 0; i < actual_size; i++)
      initialize(&Field(new_global_data, i), Field(global_data, i));
    for (i = actual_size; i < requested_size; i++){
      Field (new_global_data, i) = Val_long (0);
    }
    global_data = new_global_data;
  }
  return Val_unit;
}
    
value available_primitives()    /* ML */
{
  return copy_string_array(names_of_cprim);
}
