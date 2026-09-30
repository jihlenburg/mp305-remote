/* Address: ram:0004c756; name: FUN_ram_0004c756; body bytes: 44 */

void FUN_ram_0004c756(undefined2 param_1,undefined2 param_2)

{
  undefined2 uStack_14;
  undefined2 auStack_12 [7];
  
  gp = 0x20004000;
  if (DAT_ram_20001a5c == '\x01') {
    uStack_14 = param_2;
    auStack_12[0] = param_1;
    FUN_ram_00052522(1,auStack_12,&uStack_14);
  }
  return;
}

