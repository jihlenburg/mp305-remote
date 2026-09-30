/* Address: ram:00061f0a; name: FUN_ram_00061f0a; body bytes: 294 */

void FUN_ram_00061f0a(uint param_1,int param_2)

{
  undefined4 *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  puVar1 = DAT_ram_20001e90;
  gp = 0x20004000;
  if (DAT_ram_20001e90 != (undefined4 *)0x0) {
    *(uint *)DAT_ram_20001e90[4] = *(uint *)DAT_ram_20001e90[4] | DAT_ram_20001e90[5];
    puVar2 = (uint *)*puVar1;
    *puVar2 = puVar1[2] | *puVar2;
  }
  iVar3 = DAT_ram_20001eb0;
  puVar2 = DAT_ram_20001e88;
  uVar4 = (uint)DAT_ram_20001e9e;
  if ((param_1 & 2) == 0) {
    iVar5 = uVar4 + 0x9e;
    if ((param_1 & 1) != 0) {
      *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffcfff;
      *(undefined4 *)(iVar3 + 0xc) = 0xd00f;
      iVar3 = DAT_ram_20001eb0;
      fence.i();
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      param_2 = (param_2 + 0xb) * 4;
      goto LAB_ram_00061f9e;
    }
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffcfff | 0x1000;
    *(undefined4 *)(iVar3 + 0xc) = 0xd00f;
    iVar3 = DAT_ram_20001eb0;
    fence.i();
    param_2 = param_2 + 10;
    *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
  }
  else {
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffcfff | 0x2000;
    param_2 = (param_2 + 2) * 8;
    iVar5 = uVar4 + 0xbe;
    if (param_1 == 3) {
      *puVar2 = *puVar2 & 0xffff3fff | 0x4000;
      *(undefined4 *)(iVar3 + 0xc) = 0xd00f;
      iVar3 = DAT_ram_20001eb0;
      fence.i();
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      param_2 = (param_2 + 0xd7) * 2;
      goto LAB_ram_00061f9e;
    }
    *puVar2 = *puVar2 & 0xffff3fff;
    *(undefined4 *)(iVar3 + 0xc) = 0xd00f;
    iVar3 = DAT_ram_20001eb0;
    fence.i();
    param_2 = param_2 + 0x4a;
    *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
  }
  param_2 = param_2 << 3;
LAB_ram_00061f9e:
  DAT_ram_20001e98 = 0x80;
  *(int *)(iVar3 + 100) = (param_2 + iVar5) * 2;
  *(undefined4 *)(iVar3 + 0xc) = 0xf00f;
  return;
}

