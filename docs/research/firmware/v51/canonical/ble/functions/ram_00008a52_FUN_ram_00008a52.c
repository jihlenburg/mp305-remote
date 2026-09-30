/* Address: ram:00008a52; name: FUN_ram_00008a52; body bytes: 134 */

uint FUN_ram_00008a52(int param_1,byte param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  gp = &DAT_ram_20002000;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_3 == &DAT_ram_00009234) {
    param_3 = *(undefined4 **)(param_1 + 4);
  }
  else if (param_3 == (undefined4 *)&DAT_ram_00009254) {
    param_3 = *(undefined4 **)(param_1 + 8);
  }
  else if (param_3 == (undefined4 *)&DAT_ram_00009214) {
    param_3 = *(undefined4 **)(param_1 + 0xc);
  }
  iVar2 = param_3[2] + -1;
  param_3[2] = iVar2;
  if (iVar2 < 0) {
    if ((int)param_3[6] <= iVar2) {
      if (param_2 != 10) goto LAB_ram_00008ac0;
    }
    uVar1 = FUN_ram_00007ac2(param_1);
    return uVar1;
  }
LAB_ram_00008ac0:
  pbVar3 = (byte *)*param_3;
  *param_3 = pbVar3 + 1;
  *pbVar3 = param_2;
  return (uint)param_2;
}

