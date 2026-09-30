/* Address: ram:0005d790; name: FUN_ram_0005d790; body bytes: 96 */

void FUN_ram_0005d790(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = DAT_ram_20001e1c;
  while( true ) {
    if (iVar1 == 0) {
      return;
    }
    if (iVar1 == param_1) break;
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  if (*(char *)(param_1 + 10) != '\0') {
    FUN_ram_000529ae(param_1 + 0x1a,param_1 + 0xc);
  }
  if (*(char *)(param_1 + 0x12) != '\0') {
    FUN_ram_000529ae(param_1 + 0x2a,param_1 + 0x14);
  }
  FUN_ram_0005d77e(param_1,DAT_ram_20001d94);
  return;
}

