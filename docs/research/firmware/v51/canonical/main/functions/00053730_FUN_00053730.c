/* Address: 00053730; name: FUN_00053730; body bytes: 142 */

void FUN_00053730(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  iVar1 = FUN_00046698();
  uVar2 = FUN_0004bc8c();
  uVar3 = FUN_0004bc8c();
  puVar4 = (uint *)FUN_0003f334();
  uVar6 = *puVar4;
  iVar8 = (int)(uVar6 << 8) >> 0x18;
  if (0xb < iVar8 - 1U) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar5 = FUN_0004b9de(uVar2,0);
  if (iVar5 == iVar1) {
    if (iVar8 != 1) {
      uVar6 = uVar6 & 0xff00ffff | (iVar8 - 1U & 0xff) << 0x10;
      goto LAB_00053782;
    }
    uVar7 = uVar6 & 0xff00ffff | 0xc0000;
    uVar6 = uVar7 - 1;
  }
  else {
    if (iVar8 != 0xc) {
      uVar6 = uVar6 & 0xff00ffff | (iVar8 + 1U & 0xff) << 0x10;
      goto LAB_00053782;
    }
    uVar7 = uVar6 & 0xff00ffff | 0x10000;
    uVar6 = uVar7 + 1;
  }
  uVar6 = uVar7 & 0xffff0000 | uVar6 & 0xffff;
LAB_00053782:
  FUN_0003f338(uVar3);
  uVar2 = FUN_0004b9de(uVar2,1);
  FUN_000499de(uVar2,"%d %s",uVar6 & 0xffff,(&PTR_DAT_1ffe0094)[(int)(uVar6 << 8) >> 0x18]);
  return;
}

