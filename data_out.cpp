#include "dataflow_api.h"
#include "debug/dprint.h"

void kernel_main() {
    uint32_t fn_arg_0 = get_arg_val<uint32_t>(0);
    uint32_t fn_arg_1 = get_arg_val<uint32_t>(1);
    uint32_t fn_arg_2 = get_arg_val<uint32_t>(2);
    uint64_t noc_addr_18 = get_noc_addr_from_bank_id<true>(fn_arg_0, fn_arg_1);
    uint32_t read_ptr_19 = get_read_ptr(16);
    cb_wait_front(16, 1);
    noc_async_write(read_ptr_19, noc_addr_18, fn_arg_2);
    noc_async_write_barrier();
    cb_pop_front(16, 1);
}
