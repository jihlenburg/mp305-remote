/* Address: 00020316; name: FUN_00020316; body bytes: 80 */

int FUN_00020316(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  
  if (param_4 == 0) {
    param_4 = FUN_00041788(param_1,param_3);
  }
  iVar1 = param_4 * param_2;
  if (param_3 != 0x14) {
    if (param_3 - 7U < 4) {
      if (param_3 == 7) {
        iVar2 = 2;
      }
      else if (param_3 == 8) {
        iVar2 = 4;
      }
      else if (param_3 == 9) {
        iVar2 = 0x10;
      }
      else if (param_3 == 10) {
        iVar2 = 0x100;
      }
      else {
        iVar2 = 0;
      }
      iVar1 = iVar1 + iVar2 * 4;
    }
    return iVar1;
  }
  return (param_4 >> 1) * param_2 + iVar1;
}

