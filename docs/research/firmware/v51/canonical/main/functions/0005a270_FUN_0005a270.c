/* Address: 0005a270; name: FUN_0005a270; body bytes: 48 */

void FUN_0005a270(void)

{
  byte bVar1;
  
  DAT_1ffe02b4 = 0;
  if (DAT_1fffaad7 == '\0') {
    bVar1 = 1;
  }
  else {
    bVar1 = 2;
  }
  DAT_1fffaae4 = DAT_1fffaae4 ^ bVar1;
  FUN_00057064(DAT_1fffaae4,1);
  FUN_0001cb8c(0xf);
  return;
}

