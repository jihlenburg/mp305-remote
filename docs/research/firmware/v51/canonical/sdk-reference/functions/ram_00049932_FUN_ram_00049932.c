/* Address: ram:00049932; name: FUN_ram_00049932; body bytes: 146 */

undefined4 FUN_ram_00049932(undefined2 *param_1,int param_2,ushort *param_3)

{
  ushort uVar1;
  ushort uVar2;
  
  gp = 0x20004000;
  if (param_2 == 0x11) {
    uVar1 = *param_3;
    uVar2 = param_3[1];
    *(char *)(param_1 + 0x12) = *(char *)(param_1 + 0x12) + '\x01';
    uVar1 = *(ushort *)(*(int *)(param_3 + 2) + ((uVar1 - 1) * (uint)uVar2 & 0xffff) + 2);
    if ((uVar1 != 0xffff) && (param_1[6] = uVar1 + 1, uVar1 < (ushort)param_1[7])) {
      FUN_ram_000437d2(*param_1,param_1 + 6);
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

