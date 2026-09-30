/* Address: ram:0004e602; name: FUN_ram_0004e602; body bytes: 52 */

void FUN_ram_0004e602(uint param_1,int param_2)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if (((*(ushort **)(iVar1 + 0x34) != (ushort *)0x0) && (**(ushort **)(iVar1 + 0x34) == param_1)) &&
     (param_2 == 1)) {
    FUN_ram_0004e524();
    return;
  }
  return;
}

