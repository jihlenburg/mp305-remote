/* Address: 00040314; name: FUN_00040314; body bytes: 42 */

undefined4 FUN_00040314(undefined4 param_1)

{
  switch(param_1) {
  case 6:
  case 10:
  case 0xe:
    return 8;
  case 7:
  case 0xb:
    return 1;
  case 8:
  case 0xc:
    return 2;
  case 9:
  case 0xd:
    return 4;
  case 0xf:
  case 0x13:
    return 0x18;
  case 0x10:
  case 0x11:
    return 0x20;
  case 0x12:
  case 0x14:
  case 0x15:
    return 0x10;
  default:
    return 0;
  }
}

