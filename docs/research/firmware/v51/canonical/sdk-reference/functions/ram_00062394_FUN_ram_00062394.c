/* Address: ram:00062394; name: FUN_ram_00062394; body bytes: 328 */

void FUN_ram_00062394(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  
  puVar1 = DAT_ram_20001eb0;
  gp = 0x20004000;
  if ((*DAT_ram_20001eb0 & 3) != 0) {
    DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
    *puVar1 = *puVar1 | 8;
  }
  puVar1 = DAT_ram_20001e88;
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
  puVar2 = DAT_ram_20001eb0;
  DAT_ram_20001eb0[0x1c] = DAT_ram_20001ea8;
  *puVar1 = *puVar1 & 0xfffffe7f;
  *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
  iVar3 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  puVar2[0x14] = 0xda;
  puVar2[0x19] = 0xa0;
  if (param_2 == 0) {
    *(uint *)(iVar3 + 0x2c) = *(uint *)(iVar3 + 0x2c) & 0xfffffffd;
    *puVar1 = *puVar1 & 0xffffff80 | param_1 & 0x7f;
    uVar4 = 0x8e89bed6;
  }
  else {
    *(uint *)(iVar3 + 0x2c) = *(uint *)(iVar3 + 0x2c) & 0xfffffffd;
    *puVar1 = *puVar1 & 0xffffff80 | param_1 & 0x7f | 0x40;
    uVar4 = 0x71764129;
  }
  puVar1[2] = uVar4;
  puVar1[1] = 0x555555;
  DAT_ram_20001e96 = 0;
  DAT_ram_20001e97 = 0;
  DAT_ram_20001e98 = 0;
  puVar2[1] = puVar2[1] & 0xfffffffe;
  DAT_ram_20001e9b = 4;
  FUN_ram_200011be(0,param_4);
  if (DAT_ram_20001e90 != 0) {
    **(uint **)(DAT_ram_20001e90 + 4) =
         **(uint **)(DAT_ram_20001e90 + 4) | *(uint *)(DAT_ram_20001e90 + 8);
  }
  if ((DAT_ram_20001e97 & 1) != 0) {
    DAT_ram_20001d68 = DAT_ram_20001d68 + 1;
  }
  return;
}

