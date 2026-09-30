/* Address: ram:00041efc; name: FUN_ram_00041efc; body bytes: 290 */

void FUN_ram_00041efc(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint auStack_14 [2];
  
  gp = 0x20004000;
  uVar1 = FUN_ram_0005667a(auStack_14);
  if (uVar1 == 0xffffffff) {
    if (DAT_ram_20001b74 == 0xa8c00000) {
      gp = 0x20004000;
      return;
    }
    iVar2 = (*DAT_ram_20001c00)();
    uVar1 = iVar2 + (DAT_ram_20001b74 - DAT_ram_20001bd1);
joined_r0x00042014:
    if ((DAT_ram_20001bd2 < '\0') || (uVar1 < 0xa8c00000)) goto LAB_ram_00041f74;
    iVar2 = 0x57400000;
  }
  else {
    uVar3 = (uint)DAT_ram_20001bd1;
    if (auStack_14[0] <= uVar3) {
      gp = 0x20004000;
      return;
    }
    if (DAT_ram_20001b74 != 0xa8c00000) {
      iVar2 = (*DAT_ram_20001c00)();
      uVar1 = DAT_ram_20001b74;
      if (auStack_14[0] < DAT_ram_20001b74) {
        uVar1 = auStack_14[0];
      }
      uVar1 = iVar2 + (uVar1 - DAT_ram_20001bd1);
      goto joined_r0x00042014;
    }
    if ((DAT_ram_20001bd2 < '\0') || (uVar3 <= uVar1)) {
      uVar1 = uVar1 - uVar3;
      goto LAB_ram_00041f74;
    }
    iVar2 = -0x57400000 - uVar3;
  }
  uVar1 = uVar1 + iVar2;
LAB_ram_00041f74:
  if (DAT_ram_20001eac != 0) {
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) & 0xffccffff;
  }
  if (uVar1 == 0) {
    uVar1 = 0xa8c00000;
  }
  iVar2 = (*DAT_ram_20001be0)(uVar1);
  if (iVar2 == 0) {
    if (DAT_ram_20001eac == 0) {
      gp = 0x20004000;
      return;
    }
    FUN_ram_00062730();
    FUN_ram_00061c92();
  }
  if (DAT_ram_20001eac != 0) {
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  }
  return;
}

