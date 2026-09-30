/* Address: 0001fc0c; name: FUN_0001fc0c; body bytes: 20 */

void FUN_0001fc0c(undefined2 param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_1ffe01c8;
  uVar2 = 0;
  do {
    *(undefined2 *)(iVar1 + uVar2 * 2) = param_1;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 2);
  return;
}

