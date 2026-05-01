#include <cstdio>
#include <beethoven/fpga_handle.h>
#include <beethoven_hardware.h>

using namespace beethoven;

int main() {
  fpga_handle_t handle;
  constexpr int n_eles = 32;
  constexpr int sz_int = sizeof(int);

  auto vec_a   = handle.malloc(sz_int * n_eles);
  auto vec_b   = handle.malloc(sz_int * n_eles);
  auto vec_out = handle.malloc(sz_int * n_eles);

  auto a = (int*)vec_a.getHostAddr();
  auto b = (int*)vec_b.getHostAddr();
  for (int i = 0; i < n_eles; ++i) {
    a[i] = i + 1;
    b[i] = i * 2;
  }
  handle.copy_to_fpga(vec_a);
  handle.copy_to_fpga(vec_b);

  myVectorAdd::vector_add(0, vec_a, vec_b, vec_out, n_eles).get();

  handle.copy_from_fpga(vec_out);

  auto out = (int*)vec_out.getHostAddr();
  int errors = 0;
  for (int i = 0; i < n_eles; ++i) {
    int expected = (i + 1) + (i * 2);
    if (out[i] != expected) {
      printf("[FAIL] index %d: got %d, expected %d\n", i, out[i], expected);
      ++errors;
    }
  }
  if (errors == 0) {
    printf("[PASS] vector_add: all %d elements match.\n", n_eles);
  } else {
    printf("[FAIL] vector_add: %d/%d elements wrong.\n", errors, n_eles);
  }

  handle.shutdown();
  return errors == 0 ? 0 : 1;
}
