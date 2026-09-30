/* Address: 0004778c; name: FUN_0004778c; body bytes: 84 */

undefined4 FUN_0004778c(undefined4 param_1,undefined4 param_2)

{
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  FUN_0004a152(&DAT_2003a530,0x18);
  FUN_000475c8(param_1);
  if (DAT_2003a540 == 0) {
    DAT_2003a540 = FUN_0003f0e6(&PTR_FUN_000236a0_1_0007a50c,0x18,param_2,0x39139,0,0x3917d,unaff_r4
                                ,unaff_lr);
    FUN_0003f218(DAT_2003a540,"IMAGE_HEADER");
    if (DAT_2003a540 == 0) {
      return 0;
    }
  }
  return 1;
}

