/* Address: ram:20000298; name: FUN_ram_20000298; body bytes: 1 */

void FUN_ram_20000298(undefined1 *param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  gp = 0x20004000;
  puVar2 = param_1 + param_3;
  puVar1 = (undefined1 *)(param_2 + param_3 + -1);
  for (; param_1 != puVar2; param_1 = param_1 + 1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + -1;
  }
  return;
}

