/* Address: 000125c0; name: FUN_000125c0; body bytes: 192 */

void FUN_000125c0(void)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  uint in_fpscr;
  float fVar4;
  uint local_20;
  
  local_20 = 0;
  FUN_00012244(&DAT_40040000);
  do {
    iVar1 = FUN_00012208(&DAT_40040000,1);
    if (iVar1 == 1) {
      FUN_000121de(&DAT_40040000,1);
      uVar2 = FUN_00012218(&DAT_40040000,3);
      fVar4 = (float)VectorUnsignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      uVar2 = VectorFloatToUnsigned(fVar4 * 3.3 * 0.00024414062 * 1000.0,3);
      DAT_1fffa9c8 = (undefined2)uVar2;
      uVar2 = FUN_00012218(&DAT_40040000,6);
      fVar4 = (float)VectorUnsignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      iVar1 = VectorFloatToUnsigned(fVar4 * 3.3 * 0.00024414062 * 1000.0,3);
      DAT_1fffa9c4 = ((short)iVar1 + (short)(iVar1 << 2)) * 2;
      return;
    }
    bVar3 = local_20 < 1000;
    local_20 = local_20 + 1;
  } while (bVar3);
  DAT_40040000 = 0;
  return;
}

