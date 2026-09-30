/* Address: ram:00064394; name: FUN_ram_00064394; body bytes: 3396 */

/* WARNING: Removing unreachable block (ram,0x00064dda) */
/* WARNING: Removing unreachable block (ram,0x00064d96) */
/* WARNING: Removing unreachable block (ram,0x00064d56) */
/* WARNING: Removing unreachable block (ram,0x00064d1e) */
/* WARNING: Removing unreachable block (ram,0x00064cdc) */
/* WARNING: Removing unreachable block (ram,0x00064cac) */
/* WARNING: Removing unreachable block (ram,0x00064c74) */
/* WARNING: Removing unreachable block (ram,0x00064c3a) */
/* WARNING: Removing unreachable block (ram,0x00064c00) */
/* WARNING: Removing unreachable block (ram,0x00064bc0) */
/* WARNING: Removing unreachable block (ram,0x00064b7a) */
/* WARNING: Removing unreachable block (ram,0x00064b34) */
/* WARNING: Removing unreachable block (ram,0x00064b14) */
/* WARNING: Removing unreachable block (ram,0x00064ad6) */
/* WARNING: Removing unreachable block (ram,0x00064a96) */
/* WARNING: Removing unreachable block (ram,0x00064a56) */
/* WARNING: Removing unreachable block (ram,0x00064a12) */
/* WARNING: Removing unreachable block (ram,0x000649e6) */
/* WARNING: Removing unreachable block (ram,0x000649a0) */
/* WARNING: Removing unreachable block (ram,0x0006495e) */
/* WARNING: Removing unreachable block (ram,0x0006491c) */
/* WARNING: Removing unreachable block (ram,0x000648ec) */
/* WARNING: Removing unreachable block (ram,0x000648c8) */
/* WARNING: Removing unreachable block (ram,0x00064896) */
/* WARNING: Removing unreachable block (ram,0x00064866) */
/* WARNING: Removing unreachable block (ram,0x00064834) */
/* WARNING: Removing unreachable block (ram,0x000647f4) */
/* WARNING: Removing unreachable block (ram,0x000647d2) */
/* WARNING: Removing unreachable block (ram,0x000647a2) */
/* WARNING: Removing unreachable block (ram,0x00064770) */
/* WARNING: Removing unreachable block (ram,0x0006473a) */
/* WARNING: Removing unreachable block (ram,0x00064704) */
/* WARNING: Removing unreachable block (ram,0x000646ce) */
/* WARNING: Removing unreachable block (ram,0x00064698) */
/* WARNING: Removing unreachable block (ram,0x00064660) */
/* WARNING: Removing unreachable block (ram,0x00064622) */
/* WARNING: Removing unreachable block (ram,0x000645f4) */
/* WARNING: Removing unreachable block (ram,0x000645b6) */
/* WARNING: Removing unreachable block (ram,0x0006457a) */
/* WARNING: Removing unreachable block (ram,0x0006453e) */
/* WARNING: Removing unreachable block (ram,0x0006459a) */
/* WARNING: Removing unreachable block (ram,0x000645d6) */
/* WARNING: Removing unreachable block (ram,0x00064606) */
/* WARNING: Removing unreachable block (ram,0x00064644) */
/* WARNING: Removing unreachable block (ram,0x0006467c) */
/* WARNING: Removing unreachable block (ram,0x000646b4) */
/* WARNING: Removing unreachable block (ram,0x000646e2) */
/* WARNING: Removing unreachable block (ram,0x0006471e) */
/* WARNING: Removing unreachable block (ram,0x00064754) */
/* WARNING: Removing unreachable block (ram,0x0006478a) */
/* WARNING: Removing unreachable block (ram,0x000647b0) */
/* WARNING: Removing unreachable block (ram,0x000647ea) */
/* WARNING: Removing unreachable block (ram,0x0006481a) */
/* WARNING: Removing unreachable block (ram,0x0006484e) */
/* WARNING: Removing unreachable block (ram,0x00064874) */
/* WARNING: Removing unreachable block (ram,0x000648ae) */
/* WARNING: Removing unreachable block (ram,0x000648da) */
/* WARNING: Removing unreachable block (ram,0x0006490a) */
/* WARNING: Removing unreachable block (ram,0x00064952) */
/* WARNING: Removing unreachable block (ram,0x00064992) */
/* WARNING: Removing unreachable block (ram,0x000649c0) */
/* WARNING: Removing unreachable block (ram,0x00064a04) */
/* WARNING: Removing unreachable block (ram,0x00064a38) */
/* WARNING: Removing unreachable block (ram,0x00064a76) */
/* WARNING: Removing unreachable block (ram,0x00064ab6) */
/* WARNING: Removing unreachable block (ram,0x00064ada) */
/* WARNING: Removing unreachable block (ram,0x00064b30) */
/* WARNING: Removing unreachable block (ram,0x00064b68) */
/* WARNING: Removing unreachable block (ram,0x00064ba0) */
/* WARNING: Removing unreachable block (ram,0x00064be0) */
/* WARNING: Removing unreachable block (ram,0x00064c1e) */
/* WARNING: Removing unreachable block (ram,0x00064c58) */
/* WARNING: Removing unreachable block (ram,0x00064c90) */
/* WARNING: Removing unreachable block (ram,0x00064cc8) */
/* WARNING: Removing unreachable block (ram,0x00064d04) */
/* WARNING: Removing unreachable block (ram,0x00064d3a) */
/* WARNING: Removing unreachable block (ram,0x00064d76) */
/* WARNING: Removing unreachable block (ram,0x00064d9a) */
/* WARNING: Removing unreachable block (ram,0x00064dee) */

void FUN_ram_00064394(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  iVar1 = DAT_ram_20001efc;
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001efc + 4) = *(uint *)(DAT_ram_20001efc + 4) & 0xfffffeff;
  *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) & 0xffffefff;
  *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) & 0xffffffef;
  *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | 0x20000;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x10;
  if (DAT_ram_20001ef4 == 0x12345678) {
    DAT_ram_20001ef4 = 0;
  }
  else {
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffffffe;
    *(uint *)(iVar1 + 0x38) = *(uint *)(iVar1 + 0x38) & 0xfffe00ff | 0xbf00;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
    FUN_ram_2000188a();
    iVar1 = DAT_ram_20001efc;
    DAT_ram_20001a75 = (byte)*(undefined4 *)(DAT_ram_20001efc + 0x90) & 0x3f;
    DAT_ram_20001a76 = (byte)(*(uint *)(DAT_ram_20001efc + 0x94) >> 10) & 0x7f;
    *(uint *)(DAT_ram_20001efc + 4) = *(uint *)(DAT_ram_20001efc + 4) & 0xfffffffe;
    *(uint *)(iVar1 + 0x38) = *(uint *)(iVar1 + 0x38) & 0xfffe00ff | 0xe700;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
    FUN_ram_2000188a();
    iVar1 = DAT_ram_20001efc;
    DAT_ram_20001f01 = (byte)*(undefined4 *)(DAT_ram_20001efc + 0x90) & 0x3f;
    DAT_ram_20001ef8 = (byte)(*(uint *)(DAT_ram_20001efc + 0x94) >> 10) & 0x7f;
    *(uint *)(DAT_ram_20001efc + 4) = *(uint *)(DAT_ram_20001efc + 4) & 0xfffffffe;
    *(uint *)(iVar1 + 0x38) = *(uint *)(iVar1 + 0x38) & 0xfffe00ff | 0xd300;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
    FUN_ram_2000188a();
    DAT_ram_20001f00 = (byte)*(undefined4 *)(DAT_ram_20001efc + 0x90) & 0x3f;
    DAT_ram_20001ef0 = (byte)(*(uint *)(DAT_ram_20001efc + 0x94) >> 10) & 0x7f;
  }
  iVar1 = DAT_ram_20001efc;
  uVar8 = (uint)DAT_ram_20001f00;
  uVar5 = DAT_ram_20001a75 - uVar8;
  *(uint *)(DAT_ram_20001efc + 0xa0) = *(uint *)(DAT_ram_20001efc + 0xa0) & 0xfffffff0 | uVar5 & 0xf
  ;
  *(uint *)(iVar1 + 0xa0) =
       ((int)(uVar5 * 0x26) / 0x27 & 0xfU) << 4 | *(uint *)(iVar1 + 0xa0) & 0xffffff0f;
  *(uint *)(iVar1 + 0xa0) =
       ((int)(uVar5 * 0x25) / 0x27 & 0xfU) << 8 | *(uint *)(iVar1 + 0xa0) & 0xfffff0ff;
  *(uint *)(iVar1 + 0xa0) =
       ((int)(uVar5 * 0x24) / 0x27 & 0xfU) << 0xc | *(uint *)(iVar1 + 0xa0) & 0xffff0fff;
  *(uint *)(iVar1 + 0xa0) =
       ((int)(uVar5 * 0x23) / 0x27 & 0xfU) << 0x10 | *(uint *)(iVar1 + 0xa0) & 0xfff0ffff;
  *(uint *)(iVar1 + 0xa0) =
       ((int)(uVar5 * 0x22) / 0x27 & 0xfU) << 0x14 | *(uint *)(iVar1 + 0xa0) & 0xff0fffff;
  *(uint *)(iVar1 + 0xa0) =
       ((int)(uVar5 * 0x21) / 0x27 & 0xfU) << 0x18 | *(uint *)(iVar1 + 0xa0) & 0xf0ffffff;
  *(uint *)(iVar1 + 0xa0) = *(uint *)(iVar1 + 0xa0) & 0xfffffff | (int)(uVar5 * 0x20) / 0x27 << 0x1c
  ;
  *(uint *)(iVar1 + 0xa4) = *(uint *)(iVar1 + 0xa4) & 0xfffffff0 | (int)(uVar5 * 0x1f) / 0x27 & 0xfU
  ;
  *(uint *)(iVar1 + 0xa4) =
       ((int)(uVar5 * 0x1e) / 0x27 & 0xfU) << 4 | *(uint *)(iVar1 + 0xa4) & 0xffffff0f;
  *(uint *)(iVar1 + 0xa4) =
       ((int)(uVar5 * 0x1d) / 0x27 & 0xfU) << 8 | *(uint *)(iVar1 + 0xa4) & 0xfffff0ff;
  *(uint *)(iVar1 + 0xa4) =
       ((int)(uVar5 * 0x1c) / 0x27 & 0xfU) << 0xc | *(uint *)(iVar1 + 0xa4) & 0xffff0fff;
  *(uint *)(iVar1 + 0xa4) =
       ((int)(uVar5 * 0x1b) / 0x27 & 0xfU) << 0x10 | *(uint *)(iVar1 + 0xa4) & 0xfff0ffff;
  *(uint *)(iVar1 + 0xa4) =
       ((int)(uVar5 * 0x1a) / 0x27 & 0xfU) << 0x14 | *(uint *)(iVar1 + 0xa4) & 0xff0fffff;
  *(uint *)(iVar1 + 0xa4) =
       ((int)(uVar5 * 0x19) / 0x27 & 0xfU) << 0x18 | *(uint *)(iVar1 + 0xa4) & 0xf0ffffff;
  *(uint *)(iVar1 + 0xa4) = *(uint *)(iVar1 + 0xa4) & 0xfffffff | (int)(uVar5 * 0x18) / 0x27 << 0x1c
  ;
  *(uint *)(iVar1 + 0xa8) = *(uint *)(iVar1 + 0xa8) & 0xfffffff0 | (int)(uVar5 * 0x17) / 0x27 & 0xfU
  ;
  *(uint *)(iVar1 + 0xa8) =
       ((int)(uVar5 * 0x16) / 0x27 & 0xfU) << 4 | *(uint *)(iVar1 + 0xa8) & 0xffffff0f;
  *(uint *)(iVar1 + 0xa8) =
       ((int)(uVar5 * 0x15) / 0x27 & 0xfU) << 8 | *(uint *)(iVar1 + 0xa8) & 0xfffff0ff;
  *(uint *)(iVar1 + 0xa8) =
       ((int)(uVar5 * 0x14) / 0x27 & 0xfU) << 0xc | *(uint *)(iVar1 + 0xa8) & 0xffff0fff;
  *(uint *)(iVar1 + 0xa8) =
       ((int)(uVar5 * 0x13) / 0x27 & 0xfU) << 0x10 | *(uint *)(iVar1 + 0xa8) & 0xfff0ffff;
  *(uint *)(iVar1 + 0xa8) =
       ((int)(uVar5 * 0x12) / 0x27 & 0xfU) << 0x14 | *(uint *)(iVar1 + 0xa8) & 0xff0fffff;
  *(uint *)(iVar1 + 0xa8) =
       ((int)(uVar5 * 0x11) / 0x27 & 0xfU) << 0x18 | *(uint *)(iVar1 + 0xa8) & 0xf0ffffff;
  *(uint *)(iVar1 + 0xa8) = *(uint *)(iVar1 + 0xa8) & 0xfffffff | (int)(uVar5 * 0x10) / 0x27 << 0x1c
  ;
  *(uint *)(iVar1 + 0xac) = *(uint *)(iVar1 + 0xac) & 0xfffffff0 | (int)(uVar5 * 0xf) / 0x27 & 0xfU;
  *(uint *)(iVar1 + 0xac) =
       ((int)(uVar5 * 0xe) / 0x27 & 0xfU) << 4 | *(uint *)(iVar1 + 0xac) & 0xffffff0f;
  *(uint *)(iVar1 + 0xac) = *(uint *)(iVar1 + 0xac) & 0xfffff0ff | ((int)uVar5 / 3 & 0xfU) << 8;
  *(uint *)(iVar1 + 0xac) =
       ((int)(uVar5 * 0xc) / 0x27 & 0xfU) << 0xc | *(uint *)(iVar1 + 0xac) & 0xffff0fff;
  *(uint *)(iVar1 + 0xac) =
       ((int)(uVar5 * 0xb) / 0x27 & 0xfU) << 0x10 | *(uint *)(iVar1 + 0xac) & 0xfff0ffff;
  *(uint *)(iVar1 + 0xac) =
       ((int)(uVar5 * 10) / 0x27 & 0xfU) << 0x14 | *(uint *)(iVar1 + 0xac) & 0xff0fffff;
  *(uint *)(iVar1 + 0xac) =
       ((int)(uVar5 * 9) / 0x27 & 0xfU) << 0x18 | *(uint *)(iVar1 + 0xac) & 0xf0ffffff;
  *(uint *)(iVar1 + 0xac) = *(uint *)(iVar1 + 0xac) & 0xfffffff | (int)(uVar5 * 8) / 0x27 << 0x1c;
  *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) & 0xfffffff0 | (int)(uVar5 * 7) / 0x27 & 0xfU;
  *(uint *)(iVar1 + 0xb0) =
       ((int)(uVar5 * 6) / 0x27 & 0xfU) << 4 | *(uint *)(iVar1 + 0xb0) & 0xffffff0f;
  *(uint *)(iVar1 + 0xb0) =
       ((int)(uVar5 * 5) / 0x27 & 0xfU) << 8 | *(uint *)(iVar1 + 0xb0) & 0xfffff0ff;
  *(uint *)(iVar1 + 0xb0) =
       ((int)(uVar5 * 4) / 0x27 & 0xfU) << 0xc | *(uint *)(iVar1 + 0xb0) & 0xffff0fff;
  *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) & 0xfff0ffff | ((int)uVar5 / 0xd & 0xfU) << 0x10
  ;
  *(uint *)(iVar1 + 0xb0) =
       ((int)(uVar5 * 2) / 0x27 & 0xfU) << 0x14 | *(uint *)(iVar1 + 0xb0) & 0xff0fffff;
  *(uint *)(iVar1 + 0xb0) =
       *(uint *)(iVar1 + 0xb0) & 0xf0ffffff | ((int)uVar5 / 0x27 & 0xfU) << 0x18;
  *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) & 0xfffffff;
  iVar6 = uVar8 - DAT_ram_20001f01;
  *(uint *)(iVar1 + 0xb4) = *(uint *)(iVar1 + 0xb4) & 0xfffffff0 | iVar6 / 0x28 & 0xfU;
  *(uint *)(iVar1 + 0xb4) = *(uint *)(iVar1 + 0xb4) & 0xffffff0f | (iVar6 / 0x14 & 0xfU) << 4;
  *(uint *)(iVar1 + 0xb4) = *(uint *)(iVar1 + 0xb4) & 0xfffff0ff | ((iVar6 * 3) / 0x28 & 0xfU) << 8;
  *(uint *)(iVar1 + 0xb4) = *(uint *)(iVar1 + 0xb4) & 0xffff0fff | (iVar6 / 10 & 0xfU) << 0xc;
  *(uint *)(iVar1 + 0xb4) = *(uint *)(iVar1 + 0xb4) & 0xfff0ffff | (iVar6 / 8 & 0xfU) << 0x10;
  *(uint *)(iVar1 + 0xb4) =
       *(uint *)(iVar1 + 0xb4) & 0xff0fffff | ((iVar6 * 6) / 0x28 & 0xfU) << 0x14;
  *(uint *)(iVar1 + 0xb4) =
       *(uint *)(iVar1 + 0xb4) & 0xf0ffffff | ((iVar6 * 7) / 0x28 & 0xfU) << 0x18;
  *(uint *)(iVar1 + 0xb4) = *(uint *)(iVar1 + 0xb4) & 0xfffffff | iVar6 / 5 << 0x1c;
  *(uint *)(iVar1 + 0xb8) = *(uint *)(iVar1 + 0xb8) & 0xfffffff0 | (iVar6 * 9) / 0x28 & 0xfU;
  *(uint *)(iVar1 + 0xb8) = *(uint *)(iVar1 + 0xb8) & 0xffffff0f | (iVar6 / 4 & 0xfU) << 4;
  *(uint *)(iVar1 + 0xb8) =
       *(uint *)(iVar1 + 0xb8) & 0xfffff0ff | ((iVar6 * 0xb) / 0x28 & 0xfU) << 8;
  *(uint *)(iVar1 + 0xb8) =
       *(uint *)(iVar1 + 0xb8) & 0xffff0fff | ((iVar6 * 0xc) / 0x28 & 0xfU) << 0xc;
  *(uint *)(iVar1 + 0xb8) =
       *(uint *)(iVar1 + 0xb8) & 0xfff0ffff | ((iVar6 * 0xd) / 0x28 & 0xfU) << 0x10;
  *(uint *)(iVar1 + 0xb8) =
       *(uint *)(iVar1 + 0xb8) & 0xff0fffff | ((iVar6 * 0xe) / 0x28 & 0xfU) << 0x14;
  *(uint *)(iVar1 + 0xb8) =
       *(uint *)(iVar1 + 0xb8) & 0xf0ffffff | ((iVar6 * 0xf) / 0x28 & 0xfU) << 0x18;
  *(uint *)(iVar1 + 0xb8) = *(uint *)(iVar1 + 0xb8) & 0xfffffff | (iVar6 * 0x10) / 0x28 << 0x1c;
  *(uint *)(iVar1 + 0xbc) = *(uint *)(iVar1 + 0xbc) & 0xfffffff0 | (iVar6 * 0x11) / 0x28 & 0xfU;
  *(uint *)(iVar1 + 0xbc) =
       *(uint *)(iVar1 + 0xbc) & 0xffffff0f | ((iVar6 * 0x12) / 0x28 & 0xfU) << 4;
  *(uint *)(iVar1 + 0xbc) =
       *(uint *)(iVar1 + 0xbc) & 0xfffff0ff | ((iVar6 * 0x13) / 0x28 & 0xfU) << 8;
  *(uint *)(iVar1 + 0xbc) = *(uint *)(iVar1 + 0xbc) & 0xffff0fff | (iVar6 / 2 & 0xfU) << 0xc;
  *(uint *)(iVar1 + 0xbc) =
       *(uint *)(iVar1 + 0xbc) & 0xfff0ffff | ((iVar6 * 0x15) / 0x28 & 0xfU) << 0x10;
  *(uint *)(iVar1 + 0xbc) =
       *(uint *)(iVar1 + 0xbc) & 0xff0fffff | ((iVar6 * 0x16) / 0x28 & 0xfU) << 0x14;
  *(uint *)(iVar1 + 0xbc) =
       *(uint *)(iVar1 + 0xbc) & 0xf0ffffff | ((iVar6 * 0x17) / 0x28 & 0xfU) << 0x18;
  *(uint *)(iVar1 + 0xbc) = *(uint *)(iVar1 + 0xbc) & 0xfffffff | (iVar6 * 0x18) / 0x28 << 0x1c;
  *(uint *)(iVar1 + 0xc0) = *(uint *)(iVar1 + 0xc0) & 0xfffffff0 | (iVar6 * 0x19) / 0x28 & 0xfU;
  *(uint *)(iVar1 + 0xc0) =
       *(uint *)(iVar1 + 0xc0) & 0xffffff0f | ((iVar6 * 0x1a) / 0x28 & 0xfU) << 4;
  *(uint *)(iVar1 + 0xc0) =
       *(uint *)(iVar1 + 0xc0) & 0xfffff0ff | ((iVar6 * 0x1b) / 0x28 & 0xfU) << 8;
  *(uint *)(iVar1 + 0xc0) =
       *(uint *)(iVar1 + 0xc0) & 0xffff0fff | ((iVar6 * 0x1c) / 0x28 & 0xfU) << 0xc;
  *(uint *)(iVar1 + 0xc0) =
       *(uint *)(iVar1 + 0xc0) & 0xfff0ffff | ((iVar6 * 0x1d) / 0x28 & 0xfU) << 0x10;
  *(uint *)(iVar1 + 0xc0) =
       *(uint *)(iVar1 + 0xc0) & 0xff0fffff | ((iVar6 * 0x1e) / 0x28 & 0xfU) << 0x14;
  *(uint *)(iVar1 + 0xc0) =
       *(uint *)(iVar1 + 0xc0) & 0xf0ffffff | ((iVar6 * 0x1f) / 0x28 & 0xfU) << 0x18;
  *(uint *)(iVar1 + 0xc0) = *(uint *)(iVar1 + 0xc0) & 0xfffffff | (iVar6 * 0x20) / 0x28 << 0x1c;
  *(uint *)(iVar1 + 0xc4) = *(uint *)(iVar1 + 0xc4) & 0xfffffff0 | (iVar6 * 0x21) / 0x28 & 0xfU;
  *(uint *)(iVar1 + 0xc4) =
       *(uint *)(iVar1 + 0xc4) & 0xffffff0f | ((iVar6 * 0x22) / 0x28 & 0xfU) << 4;
  *(uint *)(iVar1 + 0xc4) =
       *(uint *)(iVar1 + 0xc4) & 0xfffff0ff | ((iVar6 * 0x23) / 0x28 & 0xfU) << 8;
  *(uint *)(iVar1 + 0xc4) =
       *(uint *)(iVar1 + 0xc4) & 0xffff0fff | ((iVar6 * 0x24) / 0x28 & 0xfU) << 0xc;
  *(uint *)(iVar1 + 0xc4) =
       *(uint *)(iVar1 + 0xc4) & 0xfff0ffff | ((iVar6 * 0x25) / 0x28 & 0xfU) << 0x10;
  *(uint *)(iVar1 + 0xc4) =
       *(uint *)(iVar1 + 0xc4) & 0xff0fffff | ((iVar6 * 0x26) / 0x28 & 0xfU) << 0x14;
  *(uint *)(iVar1 + 0xc4) =
       ((iVar6 * 0x27) / 0x28 & 0xfU) << 0x18 | *(uint *)(iVar1 + 0xc4) & 0xf0ffffff;
  *(uint *)(iVar1 + 0xc4) = *(uint *)(iVar1 + 0xc4) & 0xfffffff | iVar6 * 0x10000000;
  *(uint *)(iVar1 + 200) = (iVar6 * 0x29) / 0x28 & 0xfU | *(uint *)(iVar1 + 200) & 0xfffffff0;
  *(uint *)(iVar1 + 200) = ((iVar6 * 0x2a) / 0x28 & 0xfU) << 4 | *(uint *)(iVar1 + 200) & 0xffffff0f
  ;
  uVar3 = (uint)DAT_ram_20001ef0;
  iVar4 = uVar3 - DAT_ram_20001ef8;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 10) / iVar6;
  }
  *(uint *)(iVar1 + 200) = *(uint *)(iVar1 + 200) & 0xfffff0ff | (uVar2 & 0xf | 8) << 8;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 9) / iVar6;
  }
  *(uint *)(iVar1 + 200) = *(uint *)(iVar1 + 200) & 0xffff0fff | (uVar2 & 0xf | 8) << 0xc;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 8) / iVar6;
  }
  *(uint *)(iVar1 + 200) = *(uint *)(iVar1 + 200) & 0xfff0ffff | (uVar2 & 0xf | 8) << 0x10;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 7) / iVar6;
  }
  *(uint *)(iVar1 + 200) = *(uint *)(iVar1 + 200) & 0xff0fffff | (uVar2 & 0xf | 8) << 0x14;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 6) / iVar6;
  }
  *(uint *)(iVar1 + 200) = *(uint *)(iVar1 + 200) & 0xf0ffffff | (uVar2 & 0xf | 8) << 0x18;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 5) / iVar6;
  }
  *(uint *)(iVar1 + 200) = *(uint *)(iVar1 + 200) & 0xfffffff | (uVar2 | 8) << 0x1c;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 4) / iVar6;
  }
  *(uint *)(iVar1 + 0xcc) = *(uint *)(iVar1 + 0xcc) & 0xfffffff0 | uVar2 & 0xf | 8;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 3) / iVar6;
  }
  *(uint *)(iVar1 + 0xcc) = *(uint *)(iVar1 + 0xcc) & 0xffffff0f | (uVar2 & 0xf | 8) << 4;
  if (iVar6 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 2) / iVar6;
  }
  if (iVar6 == 0) {
    uVar7 = 0xffffffff;
  }
  else {
    uVar7 = iVar4 / iVar6;
  }
  *(uint *)(iVar1 + 0xcc) = *(uint *)(iVar1 + 0xcc) & 0xfffff0ff | (uVar2 & 0xf | 8) << 8;
  *(uint *)(iVar1 + 0xcc) = (uVar7 & 0xf | 8) << 0xc | *(uint *)(iVar1 + 0xcc) & 0xffff0fff;
  *(uint *)(iVar1 + 0xcc) = *(uint *)(iVar1 + 0xcc) & 0xfff0ffff;
  iVar4 = DAT_ram_20001a76 - uVar3;
  if (uVar5 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = iVar4 / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xcc) = *(uint *)(iVar1 + 0xcc) & 0xff0fffff | (uVar2 & 0xf) << 0x14;
  if (uVar5 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 2) / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xcc) = (uVar2 & 0xf) << 0x18 | *(uint *)(iVar1 + 0xcc) & 0xf0ffffff;
  if (uVar5 == 0) {
    iVar6 = -1;
  }
  else {
    iVar6 = (iVar4 * 3) / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xcc) = *(uint *)(iVar1 + 0xcc) & 0xfffffff | iVar6 << 0x1c;
  if (uVar5 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 4) / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xd0) = *(uint *)(iVar1 + 0xd0) & 0xfffffff0 | uVar2 & 0xf;
  if (uVar5 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 5) / (int)uVar5;
  }
  if (uVar5 == 0) {
    uVar7 = 0xffffffff;
  }
  else {
    uVar7 = (iVar4 * 6) / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xd0) = *(uint *)(iVar1 + 0xd0) & 0xffffff0f | (uVar2 & 0xf) << 4;
  *(uint *)(iVar1 + 0xd0) = *(uint *)(iVar1 + 0xd0) & 0xfffff0ff | (uVar7 & 0xf) << 8;
  if (uVar5 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 7) / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xd0) = *(uint *)(iVar1 + 0xd0) & 0xffff0fff | (uVar2 & 0xf) << 0xc;
  if (uVar5 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 8) / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xd0) = *(uint *)(iVar1 + 0xd0) & 0xfff0ffff | (uVar2 & 0xf) << 0x10;
  if (uVar5 == 0) {
    uVar2 = 0xffffffff;
    uVar5 = 0xffffffff;
  }
  else {
    uVar2 = (iVar4 * 9) / (int)uVar5;
    uVar5 = (iVar4 * 10) / (int)uVar5;
  }
  *(uint *)(iVar1 + 0xd0) = *(uint *)(iVar1 + 0xd0) & 0xff0fffff | (uVar2 & 0xf) << 0x14;
  *(uint *)(iVar1 + 0xd0) = (uVar5 & 0xf) << 0x18 | *(uint *)(iVar1 + 0xd0) & 0xf0ffffff;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xffffffef;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffffffe;
  *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) | 0x1000;
  *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) | 0x10;
  *(uint *)(iVar1 + 0x38) = *(uint *)(iVar1 + 0x38) & 0xffffffc0 | uVar8 & 0x3f;
  *(uint *)(iVar1 + 0x38) = (uVar3 & 0x7f) << 0x18 | *(uint *)(iVar1 + 0x38) & 0x80ffffff;
  return;
}

