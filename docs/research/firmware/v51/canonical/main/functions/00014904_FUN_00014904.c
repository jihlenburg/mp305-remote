/* Address: 00014904; name: FUN_00014904; body bytes: 66 */

undefined4 FUN_00014904(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  DAT_40010418 = DAT_40010418 & 0xfffffff0 | param_1 & 0xf;
  do {
    if ((param_1 & 0xf) == param_1) {
      return 0;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 <= (DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18)) / 20000);
  return 0xfffffff8;
}

