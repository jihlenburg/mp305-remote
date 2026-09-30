/* Address: 00016060; name: FUN_00016060; body bytes: 64 */

void FUN_00016060(undefined4 param_1)

{
  undefined4 uVar1;
  
  DAT_1fffab21 = (undefined1)param_1;
  switch(param_1) {
  case 0:
    uVar1 = 0x18;
    break;
  case 1:
    uVar1 = 0x19;
    break;
  case 2:
    uVar1 = 0x1a;
    break;
  case 3:
    uVar1 = 0x1b;
    break;
  case 4:
    uVar1 = 0x1c;
    break;
  case 5:
    uVar1 = 0x1d;
    break;
  case 6:
    uVar1 = 0x1e;
    break;
  case 7:
    uVar1 = 0x1f;
    break;
  case 8:
    uVar1 = 0x20;
    break;
  default:
    uVar1 = 0x23;
    break;
  case 10:
    uVar1 = 0x21;
    break;
  case 0xb:
    uVar1 = 0x22;
  }
  FUN_00015a5c(uVar1);
  return;
}

