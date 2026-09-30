/* Address: 0003a024; name: FUN_0003a024; body bytes: 130 */

void FUN_0003a024(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_r2;
  int iVar3;
  int local_18;
  
  iVar3 = *(int *)(param_1 + 0x74);
  if ((iVar3 != 0) && (*(int *)(param_1 + 0x94) != 0)) {
    DAT_2003a474 = iVar3;
    local_18 = param_4;
    iVar1 = FUN_0004d45a(iVar3);
    if (iVar1 == 0) {
      uVar2 = (uint)*(byte *)(param_1 + 0x24);
      if (*(int *)(param_1 + 0x94) < 1) {
        uVar2 = -uVar2;
      }
      *(int *)(param_1 + 0x68) = iVar3;
      *(uint *)(param_1 + 0x4c) = uVar2;
      iVar3 = FUN_00047f68(param_1);
      if (iVar3 != 0) {
        iVar1 = *(int *)(param_1 + 0x2c);
        iVar3 = FUN_0004c954(iVar3,0);
        iVar1 = iVar3 * iVar1 * *(int *)(param_1 + 0x94) + 0x8000;
        iVar3 = iVar1 >> 0x10;
        *(int *)(param_1 + 0x5c) = iVar3;
        *(int *)(param_1 + 100) = iVar3;
        FUN_00048428(param_1,iVar1,extraout_r2,local_18);
        return;
      }
    }
    else {
      iVar1 = *(int *)(param_1 + 0x2c);
      iVar3 = FUN_0004c954(DAT_2003a474,0);
      local_18 = iVar3 * iVar1 * *(int *)(param_1 + 0x94) + 0x8000 >> 0x10;
      FUN_0005e710(0xf,&local_18);
    }
  }
  return;
}

