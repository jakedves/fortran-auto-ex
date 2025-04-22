#include <stdint.h>
#include "dataflow_api.h"
#include "debug/dprint.h"

void kernel_main() {
    DPRINT_DATA0(DPRINT << "Entered data in..." << ENDL());
    uint32_t fn_arg_0 = get_arg_val<uint32_t>(0);
    uint32_t fn_arg_1 = get_arg_val<uint32_t>(1);
    uint32_t fn_arg_2 = get_arg_val<uint32_t>(2);
    uint32_t fn_arg_3 = get_arg_val<uint32_t>(3);
    uint32_t fn_arg_4 = get_arg_val<uint32_t>(4);
    uint32_t fn_arg_5 = get_arg_val<uint32_t>(5);
    uint64_t noc_addr_14 = get_noc_addr_from_bank_id<true>(fn_arg_0, fn_arg_1, static_cast<std::uint8_t>(0));
    uint64_t noc_addr_15 = get_noc_addr_from_bank_id<true>(fn_arg_2, fn_arg_3, static_cast<std::uint8_t>(0));
    uint32_t write_ptr_16 = get_write_ptr(0);
    uint32_t write_ptr_17 = get_write_ptr(1);
    DPRINT_DATA0(DPRINT << "Arguments parsed in data in" << ENDL());
    cb_reserve_back(0, 1);
    noc_async_read(noc_addr_14, write_ptr_16, fn_arg_4);
    noc_async_read_barrier();
    cb_push_back(0, 1);

    DPRINT_DATA0(DPRINT << "Read data from NOC into cb0" << ENDL());

    cb_reserve_back(1, 1);
    noc_async_read(noc_addr_14, write_ptr_16, fn_arg_5);
    noc_async_read_barrier();
    cb_push_back(1, 1);

    DPRINT_DATA0(DPRINT << "Read data from NOC into cb1" << ENDL());
    DPRINT_DATA0(DPRINT << "Exiting data in..." << ENDL());
}
