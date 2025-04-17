# Compilation

`fortran.o` is created from the following MLIR:

```
builtin.module {
  func.func @_QMproblem_modPentry() {
    %0 = "memref.alloca"() <{operandSegmentSizes = array<i32: 0, 0>}> : () -> memref<10x10xi32>
    %1 = "memref.alloca"() <{operandSegmentSizes = array<i32: 0, 0>}> : () -> memref<10x10xi32>
    %2 = "memref.alloca"() <{operandSegmentSizes = array<i32: 0, 0>}> : () -> memref<10x10xi32>
    %3 = "memref.alloca"() <{operandSegmentSizes = array<i32: 0, 0>}> : () -> memref<10x10xi32>
    func.call @host_entry(%0, %1, %3) : (memref<10x10xi32>, memref<10x10xi32>, memref<10x10xi32>) -> ()
    "memref.copy"(%3, %2) : (memref<10x10xi32>, memref<10x10xi32>) -> ()
    func.return
  }
  func.func @main() {
    "memref.alloca_scope"() ({
      func.call @_QMproblem_modPentry() : () -> ()
      "memref.alloca_scope.return"() : () -> ()
    }) : () -> ()
    func.return
  }
  func.func private @host_entry(memref<10x10xi32>, memref<10x10xi32>, memref<10x10xi32>) -> ()
}
```

Compiled to the LLVM dialect, and then to an `ll` file, and finally to an object file for the Tenstorrent machine:

```bash
> mlir-opt --convert-to-llvm input.mlir > output.mlir
> mlir-translate --mlir-to-llcvmir output.mlir > output.ll
> llc -mtriple=x86_64-pc-linux-gnu -filetype=obj output.ll -o output.o
```

and `host.o` is created by running `make` and just letting it error on the link step. 

The files are then manually linked with:

```bash
clang++-17 fortran.o host.o -o executable -rdynamic -L${TT_METAL_LIB} -ltt_metal -ldl -lstdc++fs -pthread -lyaml-cpp -lm -lc++ -ldevice
```

With the executable ran as:

```bash
./executable
```
