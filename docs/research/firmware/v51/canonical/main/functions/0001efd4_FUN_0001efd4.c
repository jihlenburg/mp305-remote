/* Address: 0001efd4; name: FUN_0001efd4; body bytes: 48 */

void FUN_0001efd4(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_2 & 0xffff;
  if (uVar1 != 0) {
    if (param_3 == 1) {
      uVar1 = *(uint *)(param_1 + 0xc) | uVar1;
    }
    else {
      uVar1 = *(uint *)(param_1 + 0xc) & ~uVar1;
    }
    *(uint *)(param_1 + 0xc) = uVar1;
  }
  uVar1 = param_2 >> 0x10 & 0x411e;
  if (uVar1 != 0) {
    if (param_3 == 1) {
      uVar1 = *(uint *)(param_1 + 0x10) | uVar1;
    }
    else {
      uVar1 = *(uint *)(param_1 + 0x10) & ~uVar1;
    }
    *(uint *)(param_1 + 0x10) = uVar1;
  }
  return;
}

