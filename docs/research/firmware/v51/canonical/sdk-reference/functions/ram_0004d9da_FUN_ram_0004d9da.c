/* Address: ram:0004d9da; name: FUN_ram_0004d9da; body bytes: 138 */

undefined4 FUN_ram_0004d9da(int param_1,short *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if ((3 < (ushort)(*param_2 - 4U)) || (*(int *)(param_2 + 2) == 0)) {
    return 2;
  }
  iVar1 = linkDB_State(param_1,1);
  if (iVar1 == 0) {
    uVar2 = 0x14;
  }
  else {
    iVar1 = FUN_ram_0004e066(param_1);
    if ((((param_1 == 0xfffe) || (iVar1 != 0)) || (param_2[1] == 0)) ||
       ((*param_2 == 6 && ((ushort)param_2[1] < DAT_ram_20001a5e)))) {
      if (DAT_ram_20001a62 != '\0') {
        uVar2 = FUN_ram_0004d656();
        return uVar2;
      }
      uVar2 = FUN_ram_0004d412(param_1,param_2);
      return uVar2;
    }
    uVar2 = 0x1b;
  }
  return uVar2;
}

