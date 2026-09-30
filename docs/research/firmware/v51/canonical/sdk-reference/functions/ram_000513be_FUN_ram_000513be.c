/* Address: ram:000513be; name: FUN_ram_000513be; body bytes: 324 */

int FUN_ram_000513be(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    int param_5,undefined4 param_6,int param_7,undefined4 param_8,undefined4 param_9
                    )

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_50 [7];
  undefined1 auStack_49 [7];
  undefined1 uStack_42;
  undefined1 uStack_41;
  undefined1 auStack_40 [4];
  undefined1 auStack_3c [6];
  undefined1 auStack_36 [14];
  
  gp = 0x20004000;
  iVar2 = FUN_ram_20000040(0x30,0x53);
  if (iVar2 == 0) {
    iVar3 = 0x13;
  }
  else {
    tmos_memset(iVar2,0,0x30);
    FUN_ram_20000298(iVar2,param_1,0x10);
    tmos_memset(auStack_50,0,0x10);
    FUN_ram_20000298(auStack_50,param_3,7);
    FUN_ram_20000298(auStack_49,param_4,7);
    uStack_42 = param_7 != 0;
    uStack_41 = param_5 != 0;
    tmos_memset(auStack_40,0,0x10);
    FUN_ram_20000298(auStack_3c,param_6,6);
    FUN_ram_20000298(auStack_36,param_8,6);
    iVar1 = iVar2 + 0x10;
    FUN_ram_20000298(iVar1,param_2,0x10);
    FUN_ram_0005130a(iVar1,auStack_50);
    iVar4 = iVar2 + 0x20;
    iVar3 = LL_Encrypt(iVar2,iVar1,iVar4);
    if (iVar3 == 0) {
      tmos_memcpy(iVar1,iVar4,0x10);
      FUN_ram_0005130a(iVar1,auStack_40);
      iVar3 = LL_Encrypt(iVar2,iVar1,iVar4);
      FUN_ram_20000298(param_9,iVar4,0x10);
    }
    FUN_ram_20000104(iVar2);
  }
  return iVar3;
}

