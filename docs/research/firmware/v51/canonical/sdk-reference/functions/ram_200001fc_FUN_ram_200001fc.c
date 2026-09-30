/* Address: ram:200001fc; name: FUN_ram_200001fc; body bytes: 1 */

void FUN_ram_200001fc(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  gp = 0x20004000;
  if ((param_1 != (undefined4 *)0x0) && (param_2 != (undefined4 *)0x0)) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
  }
  return;
}

