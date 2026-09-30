/* Address: 000121c4; name: FUN_000121c4; body bytes: 26 */

void FUN_000121c4(int param_1,int param_2,uint param_3,int param_4)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 1 << (param_3 & 0xff);
  puVar1 = (uint *)(param_1 + param_2 * 4 + 0xc);
  uVar3 = *puVar1;
  if (param_4 == 1) {
    uVar3 = uVar3 | uVar2;
  }
  else {
    uVar3 = uVar3 & ~uVar2;
  }
  *puVar1 = uVar3;
  return;
}

