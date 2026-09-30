/* Address: ram:000666ca; name: FUN_ram_000666ca; body bytes: 338 */

undefined4 FUN_ram_000666ca(undefined4 param_1,undefined4 param_2,undefined4 param_3,byte *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    uVar2 = 2;
    if (*(char *)(iVar1 + 0xb) == '\0') {
      tmos_memcpy(iVar1 + 399,param_2,8);
      *(char *)(iVar1 + 0x197) = (char)param_3;
      *(char *)(iVar1 + 0x198) = (char)((uint)param_3 >> 8);
      iVar4 = (uint)param_4[0xe] * 0x100 + (uint)param_4[0xd] * 0x10000 + (uint)param_4[0xf] +
              (uint)param_4[0xc] * 0x1000000;
      if (*(char *)(iVar1 + 0x4a) == '\0') {
        *(int *)(iVar1 + 0xcc) = iVar4;
        uVar3 = *(uint *)(iVar1 + 0xa4) | 8;
        *(uint *)(iVar1 + 0xd0) =
             (uint)param_4[10] * 0x100 + (uint)param_4[9] * 0x10000 + (uint)param_4[0xb] +
             (uint)param_4[8] * 0x1000000;
        *(uint *)(iVar1 + 0xd4) =
             (uint)param_4[6] * 0x100 + (uint)param_4[5] * 0x10000 + (uint)param_4[7] +
             (uint)param_4[4] * 0x1000000;
        *(uint *)(iVar1 + 0xd8) =
             (uint)param_4[2] * 0x100 + (uint)param_4[1] * 0x10000 + (uint)param_4[3] +
             (uint)*param_4 * 0x1000000;
      }
      else {
        *(int *)(iVar1 + 0xac) = iVar4;
        uVar3 = *(uint *)(iVar1 + 0xa4) | 0x20;
        *(uint *)(iVar1 + 0xb0) =
             (uint)param_4[10] * 0x100 + (uint)param_4[9] * 0x10000 + (uint)param_4[0xb] +
             (uint)param_4[8] * 0x1000000;
        *(uint *)(iVar1 + 0xb4) =
             (uint)param_4[6] * 0x100 + (uint)param_4[5] * 0x10000 + (uint)param_4[7] +
             (uint)param_4[4] * 0x1000000;
        *(uint *)(iVar1 + 0xb8) =
             (uint)param_4[2] * 0x100 + (uint)param_4[1] * 0x10000 + (uint)param_4[3] +
             (uint)*param_4 * 0x1000000;
        *(undefined1 *)(iVar1 + 0x4b) = 1;
      }
      *(uint *)(iVar1 + 0xa4) = uVar3;
      uVar2 = 0;
    }
  }
  return uVar2;
}

