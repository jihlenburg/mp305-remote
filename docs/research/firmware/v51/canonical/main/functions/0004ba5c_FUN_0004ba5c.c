/* Address: 0004ba5c; name: FUN_0004ba5c; body bytes: 10 */

undefined2 FUN_0004ba5c(int param_1)

{
  undefined2 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 8) + 0x28);
  }
  return uVar1;
}

