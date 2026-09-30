/* Address: 0004cda6; name: FUN_0004cda6; body bytes: 86 */

uint FUN_0004cda6(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 auStack_28 [16];
  undefined4 local_18;
  byte local_14;
  
  iVar1 = FUN_0004cd84(param_1,2);
  uVar2 = 0;
  if (iVar1 != 0) {
    FUN_0004ba8e(param_1,auStack_28);
    uVar2 = FUN_0003dcb8(auStack_28,param_2,0);
    if (uVar2 == 0) {
      uVar2 = 0;
    }
    else {
      iVar1 = FUN_0004cd84(param_1,0x10000);
      if (iVar1 != 0) {
        local_14 = 1;
        local_18 = param_2;
        FUN_0004e5a6(param_1,0x13,&local_18);
        uVar2 = (uint)local_14;
      }
    }
  }
  return uVar2;
}

