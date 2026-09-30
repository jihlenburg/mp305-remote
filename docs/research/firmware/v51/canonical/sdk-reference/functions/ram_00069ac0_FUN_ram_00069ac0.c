/* Address: ram:00069ac0; name: FUN_ram_00069ac0; body bytes: 148 */

undefined4 FUN_ram_00069ac0(int param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  gp = 0x20004000;
  if (param_1 == 0xffff) {
    uVar2 = 0x15;
    for (bVar1 = 0; bVar1 < DAT_ram_20001a8d; bVar1 = bVar1 + 1) {
      iVar3 = FUN_ram_00069350(bVar1,param_2);
      if (iVar3 != 0) {
        uVar2 = 0;
      }
    }
    if (param_2 != 0) {
      linkDB_PerformFunc(FUN_ram_00068e98);
    }
  }
  else {
    iVar3 = FUN_ram_0004df14();
    uVar2 = 0x14;
    if (iVar3 != 0) {
      uVar2 = 0x15;
      uVar4 = FUN_ram_00069942(*(undefined1 *)(iVar3 + 5),iVar3 + 6,0);
      if (uVar4 < DAT_ram_20001a8d) {
        FUN_ram_00069350(uVar4,param_2);
        uVar2 = 0;
      }
      if (param_2 != 0) {
        FUN_ram_00068e98(iVar3);
      }
    }
  }
  return uVar2;
}

