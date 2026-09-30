/* Address: ram:0006681c; name: FUN_ram_0006681c; body bytes: 300 */

undefined4 FUN_ram_0006681c(undefined4 param_1,byte *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = 1;
    if ((*(char *)(iVar1 + 0xb) == '\x01') && (uVar2 = 0, *(char *)(iVar1 + 0x10) == '$')) {
      iVar3 = (uint)param_2[0xe] * 0x100 + (uint)param_2[0xd] * 0x10000 + (uint)param_2[0xf] +
              (uint)param_2[0xc] * 0x1000000;
      if (*(char *)(iVar1 + 0x4b) == '\0') {
        *(int *)(iVar1 + 0xcc) = iVar3;
        *(uint *)(iVar1 + 0xd0) =
             (uint)param_2[10] * 0x100 + (uint)param_2[9] * 0x10000 + (uint)param_2[0xb] +
             (uint)param_2[8] * 0x1000000;
        *(uint *)(iVar1 + 0xd4) =
             (uint)param_2[6] * 0x100 + (uint)param_2[5] * 0x10000 + (uint)param_2[7] +
             (uint)param_2[4] * 0x1000000;
        *(uint *)(iVar1 + 0xd8) =
             (uint)param_2[2] * 0x100 + (uint)param_2[1] * 0x10000 + (uint)param_2[3] +
             (uint)*param_2 * 0x1000000;
      }
      else {
        *(int *)(iVar1 + 0xac) = iVar3;
        *(uint *)(iVar1 + 0xb0) =
             (uint)param_2[10] * 0x100 + (uint)param_2[9] * 0x10000 + (uint)param_2[0xb] +
             (uint)param_2[8] * 0x1000000;
        *(uint *)(iVar1 + 0xb4) =
             (uint)param_2[6] * 0x100 + (uint)param_2[5] * 0x10000 + (uint)param_2[7] +
             (uint)param_2[4] * 0x1000000;
        *(uint *)(iVar1 + 0xb8) =
             (uint)param_2[2] * 0x100 + (uint)param_2[1] * 0x10000 + (uint)param_2[3] +
             (uint)*param_2 * 0x1000000;
      }
      *(undefined1 *)(iVar1 + 0x10) = 0x2a;
      uVar2 = 0;
    }
  }
  return uVar2;
}

