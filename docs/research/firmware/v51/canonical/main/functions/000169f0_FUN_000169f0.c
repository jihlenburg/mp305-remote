/* Address: 000169f0; name: FUN_000169f0; body bytes: 106 */

void FUN_000169f0(void)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  if ((1 < DAT_1fff8eb0) && (DAT_1fff8ebc == DAT_1fff8eb0 - 2)) {
    FUN_000166dc(&DAT_4004e000,0x400);
  }
  if (DAT_1fff8ebc == DAT_1fff8eb0 - 1) {
    FUN_00016988(&DAT_4004e000,0x10,1);
    FUN_00016988(&DAT_4004e000,0x40,0);
    FUN_00016928(&DAT_4004e000);
    FUN_000166dc(&DAT_4004e000,0);
    FUN_000277f0(&DAT_1ffe0154,0,&DAT_1ffe0156,&DAT_1ffe0158);
  }
  uVar1 = FUN_00016a68(&DAT_4004e000);
  puVar2 = (undefined1 *)(DAT_1fff8eac + DAT_1fff8ebc);
  DAT_1fff8ebc = DAT_1fff8ebc + 1;
  *puVar2 = uVar1;
  return;
}

