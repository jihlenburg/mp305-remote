/* Address: CODE:7f77; name: FUN_CODE_7f77; body bytes: 63 */

void FUN_CODE_7f77(byte param_1,byte param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)(CONCAT11(param_3,param_4) + 1);
  if (*pbVar2 != param_2) {
    FUN_CODE_4521();
    *pbVar2 = 1;
  }
  pbVar2 = (byte *)(CONCAT11(param_3,param_4) + 1);
  *pbVar2 = param_2;
  FUN_CODE_4521();
  if ((*pbVar2 < param_1) << 7 < '\0') {
    FUN_CODE_4521(*pbVar2 - param_1);
    *pbVar2 = *pbVar2 + 1;
  }
  else {
    if (*(char *)CONCAT11(param_3,param_4) != BANK0_R5) {
LAB_CODE_7fa6:
      *(byte *)CONCAT11(param_3,param_4) = param_2;
      return;
    }
    if (param_2 == 0) {
      cVar1 = FUN_CODE_44d1();
      if (cVar1 == '\x01') goto LAB_CODE_7fa6;
    }
  }
  return;
}

