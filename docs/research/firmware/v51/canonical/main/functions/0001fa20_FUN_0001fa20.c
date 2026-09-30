/* Address: 0001fa20; name: FUN_0001fa20; body bytes: 78 */

void FUN_0001fa20(void)

{
  switch(DAT_1fffaaad) {
  case 0:
    DAT_1fffaa74 = 0xc1c;
    break;
  case 1:
    DAT_1fffaa74 = 3000;
    break;
  case 2:
    DAT_1fffaa74 = 0xb54;
    break;
  case 3:
    DAT_1fffaa74 = 0xa28;
    break;
  case 4:
    DAT_1fffaa74 = 0x708;
    break;
  case 5:
    DAT_1fffaa72 = 0x5dc;
    DAT_1fffaa74 = 800;
    DAT_1fffaa76 = 0;
  default:
    goto switchD_0001fa2e_default;
  }
  DAT_1fffaa72 = DAT_1fffaa70;
  DAT_1fffaa76 = DAT_1fffaa74;
switchD_0001fa2e_default:
  return;
}

