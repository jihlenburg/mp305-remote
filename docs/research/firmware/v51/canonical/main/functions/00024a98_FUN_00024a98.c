/* Address: 00024a98; name: FUN_00024a98; body bytes: 156 */

void FUN_00024a98(byte *param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_10;
  
  uVar5 = param_2 & 0xff;
  uVar4 = (param_2 & 0xffff) >> 8;
  uVar3 = (param_2 & 0xffffff) >> 0x10;
  if (param_3 == 1) {
    uVar5 = *param_1 + uVar5;
    if (0xfe < uVar5) {
      uVar5 = 0xff;
    }
    uVar4 = param_1[1] + uVar4;
    if (0xfe < uVar4) {
      uVar4 = 0xff;
    }
    local_10._0_2_ = CONCAT11((char)uVar4,(char)uVar5);
    uVar3 = param_1[2] + uVar3;
    if (0xfe < uVar3) {
      uVar3 = 0xff;
    }
  }
  else if (param_3 == 2) {
    iVar1 = *param_1 - uVar5;
    if (iVar1 < 1) {
      iVar1 = 0;
    }
    iVar2 = param_1[1] - uVar4;
    if (iVar2 < 1) {
      iVar2 = 0;
    }
    local_10._0_2_ = CONCAT11((char)iVar2,(char)iVar1);
    uVar3 = param_1[2] - uVar3;
    if ((int)uVar3 < 1) {
      uVar3 = 0;
    }
  }
  else {
    if (param_3 != 3) {
      return;
    }
    local_10._0_2_ =
         CONCAT11((char)((uint)((int)(short)(ushort)param_1[1] *
                               (int)(short)(ushort)(byte)(param_2 >> 8)) >> 8),
                  (char)((uint)((int)(short)(ushort)*param_1 * (int)(short)uVar5) >> 8));
    uVar3 = (uint)((int)(short)(ushort)param_1[2] * (int)(short)(ushort)(byte)(param_2 >> 0x10)) >>
            8;
  }
  local_10 = (uint)CONCAT12((char)uVar3,(undefined2)local_10);
  FUN_000400ba(&local_10,param_1,param_2 >> 0x18);
  return;
}

