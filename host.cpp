#include "host_api.hpp"
#include "device_impl.hpp"

using namespace tt;
using namespace tt::tt_metal;

extern "C" void host_entry(std::int32_t* fn_arg_0, std::int32_t* fn_arg_1, std::int32_t* fn_arg_2) {
    Program program_0 = CreateProgram();
    IDevice* device_1 = CreateDevice(0);
    CoreCoord core = {0, 0};

    printf("%d, %d, %d, %d, %d", fn_arg_0[0], fn_arg_0[1], fn_arg_0[2], fn_arg_0[3], fn_arg_0[4]);

    std::shared_ptr<Buffer> buffer_2 = CreateBuffer({.device=device_1, .size=400, .page_size=400, .buffer_type = BufferType::DRAM});
    std::shared_ptr<Buffer> buffer_3 = CreateBuffer({.device=device_1, .size=400, .page_size=400, .buffer_type = BufferType::DRAM});
    std::shared_ptr<Buffer> buffer_4 = CreateBuffer({.device=device_1, .size=400, .page_size=400, .buffer_type = BufferType::DRAM});
    EnqueueWriteBuffer(device_1->command_queue(), buffer_2, fn_arg_0, false);
    EnqueueWriteBuffer(device_1->command_queue(), buffer_3, fn_arg_1, false);
    CircularBufferConfig cb_config_5 = CircularBufferConfig(1*400, {{0, tt::DataFormat::Int32}}).set_page_size(0, 400);
    CircularBufferConfig cb_config_6 = CircularBufferConfig(1*400, {{1, tt::DataFormat::Int32}}).set_page_size(1, 400);
    CircularBufferConfig cb_config_7 = CircularBufferConfig(1*400, {{16, tt::DataFormat::Int32}}).set_page_size(16, 400);
    CBHandle cb_8 = tt_metal::CreateCircularBuffer(program_0, CoreCoord{0, 0}, cb_config_5);
    CBHandle cb_9 = tt_metal::CreateCircularBuffer(program_0, core, cb_config_6);
    CBHandle cb_10 = tt_metal::CreateCircularBuffer(program_0, core, cb_config_7);
    
    KernelHandle kernel_11 = CreateKernel(
	program_0, 
	"/home/jakedves/tenstorrent-projects/fortran-auto/reader.cpp",
	core,
	DataMovementConfig {
	    .processor = DataMovementProcessor::RISCV_0, 
	    .noc=NOC::RISCV_0_default
	}
    );

    KernelHandle kernel_12 = CreateKernel(
        program_0,
	"/home/jakedves/tenstorrent-projects/fortran-auto/writer.cpp",
	core,
	DataMovementConfig {
	    .processor = DataMovementProcessor::RISCV_1,
	    .noc=NOC::RISCV_1_default
	}
    );

    KernelHandle kernel_13 = CreateKernel(
	program_0,
	"/home/jakedves/tenstorrent-projects/fortran-auto/compute.cpp",
	core,
	ComputeConfig {
	    .math_fidelity = MathFidelity::LoFi,
	    .fp32_dest_acc_en = false,
	    .math_approx_mode = false,
	    .compile_args = {}
	}
    );

    SetRuntimeArgs(program_0, kernel_11, core, {buffer_2->address(), buffer_3->address(), 0, 0, 400, 400});
    SetRuntimeArgs(program_0, kernel_13, core, {});
    SetRuntimeArgs(program_0, kernel_12, core, {buffer_4->address(), 0, 400});
    
    EnqueueProgram(device_1->command_queue(), program_0, false);
    printf("Jake: Program queued...\n");
    
    Finish(device_1->command_queue());
    printf("Program finished.\n");
    
    EnqueueReadBuffer(device_1->command_queue(), buffer_4, fn_arg_2, true);
    printf("Read finished.\n");
    
    CloseDevice(device_1);
    printf("Device closed. Host kernel complete.\n");
}
