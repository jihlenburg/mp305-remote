/* Address: ram:00048936; name: GATT_DiscAllChars; body bytes: 42 */

void GATT_DiscAllChars(undefined4 param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined *puStack_24;
  undefined1 uStack_22;
  
  gp = 0x20004000;
  puStack_24 = &medeleg;
  uStack_22 = 0x28;
  uStack_28 = param_2;
  uStack_26 = param_3;
  FUN_ram_0004864e(param_1,&uStack_28,0);
  return;
}

