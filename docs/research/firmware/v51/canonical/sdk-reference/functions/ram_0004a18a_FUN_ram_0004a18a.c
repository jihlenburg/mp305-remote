/* Address: ram:0004a18a; name: FUN_ram_0004a18a; body bytes: 234 */

undefined4 FUN_ram_0004a18a(undefined4 param_1,int param_2)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  undefined4 uVar5;
  short sVar6;
  short *psVar7;
  short sVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  gp = 0x20004000;
  psVar3 = (short *)(param_2 + 4);
  uVar9 = 0;
  sVar2 = 0;
  sVar6 = 0;
  sVar8 = 0;
  psVar7 = psVar3;
  while (sVar1 = *psVar7, sVar1 != 0) {
    if (sVar6 == 0) {
      sVar2 = psVar7[2];
      sVar8 = psVar7[1] + sVar2;
      sVar6 = sVar1;
    }
    else {
      if ((sVar1 != sVar6) || (psVar7[1] != sVar8)) goto LAB_ram_0004a23c;
      sVar2 = sVar2 + psVar7[2];
      sVar8 = sVar8 + psVar7[2];
    }
    uVar9 = uVar9 + 1;
    psVar7 = psVar7 + 6;
    if (uVar9 == 0xf) goto LAB_ram_0004a1cc;
  }
  uVar5 = 1;
  if (1 < uVar9) {
LAB_ram_0004a1cc:
    if ((sVar2 == 0) || (iVar4 = FUN_ram_20000040(sVar2,0x4704), iVar4 == 0)) {
LAB_ram_0004a23c:
      uVar5 = 0;
    }
    else {
      uVar11 = 0;
      uVar10 = 0;
      do {
        if (*(int *)(psVar3 + 4) != 0) {
          tmos_memcpy(iVar4 + uVar10,*(int *)(psVar3 + 4),psVar3[2]);
          uVar10 = uVar10 + (ushort)psVar3[2] & 0xffff;
          FUN_ram_20000104(*(undefined4 *)(psVar3 + 4));
        }
        if (uVar11 != 0) {
          tmos_memset(psVar3,0,0xc);
        }
        uVar11 = uVar11 + 1;
        psVar3 = psVar3 + 6;
      } while (uVar11 < uVar9);
      *(int *)(param_2 + 0xc) = iVar4;
      *(short *)(param_2 + 8) = sVar2;
      uVar5 = 1;
    }
  }
  return uVar5;
}

