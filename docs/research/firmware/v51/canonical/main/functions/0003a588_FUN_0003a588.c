/* Address: 0003a588; name: FUN_0003a588; body bytes: 60 */

void FUN_0003a588(int param_1)

{
  if ((int)((uint)*(byte *)(param_1 + 10) << 0x1e) < 0) {
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x70) = 0;
    *(undefined4 *)(param_1 + 0x78) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(byte *)(param_1 + 0x98) = *(byte *)(param_1 + 0x98) & 0xf0;
    *(undefined4 *)(param_1 + 0x58) = 0;
    *(undefined4 *)(param_1 + 0x5c) = 0;
    *(undefined4 *)(param_1 + 0x8c) = 0;
    *(undefined4 *)(param_1 + 0x90) = 0;
    *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) & 0xec;
    DAT_2003a474 = 0;
  }
  return;
}

