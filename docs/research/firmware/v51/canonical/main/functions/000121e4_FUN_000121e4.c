/* Address: 000121e4; name: FUN_000121e4; body bytes: 20 */

void FUN_000121e4(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 1 << (param_2 & 0xff);
  if (param_3 == 1) {
    uVar1 = *(uint *)(param_1 + 0x14) | uVar1;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x14) & ~uVar1;
  }
  *(uint *)(param_1 + 0x14) = uVar1;
  return;
}

