/* Address: 0001681c; name: FUN_0001681c; body bytes: 20 */

void FUN_0001681c(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 1) {
    uVar1 = *(uint *)(param_1 + 0xc) | 0x400;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0xc) & 0xfffffbff;
  }
  *(uint *)(param_1 + 0xc) = uVar1;
  return;
}

