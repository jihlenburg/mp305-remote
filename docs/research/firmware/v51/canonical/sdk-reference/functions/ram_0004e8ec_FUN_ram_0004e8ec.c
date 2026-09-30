/* Address: ram:0004e8ec; name: FUN_ram_0004e8ec; body bytes: 180 */

void FUN_ram_0004e8ec(undefined2 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 auStack_80 [8];
  undefined1 auStack_78 [8];
  undefined1 auStack_70 [76];
  
  gp = 0x20004000;
  if (param_1 != (undefined2 *)0x0) {
    iVar1 = FUN_ram_0004df14(*param_1);
    if (iVar1 != 0) {
      FUN_ram_0004e85c(param_1,auStack_70);
      iVar4 = iVar1 + 6;
      if (*(char *)(param_1 + 1) == '\0') {
        uVar5 = FUN_ram_000443b8();
        uVar2 = (uint)*(byte *)(iVar1 + 5);
        iVar1 = FUN_ram_00044398(0);
        FUN_ram_0004fffa(*(undefined4 *)(param_1 + 0x14),auStack_80);
        FUN_ram_00050004(auStack_70,auStack_78);
      }
      else {
        uVar2 = FUN_ram_000443b8();
        uVar5 = (uint)*(byte *)(iVar1 + 5);
        iVar3 = FUN_ram_00044398(0);
        FUN_ram_0004fffa(auStack_70,auStack_80);
        FUN_ram_00050004(*(undefined4 *)(param_1 + 0x14),auStack_78);
        iVar1 = iVar4;
        iVar4 = iVar3;
      }
      FUN_ram_000513be(param_2,param_3,auStack_78,auStack_80,uVar2,iVar4,uVar5,iVar1,param_4);
    }
    return;
  }
  return;
}

