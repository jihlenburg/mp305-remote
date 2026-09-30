/* Address: ram:000682a2; name: thunk_FUN_ram_000519f6; body bytes: 4 */

void thunk_FUN_ram_000519f6
               (undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
               undefined2 param_5)

{
  int iVar1;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined2 uStack_14;
  undefined2 uStack_12;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if (iVar1 != 0) {
    uStack_18 = param_2;
    uStack_16 = param_3;
    uStack_14 = param_4;
    uStack_12 = param_5;
    FUN_ram_0004de08(param_1,&uStack_18,0xff);
  }
  return;
}

