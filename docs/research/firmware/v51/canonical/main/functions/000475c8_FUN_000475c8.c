/* Address: 000475c8; name: FUN_000475c8; body bytes: 54 */

undefined4 FUN_000475c8(undefined4 param_1)

{
  if (DAT_2003a53c == 0) {
    DAT_2003a53c = FUN_0003f0e6(&PTR_FUN_000236a0_1_0007a534,0x18,param_1,0x38f83,0,0x38fc7);
    FUN_0003f218(DAT_2003a53c,"IMAGE");
    if (DAT_2003a53c == 0) {
      return 0;
    }
  }
  return 1;
}

