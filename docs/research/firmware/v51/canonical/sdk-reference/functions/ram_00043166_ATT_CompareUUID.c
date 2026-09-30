/* Address: ram:00043166; name: ATT_CompareUUID; body bytes: 102 */

undefined4 ATT_CompareUUID(undefined1 *param_1,int param_2,undefined1 *param_3,int param_4)

{
  undefined4 uVar1;
  undefined1 auStack_20 [20];
  
  gp = 0x20004000;
  if (param_2 == 2) {
    if (param_4 != 2) {
      if (param_4 != 0x10) {
        gp = 0x20004000;
        return 0;
      }
      FUN_ram_00043120(param_1,auStack_20);
      param_2 = 0x10;
      param_1 = param_3;
      param_3 = auStack_20;
    }
  }
  else {
    if (param_2 != 0x10) {
      gp = 0x20004000;
      return 0;
    }
    if (param_4 == 2) {
      FUN_ram_00043120(param_3,auStack_20);
      param_2 = 0x10;
      param_3 = auStack_20;
    }
    else if (param_4 != 0x10) {
      gp = 0x20004000;
      return 0;
    }
  }
  uVar1 = tmos_memcmp(param_1,param_3,param_2);
  return uVar1;
}

