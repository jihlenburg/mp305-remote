/* Address: ram:00069a36; name: FUN_ram_00069a36; body bytes: 138 */

void FUN_ram_00069a36(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uStack_18;
  undefined2 uStack_14;
  
  gp = 0x20004000;
  uStack_18 = 0;
  uStack_14 = 0;
  iVar1 = FUN_ram_0004df14();
  if ((iVar1 != 0) && (DAT_ram_200019c7 != '\x02')) {
    uVar2 = FUN_ram_00069942(*(undefined1 *)(iVar1 + 5),iVar1 + 6,&uStack_18);
    if (uVar2 < DAT_ram_20001a8d) {
      uVar3 = FUN_ram_00068a5c();
      FUN_ram_00068ea8(param_1,uVar2,uVar3,8,1);
    }
    else if (DAT_ram_200019c7 == '\0') {
      FUN_ram_000450ea(param_1,5);
    }
    else if (DAT_ram_200019c7 == '\x01') {
      FUN_ram_00068f1c(param_1,*(undefined1 *)(iVar1 + 5),0);
    }
  }
  return;
}

