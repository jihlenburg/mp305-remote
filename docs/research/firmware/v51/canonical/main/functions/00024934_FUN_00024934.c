/* Address: 00024934; name: FUN_00024934; body bytes: 166 */

void FUN_00024934(byte *param_1,uint param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = (param_2 & 0xffffff) >> 0x10;
  uVar3 = (param_2 & 0xffff) >> 8;
  uVar2 = param_2 & 0xff;
  if (param_3 == 1) {
    uVar4 = uVar4 + param_1[2];
    if (0xfe < uVar4) {
      uVar4 = 0xff;
    }
    uVar3 = uVar3 + param_1[1];
    if (0xfe < uVar3) {
      uVar3 = 0xff;
    }
    uVar3 = (uVar4 & 0xff) << 0x10 | (uVar3 & 0xff) << 8;
    uVar2 = uVar2 + *param_1;
    if (0xfe < uVar2) {
      uVar2 = 0xff;
    }
  }
  else if (param_3 == 2) {
    uVar4 = param_1[2] - uVar4;
    if ((int)uVar4 < 1) {
      uVar4 = 0;
    }
    uVar3 = param_1[1] - uVar3;
    if ((int)uVar3 < 1) {
      uVar3 = 0;
    }
    uVar3 = (uVar4 & 0xff) << 0x10 | (uVar3 & 0xff) << 8;
    uVar2 = *param_1 - uVar2;
    if ((int)uVar2 < 1) {
      uVar2 = 0;
    }
  }
  else {
    if (param_3 != 3) {
      return;
    }
    uVar3 = ((uint)((int)(short)(ushort)param_1[2] * (int)(short)(ushort)(byte)(param_2 >> 0x10)) >>
            8) << 0x10 |
            (int)(short)(ushort)param_1[1] * (int)(short)(ushort)(byte)(param_2 >> 8) & 0xffffff00U;
    uVar2 = (uint)((int)(short)(ushort)*param_1 * (int)(short)uVar2) >> 8;
  }
  uVar1 = FUN_00040106(uVar3 | uVar2 & 0xff | param_2 & 0xff000000,*(undefined4 *)param_1,param_4);
  *(undefined4 *)param_1 = uVar1;
  return;
}

