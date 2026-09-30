/* Address: ram:00008b08; name: FUN_ram_00008b08; body bytes: 48 */

void FUN_ram_00008b08(undefined4 param_1,int param_2)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  iVar1 = FUN_ram_00008cda(param_1,(int)*(short *)(param_2 + 0xe));
  if (iVar1 < 0) {
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 0xefff;
  }
  else {
    *(int *)(param_2 + 0x54) = *(int *)(param_2 + 0x54) + iVar1;
  }
  return;
}

