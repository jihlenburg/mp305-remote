/* Address: ram:00046df2; name: FUN_ram_00046df2; body bytes: 266 */

undefined4 FUN_ram_00046df2(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  char cVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  char cVar14;
  char cStack_21;
  
  gp = 0x20004000;
  uVar11 = 1;
  if (DAT_ram_200019e4 != 0) {
    GAPBondMgr_GetParameter(0x41f,&cStack_21);
    GAPBondMgr_GetParameter(0x41f,&cStack_21);
    cVar14 = DAT_ram_20001c06 != '\0';
    if (cStack_21 != '\0') {
      cVar14 = cVar14 + '\x02';
    }
    uVar11 = FUN_ram_000442de(*(undefined1 *)(DAT_ram_200019e4 + 3),DAT_ram_200019e4 + 4);
    uVar1 = *(undefined1 *)(DAT_ram_200019e4 + 2);
    uVar12 = GAP_GetParamValue(3);
    uVar13 = GAP_GetParamValue(4);
    iVar4 = DAT_ram_200019e4;
    uVar2 = *(undefined1 *)(DAT_ram_200019e4 + 10);
    uVar3 = *(undefined1 *)(DAT_ram_200019e4 + 0xb);
    cVar5 = GAP_GetParamValue(0x19);
    uVar6 = GAP_GetParamValue(0x1a);
    uVar7 = GAP_GetParamValue(0x1c);
    uVar8 = GAP_GetParamValue(0x1b);
    uVar9 = GAP_GetParamValue(0x1d);
    uVar10 = GAP_GetParamValue(0x1e);
    uVar11 = FUN_ram_00052596(1,uVar1,uVar12,uVar13,uVar2,cVar14,uVar11,iVar4 + 4,uVar3,(int)cVar5,
                              uVar6,uVar7,uVar8,uVar9,uVar10);
  }
  return uVar11;
}

