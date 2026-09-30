/* Address: ram:000497aa; name: FUN_ram_000497aa; body bytes: 146 */

undefined4 FUN_ram_000497aa(undefined2 *param_1,int param_2,ushort *param_3)

{
  uint uVar1;
  int iVar2;
  
  gp = 0x20004000;
  if (param_2 == 5) {
    *(char *)(param_1 + 0x12) = *(char *)(param_1 + 0x12) + '\x01';
    uVar1 = *param_3 - 1 & 0xffff;
    if ((char)param_3[1] == '\x01') {
      iVar2 = uVar1 << 2;
    }
    else {
      iVar2 = uVar1 * 0x12;
    }
    if (*(ushort *)(iVar2 + *(int *)(param_3 + 2)) < (ushort)param_1[7]) {
      param_1[6] = *(ushort *)(iVar2 + *(int *)(param_3 + 2)) + 1;
      FUN_ram_00043650(*param_1,param_1 + 6);
      FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
      return 0x16;
    }
  }
  else {
    if ((char)param_3[2] != '\n') {
      gp = 0x20004000;
      return 1;
    }
    if (*(char *)(param_1 + 0x12) == '\0') {
      gp = 0x20004000;
      return 1;
    }
  }
  return 0;
}

