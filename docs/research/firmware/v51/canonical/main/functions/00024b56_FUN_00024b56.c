/* Address: 00024b56; name: FUN_00024b56; body bytes: 20 */

undefined4 FUN_00024b56(int param_1,int param_2)

{
  if (param_2 + 0x10U <= (*(uint *)(param_1 + 4) & 0xfffffffc)) {
    return 1;
  }
  return 0;
}

