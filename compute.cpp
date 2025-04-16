#include <cstdint>
#include "compute_kernel_api/tile_move_copy.h"
#include "compute_kernel_api/eltwise_binary.h"
#include "compute_kernel_api/matmul.h"
#include "debug/dprint.h"

void MAIN {
    binary_op_init_common(static_cast<std::uint32_t>(0), static_cast<std::uint32_t>(1), static_cast<std::uint32_t>(16));
    cb_wait_front(0, 1);
    cb_wait_front(1, 1);
    tile_regs_acquire();
    matmul_tiles(static_cast<std::uint32_t>(0), static_cast<std::uint32_t>(1), static_cast<std::uint32_t>(0), static_cast<std::uint32_t>(0), static_cast<std::uint32_t>(0), static_cast<std::uint32_t>(0));
    tile_regs_commit();
    tile_regs_wait();
    pack_tile<false>(static_cast<std::uint32_t>(0), static_cast<std::uint32_t>(16), static_cast<std::uint32_t>(0));
    tile_regs_release();
    cb_pop_front(0, 1);
    cb_pop_front(1, 1);
    cb_push_back(16, 1);
}
