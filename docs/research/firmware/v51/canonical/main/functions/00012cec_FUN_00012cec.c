/* Address: 00012cec; name: FUN_00012cec; body bytes: 56 */

undefined4 FUN_00012cec(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if ((param_1 != 0) && (param_2 != 0)) {
    uVar1 = FUN_0001c162(&DAT_4001c800,0,param_1,param_2,
                         DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18));
  }
  return uVar1;
}

