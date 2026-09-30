/* Address: 0004a388; name: FUN_0004a388; body bytes: 60 */

int FUN_0004a388(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  if ((param_2 <= param_3) && (param_3 <= param_1)) {
    return param_5;
  }
  if ((param_3 < param_2) || (param_2 < param_1)) {
    if ((param_3 <= param_2) && (param_1 <= param_3)) {
      return param_5;
    }
    if ((param_2 < param_3) || (param_1 < param_2)) {
      return ((param_5 - param_4) * (param_1 - param_2)) / (param_3 - param_2) + param_4;
    }
  }
  return param_4;
}

