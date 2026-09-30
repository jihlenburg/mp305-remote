/* Address: ram:0004d0a0; name: FUN_ram_0004d0a0; body bytes: 248 */

void FUN_ram_0004d0a0(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  byte bStack_24;
  undefined1 uStack_23;
  ushort uStack_22;
  undefined4 auStack_20 [2];
  ushort uStack_18;
  ushort uStack_16;
  int iStack_14;
  
  gp = 0x20004000;
  uVar1 = *(undefined2 *)(param_1 + 2);
  iVar2 = FUN_ram_0004cd62(&uStack_18,param_1);
  if (iStack_14 == 0) {
    if (iVar2 == 0) goto LAB_ram_0004d0bc;
  }
  else {
    uVar3 = (uint)uStack_18;
    if (uVar3 == 5) {
      if (3 < uStack_16) {
        FUN_ram_0004cd40(&bStack_24);
        if (0x17 < uStack_22) {
          auStack_20[0] = 0x170001;
          FUN_ram_0004ddcc(uVar1,uStack_23,auStack_20);
        }
        if ((uint)uStack_16 != uStack_22 + 4) {
          FUN_ram_0004c746(uVar1);
        }
        if ((bStack_24 & 1) == 0) {
          iVar2 = FUN_ram_0004cdee(uVar1,&bStack_24,iStack_14 + 4);
        }
        else {
          iVar2 = FUN_ram_0004cf50();
        }
        if (iVar2 != 0) {
          FUN_ram_0004c746(uVar1);
        }
      }
    }
    else if ((uVar3 == 4) || ((uVar3 - 6 & 0xffff) < 2)) {
      iVar2 = (uVar3 - 4) * 0xc;
      if ((*(short *)(&DAT_ram_20001ccc + iVar2) != 0) &&
         (iVar2 = FUN_ram_0004d198((&DAT_ram_20001cce)[iVar2],uVar1,&uStack_18), iVar2 == 0)) {
        if (uStack_18 == 4) {
          gp = 0x20004000;
          return;
        }
        goto LAB_ram_0004d0bc;
      }
    }
    else {
      iVar2 = FUN_ram_0004d4e2(uVar1,&uStack_18);
      if (iVar2 == 0) {
        gp = 0x20004000;
        return;
      }
    }
  }
  if (*(int *)(param_1 + 8) != 0) {
    FUN_ram_20000104();
  }
LAB_ram_0004d0bc:
  FUN_ram_0004c756(uVar1,1);
  return;
}

