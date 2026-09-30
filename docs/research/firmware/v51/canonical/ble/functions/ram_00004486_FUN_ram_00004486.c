/* Address: ram:00004486; name: FUN_ram_00004486; body bytes: 334 */

uint FUN_ram_00004486(undefined1 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  gp = &DAT_ram_20002000;
  *param_1 = 0xbb;
  param_1[1] = DAT_ram_20004c08;
  uVar1 = 2;
  for (uVar4 = 0; uVar4 < DAT_ram_20004c08; uVar4 = uVar4 + 1 & 0xff) {
    iVar2 = uVar4 * 6;
    uVar5 = uVar1 + 7;
    param_1[uVar1] = (&DAT_ram_20004be5)[iVar2];
    param_1[uVar1 + 1 & 0xff] = (&DAT_ram_20004be6)[iVar2];
    param_1[uVar1 + 2 & 0xff] = (&DAT_ram_20004be7)[iVar2];
    param_1[uVar1 + 3 & 0xff] = (&DAT_ram_20004be8)[iVar2];
    param_1[uVar1 + 4 & 0xff] = (&DAT_ram_20004be9)[iVar2];
    param_1[uVar1 + 5 & 0xff] = (&DAT_ram_20004bea)[iVar2];
    param_1[uVar1 + 6 & 0xff] = (&DAT_ram_20004c03)[uVar4];
    for (uVar3 = 0; uVar1 = uVar3 + (uVar5 & 0xff) & 0xff, uVar3 < (byte)(&DAT_ram_20004c03)[uVar4];
        uVar3 = uVar3 + 1 & 0xff) {
      param_1[uVar1] = (&DAT_ram_20004b4a)[uVar4 * 0x1f + uVar3];
    }
  }
  FUN_ram_000042a4(param_1,uVar1,0);
  if ((byte)(DAT_ram_20002f94 + 1U) < 0xf) {
    if (DAT_ram_20002ff4 == 0) {
      gp = &DAT_ram_20002000;
      DAT_ram_20002f94 = DAT_ram_20002f94 + '\x01';
      return uVar1;
    }
  }
  else if (DAT_ram_20002ff4 == 0) {
    DAT_ram_20002f94 = DAT_ram_20002f94 + '\x01';
    FUN_ram_00001d1a(&DAT_ram_20004b40,0,0xcc);
  }
  DAT_ram_20002f94 = 0;
  return uVar1;
}

