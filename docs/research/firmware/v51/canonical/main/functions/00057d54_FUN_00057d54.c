/* Address: 00057d54; name: FUN_00057d54; body bytes: 120 */

void FUN_00057d54(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((DAT_1fff9430 != DAT_1ffe025e) || (DAT_1fff9434 != DAT_1ffe025f)) ||
     (DAT_1fff9b91 != DAT_1ffe0260)) {
    iVar1 = FUN_0004ba5c(DAT_1ffe05b0);
    uVar2 = FUN_0004b9de(DAT_1ffe05b0,iVar1 + -1);
    uVar2 = FUN_0004b9de(uVar2,1);
    FUN_000499de(uVar2,"%d.%d/%d.%d/%d.%d/%d.%d",0,0x33,DAT_1fff9b91,DAT_1fff9b92,DAT_1fff9432,
                 DAT_1fff9433,DAT_1fff9434,DAT_1fff9435);
    DAT_1ffe025e = DAT_1fff9430;
    DAT_1ffe025f = DAT_1fff9434;
    DAT_1ffe0260 = DAT_1fff9b91;
  }
  return;
}

