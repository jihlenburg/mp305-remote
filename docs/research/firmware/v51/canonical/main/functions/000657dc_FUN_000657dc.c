/* Address: 000657dc; name: FUN_000657dc; body bytes: 136 */

uint FUN_000657dc(void)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined4 unaff_r4;
  uint *puVar9;
  uint *puVar10;
  
  uVar3 = FUN_00015a0a();
  puVar2 = DAT_1ffe0224;
  if (uVar3 != 0) {
    return uVar3;
  }
  if (DAT_1ffe0224 == (uint *)0x0) {
    return 0;
  }
  uVar3 = 0;
  puVar10 = DAT_1ffe0224 + 3;
  FUN_00065c04();
  *puVar2 = *puVar2 | 1;
  puVar9 = (uint *)puVar2[4];
LAB_00066540:
  do {
    puVar4 = puVar9;
    if (puVar4 == puVar10) {
      *puVar2 = *puVar2 & ~uVar3;
      FUN_00066f6c();
      return *puVar2;
    }
    puVar9 = (uint *)puVar4[1];
    uVar6 = *puVar4 & 0xff000000;
    uVar8 = *puVar2;
    uVar5 = *puVar4 & 0xffffff;
    if ((int)(uVar6 << 5) < 0) goto LAB_00066528;
  } while ((uVar8 & uVar5) == 0);
  goto LAB_0006652e;
LAB_00066528:
  uVar1 = ~uVar8;
  uVar8 = 0;
  if ((uVar5 & uVar1) == 0) {
LAB_0006652e:
    iVar7 = uVar6 << 7;
    if (iVar7 < 0) {
      uVar3 = uVar3 | uVar5;
    }
    FUN_00065b08(puVar4,*puVar2 | 0x2000000,iVar7,uVar8,unaff_r4);
  }
  goto LAB_00066540;
}

