/* Address: CODE:3f72; name: FUN_CODE_3f72; body bytes: 140 */

void FUN_CODE_3f72(byte param_1)

{
  byte bVar1;
  char in_PSW;
  char cVar2;
  
  FUN_CODE_a471();
  DAT_EXTMEM_04a6 = param_1;
  DAT_EXTMEM_04a7 = param_1;
  FUN_CODE_a60e(2);
  if ((in_PSW < '\0') || (DAT_INTMEM_cc == '\t')) {
LAB_CODE_3f91:
    DAT_EXTMEM_04a7 = 1;
    goto switchD_CODE_3fc3_default;
  }
  bVar1 = 8;
  FUN_CODE_a60e();
  if (in_PSW < '\0') goto LAB_CODE_3f91;
  cVar2 = (DAT_EXTMEM_04a7 < 8) << 7;
  if (DAT_EXTMEM_04a7 >= 8) {
    thunk_FUN_CODE_a45d(DAT_EXTMEM_04a7 - 8);
    FUN_CODE_a11f();
    if (cVar2 < '\0') {
      DAT_EXTMEM_04a7 = 2;
    }
    else {
      DAT_EXTMEM_04a7 = 1;
    }
  }
  switch(DAT_EXTMEM_04a7) {
  case 0:
    goto LAB_CODE_3fd2;
  case 1:
LAB_CODE_3fd2:
    FUN_CODE_a25f();
    DAT_EXTMEM_04a7 = bVar1;
    break;
  case 2:
    FUN_CODE_9c43();
    DAT_EXTMEM_04a7 = bVar1;
    break;
  case 3:
    FUN_CODE_7dac();
    DAT_EXTMEM_04a7 = bVar1;
    break;
  case 4:
    FUN_CODE_7b3a();
    DAT_EXTMEM_04a7 = bVar1;
    break;
  case 5:
    FUN_CODE_9d3c();
    DAT_EXTMEM_04a7 = bVar1;
    break;
  case 6:
    FUN_CODE_8136();
    DAT_EXTMEM_04a7 = bVar1;
  }
switchD_CODE_3fc3_default:
  FUN_CODE_69a3(DAT_EXTMEM_04a7,DAT_EXTMEM_04a6);
  return;
}

