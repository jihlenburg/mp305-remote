/* Address: 00053566; name: FUN_00053566; body bytes: 44 */

void FUN_00053566(uint param_1,int *param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  
  if (param_1 < 0x80) {
    iVar1 = 0;
    uVar2 = (int)(param_1 + ((uint)((int)param_1 >> 0x1f) >> 0x1e)) >> 2;
  }
  else {
    iVar1 = FUN_000632cc();
    uVar2 = param_1 >> (iVar1 - 5U & 0xff) ^ 0x20;
    iVar1 = iVar1 + -6;
  }
  *param_2 = iVar1;
  *param_3 = uVar2;
  return;
}

