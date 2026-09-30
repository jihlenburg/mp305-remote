/* Address: ram:00008160; name: FUN_ram_00008160; body bytes: 158 */

void FUN_ram_00008160(int param_1,int *param_2)

{
  ushort uVar1;
  int iVar2;
  int iStack_18;
  int iStack_14;
  
  gp = &DAT_ram_20002000;
  if ((*(ushort *)(param_2 + 3) & 2) == 0) {
    uVar1 = FUN_ram_00008106(param_1,param_2,&iStack_18,&iStack_14);
    iVar2 = FUN_ram_000082ae(param_1,iStack_18);
    if (iVar2 != 0) {
      *(code **)(param_1 + 0x28) = FUN_ram_00007f40;
      *param_2 = iVar2;
      param_2[4] = iVar2;
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x80;
      param_2[5] = iStack_18;
      if ((iStack_14 != 0) &&
         (iVar2 = FUN_ram_00008c58(param_1,(int)*(short *)((int)param_2 + 0xe)), iVar2 != 0)) {
        *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) & 0xfffc | 1;
      }
      *(ushort *)(param_2 + 3) = uVar1 | *(ushort *)(param_2 + 3);
      gp = &DAT_ram_20002000;
      return;
    }
    if ((*(ushort *)(param_2 + 3) & 0x200) != 0) {
      gp = &DAT_ram_20002000;
      return;
    }
    *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) & 0xfffc | 2;
  }
  *param_2 = (int)param_2 + 0x47;
  param_2[4] = (int)param_2 + 0x47;
  param_2[5] = 1;
  return;
}

