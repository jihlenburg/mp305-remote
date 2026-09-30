/* Address: ram:00045118; name: FUN_ram_00045118; body bytes: 154 */

int FUN_ram_00045118(uint param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  byte *pbVar2;
  
  gp = 0x20004000;
  if (param_2 == 0xfffe) {
    if ((DAT_ram_200019ec != (undefined4 *)0x0) && ((code *)*DAT_ram_200019ec != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00045146. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      iVar1 = (*(code *)*DAT_ram_200019ec)();
      return iVar1;
    }
    return 0x12;
  }
  if (param_2 != 0xffff) {
    pbVar2 = (byte *)FUN_ram_0004df14(param_2);
    if (pbVar2 == (byte *)0x0) {
      gp = 0x20004000;
      return 0x12;
    }
    if (*pbVar2 != param_1) {
      gp = 0x20004000;
      return 3;
    }
    iVar1 = thunk_FUN_ram_0006512c(param_2,param_3);
    return iVar1;
  }
  if ((DAT_ram_200019ec != (undefined4 *)0x0) && ((code *)*DAT_ram_200019ec != (code *)0x0)) {
    iVar1 = (*(code *)*DAT_ram_200019ec)();
    if (iVar1 == 0) goto LAB_ram_00045170;
  }
  iVar1 = FUN_ram_00043e98(param_1,param_3);
  if (iVar1 != 0) {
    gp = 0x20004000;
    return iVar1;
  }
LAB_ram_00045170:
  DAT_ram_20001a01 = (char)param_3;
  DAT_ram_20001a00 = (char)param_1;
  return 0;
}

