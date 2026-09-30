/* Address: ram:20000214; name: tmos_memset; body bytes: 18 */

void tmos_memset(undefined1 *param_1,undefined1 param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  gp = 0x20004000;
  if ((param_1 != (undefined1 *)0x0) && (param_3 != 0)) {
    puVar2 = param_1;
    do {
      puVar1 = puVar2 + 1;
      *puVar2 = param_2;
      puVar2 = puVar1;
    } while (param_1 + param_3 != puVar1);
  }
  return;
}

