/* Address: 00054818; name: FUN_00054818; body bytes: 66 */

void FUN_00054818(uint param_1)

{
  undefined4 uVar1;
  
  if (DAT_1ffe0266 != param_1) {
    if (param_1 != 0) {
      if (DAT_1ffe0330 != 0) {
        FUN_0001ba58();
        return;
      }
      uVar1 = FUN_00015a5c(0x58);
      FUN_0001d100(0,uVar1);
      uVar1 = FUN_0004b9de(DAT_1ffe0474,0);
      FUN_00047d8e(uVar1,&DAT_00082c74);
    }
    DAT_1ffe0266 = (byte)param_1;
  }
  return;
}

