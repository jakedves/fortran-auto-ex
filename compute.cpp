#include <cstdint>
#include "compute_kernel_api/tile_move_copy.h"
#include "compute_kernel_api/eltwise_binary.h"
#include "compute_kernel_api/matmul.h"
#include "debug/dprint.h"

namespace NAMESPACE {
void MAIN {
    DPRINT_MATH(DPRINT << "Have entered compute" << ENDL());
    binary_op_init_common(0, 1, 16);
    mm_init(0, 1, 0, 0);
    cb_wait_front(0, 1);
    cb_wait_front(1, 1);

    DPRINT_MATH(DPRINT << "About to aquire tile regs" << ENDL());
    tile_regs_acquire();
    matmul_tiles(0, 1, 0, 0, 0);
    tile_regs_commit();

    DPRINT_MATH(DPRINT << "Performed add and committed tiles" << ENDL());
    tile_regs_wait();
    pack_tile<false>(0, 16, 0);
    tile_regs_release();
    cb_pop_front(0, 1);
    cb_pop_front(1, 1);
    cb_push_back(16, 1);
    DPRINT_MATH(DPRINT << "Exiting compute" << ENDL());
}
}
