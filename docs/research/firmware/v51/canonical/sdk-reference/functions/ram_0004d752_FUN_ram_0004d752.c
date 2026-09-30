/* Address: ram:0004d752; name: FUN_ram_0004d752; body bytes: 118 */

undefined4 FUN_ram_0004d752(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 uStack_18;
  undefined2 uStack_16;
  int iStack_14;
  
  gp = 0x20004000;
  iVar2 = (param_1 + -4) * 0xc;
  iStack_14 = *(int *)(&DAT_ram_20001cd0 + iVar2);
  if (iStack_14 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
    if (DAT_ram_20001a62 != '\0') {
      uStack_18 = (undefined2)param_1;
      uStack_16 = *(undefined2 *)(&DAT_ram_20001cd4 + iVar2);
      iVar1 = FUN_ram_0004d656(*(undefined2 *)(&DAT_ram_20001cd6 + iVar2),&uStack_18);
      if (iVar1 != 0) {
        FUN_ram_20000104(*(undefined4 *)(&DAT_ram_20001cd0 + iVar2));
      }
      *(undefined4 *)(&DAT_ram_20001cd0 + (param_1 + -4) * 0xc) = 0;
      uVar3 = 1;
    }
  }
  return uVar3;
}

