/* Address: ram:0004ef4c; name: FUN_ram_0004ef4c; body bytes: 230 */

int FUN_ram_0004ef4c(int param_1,int param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  int iVar7;
  uint uVar8;
  undefined1 auStack_48 [8];
  undefined1 auStack_40 [28];
  
  gp = 0x20004000;
  iVar7 = 2;
  if ((param_1 != 0) && (param_3 != (undefined1 *)0x0)) {
    uVar8 = param_2 + 4U & 0xffff;
    puVar3 = (undefined1 *)FUN_ram_20000040(uVar8,0x53);
    iVar7 = 0x13;
    if (puVar3 != (undefined1 *)0x0) {
      uVar4 = FUN_ram_000443d6();
      uVar1 = (undefined1)((uint)uVar4 >> 8);
      uVar2 = (undefined1)((uint)uVar4 >> 0x10);
      FUN_ram_20000298(puVar3 + 4,param_1,param_2);
      puVar3[3] = (char)uVar4;
      puVar3[2] = uVar1;
      puVar3[1] = uVar2;
      uVar6 = (undefined1)((uint)uVar4 >> 0x18);
      *puVar3 = uVar6;
      uVar5 = FUN_ram_000443cc();
      FUN_ram_20000298(auStack_40,uVar5,0x10);
      iVar7 = FUN_ram_00051598(auStack_40,puVar3,uVar8,auStack_48,8);
      if (iVar7 == 0) {
        *param_3 = (char)uVar4;
        param_3[1] = uVar1;
        param_3[2] = uVar2;
        param_3[3] = uVar6;
        FUN_ram_20000298(param_3 + 4,auStack_48,8);
        FUN_ram_000443e2();
      }
      FUN_ram_20000104(puVar3);
    }
  }
  return iVar7;
}

