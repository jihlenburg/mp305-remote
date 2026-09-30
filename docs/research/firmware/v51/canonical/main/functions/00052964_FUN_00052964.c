/* Address: 00052964; name: FUN_00052964; body bytes: 238 */

uint FUN_00052964(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  if (DAT_2003a4a8 == '\0') {
    DAT_2003a4a8 = 1;
    if (DAT_2003a4a0 != '\0') {
      FUN_0004a314();
      iVar1 = FUN_00052708();
      if ((iVar1 == 0) && (DAT_2003a4b8 = DAT_2003a4b8 + 1, 100 < DAT_2003a4b8)) {
        DAT_2003a4b8 = 0;
      }
      do {
        DAT_2003a4a2 = '\0';
        DAT_2003a4a3 = '\0';
        iVar2 = FUN_0004a118(&DAT_2003a494);
        do {
          iVar6 = iVar2;
          if (iVar6 == 0) goto LAB_000529d8;
          iVar2 = FUN_0004a13c(&DAT_2003a494,iVar6);
          iVar3 = FUN_000528e4(iVar6);
        } while ((iVar3 == 0) || ((DAT_2003a4a3 == '\0' && (DAT_2003a4a2 == '\0'))));
      } while (iVar6 != 0);
LAB_000529d8:
      uVar5 = 0xffffffff;
      for (iVar2 = FUN_0004a118(&DAT_2003a494); iVar2 != 0;
          iVar2 = FUN_0004a13c(&DAT_2003a494,iVar2)) {
        if (((*(byte *)(iVar2 + 0x14) & 1) == 0) && (uVar4 = FUN_00052ace(iVar2), uVar4 < uVar5)) {
          uVar5 = uVar4;
        }
      }
      iVar1 = FUN_000526fc(iVar1);
      DAT_2003a4b0 = iVar1 + DAT_2003a4b0;
      uVar4 = FUN_000526fc(DAT_2003a4b4);
      if (499 < uVar4) {
        uVar4 = (uint)(DAT_2003a4b0 * 100) / uVar4;
        if ((uVar4 & 0xff) < 0x65) {
          DAT_2003a4a1 = 'd' - (char)uVar4;
        }
        else {
          DAT_2003a4a1 = '\0';
        }
        DAT_2003a4b0 = 0;
        DAT_2003a4b4 = FUN_00052708();
      }
      DAT_2003a4a8 = 0;
      DAT_2003a4a4 = uVar5;
      FUN_00052d78();
      return uVar5;
    }
    DAT_2003a4a8 = '\0';
  }
  return 1;
}

