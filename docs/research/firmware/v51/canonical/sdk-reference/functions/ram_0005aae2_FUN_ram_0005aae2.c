/* Address: ram:0005aae2; name: FUN_ram_0005aae2; body bytes: 216 */

undefined4 FUN_ram_0005aae2(int param_1)

{
  undefined1 uVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  char cVar5;
  ushort uVar6;
  int iVar7;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 0xc;
  iVar7 = *(int *)(param_1 + 0x110);
  if (iVar7 != 0) {
    *(undefined1 *)(param_1 + 0x53) = 2;
    uVar6 = *(ushort *)(param_1 + 0x3e);
    if (((uint)*(ushort *)(param_1 + 0x5c) < (uint)uVar6) ||
       ((int)((uint)*(ushort *)(param_1 + 0x5c) - (uint)uVar6) <=
        (int)(*(ushort *)(param_1 + 0x5e) + 5))) {
      cVar5 = '\x04';
      if (DAT_ram_20001e04 < 4) {
        cVar5 = (char)DAT_ram_20001e04 + '\x01';
      }
      *(char *)(param_1 + 0x53) = cVar5;
      *(ushort *)(param_1 + 0x5c) = uVar6 + *(ushort *)(param_1 + 0x5e) + 8;
    }
    *(undefined1 *)(iVar7 + 2) = 0;
    *(undefined1 *)(iVar7 + 3) = *(undefined1 *)(param_1 + 0x53);
    sVar2 = *(short *)(param_1 + 0x56);
    sVar3 = *(short *)(param_1 + 0x58);
    *(undefined1 *)(iVar7 + 4) = *(undefined1 *)(param_1 + 0x54);
    uVar1 = *(undefined1 *)(param_1 + 0x55);
    *(char *)(iVar7 + 6) = (char)sVar2;
    *(char *)(iVar7 + 8) = (char)sVar3;
    *(undefined1 *)(iVar7 + 5) = uVar1;
    *(char *)(iVar7 + 7) = (char)((ushort)sVar2 >> 8);
    *(char *)(iVar7 + 9) = (char)((ushort)sVar3 >> 8);
    sVar4 = *(short *)(param_1 + 0x5a);
    *(char *)(iVar7 + 10) = (char)sVar4;
    *(char *)(iVar7 + 0xb) = (char)((ushort)sVar4 >> 8);
    *(undefined1 *)(iVar7 + 0xc) = *(undefined1 *)(param_1 + 0x5c);
    *(undefined1 *)(iVar7 + 0xd) = *(undefined1 *)(param_1 + 0x5d);
    uVar6 = 0;
    if ((*(short *)(param_1 + 0x38) == sVar2) && (*(short *)(param_1 + 0x3a) == sVar3)) {
      uVar6 = (ushort)(*(short *)(param_1 + 0x3c) == sVar4);
    }
    *(ushort *)(param_1 + 0x60) = uVar6;
    *(undefined1 *)(param_1 + 0x10) = 0x10;
    return 0;
  }
  return 1;
}

