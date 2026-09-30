/* Address: 00011e3c; name: FUN_00011e3c; body bytes: 94 */

uint FUN_00011e3c(undefined1 *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = 1;
  uVar4 = (uint)(byte)DAT_1fffa34a;
  *param_1 = 0xbc;
  uVar1 = 0;
  do {
    iVar3 = uVar4 * 0x24 + uVar1 * 4;
    param_1[uVar2] = (&DAT_1fffa1d8)[iVar3];
    uVar2 = uVar2 + 1 & 0xff;
    param_1[uVar2] = (&DAT_1fffa1d9)[iVar3];
    uVar2 = uVar2 + 1 & 0xff;
    param_1[uVar2] = (&DAT_1fffa1da)[iVar3];
    uVar2 = uVar2 + 1 & 0xff;
    param_1[uVar2] = (&DAT_1fffa1db)[iVar3];
    (&DAT_1fff9bc0)[uVar1] = *(undefined4 *)(&DAT_1fffa1d8 + iVar3);
    uVar1 = uVar1 + 1 & 0xff;
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar1 < 9);
  DAT_1ffe0190 = DAT_1fffaaf1;
  return uVar2;
}

