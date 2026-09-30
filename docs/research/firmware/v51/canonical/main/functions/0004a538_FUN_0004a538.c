/* Address: 0004a538; name: FUN_0004a538; body bytes: 64 */

void FUN_0004a538(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 *puVar1;
  bool bVar2;
  
  if ((param_2 <= param_1) && (puVar1 = param_2 + param_3, param_1 <= puVar1)) {
    if (param_2 < param_1) {
      param_1 = param_1 + param_3;
      while( true ) {
        puVar1 = puVar1 + -1;
        param_1 = param_1 + -1;
        bVar2 = param_3 == 0;
        param_3 = param_3 + -1;
        if (bVar2) break;
        *param_1 = *puVar1;
      }
    }
    else {
      while (bVar2 = param_3 != 0, param_3 = param_3 + -1, bVar2) {
        *param_1 = *param_2;
        param_2 = param_2 + 1;
        param_1 = param_1 + 1;
      }
    }
    return;
  }
  FUN_0004a404();
  return;
}

