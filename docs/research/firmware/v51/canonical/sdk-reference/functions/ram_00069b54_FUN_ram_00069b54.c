/* Address: ram:00069b54; name: FUN_ram_00069b54; body bytes: 130 */

undefined4 FUN_ram_00069b54(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  gp = 0x20004000;
  if (param_1 == 0xffff) {
    uVar2 = 0x15;
    for (bVar1 = 0; bVar1 < DAT_ram_20001a8d; bVar1 = bVar1 + 1) {
      iVar3 = FUN_ram_000693cc(bVar1,param_2,param_3);
      if (iVar3 != 0) {
        uVar2 = 0;
      }
    }
  }
  else {
    iVar3 = FUN_ram_0004df14();
    uVar2 = 0x14;
    if (iVar3 != 0) {
      uVar2 = 0x15;
      uVar4 = FUN_ram_00069942(*(undefined1 *)(iVar3 + 5),iVar3 + 6,0);
      if (uVar4 < DAT_ram_20001a8d) {
        FUN_ram_000693cc(uVar4,param_2,param_3);
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}

