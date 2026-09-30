/* Address: 00040c74; name: FUN_00040c74; body bytes: 112 */

undefined8 FUN_00040c74(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  local_20 = param_1;
  local_1c = param_2;
  if ((2 < *(byte *)(param_2 + 0x3c)) && (*(int *)(param_2 + 0x20) != 0)) {
    if (*(float *)(param_2 + 0x24) != *(float *)(param_2 + 0x28)) {
      local_20 = *(int *)(param_2 + 0x2c) - (uint)*(ushort *)(param_2 + 0x34);
      local_1c = *(int *)(param_2 + 0x30) - (uint)*(ushort *)(param_2 + 0x34);
      local_18 = *(int *)(param_2 + 0x2c) + (uint)*(ushort *)(param_2 + 0x34) + -1;
      local_14 = *(int *)(param_2 + 0x30) + (uint)*(ushort *)(param_2 + 0x34) + -1;
      iVar1 = FUN_00040c36(param_1,&local_20);
      uVar2 = FUN_0004a318(0x40);
      *(undefined4 *)(iVar1 + 0x4c) = uVar2;
      FUN_0004a404(uVar2,param_2,0x40);
      *(undefined1 *)(iVar1 + 4) = 8;
      FUN_0004197c(param_1,iVar1);
    }
  }
  return CONCAT44(local_1c,local_20);
}

