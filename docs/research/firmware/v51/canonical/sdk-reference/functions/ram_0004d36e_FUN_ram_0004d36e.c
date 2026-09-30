/* Address: ram:0004d36e; name: FUN_ram_0004d36e; body bytes: 62 */

void FUN_ram_0004d36e(int param_1,int param_2,undefined2 param_3)

{
  undefined2 *puVar1;
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined2 uStack_24;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)0x0;
  if (param_2 == 0) {
    uStack_28 = *(undefined2 *)(param_1 + 2);
    puVar1 = &uStack_28;
    uStack_24 = param_3;
    if (*(int *)(param_1 + 0xc) != 0) {
      uStack_26 = *(undefined2 *)(*(int *)(param_1 + 0xc) + 2);
      puVar1 = &uStack_28;
    }
  }
  FUN_ram_0004d1f6(*(undefined1 *)(param_1 + 8),*(undefined2 *)(param_1 + 6),param_2,0x60,0,puVar1);
  return;
}

