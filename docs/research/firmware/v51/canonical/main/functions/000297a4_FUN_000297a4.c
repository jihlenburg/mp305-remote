/* Address: 000297a4; name: FUN_000297a4; body bytes: 28 */

void FUN_000297a4(int param_1,undefined4 param_2)

{
  FUN_0003ddf0(param_2,0,0,(*(uint *)(param_1 + 4) & 0xffff) - 1,
               (*(uint *)(param_1 + 4) >> 0x10) - 1);
  return;
}

