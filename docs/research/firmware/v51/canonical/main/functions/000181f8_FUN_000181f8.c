/* Address: 000181f8; name: FUN_000181f8; body bytes: 218 */

void FUN_000181f8(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (current_mode == '\x02') {
    if ((DAT_1fffaad1 != '\0') && (param_1 != 0)) {
      iVar1 = 0x200020;
    }
    goto LAB_00018252;
  }
  if ((((current_mode == '\0') || (current_mode == '\x01')) && (DAT_1fffaad1 != '\0')) &&
     (param_1 != 0)) {
    if (DAT_1fffaace != '\x01') {
      if (DAT_1fffaace != '\x02') {
        if (DAT_1fffaace == '\x03') {
          iVar1 = 0x2020;
        }
        goto LAB_00018252;
      }
LAB_00018250:
      iVar1 = 0x92000;
      goto LAB_00018252;
    }
  }
  else {
    if (((current_mode != '\x03') || (DAT_1fffab47 == 0)) || (param_1 == 0)) goto LAB_00018252;
    if (DAT_1fffab47 < 5) goto LAB_00018250;
  }
  iVar1 = 0x200000;
LAB_00018252:
  if (((DAT_1fffab6a != 0) || (DAT_1fffaca8 != 0)) && (3 < DAT_1fffaae5)) {
    iVar1 = 0x2000;
  }
  if ((((DAT_1fffaa50 != '\0') && (iVar1 != 0x2000)) && (5000 < DAT_1fffa9e8)) ||
     (DAT_1fffaae5 == 5)) {
    iVar1 = 0x202020;
  }
  if ((DAT_1ffe01d0 != iVar1) || (param_1 == 0)) {
    FUN_0001c5ec(0,iVar1);
    FUN_0001c5ec(1,iVar1);
    FUN_0001decc(&DAT_40026c00,2,0);
    DAT_40053080 = &DAT_1fffa8ce;
    DAT_40053088 = DAT_40053088 & 0xffff | 0x320000;
    FUN_0001453c(&DAT_40053000,1);
    DAT_1ffe01d0 = iVar1;
  }
  return;
}

