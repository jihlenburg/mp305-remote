/* Address: 00053ed8; name: FUN_00053ed8; body bytes: 158 */

void FUN_00053ed8(int *param_1)

{
  undefined4 *puVar1;
  
  if (current_mode == '\0') {
    FUN_0004e00e(DAT_1ffe03b4,1);
    FUN_0004dfd2(DAT_1ffe035c,0x65e35);
    FUN_0004dfd2(DAT_1ffe036c,0x65e35);
    FUN_0004dfd2(DAT_1ffe0354,0x65e35);
    FUN_0004dfd2(DAT_1ffe0364,0x65e35);
  }
  else if (current_mode == '\x03') {
    FUN_0004e00e(DAT_1ffe0628,1);
  }
  FUN_0004e00e(DAT_1ffe03b8,1);
  FUN_0004e00e(DAT_1ffe05b4,1);
  DAT_1ffe0330 = *param_1;
  if (DAT_1ffe0330 == DAT_1ffe0478) {
    puVar1 = &DAT_1ffe03bc;
  }
  else {
    if ((DAT_1ffe0330 != DAT_1ffe06a0) || (DAT_1fffab10 == '\0')) goto LAB_00053f68;
    puVar1 = &DAT_1ffe03c4;
  }
  FUN_0004aa6e(*puVar1,1);
LAB_00053f68:
  FUN_0004e00e(DAT_1ffe0344,0x10);
  return;
}

