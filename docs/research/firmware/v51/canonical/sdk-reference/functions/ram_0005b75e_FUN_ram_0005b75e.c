/* Address: ram:0005b75e; name: FUN_ram_0005b75e; body bytes: 142 */

undefined4 FUN_ram_0005b75e(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined4 uVar4;
  int iVar5;
  
  gp = 0x20004000;
  iVar5 = *(int *)(param_1 + 0x114);
  if ((ushort)(*(short *)(iVar5 + 3) - 0x1bU) < 0xe1) {
    sVar1 = *(short *)(iVar5 + 5);
    if ((ushort)(sVar1 - 0x148U) < 0x4149) {
      sVar2 = *(short *)(iVar5 + 7);
      if ((ushort)(sVar2 - 0x1bU) < 0xe1) {
        sVar3 = *(short *)(iVar5 + 9);
        if ((ushort)(sVar3 - 0x148U) < 0x4149) {
          *(short *)(param_1 + 0x1bc) = *(short *)(iVar5 + 3);
          *(short *)(param_1 + 0x1be) = sVar1;
          *(short *)(param_1 + 0x1c0) = sVar2;
          *(short *)(param_1 + 0x1c2) = sVar3;
          uVar4 = FUN_ram_00055b56();
          return uVar4;
        }
      }
    }
  }
  return 1;
}

