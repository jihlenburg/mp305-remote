/* Address: ram:0004e484; name: FUN_ram_0004e484; body bytes: 160 */

undefined4
FUN_ram_0004e484(undefined4 param_1,int param_2,undefined2 param_3,int param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 auStack_2c [2];
  undefined1 auStack_28 [12];
  
  gp = 0x20004000;
  iVar2 = FUN_ram_20000040(0x10,0x53);
  uVar1 = 0x13;
  if (iVar2 != 0) {
    uVar1 = 2;
    if (param_2 != 0) {
      auStack_2c[0] = param_3;
      tmos_memset(iVar2,0,0x10);
      tmos_memcpy(iVar2,param_2,param_5);
      if (param_4 == 0) {
        tmos_memset(auStack_28,0,8);
      }
      else {
        tmos_memcpy(auStack_28,param_4);
      }
      uVar1 = FUN_ram_0005255e(param_1,auStack_28,auStack_2c,iVar2);
    }
    FUN_ram_20000104(iVar2);
  }
  return uVar1;
}

