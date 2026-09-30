/* Address: ram:00062784; name: FUN_ram_00062784; body bytes: 308 */

/* WARNING: Removing unreachable block (ram,0x000627dc) */
/* WARNING: Removing unreachable block (ram,0x00062888) */
/* WARNING: Removing unreachable block (ram,0x00062846) */
/* WARNING: Removing unreachable block (ram,0x000627d8) */
/* WARNING: Removing unreachable block (ram,0x000627fa) */

void FUN_ram_00062784(uint param_1,uint param_2)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_ram_20001efc;
  puVar1 = DAT_ram_20001e88;
  gp = 0x20004000;
  if (param_2 == 0) {
    *(uint *)(DAT_ram_20001efc + 0x2c) = *(uint *)(DAT_ram_20001efc + 0x2c) & 0xfffffffd;
    *puVar1 = param_1 & 0x7f | *puVar1 & 0xffffff80;
    goto LAB_ram_0006280a;
  }
  if (param_1 < 0x24aea0) {
    uVar3 = *DAT_ram_20001e88 & 0xffffff80 | 0x25;
  }
  else if (param_1 < 0x250490) {
    uVar3 = (param_1 - 0x24a6d0) / 2000 - 1;
LAB_ram_0006284c:
    uVar3 = uVar3 & 0x7f | *DAT_ram_20001e88 & 0xffffff80;
  }
  else if (param_1 == 0x250490) {
    uVar3 = *DAT_ram_20001e88 & 0xffffff80 | 0x26;
  }
  else {
    if (param_1 < 0x25d780) {
      uVar3 = (param_1 - 0x24a6d0) / 2000 - 2;
      goto LAB_ram_0006284c;
    }
    uVar3 = *DAT_ram_20001e88 & 0xffffff80 | 0x27;
  }
  *DAT_ram_20001e88 = uVar3;
  if ((param_2 & 1) != 0) {
    if ((param_2 & 0x30) == 0x10) {
      param_1 = param_1 - 2000;
    }
    else {
      param_1 = param_1 - 1000;
    }
  }
  *(uint *)(iVar2 + 0x2c) = *(uint *)(iVar2 + 0x2c) | 2;
  *(uint *)(iVar2 + 0x44) = *(uint *)(iVar2 + 0x44) & 0xfe0fffff | (param_1 / 64000 & 0x1f) << 0x14;
  *(uint *)(iVar2 + 0x44) =
       (param_1 % 64000 << 10) / 0xfa & 0x3ffff | *(uint *)(iVar2 + 0x44) & 0xfffc0000;
LAB_ram_0006280a:
  if ((DAT_ram_20001eb4 & 2) != 0) {
    *puVar1 = *puVar1 & 0xffffff80 | *puVar1 & 0x7f | 0x40;
  }
  return;
}

