/* Address: 00051cb0; name: FUN_00051cb0; body bytes: 138 */

uint FUN_00051cb0(int param_1,int *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_14;
  
  local_14 = 0;
  if (param_2 == (int *)0x0) {
    param_2 = &local_14;
  }
  iVar4 = *param_2;
  bVar1 = *(byte *)(param_1 + iVar4);
  uVar2 = (uint)bVar1;
  uVar5 = uVar2;
  if ((int)(uVar2 << 0x18) < 0) {
    if (bVar1 >> 5 == 6) {
      iVar3 = (uVar2 & 0x1f) << 6;
    }
    else {
      if (bVar1 >> 4 == 0xe) {
        iVar3 = (uVar2 & 0xf) << 0xc;
      }
      else {
        uVar5 = 0;
        if (bVar1 >> 3 != 0x1e) goto LAB_00051d32;
        iVar4 = iVar4 + 1;
        *param_2 = iVar4;
        if (*(byte *)(param_1 + iVar4) >> 6 != 2) {
          return 0;
        }
        iVar3 = (uVar2 & 7) * 0x40000 + (*(byte *)(param_1 + iVar4) & 0x3f) * 0x1000;
      }
      iVar4 = iVar4 + 1;
      *param_2 = iVar4;
      if (*(byte *)(param_1 + iVar4) >> 6 != 2) {
        return 0;
      }
      iVar3 = iVar3 + (*(byte *)(param_1 + iVar4) & 0x3f) * 0x40;
    }
    iVar4 = iVar4 + 1;
    *param_2 = iVar4;
    if (*(byte *)(param_1 + iVar4) >> 6 != 2) {
      return 0;
    }
    uVar5 = (*(byte *)(param_1 + iVar4) & 0x3f) + iVar3;
  }
LAB_00051d32:
  *param_2 = iVar4 + 1;
  return uVar5;
}

