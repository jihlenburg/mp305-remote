/* Address: ram:0004142e; name: FUN_ram_0004142e; body bytes: 290 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_0004142e(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  puVar1 = DAT_ram_20001e88;
  gp = 0x20004000;
  if (param_1 == 0) {
    do {
    } while (DAT_ram_20001eb0[0x19] != 0);
    DAT_ram_20001e96 = 0;
    (*(code *)&SUB_ram_e00a217a)(param_2,param_3);
    puVar1 = DAT_ram_20001e88;
    *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
    puVar1[0xb] = puVar1[0xb] & 0xfffffffc;
    DAT_ram_20001e99 = 0;
    DAT_ram_20001e95 = 0;
    *DAT_ram_20001eb0 = 2;
    _DAT_ram_e000ed10 = _DAT_ram_e000ed10 & 0xfffffff3;
    wfi();
  }
  else if (param_1 == 3) {
    *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
    puVar1[0xb] = puVar1[0xb] & 0xfffffffc;
  }
  else if (param_1 == 1) {
    DAT_ram_20001eb0[3] = 0xd00f;
    puVar2 = DAT_ram_20001eb0;
    fence.i();
    DAT_ram_20001eb0[2] = 0x2000;
    DAT_ram_20001e98 = 0x80;
    if ((*DAT_ram_20001e88 >> 0xc & 3) == 2) {
      uVar3 = 0x43e;
    }
    else if ((*DAT_ram_20001e88 >> 0xc & 3) == 0) {
      uVar3 = 0x196;
    }
    else {
      uVar3 = 0x1be;
    }
    puVar2[0x19] = uVar3;
    puVar2[3] = 0xf00f;
  }
  while( true ) {
    if ((DAT_ram_20001e96 & 1) != 0) {
      gp = 0x20004000;
      return;
    }
    if ((DAT_ram_20001e97 & 1) != 0) break;
    if (DAT_ram_20001eb0[0x19] == 0) {
      return;
    }
  }
  gp = 0x20004000;
  DAT_ram_20001e98 = 0;
  return;
}

