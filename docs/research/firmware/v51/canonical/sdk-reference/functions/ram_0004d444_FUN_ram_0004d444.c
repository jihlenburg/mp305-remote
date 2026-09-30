/* Address: ram:0004d444; name: FUN_ram_0004d444; body bytes: 158 */

void FUN_ram_0004d444(int param_1,undefined4 param_2)

{
  undefined2 *puVar1;
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined2 uStack_24;
  undefined2 uStack_22;
  undefined4 uStack_20;
  
  gp = 0x20004000;
  puVar1 = *(undefined2 **)(param_1 + 0xc);
  if (puVar1 == (undefined2 *)0x0) {
    tmos_memset(&uStack_28,0,0xc);
    uStack_28 = *(undefined2 *)(param_1 + 2);
    FUN_ram_0004d1f6(*(undefined1 *)(param_1 + 8),*(undefined2 *)(param_1 + 6),param_2,100,0,
                     &uStack_28);
  }
  else {
    if (*(int *)(puVar1 + 6) != 0) {
      FUN_ram_20000104();
      *(undefined4 *)(puVar1 + 6) = 0;
    }
    uStack_26 = *puVar1;
    uStack_24 = puVar1[1];
    uStack_22 = puVar1[4];
    uStack_20 = *(undefined4 *)(puVar1 + 8);
    uStack_28 = *(undefined2 *)(param_1 + 2);
    FUN_ram_0004d1f6(*(undefined1 *)(param_1 + 8),*(undefined2 *)(param_1 + 6),param_2,100,0,
                     &uStack_28);
    *(char *)((int)puVar1 + 0x1d) = (char)param_2;
    *(undefined4 *)(puVar1 + 8) = 0;
  }
  return;
}

