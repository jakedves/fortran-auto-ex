#include "dataflow_api.h"
#include "debug/dprint.h"

void kernel_main() {
    DPRINT_DATA1(DPRINT << "Entering data out..." << ENDL());
    uint32_t fn_arg_0 = get_arg_val<uint32_t>(1);
    uint32_t fn_arg_1 = get_arg_val<uint32_t>(0);
    uint32_t fn_arg_2 = get_arg_val<uint32_t>(2);

    DPRINT_DATA1(DPRINT << "bank id: " << fn_arg_0 << ENDL());
    DPRINT_DATA1(DPRINT << "address: " << fn_arg_1 << ENDL());
    DPRINT_DATA1(DPRINT << "tsize:   " << fn_arg_2 << ENDL());
    DPRINT_DATA1(DPRINT << "xtsize0: " << get_tile_size(0) << ENDL());
    DPRINT_DATA1(DPRINT << "xtsize1: " << get_tile_size(1) << ENDL());
    DPRINT_DATA1(DPRINT << "xtsize16 " << get_tile_size(16) << ENDL());

    DPRINT_DATA1(DPRINT << "get_arg_val complete" << ENDL());

    uint64_t noc_addr_18 = get_noc_addr_from_bank_id<true>(fn_arg_0, fn_arg_1);
    uint32_t read_ptr_19 = get_read_ptr(16);

    DPRINT_DATA1(DPRINT << "Arguments read fine." << ENDL());

    cb_wait_front(16, 1);

    DPRINT_DATA1(DPRINT << "Collected items from cb16" << ENDL());

    noc_async_write(read_ptr_19, noc_addr_18, fn_arg_2);
    
    DPRINT_DATA1(DPRINT << "Submitted write request to NOC" << ENDL());

    noc_async_write_barrier();

    DPRINT_DATA1(DPRINT << "Written data to the NOC" << ENDL());

    cb_pop_front(16, 1);

    DPRINT_DATA1(DPRINT << "Removed items from cb16, exiting data out" << ENDL());
}
