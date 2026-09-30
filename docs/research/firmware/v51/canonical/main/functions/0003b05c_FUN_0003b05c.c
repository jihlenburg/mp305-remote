/* Address: 0003b05c; name: FUN_0003b05c; body bytes: 136 */

void FUN_0003b05c(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  
  *param_2 = 0;
  param_2[1] = 0;
  if (((DAT_1ffe012a == '\x01') && (DAT_1ffe0134 != 0x1d)) && (DAT_1ffe0134 != 0x1c)) {
    param_2[2] = DAT_1ffe0134;
    *(undefined1 *)((int)param_2 + 0x12) = 0;
    DAT_1ffe012a = 0;
    DAT_1fffab88 = 0;
    DAT_1fffab8c = 0;
    return;
  }
  iVar1 = FUN_0003b010();
  if (iVar1 == 3) {
    DAT_1ffe0134 = 0x1d;
    DAT_1ffe0138 = DAT_1ffe0138 + 1;
    if (0x4a < DAT_1ffe0138) {
      *(undefined1 *)((int)param_2 + 0x12) = 1;
      DAT_1ffe0134 = 0x1c;
    }
  }
  else if (iVar1 == 4) {
    *(undefined1 *)((int)param_2 + 0x12) = 1;
    DAT_1ffe0134 = 0x1c;
    DAT_1ffe0138 = 0;
  }
  else {
    if (iVar1 == 0) {
      if (DAT_1ffe0138 == 0) {
        DAT_1ffe0129 = 0;
        DAT_1ffe0245 = 0;
        *(undefined1 *)((int)param_2 + 0x12) = 0;
      }
      else {
        DAT_1ffe0138 = 0;
        *(undefined1 *)((int)param_2 + 0x12) = 1;
      }
      goto LAB_0003b0da;
    }
    *(undefined1 *)((int)param_2 + 0x12) = 1;
    DAT_1ffe0134 = iVar1;
  }
  DAT_1ffe0129 = 1;
  DAT_1fffab88 = 0;
  DAT_1fffab8c = 0;
LAB_0003b0da:
  param_2[2] = DAT_1ffe0134;
  DAT_1ffe012a = *(undefined1 *)((int)param_2 + 0x12);
  return;
}

