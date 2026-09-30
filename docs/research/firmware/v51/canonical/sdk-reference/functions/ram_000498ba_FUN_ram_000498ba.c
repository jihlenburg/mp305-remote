/* Address: ram:000498ba; name: FUN_ram_000498ba; body bytes: 120 */

undefined1 FUN_ram_000498ba(undefined2 *param_1,int param_2,ushort *param_3)

{
  undefined1 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  if (param_2 == 0xd) {
    *(char *)(param_1 + 0x12) = *(char *)(param_1 + 0x12) + '\x01';
    iVar2 = ATT_GetMTU(*param_1);
    uVar1 = 0;
    if (iVar2 + -1 <= (int)(uint)*param_3) {
      param_1[7] = *param_3 + param_1[7];
      FUN_ram_0004373c(*param_1,param_1 + 6);
      FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
      uVar1 = 0x16;
    }
  }
  else {
    uVar1 = 1;
    if ((char)param_3[2] == '\a') {
      uVar1 = *(char *)(param_1 + 0x12) == '\0';
    }
  }
  return uVar1;
}

