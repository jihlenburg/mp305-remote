/* Address: 00014738; name: FUN_00014738; body bytes: 224 */

undefined4 FUN_00014738(uint *param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  bool bVar6;
  
  uVar4 = 0;
  uVar3 = param_3 >> 2;
  DAT_40010424 = 0x13f;
  uVar5 = DAT_40010418 & 0xf0000;
  DAT_40010418 = DAT_40010418 & 0xfff0ffff;
  DAT_4001041c = (DAT_4001041c & 0xfffffff8) + 1;
  while (bVar6 = uVar3 != 0, uVar3 = uVar3 - 1, bVar6) {
    uVar1 = *param_2;
    param_2 = param_2 + 1;
    *param_1 = uVar1;
    param_1 = param_1 + 1;
    iVar2 = FUN_0001497c(0x100,(DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18)) / 20000);
    if (iVar2 == -8) {
      uVar4 = 0xfffffffb;
    }
    DAT_40010424 = 0x10;
  }
  if ((param_3 & 3) != 0) {
    *param_1 = -1 << ((param_3 & 3) << 3) | *param_2;
    iVar2 = FUN_0001497c(0x100,(DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18)) / 20000);
    if (iVar2 == -8) {
      uVar4 = 0xfffffffb;
    }
    DAT_40010424 = 0x10;
  }
  DAT_4001041c = DAT_4001041c & 0xfffffff8;
  DAT_40010418 = DAT_40010418 & 0xfff0ffff | uVar5;
  return uVar4;
}

