/* Address: 00016024; name: FUN_00016024; body bytes: 46 */

int FUN_00016024(void)

{
  uint in_fpscr;
  float fVar1;
  int iVar2;
  
  iVar2 = 0;
  if (DAT_1fff8f24 != '\0') {
    DAT_1fff8f28 = FUN_00016c6a(4);
    fVar1 = (float)VectorSignedToFloat((int)DAT_1fff8f28,(byte)(in_fpscr >> 0x16) & 3);
    iVar2 = (int)(DAT_1fff8f2c * fVar1);
  }
  return iVar2;
}

