/* Address: 00027780; name: FUN_00027780; body bytes: 88 */

uint FUN_00027780(uint param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  if ((int)param_1 < 0) {
    iVar3 = param_2 - param_3;
    if (iVar3 < 1) {
      iVar3 = param_3 - param_2;
    }
    uVar1 = (uint)(iVar3 * 100) / (param_1 & 0x3ff);
    uVar4 = (param_1 & 0x3fffffff) >> 0x14;
    uVar2 = (param_1 & 0xfffff) >> 10;
    param_1 = ((param_1 & 0x3fffffff) >> 0x14) * 10;
    uVar5 = param_1;
    if (uVar1 < uVar4 * 10) {
      uVar5 = uVar1;
    }
    if (uVar5 < uVar2 * 10) {
      param_1 = uVar2 * 10;
    }
    else if (uVar1 < uVar4 * 10) {
      return uVar1;
    }
  }
  return param_1;
}

