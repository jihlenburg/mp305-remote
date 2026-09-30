/* Address: ram:0004d656; name: FUN_ram_0004d656; body bytes: 252 */

int FUN_ram_0004d656(int param_1,undefined2 *param_2)

{
  short sVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  
  gp = 0x20004000;
  if ((param_2[1] == 0) || (DAT_ram_20001a5e < (ushort)param_2[1])) {
    return 0x1b;
  }
  puVar2 = (undefined1 *)FUN_ram_00041bf2(*(undefined4 *)(param_2 + 2),4);
  *puVar2 = (char)param_2[1];
  puVar2[1] = (char)((ushort)param_2[1] >> 8);
  puVar2[2] = (char)*param_2;
  puVar2[3] = (char)((ushort)*param_2 >> 8);
  sVar1 = param_2[1];
  if (param_1 == 0xfffe) {
    puVar3 = (undefined1 *)tmos_msg_allocate(0xc);
    if (puVar3 != (undefined1 *)0x0) {
      *puVar3 = 0x90;
      *(undefined2 *)(puVar3 + 2) = 0xfffe;
      puVar3[4] = 2;
      *(short *)(puVar3 + 6) = sVar1 + 4;
      *(undefined1 **)(puVar3 + 8) = puVar2;
      tmos_msg_send(DAT_ram_20001cc8,puVar3);
      gp = 0x20004000;
      return 0;
    }
    gp = 0x20004000;
    return 0x13;
  }
  iVar4 = thunk_FUN_ram_000681b0(param_1,0,sVar1 + 4,puVar2);
  if (iVar4 != 0) {
    if (iVar4 == 2) {
      gp = 0x20004000;
      return 0x14;
    }
    if (iVar4 == 7) {
      gp = 0x20004000;
      return 4;
    }
    if (iVar4 == 0x12) {
      gp = 0x20004000;
      return 2;
    }
    if (iVar4 != 0x1f) {
      gp = 0x20004000;
      return iVar4;
    }
  }
  if (DAT_ram_20001a62 != '\0') {
    DAT_ram_20001a62 = DAT_ram_20001a62 + -1;
  }
  return 0;
}

