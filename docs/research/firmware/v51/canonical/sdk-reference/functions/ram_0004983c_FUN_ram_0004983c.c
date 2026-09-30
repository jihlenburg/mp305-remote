/* Address: ram:0004983c; name: FUN_ram_0004983c; body bytes: 126 */

undefined1 FUN_ram_0004983c(undefined2 *param_1,int param_2,ushort *param_3)

{
  ushort uVar1;
  bool bVar2;
  
  gp = 0x20004000;
  if (param_2 == 7) {
    *(char *)(param_1 + 0x12) = *(char *)(param_1 + 0x12) + '\x01';
    uVar1 = *(ushort *)(*(int *)(param_3 + 2) + (*param_3 - 1) * 4);
    bVar2 = false;
    if (uVar1 < (ushort)param_1[7]) {
      param_1[6] = uVar1 + 1;
      FUN_ram_00048cce(*param_1,param_1 + 6);
      FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
      return 0x16;
    }
  }
  else {
    bVar2 = true;
    if ((char)param_3[2] == '\n') {
      bVar2 = *(char *)(param_1 + 0x12) == '\0';
    }
  }
  return bVar2;
}

