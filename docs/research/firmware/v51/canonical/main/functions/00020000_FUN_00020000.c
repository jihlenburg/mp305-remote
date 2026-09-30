/* Address: 00020000; name: FUN_00020000; body bytes: 48 */

void FUN_00020000(undefined1 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *local_28;
  int iStack_24;
  undefined4 uStack_4;
  
  if (param_2 == 0) {
    iStack_24 = 0;
  }
  else {
    iStack_24 = param_2 + -1;
  }
  local_28 = param_1;
  uStack_4 = param_4;
  FUN_00020e44(param_3,&uStack_4,&local_28,0x2154b);
  if (param_2 != 0) {
    *local_28 = 0;
  }
  return;
}

