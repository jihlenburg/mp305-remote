/* Address: 0001fc94; name: FUN_0001fc94; body bytes: 184 */

bool FUN_0001fc94(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte *unaff_r4;
  int iVar7;
  bool bVar8;
  byte local_98 [128];
  
  bVar8 = false;
  iVar7 = 0;
  if (*(char *)(param_1 + 1) == '\0') {
    unaff_r4 = (byte *)(param_1 + 6);
    iVar7 = (uint)*(byte *)(param_1 + 2) + (uint)*(byte *)(param_1 + 3) * 0x100 +
            (uint)*(byte *)(param_1 + 4) * 0x10000 + (uint)*(byte *)(param_1 + 5) * 0x1000000;
  }
  uVar3 = 0;
  do {
    uVar1 = uVar3 + 1;
    (&DAT_1fffa020)[uVar3] =
         (uint)*unaff_r4 + (uint)unaff_r4[1] * 0x100 + (uint)unaff_r4[2] * 0x10000 +
         (uint)unaff_r4[3] * 0x1000000;
    uVar3 = uVar1;
    unaff_r4 = unaff_r4 + 4;
  } while (uVar1 < 0x20);
  iVar2 = FUN_0001bf3a(iVar7,&DAT_1fffa020,0x80);
  if (iVar2 != 0) {
    uVar1 = 0;
    FUN_0001bef8(iVar7,local_98,0x80);
    bVar8 = *(byte *)(param_1 + 6) == local_98[0];
    uVar3 = 0;
    do {
      uVar4 = uVar1 + 1 & 0xff;
      uVar3 = uVar3 + 1;
      uVar5 = uVar4 + 1 & 0xff;
      uVar6 = uVar5 + 1 & 0xff;
      DAT_1fffa01c = (uint)local_98[uVar1] + DAT_1fffa01c + (uint)local_98[uVar4] * 0x100 +
                     (uint)local_98[uVar5] * 0x10000 + (uint)local_98[uVar6] * 0x1000000;
      uVar1 = uVar6 + 1 & 0xff;
    } while (uVar3 < 0x20);
  }
  return bVar8;
}

