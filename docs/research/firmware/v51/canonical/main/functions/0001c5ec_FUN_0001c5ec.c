/* Address: 0001c5ec; name: FUN_0001c5ec; body bytes: 54 */

void FUN_0001c5ec(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  do {
    iVar2 = uVar1 + param_1 * 0x18;
    if ((1 << (0x17 - uVar1 & 0xff) & param_2) == 0) {
      (&DAT_1fffa8d0)[iVar2] = 0x24;
    }
    else {
      (&DAT_1fffa8d0)[iVar2] = 0x6c;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x18);
  DAT_1fffa8ce = DAT_1fffa8d0;
  return;
}

