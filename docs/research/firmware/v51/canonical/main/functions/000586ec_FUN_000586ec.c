/* Address: 000586ec; name: FUN_000586ec; body bytes: 108 */

void FUN_000586ec(int param_1,int param_2,int param_3,int param_4,int *param_5,int *param_6)

{
  int iVar1;
  
  param_2 = param_2 - param_3;
  if ((param_4 < 2) && ((param_1 == 3 || (param_1 == 4)))) {
switchD_00058706_caseD_2:
    *param_6 = 0;
    param_2 = *param_5 + param_2 / 2;
  }
  else {
    switch(param_1) {
    default:
      *param_6 = 0;
      return;
    case 1:
      *param_6 = 0;
      param_2 = *param_5 + param_2;
      break;
    case 2:
      goto switchD_00058706_caseD_2;
    case 3:
      param_2 = param_2 / (param_4 + 1);
      *param_6 = param_2;
      param_2 = param_2 + *param_5;
      break;
    case 4:
      iVar1 = param_2 / param_4 + *param_6;
      *param_6 = iVar1;
      param_2 = *param_5 + iVar1 / 2;
      break;
    case 5:
      if (1 < param_4) {
        *param_6 = param_2 / (param_4 + -1);
      }
      return;
    }
  }
  *param_5 = param_2;
  return;
}

