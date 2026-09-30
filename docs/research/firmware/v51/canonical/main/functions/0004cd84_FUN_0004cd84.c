/* Address: 0004cd84; name: FUN_0004cd84; body bytes: 14 */

undefined4 FUN_0004cd84(int param_1,uint param_2)

{
  if ((param_2 & ~*(uint *)(param_1 + 0x24)) != 0) {
    return 0;
  }
  return 1;
}

