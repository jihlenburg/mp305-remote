/* Address: 00016af8; name: FUN_00016af8; body bytes: 194 */

/* Recovered from stored Thumb pointer at 000634f0; callback identification is inferred until
   reviewed. */

void FUN_00016af8(void)

{
  int iVar1;
  undefined1 *puVar2;
  
  FUN_00016988(&DAT_4004e000,8,0);
  if (DAT_1fff8ebc != 0) {
    FUN_00016988(&DAT_4004e000,0x10d8,0);
    FUN_00016830(&DAT_4004e000,0x10);
    DAT_1fff8ec0 = 0;
    DAT_1fff8ebc = 0;
    DAT_1fff8ea0 = 1;
    DAT_1fff8eac = &DAT_1fff8e96;
    DAT_1fff8eb0 = 7;
    FUN_00016988(&DAT_4004e000,1);
    DAT_4004e000 = DAT_4004e000 | 0x80;
    return;
  }
  iVar1 = FUN_00016932(&DAT_4004e000,0x40000);
  if (iVar1 != 1) {
    return;
  }
  iVar1 = FUN_00016932(&DAT_4004e000,0x1000);
  if (iVar1 == 0) {
    FUN_00016988(&DAT_4004e000,0x80,1);
    puVar2 = (undefined1 *)((int)DAT_1fff8eac + DAT_1fff8ebc);
    DAT_1fff8ebc = DAT_1fff8ebc + 1;
    DAT_4004e024 = *puVar2;
    return;
  }
  FUN_00016988(&DAT_4004e000,0x1000,0);
  FUN_00016988(&DAT_4004e000,0x10,1);
  FUN_00016928(&DAT_4004e000);
  return;
}

