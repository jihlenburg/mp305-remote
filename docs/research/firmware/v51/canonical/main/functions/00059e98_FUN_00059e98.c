/* Address: 00059e98; name: FUN_00059e98; body bytes: 20 */

undefined4 FUN_00059e98(uint param_1,uint param_2,int param_3)

{
  if (param_3 == 0) {
    if ((param_1 & param_2) != 0) {
      return 1;
    }
  }
  else if ((param_2 & ~param_1) == 0) {
    return 1;
  }
  return 0;
}

