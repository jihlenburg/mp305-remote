/* Address: 0001dae8; name: update_system_clock; body bytes: 106 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Reads 0x40010684 and clock registers at 0x40054000; MCU part number unresolved. */

void update_system_clock(void)

{
  uint uVar1;
  uint uVar2;
  
  if ((DAT_40010684 & 1) == 0) {
    uVar1 = 20000000;
  }
  else {
    uVar1 = 16000000;
  }
  DAT_2003a610 = uVar1;
  switch(DAT_40054026 & 7) {
  case 0:
    break;
  case 1:
  case 3:
    DAT_2003a60c = 8000000;
    return;
  case 2:
  case 4:
    DAT_2003a60c = 0x8000;
    return;
  case 5:
    uVar2 = 8000000;
    if (_DAT_42a8201c != 0) {
      uVar2 = uVar1;
    }
    uVar1 = ((((DAT_40054100 & 0xffff) >> 8) + 1) * (uVar2 / ((DAT_40054100 & 3) + 1))) /
            ((DAT_40054100 >> 0x1c) + 1);
    break;
  default:
    return;
  }
  DAT_2003a60c = uVar1;
  return;
}

