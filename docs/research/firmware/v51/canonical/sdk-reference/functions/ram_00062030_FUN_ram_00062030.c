/* Address: ram:00062030; name: FUN_ram_00062030; body bytes: 280 */

void FUN_ram_00062030(uint param_1,int param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  
  iVar3 = DAT_ram_20001e90;
  gp = 0x20004000;
  if (DAT_ram_20001e90 != 0) {
    **(uint **)(DAT_ram_20001e90 + 4) =
         **(uint **)(DAT_ram_20001e90 + 4) | *(uint *)(DAT_ram_20001e90 + 8);
    puVar4 = *(uint **)(iVar3 + 0xc);
    *puVar4 = *(uint *)(iVar3 + 0x14) | *puVar4;
  }
  puVar4 = DAT_ram_20001e88;
  bVar1 = DAT_ram_20001e8c & 1;
  bVar2 = DAT_ram_20001e8c & 1;
  if ((param_1 & 2) == 0) {
    DAT_ram_20001e88[8] = 0x90083;
    puVar4[5] = 0x8101901;
    puVar4[6] = 0x31624;
    puVar4[10] = 0x28be;
    puVar4[9] = 0x1006310;
    if (bVar2 == 0) {
      uVar5 = 0x3722d0;
    }
    else {
      uVar5 = 0x3fa2ce;
    }
    puVar4[4] = uVar5;
    if (param_1 == 1) {
      *puVar4 = *puVar4 & 0xffffcfff;
      iVar3 = (param_2 + 5) * 8;
    }
    else {
      *puVar4 = *puVar4 & 0xffffcfff | 0x1000;
      iVar3 = (param_2 + 5) * 0x10;
    }
    DAT_ram_20001ea0 = iVar3 + 0x3c;
  }
  else {
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffcfff | 0x2000;
    puVar4[8] = 0x90086;
    puVar4[5] = 0x8301ff1;
    puVar4[6] = 0x31619;
    puVar4[10] = 0x28de;
    puVar4[9] = 0x1006310;
    if (bVar1 == 0) {
      uVar5 = 0x3722df;
    }
    else {
      uVar5 = 0x3fa4df;
    }
    puVar4[4] = uVar5;
    DAT_ram_20001ea0 = param_2 * 0x80 + 0x364;
  }
  if (param_3 != 0) {
    DAT_ram_20001ea0 = param_3 << 1;
  }
  return;
}

