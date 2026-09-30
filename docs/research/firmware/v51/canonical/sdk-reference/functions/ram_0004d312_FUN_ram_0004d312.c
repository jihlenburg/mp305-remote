/* Address: ram:0004d312; name: FUN_ram_0004d312; body bytes: 92 */

void FUN_ram_0004d312(int param_1,int param_2,int param_3)

{
  undefined2 *puVar1;
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined1 auStack_24 [24];
  
  gp = 0x20004000;
  if (param_2 == 0) {
    tmos_memset(&uStack_28,0,0x16);
    uStack_28 = (undefined2)param_3;
    if (param_3 == 0) {
      uStack_26 = *(undefined2 *)(param_1 + 2);
      FUN_ram_0004c51c(*(undefined4 *)(param_1 + 0xc),auStack_24);
    }
    puVar1 = &uStack_28;
    param_2 = 0;
  }
  else {
    puVar1 = (undefined2 *)0x0;
  }
  FUN_ram_0004d1f6(*(undefined1 *)(param_1 + 8),*(undefined2 *)(param_1 + 6),param_2,0x60,0,puVar1);
  return;
}

