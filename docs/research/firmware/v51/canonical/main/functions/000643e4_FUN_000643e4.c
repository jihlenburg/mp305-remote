/* Address: 000643e4; name: FUN_000643e4; body bytes: 118 */

undefined4 * FUN_000643e4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar4 = 0x100;
  iVar5 = 0;
  iVar3 = 0x100;
  local_20 = param_3;
  local_1c = param_4;
  for (; param_1 != 0; param_1 = FUN_0004bc8c(param_1)) {
    sVar1 = FUN_0004c924(param_1,0,0x6e);
    iVar5 = (int)(short)(sVar1 + (short)iVar5);
    iVar4 = FUN_0004c924(param_1,0,0x6c);
    if (iVar4 < 1) {
      iVar4 = 1;
    }
    iVar2 = FUN_0004c924(param_1,0,0x6d);
    if (iVar2 < 1) {
      iVar2 = 1;
    }
    iVar4 = iVar3 * iVar4 >> 8;
    iVar3 = iVar2 * iVar3 >> 8;
  }
  local_20 = 0;
  local_1c = 0;
  FUN_0004f292(param_2,-iVar5,0x10000 / iVar4,0x10000 / iVar3);
  return &local_20;
}

