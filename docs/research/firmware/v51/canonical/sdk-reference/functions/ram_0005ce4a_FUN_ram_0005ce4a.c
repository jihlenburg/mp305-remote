/* Address: ram:0005ce4a; name: FUN_ram_0005ce4a; body bytes: 148 */

undefined4 FUN_ram_0005ce4a(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  int iVar7;
  undefined4 uVar8;
  char cVar9;
  int iVar10;
  undefined1 uVar11;
  
  gp = 0x20004000;
  iVar7 = FUN_ram_00057ba2();
  if (iVar7 == 0) {
    uVar8 = 2;
  }
  else {
    cVar9 = *(char *)(iVar7 + 0xb);
    if (cVar9 == '\x01') {
      if (DAT_ram_20001dc0 == 0) {
        gp = 0x20004000;
        return 2;
      }
      uVar11 = *(undefined1 *)(iVar7 + 0x2f);
      uVar1 = *(undefined1 *)(DAT_ram_20001dc0 + 0x45);
      uVar3 = *(undefined2 *)(iVar7 + 0x3c);
      uVar4 = *(undefined2 *)(iVar7 + 0x3a);
      uVar5 = *(undefined2 *)(iVar7 + 0x38);
      uVar6 = *(undefined2 *)(iVar7 + 8);
      uVar2 = *(undefined1 *)(iVar7 + 0x2a);
      iVar10 = DAT_ram_20001dc0 + 0x46;
      cVar9 = '\x01';
    }
    else {
      if (DAT_ram_20001de8 == 0) {
        gp = 0x20004000;
        return 2;
      }
      uVar1 = *(undefined1 *)(DAT_ram_20001de8 + 0x75);
      uVar3 = *(undefined2 *)(iVar7 + 0x3c);
      uVar4 = *(undefined2 *)(iVar7 + 0x3a);
      uVar5 = *(undefined2 *)(iVar7 + 0x38);
      uVar6 = *(undefined2 *)(iVar7 + 8);
      uVar2 = *(undefined1 *)(iVar7 + 0x2a);
      iVar10 = DAT_ram_20001de8 + 0x76;
      uVar11 = 0;
    }
    FUN_ram_00068284(uVar2,uVar6,cVar9,uVar1,iVar10,uVar5,uVar4,uVar3,uVar11);
    *(undefined1 *)(iVar7 + 0x2a) = 0;
    uVar8 = 0;
    *(byte *)(iVar7 + 0xf) = *(byte *)(iVar7 + 0xf) | 1;
  }
  return uVar8;
}

