/* Address: 0001fc86; name: FUN_0001fc86; body bytes: 14 */

bool FUN_0001fc86(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte *unaff_r4;
  int iVar8;
  bool bVar9;
  byte abStack_98 [128];
  
  FUN_0001fc0c(0x1234);
  iVar1 = FUN_0001feb8();
  bVar9 = false;
  iVar8 = 0;
  if (*(char *)(iVar1 + 1) == '\0') {
    unaff_r4 = (byte *)(iVar1 + 6);
    iVar8 = (uint)*(byte *)(iVar1 + 2) + (uint)*(byte *)(iVar1 + 3) * 0x100 +
            (uint)*(byte *)(iVar1 + 4) * 0x10000 + (uint)*(byte *)(iVar1 + 5) * 0x1000000;
  }
  uVar4 = 0;
  do {
    uVar2 = uVar4 + 1;
    (&DAT_1fffa020)[uVar4] =
         (uint)*unaff_r4 + (uint)unaff_r4[1] * 0x100 + (uint)unaff_r4[2] * 0x10000 +
         (uint)unaff_r4[3] * 0x1000000;
    uVar4 = uVar2;
    unaff_r4 = unaff_r4 + 4;
  } while (uVar2 < 0x20);
  iVar3 = FUN_0001bf3a(iVar8,&DAT_1fffa020,0x80);
  if (iVar3 != 0) {
    uVar2 = 0;
    FUN_0001bef8(iVar8,abStack_98,0x80);
    bVar9 = *(byte *)(iVar1 + 6) == abStack_98[0];
    uVar4 = 0;
    do {
      uVar5 = uVar2 + 1 & 0xff;
      uVar4 = uVar4 + 1;
      uVar6 = uVar5 + 1 & 0xff;
      uVar7 = uVar6 + 1 & 0xff;
      DAT_1fffa01c = (uint)abStack_98[uVar2] + DAT_1fffa01c + (uint)abStack_98[uVar5] * 0x100 +
                     (uint)abStack_98[uVar6] * 0x10000 + (uint)abStack_98[uVar7] * 0x1000000;
      uVar2 = uVar7 + 1 & 0xff;
    } while (uVar4 < 0x20);
  }
  return bVar9;
}

