/* Address: 000229b4; name: FUN_000229b4; body bytes: 42 */

uint FUN_000229b4(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if ((param_2 & param_2 - 1) != 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    uVar2 = (param_1 + param_2) - 1 & ~(param_2 - 1);
    if ((uVar2 < 0x40000) && (uVar1 = uVar2, uVar2 < 0xd)) {
      return 0xc;
    }
  }
  return uVar1;
}

