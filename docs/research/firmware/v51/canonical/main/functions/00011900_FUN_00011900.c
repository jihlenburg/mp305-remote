/* Address: 00011900; name: FUN_00011900; body bytes: 784 */

void FUN_00011900(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  
  iVar6 = FUN_00015ed4();
  cVar1 = *(char *)(iVar6 + 4);
  if (cVar1 == -0x4f) {
    DAT_1fff9b9d = *(undefined1 *)(iVar6 + 5);
    DAT_1fff9b9e = *(undefined1 *)(iVar6 + 6);
    DAT_1fff9b9c = *(undefined1 *)(iVar6 + 7);
    DAT_1fff9b9b = *(undefined1 *)(iVar6 + 9);
    DAT_1fff9b94 = *(byte *)(iVar6 + 10);
    DAT_1fff9b95 = *(undefined1 *)(iVar6 + 0xb);
    DAT_1fff9b54 = *(undefined2 *)(iVar6 + 0xc);
    DAT_1fff9b56 = *(undefined2 *)(iVar6 + 0xe);
    DAT_1fff9b58 = *(undefined2 *)(iVar6 + 0x10);
    DAT_1fff9b5c = *(undefined2 *)(iVar6 + 0x12);
    DAT_1fff9b5a = *(undefined2 *)(iVar6 + 0x14);
    DAT_1fff9b5e = *(undefined2 *)(iVar6 + 0x16);
    DAT_1fff9ba1 = *(undefined1 *)(iVar6 + 0x18);
    DAT_1fff9ba2 = *(undefined1 *)(iVar6 + 0x19);
    DAT_1fff9b99 = 1;
    DAT_1fff9b9a = *(char *)(iVar6 + 8);
  }
  else if (cVar1 == '\x01') {
    DAT_1fff9b91 = *(char *)(iVar6 + 5);
    DAT_1fff9b92 = *(undefined1 *)(iVar6 + 6);
    if (DAT_1fff9b91 != '\0') {
      DAT_1fff9b98 = 1;
    }
  }
  else if (cVar1 == -0x49) {
    cVar1 = *(char *)(iVar6 + 6);
    if (*(char *)(iVar6 + 5) != '\0') {
      return;
    }
    DAT_1fff9b96 = 1;
    DAT_1fff9b9a = cVar1;
    if (cVar1 == '\x01') {
      DAT_1fff9b94 = *(byte *)(iVar6 + 7);
      DAT_1fff9b95 = *(undefined1 *)(iVar6 + 8);
      uVar8 = 5;
      for (iVar7 = 0; iVar7 < (int)(uint)DAT_1fff9b94; iVar7 = (int)(short)((short)iVar7 + 1)) {
        iVar11 = iVar6 + uVar8;
        uVar9 = uVar8 + 1 & 0xff;
        uVar8 = uVar9 + 1 & 0xff;
        uVar10 = uVar8 + 1 & 0xff;
        uVar2 = *(undefined1 *)(iVar6 + uVar8 + 4);
        uVar3 = *(undefined1 *)(iVar6 + uVar10 + 4);
        uVar8 = uVar10 + 1 & 0xff;
        (&DAT_1fff9b60)[iVar7] =
             CONCAT11(*(undefined1 *)(iVar6 + uVar9 + 4),*(undefined1 *)(iVar11 + 4));
        (&DAT_1fff9b70)[iVar7] = CONCAT11(uVar3,uVar2);
      }
    }
  }
  else if (cVar1 == -0x4b) {
    bVar4 = *(byte *)(iVar6 + 5);
    uVar8 = (uint)bVar4;
    if ((uVar8 == 0) || (uVar8 == 1)) {
      (&DAT_1fff9b9a)[uVar8] = *(undefined1 *)(iVar6 + 6);
      bVar5 = *(byte *)(iVar6 + 7);
      (&DAT_1fff9b58)[uVar8] = (ushort)bVar5;
      DAT_1fff9b97 = bVar4 + 1;
      (&DAT_1fff9b58)[uVar8] = CONCAT11(*(undefined1 *)(iVar6 + 8),bVar5);
      bVar4 = *(byte *)(iVar6 + 9);
      (&DAT_1fff9b5c)[uVar8] = (ushort)bVar4;
      (&DAT_1fff9b5c)[uVar8] = CONCAT11(*(undefined1 *)(iVar6 + 10),bVar4);
      DAT_1fff9ba1 = *(undefined1 *)(iVar6 + 0xb);
      DAT_1fff9ba2 = *(undefined1 *)(iVar6 + 0xc);
    }
  }
  else if (cVar1 == -0x43) {
    if (DAT_1fffaaf6 == '\x01') {
      DAT_1fffaaf6 = '\0';
      DAT_1fff9ba3 = 1;
    }
  }
  else if (cVar1 == -0x1b) {
    DAT_1fff9b90 = *(char *)(iVar6 + 5);
    if (DAT_1fff9b90 == '\0') {
      DAT_1fff9b50 = 0;
      DAT_1fff9b8f = 0;
      DAT_1fff9b80 = 0;
      DAT_1fff9b82 = 0;
      DAT_1fff9b84 = 0;
      DAT_1fff9b86 = 0;
      DAT_1fff9b8a = 0;
      DAT_1fff9b8c = 0;
      DAT_1fff9b38 = 0;
      DAT_1fff9b8e = 0;
      DAT_1fff9b3c = 0;
      DAT_1fff9b40 = 0;
      DAT_1fff9b44 = 0;
      DAT_1fff9b48 = 0;
      DAT_1fff9b4c = 0;
    }
    else {
      DAT_1fff9b8f = *(undefined1 *)(iVar6 + 6);
      DAT_1fff9b80 = *(undefined2 *)(iVar6 + 7);
      DAT_1fff9b82 = *(undefined2 *)(iVar6 + 9);
      DAT_1fff9b84 = *(undefined2 *)(iVar6 + 0xb);
      DAT_1fff9b86 = *(undefined2 *)(iVar6 + 0xd);
      DAT_1fff9b8a = *(undefined2 *)(iVar6 + 0xf);
      DAT_1fff9b8c = *(undefined2 *)(iVar6 + 0x11);
      DAT_1fff9b38 = *(undefined4 *)(iVar6 + 0x13);
      DAT_1fff9b8e = *(undefined1 *)(iVar6 + 0x17);
      DAT_1fff9b3c = *(undefined4 *)(iVar6 + 0x18);
      DAT_1fff9b40 = *(undefined4 *)(iVar6 + 0x1c);
      DAT_1fff9b44 = *(undefined4 *)(iVar6 + 0x20);
      DAT_1fff9b48 = *(undefined4 *)(iVar6 + 0x24);
      DAT_1fff9b4c = *(undefined4 *)(iVar6 + 0x28);
      DAT_1fff9b50 = *(undefined4 *)(iVar6 + 0x2c);
    }
    DAT_1fff9ba4 = 1;
  }
  DAT_1fff9b34 = 0;
  return;
}

