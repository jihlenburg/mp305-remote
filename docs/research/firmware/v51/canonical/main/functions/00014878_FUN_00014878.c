/* Address: 00014878; name: FUN_00014878; body bytes: 128 */

undefined4 FUN_00014878(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar2 = 0;
  DAT_40010424 = 0x13f;
  uVar3 = DAT_40010418 & 0xf0000;
  DAT_40010418 = DAT_40010418 & 0xfff0ffff;
  DAT_4001041c = (DAT_4001041c & 0xfffffff8) + 4;
  *param_1 = 0;
  iVar1 = FUN_0001497c(0x100,(DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18)) / 0x32);
  if (iVar1 == -8) {
    uVar2 = 0xfffffffb;
  }
  DAT_40010424 = 0x10;
  DAT_4001041c = DAT_4001041c & 0xfffffff8;
  DAT_40010418 = DAT_40010418 & 0xfff0ffff | uVar3;
  return uVar2;
}

