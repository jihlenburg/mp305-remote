/* Address: ram:00043800; name: FUN_ram_00043800; body bytes: 104 */

undefined4 FUN_ram_00043800(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  gp = 0x20004000;
  uVar3 = 0x12;
  if (*(char *)(param_2 + 8) == '\x01') {
    iVar1 = ATT_GetMTU();
    uVar3 = 0x92;
    if (iVar1 + -0xe <= (int)(uint)*(ushort *)(param_2 + 2)) {
      return 2;
    }
  }
  if (*(char *)(param_2 + 9) == '\x01') {
    uVar3 = uVar3 | 0x40;
  }
  uVar2 = 0;
  if (*(int *)(param_2 + 4) != 0) {
    uVar2 = FUN_ram_00041bf2(*(int *)(param_2 + 4),3);
  }
  uVar2 = FUN_ram_0004332a(param_1,&LAB_ram_00043500,uVar3,param_2,uVar2);
  return uVar2;
}

