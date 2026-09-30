/* Address: 0005d148; name: FUN_0005d148; body bytes: 350 */

void FUN_0005d148(int param_1)

{
  bool bVar1;
  char cVar2;
  undefined1 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  undefined1 auStack_d4 [48];
  undefined4 local_a4;
  undefined1 auStack_80 [48];
  undefined4 local_50;
  undefined1 auStack_3c [8];
  undefined1 auStack_34 [16];
  
  uVar11 = *(ushort *)(param_1 + 0x48) & 0x7fff;
  if (((1 < uVar11) && (*(char *)(param_1 + 0x3c) != '\x10')) && (*(char *)(param_1 + 0x3c) != '\b')
     ) {
    FUN_00042462(auStack_80);
    FUN_0004cff4(param_1,0x20000,auStack_80);
    FUN_00042462(auStack_d4);
    FUN_0004cff4(param_1,&LAB_00050000,auStack_d4);
    for (uVar10 = 0; uVar10 < uVar11; uVar10 = uVar10 + 1) {
      uVar4 = (*(uint *)(param_1 + 0x48) & 0x3fffffff) >> 0xf;
      bVar1 = uVar10 == uVar4 * (uVar10 / uVar4);
      iVar5 = FUN_0004a388(uVar10,0,uVar11 - 1,*(undefined4 *)(param_1 + 0x40),
                           *(undefined4 *)(param_1 + 0x44));
      iVar6 = param_1 + 0x2c;
      for (iVar7 = FUN_0004a14a(); iVar7 != 0; iVar7 = FUN_0004a144(iVar6,iVar7)) {
        if ((*(int *)(iVar7 + 0xc) <= iVar5) && (iVar5 <= *(int *)(iVar7 + 0x10))) {
          if (bVar1) {
            puVar9 = (undefined1 *)0x20000;
            puVar3 = &stack0x0000003c;
            uVar8 = *(undefined4 *)(iVar7 + 4);
          }
          else {
            uVar8 = *(undefined4 *)(iVar7 + 8);
            puVar9 = &LAB_00050000;
            puVar3 = &stack0xffffffe8;
          }
          FUN_0005df30(param_1,puVar3 + -0xbc,uVar8,puVar9);
          break;
        }
        FUN_0004cff4(param_1,0x20000,auStack_80);
        FUN_0004cff4(param_1,&LAB_00050000,auStack_d4);
      }
      FUN_0005db06(param_1,uVar10,bVar1,auStack_3c,auStack_34);
      bVar12 = (*(ushort *)(param_1 + 0x48) & 0x7fff) != uVar10;
      uVar8 = local_a4;
      if (bVar1) {
        uVar8 = local_50;
      }
      if (((!bVar12 || uVar10 == 0) && (cVar2 = *(char *)(param_1 + 0x3c), cVar2 != '\b')) &&
         (cVar2 != '\x10')) {
        if (bVar12) {
          if ((cVar2 == '\x02') || (cVar2 == '\x04')) goto LAB_0005d274;
        }
        else if ((cVar2 != '\x02') && (cVar2 != '\x04')) {
LAB_0005d274:
          *(undefined4 *)(param_1 + 0x60) = uVar8;
          goto LAB_0005d276;
        }
        *(undefined4 *)(param_1 + 0x5c) = uVar8;
      }
LAB_0005d276:
      FUN_0005dfdc(param_1,bVar1,auStack_80,auStack_d4,iVar5,uVar10 & 0xff,auStack_3c);
    }
  }
  return;
}

