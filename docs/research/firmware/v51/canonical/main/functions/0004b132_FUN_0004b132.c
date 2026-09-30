/* Address: 0004b132; name: FUN_0004b132; body bytes: 18 */

undefined4 FUN_0004b132(int *param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != (int *)0x0) {
    if (*param_1 != param_2) {
      return 0;
    }
    uVar1 = 1;
  }
  return uVar1;
}

