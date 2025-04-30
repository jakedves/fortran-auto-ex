#include <stdint.h>
#include "dataflow_api.h"
#include "debug/dprint.h"

void kernel_main() {
    DPRINT_DATA0(DPRINT << "Entered data in..." << ENDL());
    uint32_t src0_bank_id = get_arg_val<uint32_t>(2);
    uint32_t src0_addr = get_arg_val<uint32_t>(0);
    uint32_t src1_bank_id = get_arg_val<uint32_t>(3);
    uint32_t src1_addr = get_arg_val<uint32_t>(1);
    uint32_t fn_arg_4 = get_arg_val<uint32_t>(4);
    uint32_t fn_arg_5 = get_arg_val<uint32_t>(5);
    uint64_t noc_addr_14 = get_noc_addr_from_bank_id<true>(src0_bank_id, src0_addr, static_cast<std::uint8_t>(0));
    uint64_t noc_addr_15 = get_noc_addr_from_bank_id<true>(src1_bank_id, src1_addr, static_cast<std::uint8_t>(0));
    uint32_t write_ptr_16 = get_write_ptr(0);
    uint32_t write_ptr_17 = get_write_ptr(1);

    DPRINT_DATA0(DPRINT << "src0_bank_id:      " << src0_bank_id << ENDL());
    DPRINT_DATA0(DPRINT << "src1_bank_id:      " << src1_bank_id << ENDL());
    DPRINT_DATA0(DPRINT << "src0_addr:         " << src0_addr << ENDL());
    DPRINT_DATA0(DPRINT << "tile_size0:        " << fn_arg_4 << ENDL());
    DPRINT_DATA0(DPRINT << "tile_size1:        " << fn_arg_5 << ENDL());
    DPRINT_DATA0(DPRINT << "x-tile_size0:      " << get_tile_size(0) << ENDL());
    DPRINT_DATA0(DPRINT << "x-tile_size1:      " << get_tile_size(1) << ENDL());
    DPRINT_DATA0(DPRINT << "x-tile_size16:     " << get_tile_size(16) << ENDL());

    DPRINT_DATA0(DPRINT << "Arguments parsed in data in" << ENDL());
    cb_reserve_back(0, 1);
    noc_async_read(noc_addr_14, write_ptr_16, fn_arg_4);
    noc_async_read_barrier();
    cb_push_back(0, 1);

    DPRINT_DATA0(DPRINT << "Read data from NOC into cb0" << ENDL());

    cb_reserve_back(1, 1);
    noc_async_read(noc_addr_15, write_ptr_17, fn_arg_5);
    noc_async_read_barrier();
    cb_push_back(1, 1);

    DPRINT_DATA0(DPRINT << "Read data from NOC into cb1" << ENDL());
    DPRINT_DATA0(DPRINT << "Exiting data in..." << ENDL());
}
