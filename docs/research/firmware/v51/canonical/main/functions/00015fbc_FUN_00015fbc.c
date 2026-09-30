/* Address: 00015fbc; name: FUN_00015fbc; body bytes: 32 */

uint FUN_00015fbc(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (DAT_1fff8f24 != '\0') {
    iVar1 = FUN_00016c6a(2);
    uVar2 = (uint)(iVar1 * 0x7d) / 10;
  }
  return uVar2;
}

