/* Address: ram:00008b86; name: FUN_ram_00008b86; body bytes: 54 */

void FUN_ram_00008b86(undefined4 param_1,int param_2)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  iVar1 = FUN_ram_00008c88(param_1,(int)*(short *)(param_2 + 0xe));
  if (iVar1 == -1) {
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 0xefff;
  }
  else {
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) | 0x1000;
    *(int *)(param_2 + 0x54) = iVar1;
  }
  return;
}

