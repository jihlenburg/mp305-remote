/* Address: 0001fae4; name: FUN_0001fae4; body bytes: 64 */

void FUN_0001fae4(void)

{
  uint uVar1;
  
  FUN_0001fbb0();
  uVar1 = get_output_faults();
  if (DAT_1fffaaad == '\x05') {
    if (0x7562 < DAT_1fffaa80) goto LAB_0001fb18;
  }
  else if ((uint)DAT_1fffaa60 * (uint)DAT_1fffaa72 + 0x32 < (uint)DAT_1fffaa80) {
LAB_0001fb18:
    DAT_1fffaab0 = uVar1 | 0x800;
    return;
  }
  DAT_1fffaab0 = uVar1 & 0xfffff7ff;
  return;
}

