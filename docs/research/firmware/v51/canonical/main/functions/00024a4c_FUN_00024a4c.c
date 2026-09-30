/* Address: 00024a4c; name: FUN_00024a4c; body bytes: 76 */

void FUN_00024a4c(byte *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0003ff24(param_2);
  if (param_3 == 1) {
    uVar2 = iVar1 + (uint)*param_1;
    if (0xfe < (int)uVar2) {
      uVar2 = 0xff;
    }
  }
  else {
    if (param_3 != 2) {
      if (param_3 != 3) {
        return;
      }
      uVar2 = ((int)(short)(ushort)*param_1 * (int)(short)iVar1 & 0xffffU) >> 8;
      goto LAB_00024a70;
    }
    uVar2 = (uint)*param_1 - iVar1;
    if ((int)uVar2 < 1) {
      uVar2 = 0;
    }
  }
  uVar2 = uVar2 & 0xff;
LAB_00024a70:
  FUN_00040280(uVar2,param_1,param_2 >> 0x18);
  return;
}

