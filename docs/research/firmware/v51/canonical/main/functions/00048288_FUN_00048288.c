/* Address: 00048288; name: FUN_00048288; body bytes: 30 */

void FUN_00048288(char *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != (char *)0x0) {
    if ((*param_1 == '\x01') || (*param_1 == '\x03')) {
      *param_2 = *(undefined4 *)(param_1 + 0x30);
      uVar1 = *(undefined4 *)(param_1 + 0x34);
      goto LAB_000482a2;
    }
    uVar1 = 0xffffffff;
  }
  *param_2 = uVar1;
LAB_000482a2:
  param_2[1] = uVar1;
  return;
}

