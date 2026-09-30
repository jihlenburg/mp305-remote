/* Address: ram:0005d732; name: FUN_ram_0005d732; body bytes: 76 */

void FUN_ram_0005d732(int param_1)

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
    return;
  }
  return;
}

