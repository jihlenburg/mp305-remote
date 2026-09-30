/* Address: ram:00007ac2; name: FUN_ram_00007ac2; body bytes: 192 */

uint FUN_ram_00007ac2(int param_1,byte param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  gp = &DAT_ram_20002000;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_3 == &DAT_ram_00009234) {
    param_3 = *(int **)(param_1 + 4);
  }
  else if (param_3 == (int *)&DAT_ram_00009254) {
    param_3 = *(int **)(param_1 + 8);
  }
  else if (param_3 == (int *)&DAT_ram_00009214) {
    param_3 = *(int **)(param_1 + 0xc);
  }
  param_3[2] = param_3[6];
  if ((((*(ushort *)(param_3 + 3) & 8) != 0) && (param_3[4] != 0)) ||
     (iVar1 = FUN_ram_00007b82(param_1,param_3), iVar1 == 0)) {
    uVar4 = (uint)param_2;
    iVar1 = *param_3 - param_3[4];
    if (param_3[5] <= iVar1) {
      iVar2 = FUN_ram_00007e72(param_1,param_3);
      iVar1 = 0;
      if (iVar2 != 0) {
        return 0xffffffff;
      }
    }
    param_3[2] = param_3[2] + -1;
    pbVar3 = (byte *)*param_3;
    *param_3 = (int)(pbVar3 + 1);
    *pbVar3 = param_2;
    if (param_3[5] != iVar1 + 1) {
      if ((*(ushort *)(param_3 + 3) & 1) == 0) {
        gp = &DAT_ram_20002000;
        return uVar4;
      }
      if (uVar4 != 10) {
        gp = &DAT_ram_20002000;
        return uVar4;
      }
    }
    iVar1 = FUN_ram_00007e72(param_1,param_3);
    if (iVar1 == 0) {
      gp = &DAT_ram_20002000;
      return uVar4;
    }
  }
  return 0xffffffff;
}

