/* Address: 000146e8; name: FUN_000146e8; body bytes: 28 */

void FUN_000146e8(int param_1)

{
  uint *puVar1;
  uint uVar2;
  
  if (param_1 == 1) {
    puVar1 = &DAT_40010404;
    DAT_40010404 = 0x1234567;
    uVar2 = 0xfedcba98;
  }
  else {
    puVar1 = &DAT_4001041c;
    uVar2 = DAT_4001041c | 0x10000;
  }
  *puVar1 = uVar2;
  return;
}

